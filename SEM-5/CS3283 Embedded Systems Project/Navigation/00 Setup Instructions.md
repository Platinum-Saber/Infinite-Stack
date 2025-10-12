# Multi-Robot Navigation System Setup Instructions

## Hardware Requirements

### Per Robot System:
- 1x ESP32 Development Board
- 1x LD19 LiDAR Sensor  
- 1x M-Bot (with Bluetooth module removed)
- 1x 5V Power Supply (for LiDAR)
- Connecting wires

### Central Control:
- 1x Raspberry Pi 4 (4GB+ recommended)
- 1x MicroSD Card (32GB+)
- WiFi capability (built-in on RPi4)

## Part 1: Hardware Setup

### 1.1 LD19 LiDAR to ESP32 Connections

For both Robot 1 and Robot 2:
```
LD19 Pin 1 (TX)  → ESP32 GPIO 16 (RX)
LD19 Pin 2 (PWM) → GND (for internal speed control)
LD19 Pin 3 (GND) → ESP32 GND
LD19 Pin 4 (5V)  → 5V Power Supply
```

### 1.2 ESP32 to M-Bot Connections

**Important**: Remove the Bluetooth module from M-Bot to expose UART pins.

```
ESP32 GPIO 4 → M-Bot RX (exposed after Bluetooth removal)
ESP32 GPIO 2 → M-Bot TX (exposed after Bluetooth removal)  
ESP32 GND   → M-Bot GND
```

### 1.3 M-Bot Component Setup
```
Ultrasonic Sensor → PORT_3
Left Motor        → M1
Right Motor       → M2
RGB LED           → PORT_7
```

## Part 2: Raspberry Pi Setup

### 2.1 Install Ubuntu 20.04 on Raspberry Pi
```bash
# Flash Ubuntu 20.04 Server LTS to SD card
# Boot Pi and complete initial setup
sudo apt update && sudo apt upgrade -y
```

### 2.2 Follow the Raspberry Pi Setup Instructions
- Complete all steps in the "Raspberry Pi 4 Setup and ROS2 Code" file
- This includes WiFi AP setup, ROS2 installation, and package creation

## Part 3: ESP32 Programming

### 3.1 Arduino IDE Setup
1. Install Arduino IDE 2.0+
2. Add ESP32 board support:
   - Go to File → Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
   - Go to Tools → Board → Board Manager
   - Search "ESP32" and install "ESP32 by Espressif Systems"

3. Install micro-ROS library:
   - Go to Tools → Manage Libraries
   - Search "micro_ros_arduino" and install

### 3.2 Program ESP32 Boards

**For Robot 1:**
- Use the "ESP32 Robot 1 Complete Code"
- Select Board: "ESP32 Dev Module"
- Upload to first ESP32

**For Robot 2:**
- Use the "ESP32 Robot 2 Complete Code"
- Upload to second ESP32

### 3.3 ESP32 Upload Settings
```
Board: ESP32 Dev Module
Upload Speed: 921600
CPU Frequency: 240MHz
Flash Frequency: 80MHz
Flash Mode: QIO
Flash Size: 4MB
Partition Scheme: Default 4MB with spiffs
```

## Part 4: M-Bot Programming

### 4.1 Prepare M-Bot
1. **Remove Bluetooth Module**: Carefully remove the Bluetooth module from M-Bot to expose UART pins
2. Connect ESP32 to exposed UART pins as shown in hardware setup

### 4.2 Program M-Bot
1. Use Arduino IDE with mBot library
2. Install mBot library: Tools → Manage Libraries → Search "Makeblock"
3. Upload the "M-Bot Arduino Code" to both M-Bots
4. **Important**: Change `ROBOT_ID` in the code:
   - Set `const int ROBOT_ID = 1;` for Robot 1
   - Set `const int ROBOT_ID = 2;` for Robot 2

## Part 5: System Startup Procedure

### 5.1 Power-On Sequence
1. **Power on Raspberry Pi** - wait for full boot
2. **Power on Robot 1** - ESP32 and M-Bot
3. **Power on Robot 2** - ESP32 and M-Bot
4. Wait for all connections to establish

### 5.2 Verify Connections

**Check WiFi Network:**
```bash
# On Raspberry Pi
iwconfig wlan0
arp -a | grep 192.168.4
```

**Check Robot Connections:**
```bash
# On Raspberry Pi
ros2 topic list | grep robot
ros2 topic hz /robot1/scan
ros2 topic hz /robot2/scan
```

### 5.3 Start Navigation System
```bash
# Terminal 1: Launch system
cd ~/multirobot_ws
source install/setup.bash
ros2 launch multirobot_nav multirobot_launch.py

# Terminal 2: Monitor status
watch -n 2 'ros2 topic list | grep robot'
```

## Part 6: Network Configuration

### 6.1 WiFi Network Details
```
Network Name: MultiRobot_Network
Password: multirobot2024
Raspberry Pi: 192.168.4.1 (Gateway)
Robot 1: 192.168.4.10 (Reserved)
Robot 2: 192.168.4.20 (Reserved)
IP Range: 192.168.4.10 - 192.168.4.50
```

### 6.2 Port Assignments
```
micro-ROS Agent Robot 1: Port 8888
micro-ROS Agent Robot 2: Port 8889
```

## Part 7: Status Indicators

### 7.1 ESP32 Built-in LED
- **Solid ON**: Full micro-ROS connection
- **Slow Blink**: WiFi connected, micro-ROS disconnected  
- **Fast Blink**: WiFi disconnected

### 7.2 M-Bot RGB LED
- **Robot 1**: Blue identification color
- **Robot 2**: Red identification color
- **Green**: Autonomous mode active
- **Red**: Emergency stop active
- **Yellow**: Manual mode
- **White**: Moving/stopped

### 7.3 Audio Indicators
- **Startup Beep**: Different pitch for each robot
- **Emergency**: High-pitched warning beeps

## Part 8: Testing Procedures

### 8.1 Individual Robot Testing
```bash
# Test Robot 1 movement
ros2 topic pub /robot1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.1}, angular: {z: 0.0}}" --once

# Test Robot 2 movement
ros2 topic pub /robot2/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.1}, angular: {z: 0.0}}" --once

# Stop both robots
ros2 topic pub /robot1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
ros2 topic pub /robot2/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
```

### 8.2 LiDAR Data Verification
```bash
# Check scan data
ros2 topic echo /robot1/scan --once
ros2 topic echo /robot2/scan --once

# Check data rates
ros2 topic hz /robot1/scan
ros2 topic hz /robot2/scan
```

### 8.3 Mapping Test
```bash
# Check map generation
ros2 topic echo /map --once

# Visualize in RViz
rviz2
```

## Part 9: Troubleshooting

### 9.1 WiFi Connection Issues
```bash
# Check AP status
sudo systemctl status hostapd
sudo systemctl status dnsmasq

# Restart services
sudo systemctl restart hostapd
sudo systemctl restart dnsmasq

# Check connected devices
arp -a | grep 192.168.4
```

### 9.2 ESP32 Issues
- **No WiFi Connection**: Check network credentials
- **micro-ROS Connection Failed**: Verify agent is running on correct port
- **LiDAR No Data**: Check power supply and wiring

### 9.3 M-Bot Issues
- **No Response**: Check UART connections after Bluetooth removal
- **Emergency Stop**: Check ultrasonic sensor, send 'R' command to reset

### 9.4 ROS2 Issues
```bash
# Restart micro-ROS agents
killall micro_ros_agent
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8889 &

# Check node status
ros2 node list
ros2 topic list
```

## Part 10: Advanced Configuration

### 10.1 Adjust Robot Parameters
Edit parameters in launch file or config files:
- Navigation speeds
- Safety distances  
- Coordination strategy
- Map resolution

### 10.2 Add More Robots
1. Reserve new IP in dnsmasq config
2. Create new ESP32 code with different port
3. Add new robot controller in ROS2 launch file
4. Update coordinator for additional robots

### 10.3 Performance Tuning
```bash
# Increase CPU performance
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# Optimize network buffers
export RMW_UXRCE_MAX_OUTPUT_BUFFER_SIZE=16384
export RMW_UXRCE_MAX_INPUT_BUFFER_SIZE=16384
```

## Part 11: Safety Guidelines

### 11.1 Operating Procedures
1. Always have emergency stop accessible
2. Test in open area first
3. Monitor battery levels
4. Keep robots within WiFi range
5. Supervise autonomous operation

### 11.2 Emergency Procedures
- **Manual Stop**: Send stop commands via ROS2
- **Hardware Stop**: Power off robots
- **Software Reset**: Restart ROS2 system
- **M-Bot Reset**: Send 'R' command to reset emergency state

### 11.3 Maintenance
- Check all connections regularly
- Keep LiDAR sensors clean
- Monitor system logs
- Update software as needed

## System Architecture Summary

```
Raspberry Pi 4 (192.168.4.1)
├── WiFi Access Point (MultiRobot_Network)
├── ROS2 Foxy Environment
├── micro-ROS Agents (ports 8888, 8889)
├── Robot Coordinator Node
├── Multi-Robot SLAM Node
└── Individual Robot Controllers

Robot 1 (192.168.4.10)
├── ESP32 (micro-ROS node)
├── LD19 LiDAR (Serial communication)
└── M-Bot (UART communication)

Robot 2 (192.168.4.20)  
├── ESP32 (micro-ROS node)
├── LD19 LiDAR (Serial communication)
└── M-Bot (UART communication)
```

This completes the full setup for a coordinated multi-robot navigation and mapping system using WiFi communication.