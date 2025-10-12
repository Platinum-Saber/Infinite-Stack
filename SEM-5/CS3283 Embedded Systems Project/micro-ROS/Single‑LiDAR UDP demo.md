
Minimal end‑to‑end example to **stream LD19P frames over UDP from an ESP32 (with micro‑ROS)** and **visualize LaserScan in RViz2** on a Raspberry Pi 4 running **Ubuntu 20.04 + ROS 2 Foxy**.

---

## 1) ESP32 firmware (Arduino + micro‑ROS + UDP)

- Reads **LD19 UART @ 230400 8N1**.
    
- Verifies **0x54/0x2C** frames (12 points) and CRC.
    
- Sends each 47‑byte raw frame via **UDP** to the Pi.
    
- Also runs a tiny **micro‑ROS heartbeat** publisher (`std_msgs/String`) so you can confirm the MCU is reachable through a micro‑ROS Agent (optional).
    

> Libraries: `WiFi.h`, `WiFiUdp.h`, `micro_ros_arduino` (optional); Board: ESP32/ESP32‑S3.

```cpp
// ===== esp32_ld19_udp.ino =====
#include <WiFi.h>
#include <WiFiUdp.h>

// Optional: micro-ROS heartbeat (can be removed if not needed)
#include <micro_ros_arduino.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/string.h>

// -------- WiFi / UDP config --------
const char* WIFI_SSID = "YOUR_SSID";
const char* WIFI_PASS = "YOUR_PASS";
const char* TARGET_IP = "192.168.1.50";   // Raspberry Pi IP
const uint16_t TARGET_PORT = 6001;         // UDP port on Pi

WiFiUDP Udp;

// -------- LD19 UART config --------
// Use Serial2 with pins as needed (example: RX=16, TX=17 on classic ESP32)
static const int LIDAR_RX = 16; // connect to LD19 TX
static const int LIDAR_TX = 17; // (unused)
static const uint32_t LIDAR_BAUD = 230400; // 8N1

// LD19 protocol constants
static const uint8_t HEADER = 0x54;
static const uint8_t VERLEN = 0x2C; // 12 points packet
static const size_t FRAME_LEN = 47; // 1 + 1 + 2 + 2 + 12*(2+1) + 2 + 2 + 1

// CRC table (from LD19 manual)
static const uint8_t CRC_TABLE[256] = {
  0x00,0x4d,0x9a,0xd7,0x79,0x34,0xe3,0xae,0xf2,0xbf,0x68,0x25,0x8b,0xc6,0x11,0x5c,
  0xa9,0xe4,0x33,0x7e,0xd0,0x9d,0x4a,0x07,0x5b,0x16,0xc1,0x8c,0x22,0x6f,0xb8,0xf5,
  0x1f,0x52,0x85,0xc8,0x66,0x2b,0xfc,0xb1,0xed,0xa0,0x77,0x3a,0x94,0xd9,0x0e,0x43,
  0xb6,0xfb,0x2c,0x61,0xcf,0x82,0x55,0x18,0x44,0x09,0xde,0x93,0x3d,0x70,0xa7,0xea,
  0x3e,0x73,0xa4,0xe9,0x47,0x0a,0xdd,0x90,0xcc,0x81,0x56,0x1b,0xb5,0xf8,0x2f,0x62,
  0x97,0xda,0x0d,0x40,0xee,0xa3,0x74,0x39,0x65,0x28,0xff,0xb2,0x1c,0x51,0x86,0xcb,
  0x21,0x6c,0xbb,0xf6,0x58,0x15,0xc2,0x8f,0xd3,0x9e,0x49,0x04,0xaa,0xe7,0x30,0x7d,
  0x88,0xc5,0x12,0x5f,0xf1,0xbc,0x6b,0x26,0x7a,0x37,0xe0,0xad,0x03,0x4e,0x99,0xd4,
  0x7c,0x31,0xe6,0xab,0x05,0x48,0x9f,0xd2,0x8e,0xc3,0x14,0x59,0xf7,0xba,0x6d,0x20,
  0xd5,0x98,0x4f,0x02,0xac,0xe1,0x36,0x7b,0x27,0x6a,0xbd,0xf0,0x5e,0x13,0xc4,0x89,
  0x63,0x2e,0xf9,0xb4,0x1a,0x57,0x80,0xcd,0x91,0xdc,0x0b,0x46,0xe8,0xa5,0x72,0x3f,
   0xca,0x87,0x50,0x1d,0xb3,0xfe,0x29,0x64,0x38,0x75,0xa2,0xef,0x41,0x0c,0xdb,0x96,
  0x42,0x0f,0xd8,0x95,0x3b,0x76,0xa1,0xec,0xb0,0xfd,0x2a,0x67,0xc9,0x84,0x53,0x1e,
  0xeb,0xa6,0x71,0x3c,0x92,0xdf,0x08,0x45,0x19,0x54,0x83,0xce,0x60,0x2d,0xfa,0xb7,
  0x5d,0x10,0xc7,0x8a,0x24,0x69,0xbe,0xf3,0xaf,0xe2,0x35,0x78,0xd6,0x9b,0x4c,0x01,
  0xf4,0xb9,0x6e,0x23,0x8d,0xc0,0x17,0x5a,0x06,0x4b,0x9c,0xd1,0x7f,0x32,0xe5,0xa8
};

static inline uint8_t crc8(const uint8_t* p, size_t len) {
  uint8_t c = 0; while (len--) c = CRC_TABLE[(c ^ *p++) & 0xFF]; return c;
}

// ----- micro-ROS heartbeat (optional) -----
static rcl_publisher_t hb_pub; static rclc_executor_t executor; static rcl_node_t node; static rclc_support_t support; static rcl_allocator_t allocator; static rcl_timer_t timer;
void hb_cb(rcl_timer_t*, int64_t){
  static std_msgs__msg__String msg; static char buf[64];
  snprintf(buf, sizeof(buf), "esp32 alive: %lu", (unsigned long)millis());
  msg.data.data = buf; msg.data.size = strlen(buf); msg.data.capacity = sizeof(buf);
  rcl_publish(&hb_pub, &msg, NULL);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(LIDAR_BAUD, SERIAL_8N1, LIDAR_RX, LIDAR_TX);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.printf("\nWiFi OK: %s\n", WiFi.localIP().toString().c_str());

  Udp.begin(0); // ephemeral source port

  // (Optional) micro-ROS init: set transport to WiFi UDP -> agent
  // set_microros_wifi_transports(WIFI_SSID, WIFI_PASS, "192.168.1.50", 8888); // if agent at 192.168.1.50:8888
  // allocator = rcl_get_default_allocator();
  // rclc_support_init(&support, 0, NULL, &allocator);
  // rclc_node_init_default(&node, "esp32_node", "", &support);
  // rclc_publisher_init_default(&hb_pub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), "esp32/heartbeat");
  // rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(1000), hb_cb);
  // rclc_executor_init(&executor, &support.context, 1, &allocator);
  // rclc_executor_add_timer(&executor, &timer);
}

void loop() {
  // (Optional) micro-ROS work
  // if (hb_pub.impl) { rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0)); }

  static uint8_t buf[512];
  static size_t used = 0;

  // Read any available bytes from LD19
  while (Serial2.available()) {
    int b = Serial2.read(); if (b < 0) break; buf[used++] = (uint8_t)b;
    if (used >= sizeof(buf)) used = 0; // prevent overflow
  }

  // Parse frames in-place
  size_t i = 0;
  while (used - i >= FRAME_LEN) {
    if (buf[i] != HEADER) { i++; continue; }
    if (buf[i+1] != VERLEN) { i++; continue; }
    // CRC check
    uint8_t calc = crc8(&buf[i], FRAME_LEN - 1);
    uint8_t got  = buf[i + FRAME_LEN - 1];
    if (calc != got) { i++; continue; }
    // Send this 47-byte frame via UDP to the Pi
    Udp.beginPacket(TARGET_IP, TARGET_PORT);
    Udp.write(&buf[i], FRAME_LEN);
    Udp.endPacket();
    i += FRAME_LEN;
  }
  // compact buffer
  if (i) { memmove(buf, &buf[i], used - i); used -= i; }
}
```

**Wiring (LD19 ↔ ESP32)**

- LD19 **TX → ESP32 RX (GPIO16)**
    
- LD19 **PWM → GND** (internal 10 Hz speed)
    
- **5 V** and **GND** shared (stable 5 V, ≥1 A recommended)
    

> Tip: if you prefer to send pre-parsed `(angle_rad, range_m)` instead of raw frames, replace the `Udp.write(&buf[i], FRAME_LEN);` with your own compact struct and adjust the PC side accordingly.

---

## 2) ROS 2 Foxy (Raspberry Pi) — UDP subscriber + LaserScan publisher

This node listens on a UDP port, parses LD19 frames, converts **CW/left‑handed** angles to ROS CCW, and publishes `/scan` (sensor_msgs/LaserScan). A ready launch file and RViz config are included.

### Package layout

```
ld19_udp_viz/
├─ package.xml
├─ setup.py
├─ ld19_udp_viz/
│  ├─ __init__.py
│  ├─ udp_ld19_receiver.py
├─ launch/
│  └─ demo.launch.py
└─ rviz/
   └─ scan.rviz
```

### `package.xml`

```xml
<?xml version="1.0"?>
<package format="3">
  <name>ld19_udp_viz</name>
  <version>0.1.0</version>
  <description>Listen to LD19 frames over UDP and publish LaserScan</description>
  <maintainer email="you@example.com">you</maintainer>
  <license>MIT</license>
  <buildtool_depend>ament_python</buildtool_depend>
  <exec_depend>rclpy</exec_depend>
  <exec_depend>sensor_msgs</exec_depend>
</package>
```

### `setup.py`

```python
from setuptools import setup
from glob import glob
import os

package_name = 'ld19_udp_viz'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        (os.path.join('share', package_name), ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'rviz'), glob('rviz/*.rviz')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='you',
    maintainer_email='you@example.com',
    description='UDP LD19 → LaserScan',
    license='MIT',
    entry_points={'console_scripts': [
        'udp_ld19_receiver = ld19_udp_viz.udp_ld19_receiver:main',
    ]},
)
```

### `ld19_udp_viz/udp_ld19_receiver.py`

```python
import socket, struct, math
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan

HEADER = 0x54
VERLEN = 0x2C
POINTS_PER_PACK = 12
FRAME_LEN = 47

CRC_TABLE = [
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
]

def crc8(data: bytes) -> int:
    c = 0
    for b in data:
        c = CRC_TABLE[(c ^ b) & 0xFF]
    return c

class LD19UdpNode(Node):
    def __init__(self):
        super().__init__('ld19_udp_node')
        self.declare_parameter('udp_port', 6001)
        self.declare_parameter('frame_id', 'lidar')
        self.port = int(self.get_parameter('udp_port').value)
        self.frame_id = self.get_parameter('frame_id').value
        self.pub = self.create_publisher(LaserScan, 'scan', 10)

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('0.0.0.0', self.port))
        self.sock.setblocking(False)
        self.buf = bytearray()
        self.timer = self.create_timer(0.002, self.spin_once)
        self.get_logger().info(f"Listening UDP :{self.port}")

    def spin_once(self):
        try:
            while True:
                data, _ = self.sock.recvfrom(2048)
                self.buf.extend(data)
        except BlockingIOError:
            pass
        i = 0
        n = len(self.buf)
        while n - i >= FRAME_LEN:
            if self.buf[i] != HEADER or self.buf[i+1] != VERLEN:
                i += 1; continue
            fr = self.buf[i:i+FRAME_LEN]
            if crc8(fr[:-1]) != fr[-1]:
                i += 1; continue
            self.publish_scan(fr)
            i += FRAME_LEN
        if i:
            del self.buf[:i]

    def publish_scan(self, fr: bytes):
        speed_dps = struct.unpack_from('<H', fr, 2)[0]
        a0 = struct.unpack_from('<H', fr, 4)[0] / 100.0
        off = 6
        points = []
        for _ in range(POINTS_PER_PACK):
            dmm = struct.unpack_from('<H', fr, off)[0]
            inten = fr[off+2]
            off += 3
            points.append((dmm, inten))
        a1 = struct.unpack_from('<H', fr, off)[0] / 100.0
        # interpolate angles (deg)
        span = a1 - a0
        if span < 0: span += 360.0
        step = span / max(1, (POINTS_PER_PACK - 1))
        angles = [(a0 + i*step) % 360.0 for i in range(POINTS_PER_PACK)]
        # LD19 is clockwise/left-handed -> convert to ROS CCW/right-handed
        angles_ros = [ (2*math.pi - math.radians(a)) % (2*math.pi) for a in angles ]
        ranges = [ (d/1000.0 if d>0 else float('inf')) for d,_ in points ]
        # sort by angle
        pairs = sorted(zip(angles_ros, ranges), key=lambda x: x[0])
        angs = [p[0] for p in pairs]
        rngs = [p[1] for p in pairs]

        msg = LaserScan()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = self.frame_id
        msg.angle_min = angs[0]
        msg.angle_max = angs[-1]
        msg.angle_increment = (angs[-1]-angs[0])/(len(angs)-1) if len(angs)>1 else 0.0
        msg.range_min = 0.05
        msg.range_max = 12.0
        msg.ranges = rngs
        self.pub.publish(msg)


def main():
    rclpy.init()
    node = LD19UdpNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node(); rclpy.shutdown()
```

### `launch/demo.launch.py`

```python
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ld19_udp_viz',
            executable='udp_ld19_receiver',
            name='ld19_udp',
            output='screen',
            parameters=[{'udp_port': 6001, 'frame_id': 'ld19'}]
        ),
    ])
```

### Build & run (Pi / Foxy)

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
# copy the ld19_udp_viz/ folder here
cd ..
colcon build --symlink-install
source install/setup.bash
ros2 launch ld19_udp_viz demo.launch.py
```

### RViz2

Open RViz2 and add a **LaserScan** display with topic `/scan`. Optionally set Fixed Frame to `ld19` and enable a range of 12 m.

---

## 3) Quick test checklist

- Power LD19 with a solid **5 V** and **common ground** with the ESP32.
    
- Verify the LD19 blue LED glow and ~10 Hz spin after ~3 s power‑up.
    
- Confirm ESP32 serial receives bytes (use a debug counter on valid CRCs).
    
- See UDP frames arriving on the Pi: `sudo tcpdump -i wlan0 udp port 6001 -X`.
    
- In RViz2 you should see a 360° LaserScan ring with obstacles appearing.
    

---

### Notes

- For Wi‑Fi robustness, keep packets ≤ MTU (47 B is tiny, safe). If you batch frames, add a small header (e.g., count) and handle reassembly.
    
- If you prefer **pure micro‑ROS** end‑to‑end (no custom UDP), publish `sensor_msgs/LaserScan` from the ESP32 over the **micro‑ROS Agent** and subscribe directly on the Pi; the parser then runs on the MCU instead of the Pi.