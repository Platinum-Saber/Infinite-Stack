# ESP32 micro-ROS Multi-Robot System Documentation

## Table of Contents
1. [System Overview](#system-overview)
2. [ESP32 micro-ROS Implementation](#esp32-micro-ros-implementation)
3. [Raspberry Pi ROS System](#raspberry-pi-ros-system)
4. [Communication Architecture](#communication-architecture)
5. [Data Flow and Message Types](#data-flow-and-message-types)
6. [Network Configuration](#network-configuration)
7. [Troubleshooting Guide](#troubleshooting-guide)

## System Overview

The multi-robot system consists of ESP32 microcontrollers running micro-ROS that communicate with a Raspberry Pi running full ROS2. Each robot has:

- **ESP32**: Handles sensor data (LD19 LiDAR), micro-ROS communication, and M-Bot control
- **Raspberry Pi**: Runs ROS2 nodes for coordination, SLAM, and navigation
- **M-Bot**: Arduino-based robot platform for motor control and ultrasonic sensing

### Architecture Diagram
```
┌─────────────────┐    WiFi/UDP    ┌─────────────────┐
│     ESP32       │ ◄──────────── │  Raspberry Pi   │
│   (micro-ROS)   │               │    (ROS2)       │
├─────────────────┤               ├─────────────────┤
│ • LD19 LiDAR    │               │ • Coordinator   │
│ • Odometry      │               │ • SLAM          │
│ • Command Sub   │               │ • Controllers   │
└─────────┬───────┘               └─────────────────┘
          │ UART
          │
┌─────────▼───────┐
│     M-Bot       │
│   (Arduino)     │
├─────────────────┤
│ • Motor Control │
│ • Ultrasonic    │
│ • Safety Logic  │
└─────────────────┘
```

## ESP32 micro-ROS Implementation

### 1. Hardware Configuration

The ESP32 interfaces with multiple components:

```cpp
// LiDAR Configuration
#define LIDAR_SERIAL Serial2
#define LIDAR_BAUDRATE 230400
#define LIDAR_RX_PIN 16
#define LIDAR_TX_PIN 17

// M-Bot Communication
#define MBOT_SERIAL Serial1
#define MBOT_RX_PIN 4
#define MBOT_TX_PIN 2
```

### 2. micro-ROS Entities

Each ESP32 creates the following ROS entities:

#### Publishers
- **Scan Publisher**: `/robot1/scan` (LaserScan messages)
- **Odometry Publisher**: `/robot1/odom` (Odometry messages)

#### Subscribers
- **Command Velocity**: `/robot1/cmd_vel` (Twist messages)

#### Timers
- **Control Timer**: 10Hz for publishing sensor data

### 3. Message Processing Flow

```
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│ LD19 LiDAR  │───▶│ ESP32 Parser │───▶│ ROS LaserScan│
└─────────────┘    └──────────────┘    └─────────────┘
                           │
                           ▼
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│   M-Bot     │◄───│ ESP32 Control│◄───│ ROS Twist   │
└─────────────┘    └──────────────┘    └─────────────┘
```

### 4. LiDAR Data Processing

The ESP32 processes LD19 LiDAR data according to the protocol:

```cpp
void process_lidar_frame(uint8_t* buffer) {
    LiDARFrameTypeDef* frame = (LiDARFrameTypeDef*)buffer;
    
    // Validate frame
    if (frame->header != HEADER || frame->ver_len != 0x2C) return;
    
    // Verify CRC
    uint8_t calculated_crc = CalCRC8(buffer, 46);
    if (calculated_crc != frame->crc8) return;
    
    // Process 12 points per frame
    for (int i = 0; i < POINT_PER_PACK; i++) {
        float angle = start_angle + i * angle_step;
        float distance = frame->point[i].distance / 1000.0; // Convert to meters
        ranges[angle_index] = distance;
    }
}
```

### 5. Coordinate System Transformation

The LD19 uses a left-handed coordinate system (clockwise), while ROS uses right-handed (counter-clockwise). The transformation is handled in the ROS system.

## Raspberry Pi ROS System

### 1. Node Architecture

The Raspberry Pi runs several interconnected ROS2 nodes:

```
┌──────────────────┐
│ Robot Coordinator│
├──────────────────┤
│ • Frontier-based │
│   exploration    │
│ • Goal assignment│
│ • Safety checks  │
└─────────┬────────┘
          │
          ▼
┌─────────────────┐    ┌─────────────────┐
│ Robot Controller│    │ Multi-Robot SLAM│
├─────────────────┤    ├─────────────────┤
│ • Path planning │    │ • Occupancy grid│
│ • Obstacle      │    │ • Map fusion    │
│   avoidance     │    │ • Localization  │
└─────────────────┘    └─────────────────┘
```

### 2. micro-ROS Agents

Each robot requires a dedicated micro-ROS agent:

```yaml
# Robot 1 Agent
micro_ros_agent:
  port: 8888
  protocol: UDP4
  
# Robot 2 Agent  
micro_ros_agent:
  port: 8889
  protocol: UDP4
```

### 3. Node Descriptions

#### Robot Coordinator (`robot_coordinator.py`)

**Purpose**: Central coordination of multi-robot exploration

**Key Functions**:
- Frontier detection and clustering
- Goal assignment optimization
- Inter-robot collision avoidance
- Exploration completion monitoring

**Publishers**:
- `/robot1/goal_pose` (PoseStamped)
- `/robot2/goal_pose` (PoseStamped)
- `/robot1/cmd_vel` (Twist) - Emergency stop
- `/robot2/cmd_vel` (Twist) - Emergency stop

**Subscribers**:
- `/robot1/odom` (Odometry)
- `/robot2/odom` (Odometry)
- `/robot1/scan` (LaserScan)
- `/robot2/scan` (LaserScan)
- `/map` (OccupancyGrid)

#### Robot Controller (`robot_controller.py`)

**Purpose**: Individual robot navigation and control

**Key Functions**:
- Goal-directed navigation
- Dynamic obstacle avoidance
- Local path planning
- Safety monitoring

**Algorithm Flow**:
```python
def control_loop(self):
    if goal_available and not goal_reached:
        # Calculate goal direction
        goal_angle = atan2(goal_y - robot_y, goal_x - robot_x)
        
        # Check for obstacles
        if obstacle_detected:
            # Obstacle avoidance behavior
            cmd = obstacle_avoidance_behavior()
        else:
            # Navigate toward goal
            cmd = navigate_to_goal(goal_angle)
    
    publish_cmd_vel(cmd)
```

#### Multi-Robot SLAM (`multirobot_slam.py`)

**Purpose**: Simultaneous Localization and Mapping for multiple robots

**Key Functions**:
- Sensor data fusion from multiple robots
- Occupancy grid generation
- Real-time map updates
- Coordinate frame management

**Map Update Process**:
```python
def update_map_with_scan(self, scan, robot_x, robot_y, robot_yaw):
    for i, range_val in enumerate(scan.ranges):
        # Calculate end point of laser ray
        angle = scan.angle_min + i * scan.angle_increment + robot_yaw
        end_x = robot_x + range_val * cos(angle)
        end_y = robot_y + range_val * sin(angle)
        
        # Ray tracing - mark free space
        self.ray_trace(robot_x, robot_y, end_x, end_y)
        
        # Mark obstacle at end point
        self.mark_obstacle(end_x, end_y)
```

## Communication Architecture

### 1. Network Setup

The system uses a dedicated WiFi network for robot communication:

```cpp
// ESP32 Configuration
char ssid[] = "MultiRobot_Network";
char password[] = "multirobot2024";
char agent_ip[] = "192.168.4.1";  // Raspberry Pi IP
```

### 2. micro-ROS Transport

micro-ROS uses UDP transport for communication:

```cpp
// Set up WiFi transport
set_microros_wifi_transports(ssid, password, agent_ip, agent_port);

// Ping agent to establish connection
while (RMW_RET_OK != rmw_uros_ping_agent(100, 1)) {
    delay(200);
}

// Synchronize session
rmw_uros_sync_session(1000);
```

### 3. Message Serialization

micro-ROS handles automatic serialization/deserialization of ROS messages over UDP.

## Data Flow and Message Types

### 1. Sensor Data Flow

```
ESP32 → Raspberry Pi:
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│ LD19 Raw    │───▶│ LaserScan    │───▶│ SLAM Node   │
│ Data        │    │ Message      │    │             │
└─────────────┘    └──────────────┘    └─────────────┘

┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│ Dead        │───▶│ Odometry     │───▶│ Coordinator │
│ Reckoning   │    │ Message      │    │             │
└─────────────┘    └──────────────┘    └─────────────┘
```

### 2. Control Data Flow

```
Raspberry Pi → ESP32:
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│ Navigation  │───▶│ Twist        │───▶│ M-Bot       │
│ Commands    │    │ Message      │    │ Control     │
└─────────────┘    └──────────────┘    └─────────────┘
```

### 3. Message Specifications

#### LaserScan Message
```cpp
sensor_msgs__msg__LaserScan scan_msg;
scan_msg.angle_min = 0.0;
scan_msg.angle_max = 2.0 * M_PI;
scan_msg.angle_increment = (2.0 * M_PI) / OUT_BEAMS;
scan_msg.range_min = 0.15;
scan_msg.range_max = 12.0;
// ranges[360] array with distance data
```

#### Odometry Message
```cpp
nav_msgs__msg__Odometry odom_msg;
odom_msg.pose.pose.position.x = robot_x;
odom_msg.pose.pose.position.y = robot_y;
odom_msg.twist.twist.linear.x = linear_velocity;
odom_msg.twist.twist.angular.z = angular_velocity;
```

#### Twist Message
```cpp
geometry_msgs__msg__Twist cmd_vel_msg;
cmd_vel_msg.linear.x = forward_speed;    // m/s
cmd_vel_msg.angular.z = turn_rate;       // rad/s
```

## Network Configuration

### 1. Raspberry Pi Setup

Configure the Raspberry Pi as a WiFi access point:

```bash
# Install hostapd and dnsmasq
sudo apt install hostapd dnsmasq

# Configure hostapd
echo 'interface=wlan0
driver=nl80211
ssid=MultiRobot_Network
hw_mode=g
channel=7
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=multirobot2024
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP' | sudo tee /etc/hostapd/hostapd.conf

# Configure static IP
sudo ip addr add 192.168.4.1/24 dev wlan0
```

### 2. Launch Configuration

```python
# multi_robot_launch.py
def generate_launch_description():
    return LaunchDescription([
        # micro-ROS agents for each robot
        Node(
            package='micro_ros_agent',
            executable='micro_ros_agent',
            arguments=['udp4', '--port', '8888'],
            name='micro_ros_agent_robot1'
        ),
        
        # Robot coordination and control nodes
        Node(package='multirobot_nav', executable='robot_coordinator'),
        Node(package='multirobot_nav', executable='robot_controller'),
        Node(package='multirobot_nav', executable='multi_robot_slam'),
    ])
```

## ROS Nodes and Topics Architecture

### 1. Complete Node Overview

The multi-robot system consists of the following ROS2 nodes:

#### Core Infrastructure Nodes
- **micro_ros_agent_robot1**: Bridge between ESP32 Robot 1 and ROS2
- **micro_ros_agent_robot2**: Bridge between ESP32 Robot 2 and ROS2

#### Robot-Specific Nodes (per robot)
- **robot1_node** (ESP32): Hardware interface and sensor data publisher
- **robot2_node** (ESP32): Hardware interface and sensor data publisher
- **robot1_controller**: Individual robot navigation and control
- **robot2_controller**: Individual robot navigation and control

#### System-Wide Nodes
- **robot_coordinator**: Multi-robot coordination and goal assignment
- **multi_robot_slam**: Simultaneous localization and mapping
- **static_transform_publishers**: TF frame relationships

### 2. Complete ROS Topics List

#### Robot 1 Topics
```
Publishers (from ESP32):
/robot1/scan           (sensor_msgs/LaserScan)
/robot1/odom           (nav_msgs/Odometry)

Subscribers (to ESP32):
/robot1/cmd_vel        (geometry_msgs/Twist)
/robot1/goal_pose      (geometry_msgs/PoseStamped)
```

#### Robot 2 Topics
```
Publishers (from ESP32):
/robot2/scan           (sensor_msgs/LaserScan)
/robot2/odom           (nav_msgs/Odometry)

Subscribers (to ESP32):
/robot2/cmd_vel        (geometry_msgs/Twist)
/robot2/goal_pose      (geometry_msgs/PoseStamped)
```

#### System-Wide Topics
```
/map                   (nav_msgs/OccupancyGrid)
/tf                    (tf2_msgs/TFMessage)
/tf_static             (tf2_msgs/TFMessage)
```

### 3. Node Interaction Diagram

```
┌────────────────────────────────────────────────────────────────────┐
│                        Raspberry Pi ROS2 System                    │
├────────────────────────────────────────────────────────────────────┤
│                                                                    │
│  ┌─────────────────┐         /map          ┌─────────────────┐     │
│  │ Robot           │◄─────────────────────►│ Multi-Robot     │     │
│  │ Coordinator     │                       │ SLAM            │     │
│  └─────┬───────────┘                       └─────▲───────────┘     │
│        │                                         │                 │
│        │ /robot1/goal_pose                       │ /robot1/scan    │
│        │ /robot2/goal_pose                       │ /robot2/scan    │
│        │                                         │ /robot1/odom    │
│        ▼                                         │ /robot2/odom    │
│  ┌─────────────────┐                       ┌─────┴───────────┐     │
│  │ Robot1          │ /robot1/cmd_vel       │ Robot2          │     │
│  │ Controller      │◄──────────────────────┤ Controller      │     │
│  └─────┬───────────┘                       └─────┬───────────┘     │
│        │                                         │                 │
└────────┼─────────────────────────────────────────┼─────────────────┘
         │                                         │
         │ /robot1/cmd_vel                         │ /robot2/cmd_vel
         │ /robot1/goal_pose                       │ /robot2/goal_pose
         ▼                                         ▼
┌─────────────────┐                       ┌─────────────────┐
│ micro-ROS       │                       │ micro-ROS       │
│ Agent Robot1    │                       │ Agent Robot2    │
│ (Port 8888)     │                       │ (Port 8889)     │
└─────┬───────────┘                       └─────┬───────────┘
      │ UDP                                     │ UDP
      ▼                                         ▼
┌─────────────────┐                       ┌─────────────────┐
│ ESP32 Robot1    │                       │ ESP32 Robot2    │
│ Node            │                       │ Node            │
└─────────────────┘                       └─────────────────┘
```

### 4. Detailed Node Interactions

#### 4.1 Robot Coordinator Node

**Role**: Central coordination hub for multi-robot exploration

**Input Topics**:
```python
# Robot state monitoring
'/robot1/odom'    → self.robot1_odom_callback()
'/robot2/odom'    → self.robot2_odom_callback()

# Sensor data for safety
'/robot1/scan'    → self.robot1_scan_callback()  
'/robot2/scan'    → self.robot2_scan_callback()

# Global map for frontier detection
'/map'            → self.map_callback()
```

**Output Topics**:
```python
# Goal assignment
'/robot1/goal_pose'  ← self.send_goal_to_robot('robot1', goal)
'/robot2/goal_pose'  ← self.send_goal_to_robot('robot2', goal)

# Emergency control
'/robot1/cmd_vel'    ← self.emergency_stop() 
'/robot2/cmd_vel'    ← self.emergency_stop()
```

**Interaction Logic**:
```python
def coordinate_robots(self):
    # 1. Get current robot positions from odometry
    robot1_pos = self.robot1_pose.position
    robot2_pos = self.robot2_pose.position
    
    # 2. Find exploration frontiers from map
    frontiers = self.find_exploration_frontiers()
    
    # 3. Assign optimal goals avoiding conflicts
    best_assignment = self.optimize_goal_assignment(frontiers)
    
    # 4. Publish goals to individual controllers
    self.send_goal_to_robot('robot1', best_assignment[0])
    self.send_goal_to_robot('robot2', best_assignment[1])
    
    # 5. Monitor safety constraints
    if self.robots_too_close():
        self.emergency_stop()
```

#### 4.2 Robot Controller Nodes

**Role**: Individual robot navigation and local control

**Input Topics** (per robot):
```python
# Sensor data for obstacle avoidance
'/robot1/scan'       → self.scan_callback()
'/robot1/odom'       → self.odom_callback()

# High-level goals from coordinator
'/robot1/goal_pose'  → self.goal_callback()
```

**Output Topics** (per robot):
```python
# Motor commands to ESP32
'/robot1/cmd_vel'    ← self.control_loop()
```

**Interaction Logic**:
```python
def control_loop(self):
    if self.current_goal and not self.goal_reached:
        # 1. Calculate direction to goal
        goal_angle = self.calculate_goal_direction()
        
        # 2. Check for local obstacles
        obstacle_detected, direction = self.detect_obstacles()
        
        # 3. Generate appropriate command
        if obstacle_detected:
            cmd = self.obstacle_avoidance_behavior(direction)
        else:
            cmd = self.navigate_to_goal(goal_angle)
        
        # 4. Send command to ESP32
        self.publish_cmd_vel(cmd)
```

#### 4.3 Multi-Robot SLAM Node

**Role**: Global mapping and localization for all robots

**Input Topics**:
```python
# Sensor data from all robots
'/robot1/scan'  → self.robot1_scan_callback()
'/robot2/scan'  → self.robot2_scan_callback()
```

**Output Topics**:
```python
# Global occupancy grid map
'/map'          ← self.publish_map()
```

**Interaction Logic**:
```python
def process_scan(self, scan_msg, robot_name):
    # 1. Get robot pose from TF
    transform = self.tf_buffer.lookup_transform('map', f'{robot_name}/base_link')
    
    # 2. Transform scan to global coordinates
    global_points = self.transform_scan_to_global(scan_msg, transform)
    
    # 3. Update occupancy grid
    self.update_occupancy_grid(global_points)
    
    # 4. Publish updated map
    self.publish_map()
```

#### 4.4 ESP32 Robot Nodes

**Role**: Hardware interface and sensor data collection

**Input Topics**:
```python
# Motor commands from controller
'/robot1/cmd_vel'  → self.cmd_vel_callback()
```

**Output Topics**:
```python
# Sensor data to ROS system
'/robot1/scan'     ← self.publish_scan()
'/robot1/odom'     ← self.publish_odometry()
```

**Interaction Logic**:
```cpp
void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
    // 1. Process LiDAR data
    if (new_scan_ready) {
        publish_scan();  // → /robot1/scan
    }
    
    // 2. Update and publish odometry
    publish_odometry();  // → /robot1/odom
}

void cmd_vel_callback(const void * msgin) {
    // 3. Convert ROS commands to M-Bot protocol
    convert_and_send_to_mbot(msg);
}
```

### 5. Topic Message Flow Analysis

#### 5.1 Exploration Coordination Flow

```
Step 1: Data Collection
ESP32 → /robot1/scan → Multi-Robot SLAM
ESP32 → /robot1/odom → Multi-Robot SLAM, Robot Coordinator

Step 2: Map Update
Multi-Robot SLAM → /map → Robot Coordinator

Step 3: Goal Assignment
Robot Coordinator → /robot1/goal_pose → Robot1 Controller
Robot Coordinator → /robot2/goal_pose → Robot2 Controller

Step 4: Navigation
Robot Controller → /robot1/cmd_vel → ESP32 → M-Bot
```

#### 5.2 Safety Monitoring Flow

```
Continuous Monitoring:
ESP32 → /robot1/odom → Robot Coordinator
ESP32 → /robot1/scan → Robot Coordinator

Safety Check:
Robot Coordinator.safety_check() → Emergency Decision

Emergency Response:
Robot Coordinator → /robot1/cmd_vel (STOP) → ESP32
Robot Coordinator → /robot2/cmd_vel (STOP) → ESP32
```

#### 5.3 Obstacle Avoidance Flow

```
Local Detection:
ESP32 → /robot1/scan → Robot1 Controller

Local Decision:
Robot1 Controller.detect_obstacles() → Avoidance Behavior

Local Response:
Robot1 Controller → /robot1/cmd_vel → ESP32 → M-Bot
```

### 6. TF Frame Relationships

The system uses the following coordinate frames:

```
map
├── robot1/odom
│   └── robot1/base_link
│       └── robot1/lidar_link
└── robot2/odom
    └── robot2/base_link
        └── robot2/lidar_link
```

**Static Transforms** (Published by static_transform_publisher nodes):
```bash
# Map to odometry frames
map → robot1/odom (0,0,0)
map → robot2/odom (0,0,0)

# Base to sensor frames  
robot1/base_link → robot1/lidar_link (0,0,0.1)
robot2/base_link → robot2/lidar_link (0,0,0.1)
```

### 7. Data Synchronization and Timing

**Update Frequencies**:
- ESP32 sensor publishing: 10 Hz
- Robot controllers: 10 Hz  
- Robot coordinator: 0.5 Hz (every 2 seconds)
- SLAM map updates: 5 Hz
- Safety checks: 5 Hz (every 200ms)

**Message Latency Requirements**:
- Emergency stops: < 100ms
- Navigation commands: < 200ms
- Map updates: < 1s
- Goal assignments: < 2s

This architecture ensures robust multi-robot coordination through well-defined topic interfaces and clear separation of responsibilities between nodes.

## Troubleshooting Guide

### 1. Connection Issues

**Problem**: ESP32 cannot connect to micro-ROS agent

**Solutions**:
- Verify WiFi credentials and IP addresses
- Check agent is running: `ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888`
- Ensure firewall allows UDP traffic on agent ports
- Check ESP32 serial monitor for connection status

### 2. LiDAR Data Issues

**Problem**: No laser scan data or invalid readings

**Solutions**:
- Verify LD19 power supply (5V ±0.5V)
- Check UART connections and baud rate (230400)
- Validate CRC checksums in received frames
- Ensure proper coordinate system transformation

### 3. Robot Coordination Issues

**Problem**: Robots not receiving goals or colliding

**Solutions**:
- Check frontier detection algorithm parameters
- Verify minimum robot distance settings
- Monitor `/map` topic for proper SLAM operation
- Review exploration completion thresholds

### 4. Performance Optimization

**Recommendations**:
- Use wired Ethernet for Raspberry Pi when possible
- Implement QoS policies for critical messages
- Monitor CPU usage on Raspberry Pi
- Optimize map resolution based on environment size
- Consider message throttling for high-frequency data

### 5. Debug Commands

```bash
# Check ROS topics
ros2 topic list
ros2 topic echo /robot1/scan
ros2 topic echo /map

# Monitor node status  
ros2 node list
ros2 node info /robot_coordinator

# Check TF tree
ros2 run tf2_tools view_frames

# Visualize in RViz2
ros2 run rviz2 rviz2
```

## Conclusion

This micro-ROS multi-robot system demonstrates effective integration between resource-constrained ESP32 microcontrollers and full ROS2 systems. The architecture provides:

- **Scalability**: Easy addition of new robots
- **Reliability**: Robust error handling and safety mechanisms  
- **Performance**: Efficient data processing and communication
- **Modularity**: Clear separation of concerns between nodes

The system successfully bridges the gap between embedded sensor systems and high-level robotic coordination algorithms.