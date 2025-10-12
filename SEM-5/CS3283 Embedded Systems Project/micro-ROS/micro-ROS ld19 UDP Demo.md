### LD19 → ESP32 (micro‑ROS) → Raspberry Pi (ROS 2 Foxy)** path.

> [!info] Minimal, working setup:
> 
> * ESP32 (Arduino framework) runs a **micro‑ROS client**.
> * It reads LD19 frames on UART at **230400 8N1**, validates **CRC‑8**, converts the LD19’s **clockwise/left‑handed** angles to ROS’s **CCW/right‑handed**, and publishes `sensor_msgs/msg/LaserScan` over **micro‑ROS UDP**.
> * On the Pi, you run the **micro‑ROS Agent** (UDP) which exposes the `/scan` topic to ROS 2 Foxy so you can visualize in RViz2.


---

# 1) Wire & serial parameters (LD19 ↔ ESP32)

* LD19 **TX → ESP32 RX** (use `UART2` RX pin like GPIO16 or your choice)
* LD19 **PWM → GND** (internal 10 Hz speed)
* **5 V** to LD19 (separate 5 V rail; common **GND** with ESP32)
* Serial: **230400 baud, 8N1** (one‑way from LD19)

LD19 sends 47‑byte packets: `0x54, 0x2C, [speed], [start_angle], 12×(distance_mm,intensity), [end_angle], [timestamp], [crc8]` with CRC‑8 table provided by the vendor. Angles are in **0.01°**; rotation increases **clockwise** in a **left‑handed** frame, so we’ll flip for ROS.

---

# 2) ESP32 (Arduino) — micro‑ROS LaserScan publisher

> Requirements on your Arduino IDE / PlatformIO:
>
> * `micro_ros_arduino` library
> * `WiFi.h` (ESP32)
> * `rclc`, `sensor_msgs` come with micro‑ROS library bundle

**`esp32_ld19_microros.ino`**

```cpp
// ===== micro-ROS LD19 publisher (ESP32 + WiFi/UDP) =====
// - Foxy-style structure with RCCHECK/RCSOFTCHECK, executor, timer
// - Publishes sensor_msgs/LaserScan "scan"
// - Parses LD19 frames @ 230400 8N1 on Serial2 RX pin
// ========================================================

#include <Arduino.h>
#include <WiFi.h>
#include <micro_ros_arduino.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <sensor_msgs/msg/laser_scan.h>

// Foxy helpers for strings & sequences
#include <rosidl_runtime_c/string_functions.h>
#include <rosidl_runtime_c/primitives_sequence_functions.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ---------------- USER CONFIG ----------------
#define LED_PIN        13             // Status LED (blinks on error)
#define LIDAR_UART     Serial2
#define LIDAR_BAUD     230400
#define LIDAR_RX_PIN   16             // Pick an appropriate RX pin for your ESP32 board
#define WIFI_SSID      "Demon_net"
#define WIFI_PASS      "nopassword123"
#define AGENT_IP_STR   "192.168.1.50" // micro-ROS Agent IP (Raspberry Pi)
#define AGENT_PORT     8888           // micro-ROS Agent UDP port
#define FRAME_ID       "ld19"
// ---------------------------------------------

// ===== LD19 protocol constants =====
static const uint8_t  HEADER    = 0x54;
static const uint8_t  VERLEN    = 0x2C;     // upper 3 bits=1 (type), lower 5 bits=12 points
static const int      POINTS    = 12;
static const int      FRAME_LEN = 47;       // 1+1+2+2+36+2+2+1
static const uint16_t TS_MAX    = 30000;    // ms (wraps)

// CRC-8 table (LD19 manual)
static const uint8_t CrcTable[256] = {
  0x00,0x4D,0x9A,0xD7,0x79,0x34,0xE3,0xAE,0xF2,0xBF,0x68,0x25,0x8B,0xC6,0x11,0x5C,
  0xA9,0xE4,0x33,0x7E,0xD0,0x9D,0x4A,0x07,0x5B,0x16,0xC1,0x8C,0x22,0x6F,0xB8,0xF5,
  0x1F,0x52,0x85,0xC8,0x66,0x2B,0xFC,0xB1,0xED,0xA0,0x77,0x3A,0x94,0xD9,0x0E,0x43,
  0xB6,0xFB,0x2C,0x61,0xCF,0x82,0x55,0x18,0x44,0x09,0xDE,0x93,0x3D,0x70,0xA7,0xEA,
  0x3E,0x73,0xA4,0xE9,0x47,0x0A,0xDD,0x90,0xCC,0x81,0x56,0x1B,0xB5,0xF8,0x2F,0x62,
  0x97,0xDA,0x0D,0x40,0xEE,0xA3,0x74,0x39,0x65,0x28,0xFF,0xB2,0x1C,0x51,0x86,0xCB,
  0x21,0x6C,0xBB,0xF6,0x58,0x15,0xC2,0x8F,0xD3,0x9E,0x49,0x04,0xAA,0xE7,0x30,0x7D,
  0x88,0xC5,0x12,0x5F,0xF1,0xBC,0x6B,0x26,0x7A,0x37,0xE0,0xAD,0x03,0x4E,0x99,0xD4,
  0x7C,0x31,0xE6,0xAB,0x05,0x48,0x9F,0xD2,0x8E,0xC3,0x14,0x59,0xF7,0xBA,0x6D,0x20,
  0xD5,0x98,0x4F,0x02,0xAC,0xE1,0x36,0x7B,0x27,0x6A,0xBD,0xF0,0x5E,0x13,0xC4,0x89,
  0x63,0x2E,0xF9,0xB4,0x1A,0x57,0x80,0xCD,0x91,0xDC,0x0B,0x46,0xE8,0xA5,0x72,0x3F,
  0xCA,0x87,0x50,0x1D,0xB3,0xFE,0x29,0x64,0x38,0x75,0xA2,0xEF,0x41,0x0C,0xDB,0x96,
  0x42,0x0F,0xD8,0x95,0x3B,0x76,0xA1,0xEC,0xB0,0xFD,0x2A,0x67,0xC9,0x84,0x53,0x1E,
  0xEB,0xA6,0x71,0x3C,0x92,0xDF,0x08,0x45,0x19,0x54,0x83,0xCE,0x60,0x2D,0xFA,0xB7,
  0x5D,0x10,0xC7,0x8A,0x24,0x69,0xBE,0xF3,0xAF,0xE2,0x35,0x78,0xD6,0x9B,0x4C,0x01,
  0xF4,0xB9,0x6E,0x23,0x8D,0xC0,0x17,0x5A,0x06,0x4B,0x9C,0xD1,0x7F,0x32,0xE5,0xA8
};

static inline uint8_t crc8(const uint8_t* p, uint8_t len) {
  uint8_t crc = 0;
  while (len--) crc = CrcTable[(crc ^ *p++) & 0xFF];
  return crc;
}

// ===== RCCHECK helpers (from micro-ROS examples) =====
#define RCCHECK(fn) { rcl_ret_t rc = fn; if (rc != RCL_RET_OK) { error_loop(); } }
#define RCSOFTCHECK(fn) { rcl_ret_t rc = fn; (void)rc; }

// ===== micro-ROS globals =====
rcl_node_t node;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_timer_t timer;
rcl_publisher_t pub;
rclc_executor_t executor;
sensor_msgs__msg__LaserScan scan_msg;

// ===== WiFi connect =====
static void wifi_connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected: ");
  Serial.println(WiFi.localIP());
}

// ===== Error LED blink loop =====
void error_loop() {
  pinMode(LED_PIN, OUTPUT);
  while (true) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
}

// ====== LD19 → LaserScan (one 12-point sector) ======
static void publish_packet_as_scan(const uint8_t* frame, size_t n) {
  if (n != FRAME_LEN) return;
  if (frame[0] != HEADER || frame[1] != VERLEN) return;

  // CRC
  uint8_t calc = crc8(frame, FRAME_LEN - 1);
  if (calc != frame[FRAME_LEN - 1]) return;

  auto le16 = [](const uint8_t* p) -> uint16_t { return (uint16_t)(p[0] | (p[1] << 8)); };

  const uint16_t speed_dps = le16(&frame[2]);  // degrees/sec
  const uint16_t start_cd  = le16(&frame[4]);  // centi-deg
  const uint8_t*  points   = &frame[6];        // 12 * (2+1)
  const uint16_t end_cd    = le16(&frame[42]); // centi-deg
  // const uint16_t ts     = le16(&frame[44]); // timestamp (optional)

  const float start_deg = (start_cd % 36000) * 0.01f;
  const float end_deg   = (end_cd   % 36000) * 0.01f;

  // LD19 publishes clockwise angles; ROS uses CCW.
  // Interpolate angles across the sector and flip CW→CCW.
  const int N = POINTS;
  float angles_ccw[N];
  float ranges[N];
  float intensities[N];

  // Compute CW span with wrap handling, then per-point
  float cw_span = end_deg - start_deg;
  if (cw_span > 180.0f)  cw_span -= 360.0f;
  if (cw_span < -180.0f) cw_span += 360.0f;
  float step_deg = (N > 1) ? (cw_span / (N - 1)) : 0.0f;

  for (int i = 0; i < N; ++i) {
    float a_ld = start_deg + step_deg * i;
    if (a_ld < 0)      a_ld += 360.0f;
    if (a_ld >= 360.0f) a_ld -= 360.0f;

    float a_ccw_deg = 360.0f - a_ld;  // flip
    if (a_ccw_deg >= 360.0f) a_ccw_deg -= 360.0f;
    angles_ccw[i] = a_ccw_deg * (float)M_PI / 180.0f;

    uint16_t dist_mm = (uint16_t)(points[i*3] | (points[i*3+1] << 8));
    uint8_t  inten   = points[i*3+2];

    ranges[i] = dist_mm ? (dist_mm * 0.001f) : NAN; // meters
    intensities[i] = (float)inten;
  }

  // angle_min/max and average angle_increment (normalized)
  float amin = angles_ccw[0], amax = angles_ccw[0];
  float acc_inc = 0.0f; int inc_count = 0;
  for (int i = 0; i < N; ++i) {
    if (angles_ccw[i] < amin) amin = angles_ccw[i];
    if (angles_ccw[i] > amax) amax = angles_ccw[i];
    if (i > 0) {
      float d = angles_ccw[i] - angles_ccw[i-1];
      while (d >  M_PI) d -= 2.0f * (float)M_PI;
      while (d < -M_PI) d += 2.0f * (float)M_PI;
      acc_inc += fabsf(d);
      inc_count++;
    }
  }
  float angle_increment = (inc_count > 0) ? (acc_inc / inc_count) : 0.0f;

  // timing from reported speed
  const float spin_hz = (speed_dps > 0) ? (speed_dps / 360.0f) : 10.0f;
  const float scan_time = 1.0f / (spin_hz > 0 ? spin_hz : 10.0f);
  const float time_increment = (angle_increment > 1e-6f && spin_hz > 0)
                               ? (angle_increment / (2.0f * (float)M_PI * spin_hz))
                               : 0.0f;

  // Header time (rmw_uros_* is provided by micro-ROS)
  uint64_t now_ns = rmw_uros_epoch_nanos();
  scan_msg.header.stamp.sec = (int32_t)(now_ns / 1000000000ULL);
  scan_msg.header.stamp.nanosec = (uint32_t)(now_ns % 1000000000ULL);
  rosidl_runtime_c__String__assign(&scan_msg.header.frame_id, FRAME_ID);

  // LaserScan metadata
  scan_msg.angle_min = amin;
  scan_msg.angle_max = amax;
  scan_msg.angle_increment = angle_increment;
  scan_msg.time_increment = time_increment;
  scan_msg.scan_time = scan_time;
  scan_msg.range_min = 0.05f;
  scan_msg.range_max = 12.0f;

  // Ensure sequences are ready (one-time init to capacity N)
  static bool seq_inited = false;
  if (!seq_inited) {
    rosidl_runtime_c__float__Sequence__init(&scan_msg.ranges, N);
    rosidl_runtime_c__float__Sequence__init(&scan_msg.intensities, N);
    seq_inited = true;
  }

  // Copy data (exactly N)
  for (int i = 0; i < N; ++i) {
    scan_msg.ranges.data[i] = ranges[i];
    scan_msg.intensities.data[i] = intensities[i];
  }
  scan_msg.ranges.size = N;
  scan_msg.intensities.size = N;

  RCSOFTCHECK(rcl_publish(&pub, &scan_msg, NULL));
}

// ===== UART drain + publish =====
static void read_ld19_and_publish() {
  static uint8_t buf[FRAME_LEN];
  static int idx = 0;

  while (LIDAR_UART.available()) {
    uint8_t b = (uint8_t)LIDAR_UART.read();

    if (idx == 0 && b != HEADER) {
      continue; // resync on header
    }
    buf[idx++] = b;

    if (idx == 2 && buf[1] != VERLEN) {
      idx = 0; // wrong type/count; resync
      continue;
    }
    if (idx == FRAME_LEN) {
      publish_packet_as_scan(buf, FRAME_LEN);
      idx = 0;
    }
  }
}

// ===== Timer callback (executor-driven) =====
void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
  (void)timer; (void)last_call_time;
  read_ld19_and_publish(); // fast polling of UART
}

// ============ setup / loop ============
void setup() {
  // Status LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  Serial.begin(115200);
  LIDAR_UART.begin(LIDAR_BAUD, SERIAL_8N1, LIDAR_RX_PIN, -1); // RX only is fine

  // WiFi + micro-ROS UDP transport
  wifi_connect();
  set_microros_wifi_transports(WIFI_SSID, WIFI_PASS, AGENT_IP_STR, AGENT_PORT);

  // micro-ROS init (Foxy style)
  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "ld19_esp32_node", "", &support));

  // Publisher (sensor data: best effort)
  RCCHECK(rclc_publisher_init_best_effort(
    &pub, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
    "scan"
  ));

  // Initialize LaserScan message once
  sensor_msgs__msg__LaserScan__init(&scan_msg);

  // Timer: poll UART very frequently (1 ms)
  RCCHECK(rclc_timer_init_default(
    &timer, &support, RCL_MS_TO_NS(1), timer_callback
  ));

  // Executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  Serial.println("micro-ROS LD19 publisher started.");
}

void loop() {
  // Drive executor; keep loop lean
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(5)));
  delay(1);
}

```

**Notes**

* We publish one `LaserScan` **per LD19 packet (12 points)**. That’s perfectly fine for RViz and fast mapping tests. If you later want a full 360° scan per message, we can buffer packets for one revolution and publish a complete ring.
* The angle conversion is based on the vendor’s definition: **LD19 increases angle clockwise (left‑handed)**; ROS expects **counter‑clockwise**. We flip using `θ_ros = 360° − θ_ld19` (then convert to radians).
* CRC‑8 and field layout exactly match the manual.

---

# 3) Raspberry Pi (ROS 2 Foxy) — micro‑ROS Agent + RViz

**Install Agent (if not already):**

```bash
sudo apt update
sudo apt install ros-foxy-micro-ros-agent
```

**Run Agent (UDP, default 8888):**

```bash
source /opt/ros/foxy/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 -v6
```

If you used a different port/IP in the sketch, match them here.

**See the topic:**

```bash
ros2 topic list | grep scan
ros2 topic echo /scan --once
```

**Visualize:**

```bash
sudo apt install ros-foxy-rviz2
rviz2
```

* Fixed Frame: `ld19` (or whatever you set in `FRAME_ID`)
* Add → LaserScan → Topic `/scan`

---

# 4) Quick troubleshooting

* **No `/scan`?** Check Agent logs; confirm ESP32 can reach the Pi IP/port (same Wi‑Fi, no firewall).
* **Packets but no points in RViz?** Make sure `Fixed Frame` equals the `frame_id` you publish; and that `range_max` (\~12 m) isn’t too small.
* **Choppy view?** Increase `--port` QoS depth or lower the UART polling timer period slightly.

---

If you want, I can provide a **“full‑revolution LaserScan”** version that aggregates packets into a 360° array (e.g., 720 bins at 0.5°) before publishing—that’s nicer for some mapping stacks.
