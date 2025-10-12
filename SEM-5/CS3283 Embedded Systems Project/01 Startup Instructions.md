
## Table of Contents
1. [System Overview](#system-overview)
2. [Launch Commands](#launch-commands)
3. [Manual Robot Control](#manual-robot-control)
4. [Goal Setting and Navigation](#goal-setting-and-navigation)
5. [Monitoring and Debugging](#monitoring-and-debugging)
6. [Emergency Controls](#emergency-controls)
7. [Troubleshooting](#troubleshooting)

---

## System Overview

This multi-robot navigation system consists of several interconnected components:

### Hardware Components:
- **ESP32**: Runs micro-ROS, handles LiDAR data and communication
- **M-Bot**: Physical robot platform with motors and sensors
- **LD19 LiDAR**: 360° laser scanner for mapping and obstacle detection

### Software Components:
- **Robot Controller**: Individual robot navigation and obstacle avoidance
- **Robot Coordinator**: Multi-robot coordination and frontier exploration
- **Multi-Robot SLAM**: Simultaneous Localization and Mapping
- **micro-ROS Agents**: Bridge between ESP32 and ROS2 network

---

## Launch Commands

### 1. Start the Complete System
```bash
# Launch all components for both robots
ros2 launch multirobot_nav multi_robot_launch.py
```

**What this does:**
- Starts micro-ROS agents for both robots (ports 8888 and 8889)
- Launches robot controllers for robot1 and robot2
- Starts the robot coordinator for multi-robot coordination
- Initializes multi-robot SLAM system
- Sets up all necessary transform frames

### 2. Launch Individual Components

#### Start only Robot 1:
```bash
# Robot 1 controller only
ros2 run multirobot_nav robot_controller --ros-args -p robot_name:=robot1

# Robot 1 micro-ROS agent only
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

#### Start only Robot 2:
```bash
# Robot 2 controller only
ros2 run multirobot_nav robot_controller --ros-args -p robot_name:=robot2

# Robot 2 micro-ROS agent only
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8889
```

#### Start coordination components:
```bash
# Multi-robot coordinator
ros2 run multirobot_nav robot_coordinator

# SLAM system
ros2 run multirobot_nav multi_robot_slam
```

---

## Manual Robot Control

### Direct Velocity Control

#### Robot 1 Commands:
```bash
# Move forward at 0.2 m/s
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.2}, angular: {z: 0.0}}'

# Move backward at 0.15 m/s
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: -0.15}, angular: {z: 0.0}}'

# Turn left (counterclockwise)
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0}, angular: {z: 0.5}}'

# Turn right (clockwise)
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0}, angular: {z: -0.5}}'

# Stop
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0}, angular: {z: 0.0}}'

# Move forward while turning left
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.1}, angular: {z: 0.2}}'
```

#### Robot 2 Commands:
```bash
# Same commands but replace /robot1/ with /robot2/
ros2 topic pub -1 /robot2/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.2}, angular: {z: 0.0}}'
```

### Command Parameters Explained:

- **linear.x**: Forward/backward velocity (m/s)
  - Positive values = forward movement
  - Negative values = backward movement
  - Typical range: -0.5 to 0.5 m/s

- **angular.z**: Rotational velocity (rad/s)
  - Positive values = turn left (counterclockwise)
  - Negative values = turn right (clockwise)
  - Typical range: -1.0 to 1.0 rad/s

- **-1 flag**: Publishes the message once and exits
  - Without -1: Continuously publishes at 1Hz until Ctrl+C

---

## Goal Setting and Navigation

### Setting Navigation Goals

#### Robot 1 Goal Commands:
```bash
# Move to position (1.0, 0.0) - 1 meter forward
ros2 topic pub -1 /robot1/goal_pose geometry_msgs/msg/PoseStamped '{
  header: {frame_id: "map"},
  pose: {
    position: {x: 1.0, y: 0.0, z: 0.0},
    orientation: {w: 1.0}
  }
}'

# Move to position (0.5, 1.0) - diagonal movement
ros2 topic pub -1 /robot1/goal_pose geometry_msgs/msg/PoseStamped '{
  header: {frame_id: "map"},
  pose: {
    position: {x: 0.5, y: 1.0, z: 0.0},
    orientation: {w: 1.0}
  }
}'

# Return to origin
ros2 topic pub -1 /robot1/goal_pose geometry_msgs/msg/PoseStamped '{
  header: {frame_id: "map"},
  pose: {
    position: {x: 0.0, y: 0.0, z: 0.0},
    orientation: {w: 1.0}
  }
}'
```

#### Robot 2 Goal Commands:
```bash
# Move Robot 2 to different position
ros2 topic pub -1 /robot2/goal_pose geometry_msgs/msg/PoseStamped '{
  header: {frame_id: "map"},
  pose: {
    position: {x: -1.0, y: 0.0, z: 0.0},
    orientation: {w: 1.0}
  }
}'
```

### Goal Parameters Explained:

- **header.frame_id**: Coordinate frame ("map" for global coordinates)
- **position.x, y, z**: Target position in meters
  - x: Forward/backward from origin
  - y: Left/right from origin  
  - z: Up/down (usually 0 for ground robots)
- **orientation.w**: Quaternion for target heading (1.0 = facing forward)

### Advanced Goal Setting with Specific Orientation:

```bash
# Face 90 degrees left at position (1, 1)
ros2 topic pub -1 /robot1/goal_pose geometry_msgs/msg/PoseStamped '{
  header: {frame_id: "map"},
  pose: {
    position: {x: 1.0, y: 1.0, z: 0.0},
    orientation: {x: 0.0, y: 0.0, z: 0.707, w: 0.707}
  }
}'
```

---

## Monitoring and Debugging

### Check System Status

```bash
# List all active nodes
ros2 node list

# List all topics
ros2 topic list

# Check specific robot data
ros2 topic echo /robot1/odom       # Robot 1 position
ros2 topic echo /robot2/scan       # Robot 2 LiDAR data
ros2 topic echo /map               # Current map

# Monitor goal execution
ros2 topic echo /robot1/goal_pose  # Current goals
ros2 topic echo /robot1/cmd_vel    # Velocity commands being sent
```

### Performance Monitoring

```bash
# Check message rates
ros2 topic hz /robot1/scan         # LiDAR data rate (~10 Hz expected)
ros2 topic hz /robot1/odom         # Odometry rate (~20 Hz expected)
ros2 topic hz /map                 # Map update rate (~5 Hz expected)

# Check for message delays
ros2 topic delay /robot1/scan
```

### Network and Connectivity

```bash
# Check micro-ROS agent connections
ros2 node info /robot1_node
ros2 node info /robot2_node

# Test robot responsiveness
ros2 service call /robot1_node/get_node_info rcl_interfaces/srv/GetNodeInfo
```

---

## Emergency Controls

### Emergency Stop

```bash
# Stop all robots immediately
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0}, angular: {z: 0.0}}'
ros2 topic pub -1 /robot2/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0}, angular: {z: 0.0}}'

# Or kill the robot controllers
ros2 lifecycle set /robot1_controller shutdown
ros2 lifecycle set /robot2_controller shutdown
```

### Reset System

```bash
# Restart individual components
ros2 lifecycle set /robot_coordinator activate
ros2 lifecycle set /multi_robot_slam activate

# Or restart the entire launch file
# Ctrl+C the launch, then restart:
ros2 launch multirobot_nav multi_robot_launch.py
```

---

## Troubleshooting

### Common Issues and Solutions

#### 1. Robot not responding to commands
```bash
# Check if micro-ROS agent is connected
ros2 topic list | grep robot1

# If no topics, restart micro-ROS agent
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888

# Check robot controller status
ros2 node info /robot1_controller
```

#### 2. Robot not reaching goals
```bash
# Check current position
ros2 topic echo /robot1/odom

# Check if goal was received
ros2 topic echo /robot1/goal_pose

# Monitor obstacle detection
ros2 topic echo /robot1/scan
```

#### 3. Map not updating
```bash
# Check SLAM node status
ros2 node list | grep slam

# Restart SLAM if needed
ros2 run multirobot_nav multi_robot_slam

# Check LiDAR data flow
ros2 topic hz /robot1/scan
ros2 topic hz /robot2/scan
```

#### 4. Robots interfering with each other
```bash
# Check minimum distance parameter
ros2 param get /robot_coordinator min_robot_distance

# Increase if needed
ros2 param set /robot_coordinator min_robot_distance 2.0
```

### Debug Information Sources

#### M-Bot Serial Output:
Monitor the M-Bot's serial output for detailed command execution:
```
RECEIVED: 'M102'
EXECUTING: Type=M Value=102.00
ACTION: Moving forward
MOTORS: Forward at speed 102
```

#### ESP32 Serial Output:
Check ESP32 connectivity and micro-ROS status:
```
Robot 1 WiFi connected! IP: 192.168.4.100
Robot 1 micro-ROS initialized
```

#### ROS2 Logs:
```bash
# View detailed logs
ros2 run rqt_console rqt_console

# Or command line logs
ros2 topic echo /rosout
```

---

## System Parameters

### Robot Controller Parameters:
```bash
# View current parameters
ros2 param list /robot1_controller

# Modify speed settings
ros2 param set /robot1_controller linear_speed 0.2
ros2 param set /robot1_controller angular_speed 0.4
ros2 param set /robot1_controller safe_distance 0.5
```

### Coordinator Parameters:
```bash
# Exploration settings
ros2 param set /robot_coordinator exploration_complete_threshold 0.95
ros2 param set /robot_coordinator min_robot_distance 1.5
```

### SLAM Parameters:
```bash
# Map resolution and size
ros2 param set /multi_robot_slam map_resolution 0.05
ros2 param set /multi_robot_slam update_rate 10.0
```

---

## Quick Reference Commands

### Start System:
```bash
ros2 launch multirobot_nav multi_robot_launch.py
```

### Manual Control:
```bash
# Forward
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.2}, angular: {z: 0.0}}'

# Goal
ros2 topic pub -1 /robot1/goal_pose geometry_msgs/msg/PoseStamped '{header: {frame_id: "map"}, pose: {position: {x: 1.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}'
```

### Monitor:
```bash
ros2 topic echo /robot1/odom
ros2 topic echo /map
ros2 node list
```

### Emergency Stop:
```bash
ros2 topic pub -1 /robot1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0}, angular: {z: 0.0}}'
```