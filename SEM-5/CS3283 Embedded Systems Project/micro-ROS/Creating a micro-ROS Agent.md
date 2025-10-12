#works
### For ROS 2 Foxy on Ubuntu 20.04 :

---

## Option A (recommended): build the Agent with `micro_ros_setup`

This is the most “official” Foxy path and works well.

```bash
sudo apt update
sudo apt install -y git python3-pip build-essential cmake

# Create a workspace and grab the Foxy branch of micro_ros_setup
mkdir -p ~/microros_ws/src && cd ~/microros_ws
git clone -b foxy https://github.com/micro-ROS/micro_ros_setup.git src/micro_ros_setup

# deps + build the tools (init rosdep if needed)
sudo apt update && rosdep update
rosdep install --from-paths src --ignore-src -y
colcon build
source install/local_setup.bash

# create & build the Agent workspace
ros2 run micro_ros_setup create_agent_ws.sh
ros2 run micro_ros_setup build_agent.sh
source install/local_setup.bash
```

Run the Agent (UDP on port 8888):

```bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 -v6
```


> [!image] Expected Output
> ![[Pasted image 20250811111932.png]]
> ![[Pasted image 20250811111954.png]]




These steps (create/build/run) are straight from the micro‑ROS docs. ([micro-ROS](https://micro.ros.org/docs/tutorials/core/first_application_rtos/freertos/ "First micro-ROS Application on FreeRTOS | micro-ROS"))

---

## Option B: Snap package (quick)

```bash
sudo snap install micro-ros-agent
micro-ros-agent udp4 --port 8888 -v6
```

Note: snap is convenient; for **serial** transports it can be finicky (confinement), but for **UDP** it’s typically fine. ([Snapcraft](https://snapcraft.io/install/micro-ros-agent/ubuntu?utm_source=chatgpt.com "Install micro-ros-agent on Ubuntu using the Snap Store"), [GitHub](https://github.com/micro-ROS/micro-ROS-Agent "GitHub - micro-ROS/micro-ROS-Agent: ROS 2 package using Micro XRCE-DDS Agent."))

---

## Lidar Simulation Through micro-ROS/esp32

```cpp
// ===== micro-ROS LaserScan simulator (ESP32 + WiFi/UDP) =====
// Slim payload version: downsampled beams, no intensities.
// micro_ros_arduino v2.0.5-foxy compatible.
// =============================================================

#include <Arduino.h>
#include <WiFi.h>
#include <micro_ros_arduino.h>
#include <rmw_microros/rmw_microros.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <sensor_msgs/msg/laser_scan.h>
#include <rosidl_runtime_c/string_functions.h>
#include <rosidl_runtime_c/primitives_sequence_functions.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ---------------- USER CONFIG ----------------
// 1) Keep SIMULATE=1 to test without hardware
#define SIMULATE         1

// 2) Size & rate levers to shrink payload
#define OUT_BEAMS        120          // publish only 120 beams (e.g., 3° resolution)
#define WITH_INTENSITIES 0            // 0 = don't send intensities (saves ~1.4 KB)
#define PUB_HZ           5            // publish rate; 5 Hz reduces network load

#define LED_PIN          2
#define WIFI_SSID        "Demon_net"
#define WIFI_PASS        "nopassword123"
#define AGENT_IP_STR     "192.168.115.1"
#define AGENT_PORT       8888
#define FRAME_ID         "ld19"

// If SIMULATE=0 (real LD19), set UART pins:
#define LIDAR_UART       Serial2
#define LIDAR_BAUD       230400
#define LIDAR_RX_PIN     16
// ---------------------------------------------

#define RCCHECK(fn)  { rcl_ret_t rc = (fn); if (rc != RCL_RET_OK) { error_loop(); } }
#define RCSOFTCHECK(fn)  (void)(fn)

// ===== micro-ROS globals =====
rcl_node_t node;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_timer_t timer;
rcl_publisher_t pub;
rclc_executor_t executor;
sensor_msgs__msg__LaserScan scan_msg;

static void wifi_connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.println();
  Serial.print("WiFi connected: "); Serial.println(WiFi.localIP());
}

void error_loop() {
  pinMode(LED_PIN, OUTPUT);
  while (true) { digitalWrite(LED_PIN, !digitalRead(LED_PIN)); delay(100); }
}

// ====== SIMULATED SCAN GEN (compact) ======
#if SIMULATE
// Output scan is OUT_BEAMS across [-pi, +pi)
static const int   N_OUT   = OUT_BEAMS;
static const float ANG_MIN = -M_PI;
static const float ANG_MAX =  M_PI;
static const float ANG_INC = (ANG_MAX - ANG_MIN) / (float)N_OUT;
static float phase = 0.0f;

static inline float clampf(float x, float lo, float hi) {
  return x < lo ? lo : (x > hi ? hi : x);
}

static void fill_synthetic_scan() {
  // Timestamp (agent time sync recommended)
  uint64_t now_ns = rmw_uros_epoch_nanos();
  scan_msg.header.stamp.sec     = (int32_t)(now_ns / 1000000000ULL);
  scan_msg.header.stamp.nanosec = (uint32_t)(now_ns % 1000000000ULL);

  // Simple world: circular wall at 2 m with a gap; moving obstacle at 1.2 m
  const float wall_r    = 2.0f;
  const float gap_lo    = -15.0f * (float)M_PI / 180.0f;
  const float gap_hi    =  +15.0f * (float)M_PI / 180.0f;
  const float mover_r   = 1.2f;
  const float mover_ang = phase;
  const float mover_x   = mover_r * cosf(mover_ang);
  const float mover_y   = mover_r * sinf(mover_ang);

  for (int i = 0; i < N_OUT; ++i) {
    const float ang = ANG_MIN + i * ANG_INC;
    float range = wall_r;

    // Gap → NaN
    if (ang >= gap_lo && ang <= gap_hi) range = NAN;

    // Crude hit test against moving obstacle
    const float beam_dx = cosf(ang), beam_dy = sinf(ang);
    const float proj = mover_x * beam_dx + mover_y * beam_dy;
    if (proj > 0.1f && proj < wall_r) {
      const float perp = fabsf(mover_x * (-beam_dy) + mover_y * (beam_dx));
      if (perp < 0.10f) range = clampf(proj, scan_msg.range_min, scan_msg.range_max);
    }

    scan_msg.ranges.data[i] = range;
#if WITH_INTENSITIES
    scan_msg.intensities.data[i] = isnan(range) ? 0.0f : 120.0f;
#endif
  }

  phase += 0.05f;
  if (phase > 2.0f * (float)M_PI) phase -= 2.0f * (float)M_PI;
}
#endif

// ===== Timer callback =====
void timer_callback(rcl_timer_t * /*t*/, int64_t /*last*/) {
#if SIMULATE
  fill_synthetic_scan();
  RCSOFTCHECK(rcl_publish(&pub, &scan_msg, NULL));
#else
  // TODO: parse LD19 frames, downsample to OUT_BEAMS, fill scan_msg.ranges only
  // then: RCSOFTCHECK(rcl_publish(&pub, &scan_msg, NULL));
#endif
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Serial.begin(115200);

#if !SIMULATE
  LIDAR_UART.begin(LIDAR_BAUD, SERIAL_8N1, LIDAR_RX_PIN, -1);
#endif

  wifi_connect();
  set_microros_wifi_transports(WIFI_SSID, WIFI_PASS, AGENT_IP_STR, AGENT_PORT);

  Serial.print("Pinging micro-ROS agent");
  while (RMW_RET_OK != rmw_uros_ping_agent(100, 1)) { Serial.print("."); delay(200); }
  Serial.println(" OK");
  (void)rmw_uros_sync_session(1000); // best-effort time sync

  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "ld19_esp32_node", "", &support));

  // BEST_EFFORT is recommended for scan topics
  // RCCHECK(rclc_publisher_init_best_effort(
  //     &pub, &node,
  //     ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
  //     "/scan"
  // ));
  RCCHECK(rclc_publisher_init_default(
    &pub, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
    "/scan"));


  // Init message (once)
  sensor_msgs__msg__LaserScan__init(&scan_msg);
  rosidl_runtime_c__String__init(&scan_msg.header.frame_id);
  rosidl_runtime_c__String__assign(&scan_msg.header.frame_id, FRAME_ID);

  // Allocate ranges (OUT_BEAMS)
  if (!rosidl_runtime_c__float__Sequence__init(&scan_msg.ranges, N_OUT)) error_loop();

#if WITH_INTENSITIES
  if (!rosidl_runtime_c__float__Sequence__init(&scan_msg.intensities, N_OUT)) error_loop();
#else
  // ensure zero-length intensities (valid & smaller message)
  rosidl_runtime_c__float__Sequence__init(&scan_msg.intensities, 0);
#endif

  // Static LaserScan fields
  scan_msg.angle_min        = ANG_MIN;
  scan_msg.angle_max        = ANG_MAX - ANG_INC;
  scan_msg.angle_increment  = ANG_INC;
  scan_msg.scan_time        = 1.0f / (float)PUB_HZ;
  scan_msg.time_increment   = scan_msg.scan_time / (float)N_OUT;
  scan_msg.range_min        = 0.05f;
  scan_msg.range_max        = 12.0f;

  // Timer at PUB_HZ
  const uint32_t period_ms = (uint32_t)(1000.0f / (float)PUB_HZ + 0.5f);
  RCCHECK(rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(period_ms), timer_callback));

  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  Serial.println("micro-ROS LaserScan (compact) started → /scan");
}

void loop() {
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(5));
  delay(1);
}
```

> [!image] Expected Output
> ![[Pasted image 20250811111711.png]]



> [!info] Test /scan Topic
> -  `ros2 topic info -v /scan`
> 	- ![[Pasted image 20250811112155.png]]
> - `ros2 topic echo /scan`
> 	- ![[Pasted image 20250811112239.png]]


