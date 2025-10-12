# micro‑ROS ↔ ROS 2 Foxy: Wired vs Wireless 

> Target setup: **wireless scouts** publishing from microcontrollers (ESP32 or Pico 2 W) to a **ROS 2 Foxy agent** on Raspberry Pi 4 (Ubuntu MATE 20.04). Includes wired serial/USB fallback and LD19 notes.

---

## 1) How micro‑ROS fits into ROS 2

* **Client (on MCU):** your micro‑ROS app built on FreeRTOS/ESP‑IDF or Pico SDK. It talks XRCE‑DDS to an Agent.
* **Agent (on Pi 4):** `micro-ros-agent` bridges XRCE‑DDS <→> DDS so the rest of ROS 2 sees standard topics/services.
* **Transports:**
	  * **Wired:** Serial (UART) or USB CDC to the Agent.
	  * **Wireless:** UDP over Wi‑Fi/Ethernet to the Agent (recommended for ESP32; Pico 2 W typically uses USB/serial today).

```
[MCU: micro‑ROS client] --(Serial/USB or UDP/Wi‑Fi)--> [micro‑ROS Agent] --DDS--> [ROS 2 graph]
```

---

## 2) Topologies

### A. Wired (robust & simple)

* **Link:** USB CDC (appears as `/dev/ttyACM*`/`ttyUSB*`) or direct UART via USB‑serial dongle.
* **When to use:** bench bring‑up, deterministic links, or where Wi‑Fi is unreliable.
* **Agent command (examples):**

```bash
# USB/serial
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyUSB0 -v6
# or, via Docker
docker run --rm -it --net=host microros/micro-ros-agent:foxy serial --dev /dev/ttyUSB0 -v6
```

### B. Wireless (UDP over Wi‑Fi)

* **Link:** MCU connects to AP; sends XRCE‑DDS over UDP to the Agent’s IP\:PORT (default 8888).
* **When to use:** mobile scouts streaming sensor data to a coordinator.
* **Agent command (examples):**

```bash
# Native
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 -v6
# or Docker
docker run --rm -it --net=host microros/micro-ros-agent:foxy udp4 --port 8888 -v6
```

> Tip: If `--net=host` is not suitable in Docker, map the UDP port: `-p 8888:8888/udp`.

---

## 3) Minimal examples

Below are bare‑bones publishers you can drop in to verify transport and agent connectivity before integrating LD19.

### A) ESP32 (Arduino core) — **Wi‑Fi/UDP** heartbeat publisher

* **Why:** Fastest way to validate wireless transport with your Pi agent.
* **Requires:** `micro_ros_arduino` library, ESP32 Arduino core.

```cpp
#include <WiFi.h>
#include <micro_ros_arduino.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <std_msgs/msg/u_int32.h>

// ==== CONFIGURE ME ====
const char* WIFI_SSID = "YOUR_AP";
const char* WIFI_PASS = "YOUR_PASS";
const char* AGENT_IP  = "192.168.1.10"; // Pi 4 address
const uint16_t AGENT_PORT = 8888;        // Agent UDP port
// =======================

rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
rcl_publisher_t pub;
std_msgs__msg__UInt32 msg;

void setup() {
  Serial.begin(115200);
  // Bring up Wi‑Fi and set micro‑ROS transport to Wi‑Fi UDP
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(200);
  set_microros_wifi_transports(WIFI_SSID, WIFI_PASS, AGENT_IP, AGENT_PORT);

  allocator = rcl_get_default_allocator();
  rclc_support_init(&support, 0, NULL, &allocator);
  rclc_node_init_default(&node, "esp32_node", "", &support);
  rclc_publisher_init_default(
    &pub, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt32),
    "/scout/heartbeat");
}

void loop() {
  static uint32_t count = 0;
  msg.data = count++;
  rcl_publish(&pub, &msg, NULL);
  delay(500);
}
```

**Agent side check:**

```bash
ros2 topic echo /scout/heartbeat
```

### B) Raspberry Pi Pico 2 W — **USB/Serial** heartbeat publisher

* **Why:** Pico 2 W Wi‑Fi + micro‑ROS is still more DIY; USB/serial is the quick path.
* **Requires:** Pico SDK + `micro_ros_raspberrypi_pico_sdk`, USB CDC.

**CMake snippet** (top‑level project):

```cmake
cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(pico_heartbeat)
pico_sdk_init()
add_subdirectory(micro_ros_raspberrypi_pico_sdk)
add_executable(pico_heartbeat main.c)
target_link_libraries(pico_heartbeat pico_stdlib micro_ros_raspberrypi_pico_sdk)
pico_add_extra_outputs(pico_heartbeat)
```

**`main.c`** (minimal):

```c
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <std_msgs/msg/u_int32.h>
#include <uxr/client/profile/transport/serial/serial_transport.h>

rcl_publisher_t pub; std_msgs__msg__UInt32 msg;

int main() {
  rcl_allocator_t allocator = rcl_get_default_allocator();
  rclc_support_t support; rcl_node_t node;
  rclc_support_init(&support, 0, NULL, &allocator);
  rclc_node_init_default(&node, "pico_node", "", &support);
  rclc_publisher_init_default(&pub, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt32),
    "/scout/heartbeat");
  uint32_t c = 0;
  while (true) {
    msg.data = c++;
    rcl_publish(&pub, &msg, NULL);
    sleep_ms(500);
  }
}
```

**Flash & run:** build a UF2, press **BOOTSEL** on Pico, mount as storage, copy UF2. Then start Agent in serial mode, e.g. `--dev /dev/ttyACM0` and `ros2 topic echo /scout/heartbeat`.

---

## 4) Integrating LD19 later (notes)

* **Wiring:** `P5V`→5 V, `GND`→GND (shared), `TX`→ MCU RX (3.3 V), `PWM` grounded for internal 10 Hz speed.
* **UART:** 230400‑8‑N‑1, one‑way TX from LD19.
* **Frame:** 0x54 header, 12 points per packet, start/end angles, CRC‑8 table.

**Sketch of the bridge (ESP32):**

1. Read LD19 UART at 230400 bps into a ring buffer.
2. Reassemble packets on 0x54 + length, verify CRC‑8.
3. Convert to `sensor_msgs/msg/LaserScan` (
   compute angle step by linear interpolation, distances in meters, intensities optional).
4. Publish `/scan` with QoS **Sensor Data**.

---

## 5) Agent install options on Raspberry Pi 4

* **Native from source/apt (Foxy):** install ROS 2 Foxy, then `micro-ros-agent` from source, or use Docker (above).
* **Snap (quick):** `sudo snap install micro-ros-agent` → service runs on UDP port 8888 by default. Adjust as needed.

---

## 6) QoS & reliability tips

* Use `rclc_publisher_init_default` for simple topics; switch to best‑effort sensor QoS for LiDAR.
* On Wi‑Fi: dedicate a 5 GHz SSID; fix Agent IP; keep UDP port 8888 open.
* If multiple scouts: use **one Agent** and one UDP port (XRCE‑DDS is multiplexed) or separate ports per scout when debugging.

---

## 7) Troubleshooting checklist

* **No data on ROS 2:** confirm Agent logs (e.g., `-v6`), check transport (serial vs udp), firewall, and that the MCU is using the same IP/port.
* **ESP32 drops under load:** verify Wi‑Fi RSSI, reduce publish rate, or move to wired serial for bring‑up.
* **Packet/scan issues:** dump a few raw LD19 frames and validate CRC‑8 before parsing.

---

## 8) Quick reference

* **Agent:** `ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 -v6`
* **Serial Agent:** `ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyUSB0 -v6`
* **Check:** `ros2 topic list`, `ros2 topic echo /scout/heartbeat`

---
