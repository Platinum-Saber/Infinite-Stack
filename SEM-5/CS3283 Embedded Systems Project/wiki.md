Here are **3 structured GitHub Wiki pages** you can create for your ASCILAM project, Cryo. Each page is written in Markdown and follows a clean documentation style for easy copying into your GitHub Wiki.

---

## 📄 1. **Project Overview**

**Filename**: `Home.md`

```markdown
# ASCILAM  
## (Autonomous Simultaneous Collaborative Integrated Localization And Mapping)

### 🚀 Summary
ASCILAM is a multi-robot mapping system using modified M-Bots as scouts and a Raspberry Pi 4-powered robot as the coordinator. Scouts use LiDAR and odometry to create local maps, which are fused in real time via Wi-Fi UDP by the coordinator into a global occupancy map.

---

### 📐 Architecture Overview
![Design_Architecture](https://github.com/user-attachments/assets/ed278bd0-6e19-4823-8300-5aacd463bf56)

---

### 🔧 Hardware Components

| Component           | M-Bot Scouts (x2)                         | Coordinator Robot           |
|---------------------|-------------------------------------------|------------------------------|
| Base Platform       | Modified M-Bot                            | Custom Robot Chassis         |
| Controller          | M-Bot Controller + Wi-Fi Module (ESP32)   | Raspberry Pi 4               |
| Sensors             | LiDAR, Wheel Encoders, IMU               | None                         |
| Communication       | Wi-Fi + UDP                              | Wi-Fi + UDP                  |
| Power Supply        | Rechargeable Battery                      | Power Bank                   |

---

### 🧠 Software Stack

| Task                | Tool/Package                               |
|---------------------|---------------------------------------------|
| OS                  | Custom FW / Ubuntu 20.04                   |
| Framework           | ROS 2 Foxy (Coordinator)                  |
| SLAM                | GMapping / Cartographer                   |
| Localization        | `robot_localization` (EKF)                |
| Communication       | UDP (Wi-Fi)                               |
| Map Merging         | `multirobot_map_merge` / Custom Node      |
| Visualization       | RViz2                                     |

---

### 🧭 Future Scope
- Integrate autonomous navigation using global map.
- Add RGB-D camera for semantic mapping.
- Web dashboard for real-time map monitoring.
```

---

## 📄 2. **Timeline and Progress**

**Filename**: `Timeline.md`

```markdown
# 📅 ASCILAM Project Timeline

## 🟠 Phase 1: Setup & Communication (Week 1–2)
**Goal**: Establish UDP communication between M-Bots and Coordinator Pi.

- [x] Test LiDAR and ROS 2 integration in Docker containers.
- [ ] Install ROS 2 Foxy and Mosquitto on Raspberry Pi 4.
- [ ] Configure Wi-Fi and test UDP connections from M-Bots to Pi.
- [ ] Implement UDP streaming test (mock map and pose data).
- [ ] Coordinator logs incoming data via subscriber node.

---

## 🟡 Phase 2: M-Bot Mapping & Localization (Week 3–4)
**Goal**: Enable M-Bots to build maps and estimate positions.

- [ ] Mount and configure LiDAR (e.g., RPLiDAR) on M-Bots.
- [ ] Collect odometry using encoders; estimate orientation via IMU.
- [ ] Fuse odometry and IMU using an EKF.
- [ ] Use GMapping or Cartographer for 2D SLAM.
- [ ] Publish pose and occupancy grid.

---

## 🟢 Phase 3: UDP Map Transmission & Merging (Week 5–6)
**Goal**: Merge scout maps into a global map on the coordinator.

- [ ] Define `MapUpdate.msg` with grid + pose.
- [ ] Convert map + pose to UDP format.
- [ ] Merge maps into global map using custom node.
- [ ] Visualize merged map in RViz2.

---

## 🔵 Phase 4: Field Testing & Optimization (Week 7–8)
**Goal**: Evaluate map fusion and performance.

- [ ] Run indoor mapping tests.
- [ ] Tune UDP message rate and packet size.
- [ ] Adjust transform alignment for better merging.
```

---

## 📄 3. **Setup Instructions**

**Filename**: `Setup.md`

````markdown
# 🛠️ ASCILAM Setup Guide

## 🔌 Hardware Setup

### 🟤 M-Bot Scouts
1. Mount LiDAR (RPLiDAR A1 / STL-19P) securely.
2. Connect ESP32 (or equivalent) for Wi-Fi + UDP comm.
3. Add wheel encoders and IMU module.
4. Power via battery pack (5V / 7.4V depending on bot).

### 🔵 Coordinator Robot
- Use Raspberry Pi 4 with Ubuntu 20.04.
- Power via USB power bank.
- Optional: add screen or monitor for RViz debug.

---

## 💻 Software Setup

### Coordinator (Raspberry Pi 4)
```bash
# Update and install ROS 2 Foxy
sudo apt update && sudo apt install -y ros-foxy-desktop

# Source ROS
echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc

# Setup workspace
mkdir -p ~/ascilam_ws/src
cd ~/ascilam_ws && colcon build
````

### M-Bot UDP Client (ESP32)

- Use Arduino or PlatformIO to flash UDP client code.
    
- Mock/send pose and map fragments as JSON or custom binary packets.
    

---

## 📡 Communication Testing

### UDP Test Script (Python, Coordinator)

```python
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 8000))

while True:
    data, addr = sock.recvfrom(1024)
    print(f"From {addr}: {data}")
```

---

## 🧪 Docker Test Environment

> For development before full deployment

```bash
# Run ROS 2 Docker image with volume for code
docker run -it --rm \
  --network host \
  -v ~/ascilam_ws:/ros2_ws \
  osrf/ros:foxy-desktop
```

Use this to simulate LiDAR drivers, SLAM nodes, and map merging logic.

```

---

Would you like me to create a ZIP or script to auto-generate and push these `.md` files to your GitHub repo’s wiki folder?
```