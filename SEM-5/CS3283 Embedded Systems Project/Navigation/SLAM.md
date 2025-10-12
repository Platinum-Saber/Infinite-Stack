### 2.4 Individual Robot Controller Node
```python
# multirobot_nav/robot_controller.py
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import Odometry
import math
import numpy as np

class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller')
        
        # Parameters
        self.declare_parameter('robot_name', 'robot1')
        self.declare_parameter('linear_speed', 0.15)
        self.declare_parameter('angular_speed', 0.3)
        self.declare_parameter('safe_distance', 0.4)
        self.declare_parameter('goal_tolerance', 0.3)
        
        self.robot_name = self.get_parameter('robot_name').value
        self.linear_speed = self.get_parameter('linear_speed').value
        self.angular_speed = self.get_parameter('angular_speed').value
        self.safe_distance = self.get_parameter('safe_distance').value
        self.goal_tolerance = self.get_parameter('goal_tolerance').value
        
        # Publishers
        self.cmd_vel_pub = self.create_publisher(Twist, f'/{self.robot_name}/cmd_vel', 10)
        
        # Subscribers
        self.scan_sub = self.create_subscription(
            LaserScan, f'/{self.robot_name}/scan', self.scan_callback, 10)
        self.odom_sub = self.create_subscription(
            Odometry, f'/{self.robot_name}/odom', self.odom_callback, 10)
        self.goal_sub = self.create_subscription(
            PoseStamped, f'/{self.robot_name}/goal_pose', self.goal_callback, 10)
        
        # State variables
        self.current_scan = None
        self.current_pose = None
        self.current_goal = None
        self.goal_reached = True
        
        # Control timer
        self.control_timer = self.create_timer(0.1, self.control_loop)
        
        self.get_logger().info(f'Robot Controller initialized for {self.robot_name}')

    def scan_callback(self, msg):
        self.current_scan = msg

    def odom_callback(self, msg):
        self.current_pose = msg.pose.pose

    def goal_callback(self, msg):
        self.current_goal = (msg.pose.position.x, msg.pose.position.y)
        self.goal_reached = False
        self.get_logger().info(f'{self.robot_name} received new goal: {self.current_goal}')

    def control_loop(self):
        if self.current_scan is None or self.current_pose is None:
            return
        
        cmd = Twist()
        
        if self.current_goal is not None and not self.goal_reached:
            # Navigate to goal with obstacle avoidance
            if self.is_goal_reached():
                self.goal_reached = True
                self.get_logger().info(f'{self.robot_name} reached goal!')
                self.publish_cmd_vel(cmd)  # Stop
                return
            
            # Calculate desired direction to goal
            goal_angle = math.atan2(
                self.current_goal[1] - self.current_pose.position.y,
                self.current_goal[0] - self.current_pose.position.x
            )
            
            current_yaw = self.get_yaw_from_pose(self.current_pose)
            angle_diff = self.normalize_angle(goal_angle - current_yaw)
            
            # Check for obstacles
            obstacle_detected, obstacle_direction = self.detect_obstacles()
            
            if obstacle_detected:
                # Obstacle avoidance behavior
                cmd = self.obstacle_avoidance_behavior(obstacle_direction)
            else:
                # Move towards goal
                if abs(angle_diff) > 0.2:  # Need to turn
                    cmd.angular.z = self.angular_speed if angle_diff > 0 else -self.angular_speed
                    cmd.linear.x = 0.05  # Slow forward while turning
                else:
                    cmd.linear.x = self.linear_speed
                    cmd.angular.z = 0.3 * angle_diff  # Proportional turning
        else:
            # No goal or goal reached - stop
            cmd.linear.x = 0.0
            cmd.angular.z = 0.0
        
        self.publish_cmd_vel(cmd)

    def detect_obstacles(self):
        if self.current_scan is None:
            return False, 0
        
        ranges = np.array(self.current_scan.ranges)
        ranges = np.where(np.isfinite(ranges), ranges, self.current_scan.range_max)
        
        # Check front sectors for obstacles
        front_ranges = ranges[len(ranges)//3:2*len(ranges)//3]
        min_front_dist = np.min(front_ranges)
        
        if min_front_dist < self.safe_distance:
            # Determine obstacle direction
            left_ranges = ranges[:len(ranges)//4]
            right_ranges = ranges[3*len(ranges)//4:]
            
            avg_left = np.mean(left_ranges)
            avg_right = np.mean(right_ranges)
            
            # Return direction with more space
            direction = 'left' if avg_left > avg_right else 'right'
            return True, direction
        
        return False, None

    def obstacle_avoidance_behavior(self, obstacle_direction):
        cmd = Twist()
        
        if obstacle_direction == 'left':
            # Turn right
            cmd.angular.z = -self.angular_speed
        else:
            # Turn left
            cmd.angular.z = self.angular_speed
        
        # Slow forward motion while avoiding
        cmd.linear.x = 0.05
        
        return cmd

    def is_goal_reached(self):
        if self.current_goal is None:
            return True
        
        dist = math.sqrt(
            (self.current_goal[0] - self.current_pose.position.x)**2 +
            (self.current_goal[1] - self.current_pose.position.y)**2
        )
        
        return dist < self.goal_tolerance

    def get_yaw_from_pose(self, pose):
        # Convert quaternion to yaw
        siny_cosp = 2 * (pose.orientation.w * pose.orientation.z + 
                        pose.orientation.x * pose.orientation.y)
        cosy_cosp = 1 - 2 * (pose.orientation.y * pose.orientation.y + 
                            pose.orientation.z * pose.orientation.z)
        return math.atan2(siny_cosp, cosy_cosp)

    def normalize_angle(self, angle):
        while angle > math.pi:
            angle -= 2 * math.pi
        while angle < -math.pi:
            angle += 2 * math.pi
        return angle

    def publish_cmd_vel(self, cmd):
        self.cmd_vel_pub.publish(cmd)

def main(args=None):
    rclpy.init(args=args)
    node = RobotController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

### 2.5 Multi-Robot SLAM Node
```python
# multirobot_nav/multi_robot_slam.py
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import OccupancyGrid
from geometry_msgs.msg import TransformStamped
import tf2_ros
import numpy as np

class MultiRobotSLAM(Node):
    def __init__(self):
        super().__init__('multi_robot_slam')
        
        # Parameters
        self.declare_parameter('map_resolution', 0.05)
        self.declare_parameter('map_width', 2000)
        self.declare_parameter('map_height', 2000)
        self.declare_parameter('update_rate', 2.0)
        
        self.map_resolution = self.get_parameter('map_resolution').value
        self.map_width = self.get_parameter('map_width').value
        self.map_height = self.get_parameter('map_height').value
        self.update_rate = self.get_parameter('update_rate').value
        
        # Publishers
        self.map_pub = self.create_publisher(OccupancyGrid, '/map', 10)
        
        # Subscribers for both robots
        self.robot1_scan_sub = self.create_subscription(
            LaserScan, '/robot1/scan', self.robot1_scan_callback, 10)
        self.robot2_scan_sub = self.create_subscription(
            LaserScan, '/robot2/scan', self.robot2_scan_callback, 10)
        
        # TF
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)
        
        # Map data
        self.occupancy_grid = np.full((self.map_height, self.map_width), -1, dtype=np.int8)
        self.map_origin_x = -self.map_width * self.map_resolution / 2
        self.map_origin_y = -self.map_height * self.map_resolution / 2
        
        # Update timer
        self.update_timer = self.create_timer(1.0/self.update_rate, self.publish_map)
        
        self.get_logger().info('Multi-Robot SLAM initialized')

    def robot1_scan_callback(self, msg):
        self.process_scan(msg, 'robot1')

    def robot2_scan_callback(self, msg):
        self.process_scan(msg, 'robot2')

    def process_scan(self, scan_msg, robot_name):
        try:
            # Get robot pose in map frame
            transform = self.tf_buffer.lookup_transform(
                'map', f'{robot_name}/base_link', rclpy.time.Time())
            
            robot_x = transform.transform.translation.x
            robot_y = transform.transform.translation.y
            
            # Convert quaternion to yaw
            qx = transform.transform.rotation.x
            qy = transform.transform.rotation.y
            qz = transform.transform.rotation.z
            qw = transform.transform.rotation.w
            
            siny_cosp = 2 * (qw * qz + qx * qy)
            cosy_cosp = 1 - 2 * (qy * qy + qz * qz)
            robot_yaw = math.atan2(siny_cosp, cosy_cosp)
            
            # Update map with scan data
            self.update_map_with_scan(scan_msg, robot_x, robot_y, robot_yaw)
            
        except Exception as e:
            self.get_logger().warn(f'Failed to process scan from {robot_name}: {e}')

    def update_map_with_scan(self, scan, robot_x, robot_y, robot_yaw):
        for i, range_val in enumerate(scan.ranges):
            if not (scan.range_min <= range_val <= scan.range_max):
                continue
            
            # Calculate beam angle
            angle = scan.angle_min + i * scan.angle_increment + robot_yaw
            
            # Calculate end point of beam
            end_x = robot_x + range_val * math.cos(angle)
            end_y = robot_y + range_val * math.sin(angle)
            
            # Ray tracing - mark free space along beam
            self.ray_trace(robot_x, robot_y, end_x, end_y)
            
            # Mark obstacle at end point
            self.mark_obstacle(end_x, end_y)

    def ray_trace(self, x0, y0, x1, y1):
        # Bresenham's line algorithm for ray tracing
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        
        steps = max(int(dx / self.map_resolution), int(dy / self.map_resolution))
        
        if steps == 0:
            return
        
        x_step = (x1 - x0) / steps
        y_step = (y1 - y0) / steps
```
### 5.7 Testing and Validation

#### Test WiFi Connectivity:


```bash
# From ESP32 Serial Monitor, you should see:
# "Connecting to WiFi: LiDAR_RobotNet"
# "WiFi connected! IP: 192.168.4.x"
# "micro-ROS initialized successfully"
```

#### Test LiDAR Data:
```bash
# Check individual LiDAR streams
ros2 topic hz /lidar1/scan  # Should show ~10Hz
ros2 topic hz /lidar2/scan  # Should show ~10Hz

# Check merged scan
ros2 topic hz /scan  # Should show ~10Hz

# Visualize point cloud in RViz
# Add LaserScan display, set topic to /scan
```

#### Test Robot Movement:
```bash
# Manual movement test
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.2}, angular: {z: 0.0}}" --once

# Test turning
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.5}}" --once

# Stop robot
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
```

#### Test SLAM:
```bash
# Check map generation
ros2 topic echo /map --once

# Save map when exploration is complete
ros2 run nav2_map_server map_saver_cli -f ~/my_map
```

### 5.8 Configuration Files

#### LiDAR Configuration:
```yaml
# config/lidar_config.yaml
lidar_merger:
  ros__parameters:
    lidar1_frame: "lidar1_link"
    lidar2_frame: "lidar2_link"
    merged_frame: "base_link"
    max_range: 12.0
    min_range: 0.15
    publish_rate: 10.0
    angle_resolution: 1.0  # degrees

navigation_controller:
  ros__parameters:
    linear_speed: 0.2
    angular_speed: 0.5
    safe_distance: 0.3
    exploration_mode: true
    frontier_threshold: 0.1
    goal_tolerance: 0.5
```

#### RViz Configuration:
```yaml
# config/navigation.rviz
Panels:
  - Class: rviz_common/Displays
    Help Height: 78
    Name: Displays
    Property Tree Widget:
      Expanded:
        - /Global Options1
        - /Status1
        - /LaserScan1
        - /Map1
        - /RobotModel1
      Splitter Ratio: 0.5
    Tree Height: 557
Visualization Manager:
  Class: ""
  Displays:
    - Alpha: 0.5
      Cell Size: 1
      Class: rviz_default_plugins/Grid
      Color: 160; 160; 164
      Enabled: true
      Line Style:
        Line Width: 0.029999999329447746
        Value: Lines
      Name: Grid
      Normal Cell Count: 0
      Offset:
        X: 0
        Y: 0
        Z: 0
      Plane: XY
      Plane Cell Count: 10
      Reference Frame: <Fixed Frame>
      Value: true
    - Alpha: 1
      Autocompute Intensity Bounds: true
      Autocompute Value Bounds:
        Max Value: 10
        Min Value: -10
        Value: true
      Axis: Z
      Channel Name: intensity
      Class: rviz_default_plugins/LaserScan
      Color: 255; 255; 255
      Color Transformer: Intensity
      Decay Time: 0
      Enabled: true
      Invert Rainbow: false
      Max Color: 255; 255; 255
      Max Intensity: 4096
      Min Color: 0; 0; 0
      Min Intensity: 0
      Name: LaserScan
      Position Transformer: XYZ
      Selectable: true
      Size (Pixels): 3
      Size (m): 0.009999999776482582
      Style: Flat Squares
      Topic:
        Depth: 5
        Durability Policy: Volatile
        Filter size: 10
        History Policy: Keep Last
        Reliability Policy: Reliable
        Value: /scan
      Use Fixed Frame: true
      Use rainbow: true
      Value: true
    - Alpha: 0.7
      Class: rviz_default_plugins/Map
      Color Scheme: map
      Draw Behind: false
      Enabled: true
      Name: Map
      Topic:
        Depth: 5
        Durability Policy: Volatile
        Filter size: 10
        History Policy: Keep Last
        Reliability Policy: Reliable
        Value: /map
      Update Topic:
        Depth: 5
        Durability Policy: Volatile
        History Policy: Keep Last
        Reliability Policy: Reliable
        Value: /map_updates
      Use Timestamp: false
      Value: true
  Enabled: true
  Global Options:
    Background Color: 48; 48; 48
    Fixed Frame: map
    Frame Rate: 30
  Name: root
  Tools:
    - Class: rviz_default_plugins/Interact
      Hide Inactive Objects: true
    - Class: rviz_default_plugins/MoveCamera
    - Class: rviz_default_plugins/Select
    - Class: rviz_default_plugins/FocusCamera
    - Class: rviz_default_plugins/Measure
      Line color: 128; 128; 0
    - Class: nav2_rviz_plugins/GoalTool
  Value: true
  Views:
    Current:
      Angle: 0
      Class: rviz_default_plugins/TopDownOrtho
      Enable Stereo Rendering:
        Stereo Eye Separation: 0.05999999865889549
        Stereo Focal Distance: 1
        Swap Stereo Eyes: false
        Value: false
      Invert Z Axis: false
      Name: Current View
      Near Clip Distance: 0.009999999776482582
      Scale: 100
      Target Frame: <Fixed Frame>
      X: 0
      Y: 0
    Saved: ~
```

### 5.9 Troubleshooting Guide

#### WiFi Issues:
```bash
# Problem: ESP32 can't connect to WiFi
# Solution 1: Check WiFi AP status
sudo systemctl status hostapd
sudo systemctl restart hostapd

# Solution 2: Check WiFi credentials in ESP32 code
# Verify SSID and password match

# Solution 3: Check WiFi channel compatibility
# Some ESP32 boards only support channels 1-11
# Edit /etc/hostapd/hostapd.conf and change channel=7 to channel=6
```

#### micro-ROS Connection Issues:
```bash
# Problem: micro-ROS agent connection fails
# Solution 1: Check if agents are running
ps aux | grep micro_ros_agent

# Solution 2: Check firewall (if enabled)
sudo ufw allow 8888
sudo ufw allow 8889
sudo ufw allow 8890

# Solution 3: Restart agents
killall micro_ros_agent
# Then restart with launch file
```

#### LiDAR Data Issues:
```bash
# Problem: No LiDAR data
# Solution 1: Check LiDAR power and connections
# Verify 5V power supply can handle current draw

# Solution 2: Check serial communication
# ESP32 Serial Monitor should show valid packets

# Solution 3: Verify CRC calculation
# Compare with LD19 manual CRC table
```

#### Robot Movement Issues:
```bash
# Problem: Robot doesn't respond to commands
# Solution 1: Check M-Bot serial connection
# Verify UART pins after Bluetooth module removal

# Solution 2: Test M-Bot independently
# Use Arduino Serial Monitor to send commands directly

# Solution 3: Check battery levels
# Low battery can cause erratic behavior
```

#### SLAM/Mapping Issues:
```bash
# Problem: Map not generating
# Solution 1: Check scan data quality
ros2 topic echo /scan | head -20

# Solution 2: Verify transforms
ros2 run tf2_tools view_frames
# Should show base_link -> lidar_link transforms

# Solution 3: Adjust SLAM parameters
# Edit slam_toolbox parameters in launch file
```

### 5.10 Performance Optimization

#### Network Optimization:
```bash
# Increase WiFi transmission power (if needed)
sudo iwconfig wlan0 txpower 20dBm

# Optimize UDP buffer sizes for micro-ROS
# Add to ~/.bashrc:
echo 'export RMW_UXRCE_MAX_OUTPUT_BUFFER_SIZE=16384' >> ~/.bashrc
echo 'export RMW_UXRCE_MAX_INPUT_BUFFER_SIZE=16384' >> ~/.bashrc
```

#### CPU Optimization:
```bash
# Increase CPU performance mode
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# Increase GPU memory split (if using RViz on Pi)
sudo raspi-config
# Advanced Options -> Memory Split -> 128
```

#### Memory Optimization:
```bash
# Increase swap file if needed
sudo dphys-swapfile swapoff
sudo nano /etc/dphys-swapfile
# Change CONF_SWAPSIZE=1024
sudo dphys-swapfile setup
sudo dphys-swapfile swapon
```

### 5.11 System Monitoring

#### Create monitoring script:
```bash
# Create system monitor
nano ~/monitor_robot.sh
```

```bash
#!/bin/bash
# Robot System Monitor

echo "=== LiDAR Robot System Status ==="
echo "Date: $(date)"
echo ""

echo "=== WiFi Access Point ==="
systemctl is-active hostapd
systemctl is-active dnsmasq
echo "Connected devices:"
arp -a | grep "192.168.4" | wc -l
echo ""

echo "=== ROS2 Processes ==="
ps aux | grep -E "(micro_ros_agent|ros2)" | grep -v grep | wc -l
echo "Active agents:"
ps aux | grep micro_ros_agent | grep -v grep
echo ""

echo "=== Topic Status ==="
echo "LiDAR 1 rate: $(timeout 5 ros2 topic hz /lidar1/scan 2>/dev/null | grep 'average rate' || echo 'No data')"
echo "LiDAR 2 rate: $(timeout 5 ros2 topic hz /lidar2/scan 2>/dev/null | grep 'average rate' || echo 'No data')"
echo "Merged scan rate: $(timeout 5 ros2 topic hz /scan 2>/dev/null | grep 'average rate' || echo 'No data')"
echo ""

echo "=== System Resources ==="
echo "CPU Usage: $(top -bn1 | grep 'Cpu(s)' | awk '{print $2}' | cut -d'%' -f1)"
echo "Memory Usage: $(free | grep Mem | awk '{printf "%.1f%%", $3/$2 * 100.0}')"
echo "Temperature: $(vcgencmd measure_temp)"
echo ""
```

```bash
chmod +x ~/monitor_robot.sh

# Run monitoring
watch -n 5 ~/monitor_robot.sh
```

This completes the comprehensive WiFi-based multi-LiDAR navigation system implementation. The system now includes:

## Key Features:
1. **WiFi Access Point** on Raspberry Pi for wireless communication
2. **Multiple micro-ROS agents** handling different ESP32 nodes
3. **Wireless LiDAR data transmission** from ESP32s to ROS2
4. **Real-time sensor fusion** and navigation
5. **Comprehensive monitoring** and troubleshooting tools
6. **Robust error handling** and reconnection logic

## System Architecture:
- **Raspberry Pi 4**: Creates WiFi network, runs ROS2 navigation stack
- **ESP32 LiDAR Nodes**: Connect to WiFi, publish LiDAR data wirelessly  
- **ESP32 M-Bot Bridge**: Wireless communication with M-Bot for movement
- **M-Bot**: Physical robot platform with motors and sensors

The system is designed for reliability with automatic reconnection, status monitoring, and comprehensive error handling.## 5. Build and Run Instructions

### 5.1 Raspberry Pi WiFi Access Point Setup
```bash
# Start WiFi Access Point
sudo systemctl start hostapd
sudo systemctl start dnsmasq

# Check WiFi AP status
sudo systemctl status hostapd
sudo systemctl status dnsmasq

# Monitor connected devices
sudo cat /var/lib/dhcp/dhcpd.leases
# or
arp -a
```

### 5.2 Build ROS2 Package
```bash
cd ~/lidar_ws
colcon build --packages-select multi_lidar_nav
source install/setup.bash
```

### 5.3 Run the System

#### Terminal 1: Start micro-ROS agents for all devices
```bash
# Start micro-ROS agents for LiDAR nodes and M-Bot bridge
cd ~/lidar_ws
source install/setup.bash

# Start agent for LiDAR 1 (port 8888)
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &

# Start agent for LiDAR 2 (port 8889)
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8889 &

# Start agent for M-Bot bridge (port 8890)
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8890 &

echo "All micro-ROS agents started"
```

#### Terminal 2: Launch main navigation system
```bash
ros2 launch multi_lidar_nav multi_lidar_launch.py
```

#### Terminal 3: Launch RViz for visualization
```bash
rviz2 -d ~/lidar_ws/src/multi_lidar_nav/config/navigation.rviz
```

#### Terminal 4: Monitor system status
```bash
# Monitor topics
ros2 topic list

# Check LiDAR data
ros2 topic echo /lidar1/scan --once
ros2 topic echo /lidar2/scan --once
ros2 topic echo /scan --once

# Check navigation
ros2 topic echo /cmd_vel
ros2 topic echo /odom

# Check map
ros2 topic echo /map --once

# Monitor network connections
watch -n 2 'echo "=== WiFi Status ===" && iwconfig wlan0 && echo "=== Connected Devices ===" && arp -a | grep 192.168.4'
```

### 5.4 Hardware Connections

#### ESP32 LiDAR Node 1:
```
LD19 LiDAR ↔ ESP32
- Pin 1 (TX)  → GPIO 16 (RX)
- Pin 2 (PWM) → GND (for internal speed control)
- Pin 3 (GND) → GND
- Pin 4 (5V)  → 5V

ESP32 Power:
- VIN → 5V power supply
- GND → Common ground
- Built-in LED (GPIO 2) for status
```

#### ESP32 LiDAR Node 2:
```
Same connections as Node 1
```

#### ESP32 M-Bot Bridge:
```
ESP32 ↔ M-Bot (after removing Bluetooth module)
- GPIO 4 → M-Bot UART RX pin
- GPIO 2 → M-Bot UART TX pin  
- GND → M-Bot GND
- 5V → M-Bot 5V (if needed)

Status LED: GPIO 2 (built-in)
```

#### M-Bot Configuration:
```
- Ultrasonic sensor on PORT_3
- Motors on M1 (left), M2 (right)
- RGB LED on PORT_7
- Remove Bluetooth module to access UART pins
```

### 5.5 WiFi Network Configuration

#### Network Details:
```
SSID: LiDAR_RobotNet
Password: lidar123456
IP Range: 192.168.4.1 - 192.168.4.20
Gateway: 192.168.4.1 (Raspberry Pi)

Device IP Assignment:
- Raspberry Pi: 192.168.4.1 (static)
- ESP32 devices: 192.168.4.2+ (DHCP)
```

#### Network Troubleshooting:
```bash
# Check if WiFi AP is running
sudo systemctl status hostapd

# Check DHCP server
sudo systemctl status dnsmasq

# View connected devices
sudo tail -f /var/log/syslog | grep dnsmasq

# Restart WiFi services if needed
sudo systemctl restart hostapd
sudo systemctl restart dnsmasq

# Check WiFi interface
iwconfig wlan0
```

### 5.6 System Startup Script
```bash
# Create startup script
sudo nano /etc/systemd/system/lidar-robot.service
```

```ini
[Unit]
Description=LiDAR Robot Navigation System
After=multi-user.target
Wants=hostapd.service dnsmasq.service

[Service]
Type=simple
User=pi
WorkingDirectory=/home/pi/lidar_ws
ExecStartPre=/bin/bash -c 'source /opt/ros/foxy/setup.bash && source install/setup.bash'
ExecStart=/bin/bash -c 'source /opt/ros/foxy/setup.bash && source install/setup.bash && ros2 launch multi_lidar_nav multi_lidar_launch.py'
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target
```

```bash
# Enable startup service
sudo systemctl enable lidar-robot.service
sudo systemctl start lidar-robot.service
```

### 5.7 Testing and Validation

#### Test WiFi Connectivity:
```bash
# From ESP32 Serial Monitor, you should see:
# "Connecting to WiFi: LiDAR_RobotNet"
# "WiFi connected! IP: 192.168.4.x"
# "micro-ROS initialized successfully"
```# Multi-Robot LiDAR Navigation System Implementation
## Two M-Bots with Individual LiDAR Sensors

## 1. Raspberry Pi 4 Setup (ROS2 Foxy Environment + WiFi Access Point)

### 1.1 Install ROS2 Foxy
```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install ROS2 Foxy
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt install curl gnupg lsb-release
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

sudo apt update
sudo apt install ros-foxy-desktop python3-argcomplete
sudo apt install ros-foxy-rmw-micro-xrce-dds

# Install additional packages for multi-robot
sudo apt install python3-colcon-common-extensions
sudo apt install ros-foxy-nav2-bringup
sudo apt install ros-foxy-navigation2
sudo apt install ros-foxy-nav2-map-server
sudo apt install ros-foxy-slam-toolbox
sudo apt install ros-foxy-robot-localization
sudo apt install ros-foxy-tf2-tools
```

### 1.2 Setup WiFi Access Point
```bash
# Install hostapd and dnsmasq
sudo apt install hostapd dnsmasq

# Stop services
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq

# Configure static IP for wlan0
sudo nano /etc/dhcpcd.conf
# Add at the end:
# interface wlan0
# static ip_address=192.168.4.1/24
# nohook wpa_supplicant

# Configure dnsmasq
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
sudo nano /etc/dnsmasq.conf
```

### 1.3 dnsmasq Configuration
```bash
# /etc/dnsmasq.conf
interface=wlan0
dhcp-range=192.168.4.10,192.168.4.50,255.255.255.0,24h
dhcp-option=3,192.168.4.1
dhcp-option=6,192.168.4.1

# Reserve IPs for robots
dhcp-host=robot1,192.168.4.10
dhcp-host=robot2,192.168.4.20
```

### 1.4 hostapd Configuration
```bash
sudo nano /etc/hostapd/hostapd.conf
```

```
# /etc/hostapd/hostapd.conf
interface=wlan0
driver=nl80211
ssid=MultiRobot_Network
hw_mode=g
channel=6
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=multirobot2024
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
```

### 1.5 Enable WiFi Access Point
```bash
# Tell hostapd where to find config
sudo nano /etc/default/hostapd
# Uncomment and edit: DAEMON_CONF="/etc/hostapd/hostapd.conf"

# Enable IP forwarding
sudo nano /etc/sysctl.conf
# Uncomment: net.ipv4.ip_forward=1

# Configure iptables for NAT (if internet sharing needed)
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
sudo iptables -A FORWARD -i eth0 -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
sudo iptables -A FORWARD -i wlan0 -o eth0 -j ACCEPT
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"

# Auto-restore iptables on boot
sudo nano /etc/rc.local
# Add before "exit 0": iptables-restore < /etc/iptables.ipv4.nat

# Enable services
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq

# Reboot to apply changes
sudo reboot
```

### 1.6 Setup Environment
```bash
# Add to ~/.bashrc
echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc
source ~/.bashrc

# Create workspace
mkdir -p ~/multirobot_ws/src
cd ~/multirobot_ws
```

### 1.7 Install micro-ROS Agent
```bash
# Install micro-ROS
cd ~/multirobot_ws/src
git clone -b foxy https://github.com/micro-ROS/micro_ros_setup.git
cd ~/multirobot_ws
colcon build
source install/local_setup.bash

# Create micro-ROS agent
ros2 run micro_ros_setup create_agent_ws.sh
ros2 run micro_ros_setup build_agent.sh
source install/local_setup.bash
```

## 2. ROS2 Package for Multi-Robot Navigation

### 2.1 Create Package
```bash
cd ~/multirobot_ws/src
ros2 pkg create --build-type ament_python multirobot_nav --dependencies rclpy sensor_msgs geometry_msgs nav_msgs tf2_ros tf2_geometry_msgs laser_geometry
```

### 2.2 Package Structure
```
multirobot_nav/
├── package.xml
├── setup.py
├── setup.cfg
├── multirobot_nav/
│   ├── __init__.py
│   ├── robot_coordinator.py
│   ├── multi_robot_slam.py
│   ├── robot_controller.py
│   └── map_merger.py
├── launch/
│   ├── multirobot_launch.py
│   ├── robot1_launch.py
│   └── robot2_launch.py
└── config/
    ├── robot_params.yaml
    └── slam_params.yaml
```

### 2.3 Robot Coordinator Node
```python
# multirobot_nav/robot_coordinator.py
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped, PoseWithCovarianceStamped
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import OccupancyGrid, Odometry
from std_msgs.msg import String, Bool
import math
import numpy as np
import json

class RobotCoordinator(Node):
    def __init__(self):
        super().__init__('robot_coordinator')
        
        # Parameters
        self.declare_parameter('coordination_strategy', 'frontier_based')
        self.declare_parameter('min_robot_distance', 1.0)
        self.declare_parameter('exploration_complete_threshold', 0.95)
        
        self.coordination_strategy = self.get_parameter('coordination_strategy').value
        self.min_robot_distance = self.get_parameter('min_robot_distance').value
        self.exploration_threshold = self.get_parameter('exploration_complete_threshold').value
        
        # Publishers for robot commands
        self.robot1_cmd_pub = self.create_publisher(Twist, '/robot1/cmd_vel', 10)
        self.robot2_cmd_pub = self.create_publisher(Twist, '/robot2/cmd_vel', 10)
        self.robot1_goal_pub = self.create_publisher(PoseStamped, '/robot1/goal_pose', 10)
        self.robot2_goal_pub = self.create_publisher(PoseStamped, '/robot2/goal_pose', 10)
        
        # Subscribers for robot states
        self.robot1_odom_sub = self.create_subscription(
            Odometry, '/robot1/odom', self.robot1_odom_callback, 10)
        self.robot2_odom_sub = self.create_subscription(
            Odometry, '/robot2/odom', self.robot2_odom_callback, 10)
        self.robot1_scan_sub = self.create_subscription(
            LaserScan, '/robot1/scan', self.robot1_scan_callback, 10)
        self.robot2_scan_sub = self.create_subscription(
            LaserScan, '/robot2/scan', self.robot2_scan_callback, 10)
        self.map_sub = self.create_subscription(
            OccupancyGrid, '/map', self.map_callback, 10)
        
        # Robot states
        self.robot1_pose = None
        self.robot2_pose = None
        self.robot1_scan = None
        self.robot2_scan = None
        self.current_map = None
        self.exploration_frontiers = []
        self.robot1_goal = None
        self.robot2_goal = None
        
        # Coordination timer
        self.coordination_timer = self.create_timer(1.0, self.coordinate_robots)
        
        # Safety timer for collision avoidance
        self.safety_timer = self.create_timer(0.1, self.safety_check)
        
        self.get_logger().info('Robot Coordinator initialized')

    def robot1_odom_callback(self, msg):
        self.robot1_pose = msg.pose.pose

    def robot2_odom_callback(self, msg):
        self.robot2_pose = msg.pose.pose

    def robot1_scan_callback(self, msg):
        self.robot1_scan = msg

    def robot2_scan_callback(self, msg):
        self.robot2_scan = msg

    def map_callback(self, msg):
        self.current_map = msg
        self.find_exploration_frontiers()

    def find_exploration_frontiers(self):
        if self.current_map is None:
            return
        
        frontiers = []
        width = self.current_map.info.width
        height = self.current_map.info.height
        resolution = self.current_map.info.resolution
        origin_x = self.current_map.info.origin.position.x
        origin_y = self.current_map.info.origin.position.y
        
        # Find frontier cells (unknown cells adjacent to free space)
        for y in range(1, height-1):
            for x in range(1, width-1):
                index = y * width + x
                if self.current_map.data[index] == -1:  # Unknown cell
                    # Check if adjacent to known free space
                    adjacent_free = False
                    for dx in [-1, 0, 1]:
                        for dy in [-1, 0, 1]:
                            if dx == 0 and dy == 0:
                                continue
                            adj_index = (y+dy) * width + (x+dx)
                            if 0 <= adj_index < len(self.current_map.data):
                                if self.current_map.data[adj_index] == 0:  # Free space
                                    adjacent_free = True
                                    break
                        if adjacent_free:
                            break
                    
                    if adjacent_free:
                        # Convert to world coordinates
                        world_x = x * resolution + origin_x
                        world_y = y * resolution + origin_y
                        frontiers.append((world_x, world_y))
        
        # Cluster frontiers and find representative points
        self.exploration_frontiers = self.cluster_frontiers(frontiers)

    def cluster_frontiers(self, frontiers, cluster_distance=1.0):
        if not frontiers:
            return []
        
        clusters = []
        used = set()
        
        for i, frontier in enumerate(frontiers):
            if i in used:
                continue
            
            cluster = [frontier]
            used.add(i)
            
            for j, other_frontier in enumerate(frontiers):
                if j in used:
                    continue
                
                dist = math.sqrt((frontier[0] - other_frontier[0])**2 + 
                               (frontier[1] - other_frontier[1])**2)
                if dist < cluster_distance:
                    cluster.append(other_frontier)
                    used.add(j)
            
            if len(cluster) >= 3:  # Only consider significant frontiers
                # Find centroid of cluster
                center_x = sum(f[0] for f in cluster) / len(cluster)
                center_y = sum(f[1] for f in cluster) / len(cluster)
                clusters.append((center_x, center_y))
        
        return clusters

    def coordinate_robots(self):
        if not all([self.robot1_pose, self.robot2_pose, self.exploration_frontiers]):
            return
        
        # Check if exploration is complete
        if self.is_exploration_complete():
            self.stop_robots()
            self.get_logger().info('Exploration complete!')
            return
        
        # Assign goals to robots based on strategy
        if self.coordination_strategy == 'frontier_based':
            self.assign_frontier_goals()
        elif self.coordination_strategy == 'zone_based':
            self.assign_zone_goals()

    def assign_frontier_goals(self):
        if len(self.exploration_frontiers) == 0:
            return
        
        robot1_pos = (self.robot1_pose.position.x, self.robot1_pose.position.y)
        robot2_pos = (self.robot2_pose.position.x, self.robot2_pose.position.y)
        
        # Find best frontier assignments to minimize total distance while maintaining separation
        best_assignment = None
        min_cost = float('inf')
        
        for i, frontier1 in enumerate(self.exploration_frontiers):
            for j, frontier2 in enumerate(self.exploration_frontiers):
                if i == j:
                    continue
                
                # Calculate distances
                dist1_to_f1 = math.sqrt((robot1_pos[0] - frontier1[0])**2 + 
                                      (robot1_pos[1] - frontier1[1])**2)
                dist2_to_f2 = math.sqrt((robot2_pos[0] - frontier2[0])**2 + 
                                      (robot2_pos[1] - frontier2[1])**2)
                
                # Check minimum separation between target frontiers
                frontier_dist = math.sqrt((frontier1[0] - frontier2[0])**2 + 
                                        (frontier1[1] - frontier2[1])**2)
                
                if frontier_dist < self.min_robot_distance:
                    continue
                
                total_cost = dist1_to_f1 + dist2_to_f2
                if total_cost < min_cost:
                    min_cost = total_cost
                    best_assignment = (frontier1, frontier2)
        
        if best_assignment:
            self.send_goal_to_robot('robot1', best_assignment[0])
            self.send_goal_to_robot('robot2', best_assignment[1])
            
            # Remove assigned frontiers
            if best_assignment[0] in self.exploration_frontiers:
                self.exploration_frontiers.remove(best_assignment[0])
            if best_assignment[1] in self.exploration_frontiers:
                self.exploration_frontiers.remove(best_assignment[1])

    def send_goal_to_robot(self, robot_name, goal_pos):
        goal_msg = PoseStamped()
        goal_msg.header.stamp = self.get_clock().now().to_msg()
        goal_msg.header.frame_id = 'map'
        goal_msg.pose.position.x = goal_pos[0]
        goal_msg.pose.position.y = goal_pos[1]
        goal_msg.pose.position.z = 0.0
        goal_msg.pose.orientation.w = 1.0
        
        if robot_name == 'robot1':
            self.robot1_goal_pub.publish(goal_msg)
            self.robot1_goal = goal_pos
        elif robot_name == 'robot2':
            self.robot2_goal_pub.publish(goal_msg)
            self.robot2_goal = goal_pos
        
        self.get_logger().info(f'Sent goal to {robot_name}: ({goal_pos[0]:.2f}, {goal_pos[1]:.2f})')

    def safety_check(self):
        if not all([self.robot1_pose, self.robot2_pose]):
            return
        
        # Check distance between robots
        dist = math.sqrt((self.robot1_pose.position.x - self.robot2_pose.position.x)**2 + 
                        (self.robot1_pose.position.y - self.robot2_pose.position.y)**2)
        
        if dist < self.min_robot_distance:
            # Stop both robots if too close
            self.emergency_stop()
            self.get_logger().warn(f'Robots too close ({dist:.2f}m)! Emergency stop activated.')

    def emergency_stop(self):
        stop_msg = Twist()
        self.robot1_cmd_pub.publish(stop_msg)
        self.robot2_cmd_pub.publish(stop_msg)

    def stop_robots(self):
        stop_msg = Twist()
        self.robot1_cmd_pub.publish(stop_msg)
        self.robot2_cmd_pub.publish(stop_msg)

    def is_exploration_complete(self):
        if self.current_map is None:
            return False
        
        total_cells = len(self.current_map.data)
        known_cells = sum(1 for cell in self.current_map.data if cell != -1)
        exploration_ratio = known_cells / total_cells if total_cells > 0 else 0
        
        return exploration_ratio >= self.exploration_threshold

def main(args=None):
    rclpy.init(args=args)
    node = RobotCoordinator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

### 1.1 Install ROS2 Foxy
```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install ROS2 Foxy
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt install curl gnupg lsb-release
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

sudo apt update
sudo apt install ros-foxy-desktop python3-argcomplete
sudo apt install ros-foxy-rmw-micro-xrce-dds

# Install additional packages
sudo apt install python3-colcon-common-extensions
sudo apt install ros-foxy-nav2-bringup
sudo apt install ros-foxy-navigation2
sudo apt install ros-foxy-nav2-map-server
sudo apt install ros-foxy-slam-toolbox
```

### 1.2 Setup WiFi Access Point
```bash
# Install hostapd and dnsmasq
sudo apt install hostapd dnsmasq

# Stop services
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq

# Configure static IP for wlan0
sudo nano /etc/dhcpcd.conf
# Add at the end:
# interface wlan0
# static ip_address=192.168.4.1/24
# nohook wpa_supplicant

# Configure dnsmasq
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
sudo nano /etc/dnsmasq.conf
```

### 1.3 dnsmasq Configuration
```bash
# /etc/dnsmasq.conf
interface=wlan0
dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h
```

### 1.4 hostapd Configuration
```bash
sudo nano /etc/hostapd/hostapd.conf
```

```
# /etc/hostapd/hostapd.conf
interface=wlan0
driver=nl80211
ssid=LiDAR_RobotNet
hw_mode=g
channel=7
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=lidar123456
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
```

### 1.5 Enable WiFi Access Point
```bash
# Tell hostapd where to find config
sudo nano /etc/default/hostapd
# Uncomment and edit: DAEMON_CONF="/etc/hostapd/hostapd.conf"

# Enable IP forwarding
sudo nano /etc/sysctl.conf
# Uncomment: net.ipv4.ip_forward=1

# Configure iptables for NAT (if internet sharing needed)
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
sudo iptables -A FORWARD -i eth0 -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
sudo iptables -A FORWARD -i wlan0 -o eth0 -j ACCEPT
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"

# Auto-restore iptables on boot
sudo nano /etc/rc.local
# Add before "exit 0": iptables-restore < /etc/iptables.ipv4.nat

# Enable services
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq

# Reboot to apply changes
sudo reboot
```

### 1.6 Setup Environment
```bash
# Add to ~/.bashrc
echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc
source ~/.bashrc

# Create workspace
mkdir -p ~/lidar_ws/src
cd ~/lidar_ws
```

### 1.7 Install micro-ROS Agent
```bash
# Install micro-ROS
cd ~/lidar_ws/src
git clone -b foxy https://github.com/micro-ROS/micro_ros_setup.git
cd ~/lidar_ws
colcon build
source install/local_setup.bash

# Create micro-ROS agent
ros2 run micro_ros_setup create_agent_ws.sh
ros2 run micro_ros_setup build_agent.sh
source install/local_setup.bash
```

## 2. ROS2 Package for Multi-LiDAR Integration

### 2.1 Create Package
```bash
cd ~/lidar_ws/src
ros2 pkg create --build-type ament_python multi_lidar_nav --dependencies rclpy sensor_msgs geometry_msgs nav_msgs tf2_ros tf2_geometry_msgs laser_geometry
```

### 2.2 Package Structure
```
multi_lidar_nav/
├── package.xml
├── setup.py
├── setup.cfg
├── multi_lidar_nav/
│   ├── __init__.py
│   ├── lidar_merger.py
│   ├── map_updater.py
│   └── navigation_controller.py
├── launch/
│   ├── multi_lidar_launch.py
│   └── navigation_launch.py
└── config/
    ├── nav2_params.yaml
    └── lidar_config.yaml
```

### 2.3 LiDAR Merger Node
```python
# multi_lidar_nav/lidar_merger.py
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan, PointCloud2
from geometry_msgs.msg import TransformStamped
import tf2_ros
import tf2_geometry_msgs
from laser_geometry import LaserProjection
import numpy as np
import math

class LidarMerger(Node):
    def __init__(self):
        super().__init__('lidar_merger')
        
        # Parameters
        self.declare_parameter('lidar1_frame', 'lidar1_link')
        self.declare_parameter('lidar2_frame', 'lidar2_link')
        self.declare_parameter('merged_frame', 'base_link')
        self.declare_parameter('max_range', 12.0)
        self.declare_parameter('min_range', 0.15)
        
        self.lidar1_frame = self.get_parameter('lidar1_frame').value
        self.lidar2_frame = self.get_parameter('lidar2_frame').value
        self.merged_frame = self.get_parameter('merged_frame').value
        self.max_range = self.get_parameter('max_range').value
        self.min_range = self.get_parameter('min_range').value
        
        # Subscribers
        self.lidar1_sub = self.create_subscription(
            LaserScan, '/lidar1/scan', self.lidar1_callback, 10)
        self.lidar2_sub = self.create_subscription(
            LaserScan, '/lidar2/scan', self.lidar2_callback, 10)
        
        # Publisher
        self.merged_pub = self.create_publisher(LaserScan, '/scan', 10)
        
        # TF
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)
        
        # Laser projection
        self.laser_proj = LaserProjection()
        
        # Data storage
        self.lidar1_data = None
        self.lidar2_data = None
        
        self.get_logger().info('LiDAR Merger Node initialized')

    def lidar1_callback(self, msg):
        self.lidar1_data = msg
        self.merge_scans()

    def lidar2_callback(self, msg):
        self.lidar2_data = msg
        self.merge_scans()

    def merge_scans(self):
        if self.lidar1_data is None or self.lidar2_data is None:
            return
        
        try:
            # Transform both scans to base_link frame
            transformed_scan1 = self.transform_scan(self.lidar1_data, self.lidar1_frame)
            transformed_scan2 = self.transform_scan(self.lidar2_data, self.lidar2_frame)
            
            if transformed_scan1 is None or transformed_scan2 is None:
                return
            
            # Merge the scans
            merged_scan = self.create_merged_scan(transformed_scan1, transformed_scan2)
            self.merged_pub.publish(merged_scan)
            
        except Exception as e:
            self.get_logger().error(f'Error merging scans: {e}')

    def transform_scan(self, scan, source_frame):
        try:
            # Get transform
            transform = self.tf_buffer.lookup_transform(
                self.merged_frame, source_frame, rclpy.time.Time())
            
            # Convert scan to points and transform
            points = []
            for i, range_val in enumerate(scan.ranges):
                if self.min_range <= range_val <= self.max_range:
                    angle = scan.angle_min + i * scan.angle_increment
                    x = range_val * math.cos(angle)
                    y = range_val * math.sin(angle)
                    
                    # Transform point
                    point_stamped = tf2_geometry_msgs.PointStamped()
                    point_stamped.header.frame_id = source_frame
                    point_stamped.point.x = x
                    point_stamped.point.y = y
                    point_stamped.point.z = 0.0
                    
                    transformed_point = tf2_geometry_msgs.do_transform_point(
                        point_stamped, transform)
                    
                    points.append((transformed_point.point.x, 
                                 transformed_point.point.y, 
                                 range_val, angle))
            
            return points
            
        except Exception as e:
            self.get_logger().warn(f'Transform failed: {e}')
            return None

    def create_merged_scan(self, points1, points2):
        # Combine all points
        all_points = points1 + points2
        
        # Create merged scan message
        merged_scan = LaserScan()
        merged_scan.header.stamp = self.get_clock().now().to_msg()
        merged_scan.header.frame_id = self.merged_frame
        
        # Set scan parameters
        merged_scan.angle_min = -math.pi
        merged_scan.angle_max = math.pi
        merged_scan.angle_increment = math.pi / 180.0  # 1 degree resolution
        merged_scan.time_increment = 0.0
        merged_scan.scan_time = 0.1
        merged_scan.range_min = self.min_range
        merged_scan.range_max = self.max_range
        
        # Initialize ranges array
        num_readings = int((merged_scan.angle_max - merged_scan.angle_min) / 
                          merged_scan.angle_increment) + 1
        ranges = [float('inf')] * num_readings
        
        # Fill ranges array with closest points
        for x, y, range_val, _ in all_points:
            angle = math.atan2(y, x)
            if angle < 0:
                angle += 2 * math.pi
            
            index = int((angle - merged_scan.angle_min) / merged_scan.angle_increment)
            if 0 <= index < num_readings:
                current_range = math.sqrt(x*x + y*y)
                if current_range < ranges[index]:
                    ranges[index] = current_range
        
        # Replace inf values with max_range
        ranges = [self.max_range if r == float('inf') else r for r in ranges]
        merged_scan.ranges = ranges
        
        return merged_scan

def main(args=None):
    rclpy.init(args=args)
    node = LidarMerger()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

### 2.4 Navigation Controller
```python
# multi_lidar_nav/navigation_controller.py
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import OccupancyGrid, Odometry
from std_msgs.msg import String
import math
import numpy as np

class NavigationController(Node):
    def __init__(self):
        super().__init__('navigation_controller')
        
        # Parameters
        self.declare_parameter('linear_speed', 0.2)
        self.declare_parameter('angular_speed', 0.5)
        self.declare_parameter('safe_distance', 0.3)
        self.declare_parameter('exploration_mode', True)
        
        self.linear_speed = self.get_parameter('linear_speed').value
        self.angular_speed = self.get_parameter('angular_speed').value
        self.safe_distance = self.get_parameter('safe_distance').value
        self.exploration_mode = self.get_parameter('exploration_mode').value
        
        # Publishers
        self.cmd_vel_pub = self.create_publisher(Twist, '/cmd_vel', 10)
        self.goal_pub = self.create_publisher(PoseStamped, '/goal_pose', 10)
        
        # Subscribers
        self.scan_sub = self.create_subscription(
            LaserScan, '/scan', self.scan_callback, 10)
        self.odom_sub = self.create_subscription(
            Odometry, '/odom', self.odom_callback, 10)
        self.map_sub = self.create_subscription(
            OccupancyGrid, '/map', self.map_callback, 10)
        
        # State variables
        self.current_scan = None
        self.current_pose = None
        self.current_map = None
        self.exploration_points = []
        self.current_goal = None
        
        # Navigation timer
        self.nav_timer = self.create_timer(0.1, self.navigation_loop)
        
        self.get_logger().info('Navigation Controller initialized')

    def scan_callback(self, msg):
        self.current_scan = msg

    def odom_callback(self, msg):
        self.current_pose = msg.pose.pose

    def map_callback(self, msg):
        self.current_map = msg
        if self.exploration_mode:
            self.find_exploration_frontiers()

    def find_exploration_frontiers(self):
        if self.current_map is None:
            return
        
        # Simple frontier detection
        frontiers = []
        width = self.current_map.info.width
        height = self.current_map.info.height
        
        for y in range(1, height-1):
            for x in range(1, width-1):
                index = y * width + x
                if self.current_map.data[index] == -1:  # Unknown cell
                    # Check if adjacent to known free space
                    adjacent_free = False
                    for dx in [-1, 0, 1]:
                        for dy in [-1, 0, 1]:
                            adj_index = (y+dy) * width + (x+dx)
                            if self.current_map.data[adj_index] == 0:
                                adjacent_free = True
                                break
                        if adjacent_free:
                            break
                    
                    if adjacent_free:
                        # Convert to world coordinates
                        world_x = x * self.current_map.info.resolution + self.current_map.info.origin.position.x
                        world_y = y * self.current_map.info.resolution + self.current_map.info.origin.position.y
                        frontiers.append((world_x, world_y))
        
        self.exploration_points = frontiers

    def navigation_loop(self):
        if self.current_scan is None or self.current_pose is None:
            return
        
        if self.exploration_mode:
            self.exploration_behavior()
        else:
            self.obstacle_avoidance()

    def exploration_behavior(self):
        # If no current goal or reached goal, find new exploration point
        if self.current_goal is None or self.reached_goal():
            if self.exploration_points:
                # Find closest unexplored point
                min_dist = float('inf')
                best_point = None
                current_x = self.current_pose.position.x
                current_y = self.current_pose.position.y
                
                for point in self.exploration_points:
                    dist = math.sqrt((point[0] - current_x)**2 + (point[1] - current_y)**2)
                    if dist < min_dist:
                        min_dist = dist
                        best_point = point
                
                if best_point:
                    self.set_goal(best_point[0], best_point[1])
        
        # Move towards goal while avoiding obstacles
        self.move_to_goal_with_avoidance()

    def obstacle_avoidance(self):
        if self.current_scan is None:
            return
        
        # Simple obstacle avoidance
        cmd = Twist()
        
        # Check for obstacles in front
        front_ranges = self.current_scan.ranges[len(self.current_scan.ranges)//3:2*len(self.current_scan.ranges)//3]
        min_front_dist = min(front_ranges) if front_ranges else float('inf')
        
        if min_front_dist > self.safe_distance:
            # Move forward
            cmd.linear.x = self.linear_speed
        else:
            # Turn to find clear path
            left_ranges = self.current_scan.ranges[:len(self.current_scan.ranges)//4]
            right_ranges = self.current_scan.ranges[3*len(self.current_scan.ranges)//4:]
            
            left_clear = min(left_ranges) if left_ranges else 0
            right_clear = min(right_ranges) if right_ranges else 0
            
            if left_clear > right_clear:
                cmd.angular.z = self.angular_speed
            else:
                cmd.angular.z = -self.angular_speed
        
        self.cmd_vel_pub.publish(cmd)

    def move_to_goal_with_avoidance(self):
        if self.current_goal is None:
            return
        
        cmd = Twist()
        
        # Calculate angle to goal
        dx = self.current_goal[0] - self.current_pose.position.x
        dy = self.current_goal[1] - self.current_pose.position.y
        goal_angle = math.atan2(dy, dx)
        
        # Get current yaw
        current_yaw = self.get_yaw_from_pose(self.current_pose)
        angle_diff = self.normalize_angle(goal_angle - current_yaw)
        
        # Check for obstacles
        front_ranges = self.current_scan.ranges[len(self.current_scan.ranges)//3:2*len(self.current_scan.ranges)//3]
        min_front_dist = min(front_ranges) if front_ranges else float('inf')
        
        if min_front_dist > self.safe_distance and abs(angle_diff) < 0.3:
            # Move towards goal
            cmd.linear.x = self.linear_speed
            cmd.angular.z = 0.5 * angle_diff
        else:
            # Obstacle avoidance
            self.obstacle_avoidance()
            return
        
        self.cmd_vel_pub.publish(cmd)

    def set_goal(self, x, y):
        self.current_goal = (x, y)
        
        # Publish goal for visualization
        goal_msg = PoseStamped()
        goal_msg.header.stamp = self.get_clock().now().to_msg()
        goal_msg.header.frame_id = 'map'
        goal_msg.pose.position.x = x
        goal_msg.pose.position.y = y
        goal_msg.pose.orientation.w = 1.0
        
        self.goal_pub.publish(goal_msg)

    def reached_goal(self):
        if self.current_goal is None:
            return True
        
        dist = math.sqrt((self.current_goal[0] - self.current_pose.position.x)**2 + 
                        (self.current_goal[1] - self.current_pose.position.y)**2)
        return dist < 0.5

    def get_yaw_from_pose(self, pose):
        # Convert quaternion to yaw
        siny_cosp = 2 * (pose.orientation.w * pose.orientation.z + 
                        pose.orientation.x * pose.orientation.y)
        cosy_cosp = 1 - 2 * (pose.orientation.y * pose.orientation.y + 
                            pose.orientation.z * pose.orientation.z)
        return math.atan2(siny_cosp, cosy_cosp)

    def normalize_angle(self, angle):
        while angle > math.pi:
            angle -= 2 * math.pi
        while angle < -math.pi:
            angle += 2 * math.pi
        return angle

def main(args=None):
    rclpy.init(args=args)
    node = NavigationController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

### 2.5 Launch Files
```python
# launch/multi_lidar_launch.py
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        # micro-ROS agent for WiFi communication
        Node(
            package='micro_ros_agent',
            executable='micro_ros_agent',
            arguments=['udp4', '--port', '8888'],
            name='micro_ros_agent_lidar1'
        ),
        
        # Second micro-ROS agent for second LiDAR (different port)
        Node(
            package='micro_ros_agent',
            executable='micro_ros_agent',
            arguments=['udp4', '--port', '8889'],
            name='micro_ros_agent_lidar2'
        ),
        
        # LiDAR merger
        Node(
            package='multi_lidar_nav',
            executable='lidar_merger',
            name='lidar_merger',
            parameters=[{
                'lidar1_frame': 'lidar1_link',
                'lidar2_frame': 'lidar2_link',
                'merged_frame': 'base_link',
                'max_range': 12.0,
                'min_range': 0.15
            }]
        ),
        
        # Navigation controller
        Node(
            package='multi_lidar_nav',
            executable='navigation_controller',
            name='navigation_controller',
            parameters=[{
                'linear_speed': 0.2,
                'angular_speed': 0.5,
                'safe_distance': 0.3,
                'exploration_mode': True
            }]
        ),
        
        # SLAM Toolbox
        Node(
            package='slam_toolbox',
            executable='sync_slam_toolbox_node',
            name='slam_toolbox',
            parameters=[{
                'use_sim_time': False,
                'base_frame': 'base_link',
                'odom_frame': 'odom',
                'map_frame': 'map',
                'scan_topic': '/scan'
            }]
        ),
        
        # Static transform publishers
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0.15', '0.1', '0', '0', '0', 'base_link', 'lidar1_link']
        ),
        
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '-0.15', '0.1', '3.14159', '0', '0', 'base_link', 'lidar2_link']
        ),
        
        # WiFi network status monitor
        ExecuteProcess(
            cmd=['python3', '-c', '''
import subprocess
import time
while True:
    try:
        result = subprocess.run(["iwconfig", "wlan0"], capture_output=True, text=True)
        if "LiDAR_RobotNet" in result.stdout:
            print("WiFi AP Active: LiDAR_RobotNet")
        else:
            print("WiFi AP Issue - Check hostapd")
        time.sleep(30)
    except:
        pass
            '''],
            shell=True,
            name='wifi_monitor'
        )
    ])
```

### 2.6 Setup Files
```python
# setup.py
from setuptools import setup
import os
from glob import glob

package_name = 'multi_lidar_nav'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='your_name',
    maintainer_email='your_email@example.com',
    description='Multi-LiDAR navigation package',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'lidar_merger = multi_lidar_nav.lidar_merger:main',
            'navigation_controller = multi_lidar_nav.navigation_controller:main',
        ],
    },
)
```

```xml
<!-- package.xml -->
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypelevel="1"?>
<package format="3">
  <name>multi_lidar_nav</name>
  <version>0.0.0</version>
  <description>Multi-LiDAR navigation package</description>
  <maintainer email="your_email@example.com">your_name</maintainer>
  <license>MIT</license>

  <depend>rclpy</depend>
  <depend>sensor_msgs</depend>
  <depend>geometry_msgs</depend>
  <depend>nav_msgs</depend>
  <depend>tf2_ros</depend>
  <depend>tf2_geometry_msgs</depend>
  <depend>laser_geometry</depend>

  <test_depend>ament_copyright</test_depend>
  <test_depend>ament_flake8</test_depend>
  <test_depend>ament_pep257</test_depend>
  <test_depend>python3-pytest</test_depend>

  <export>
    <build_type>ament_python</build_type>
  </export>
</package>
```

## 3. ESP32 micro-ROS Code for LD19 LiDAR (WiFi Version)

### 3.1 Arduino IDE Setup
```bash
# Install ESP32 board in Arduino IDE
# Install micro-ROS library from library manager
# Install WiFi library (usually included with ESP32 core)
```

### 3.2 ESP32 LiDAR Node 1 Code
```cpp
// ESP32_LD19_WiFi_Node1.ino
#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <sensor_msgs/msg/laser_scan.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi Configuration
const char* ssid = "LiDAR_RobotNet";
const char* password = "lidar123456";
const char* agent_ip = "192.168.4.1";  // Raspberry Pi IP
const int agent_port = 8888;            // micro-ROS agent port for LiDAR 1

// LiDAR configuration
#define LIDAR_SERIAL Serial2
#define LIDAR_BAUDRATE 230400
#define LIDAR_RX_PIN 16
#define LIDAR_TX_PIN 17

// LED for status indication
#define STATUS_LED 2

// Packet structure from LD19 manual
#define POINT_PER_PACK 12
#define HEADER 0x54

typedef struct __attribute__((packed)) {
    uint16_t distance;
    uint8_t intensity;
} LidarPointStructDef;

typedef struct __attribute__((packed)) {
    uint8_t header;
    uint8_t ver_len;
    uint16_t speed;
    uint16_t start_angle;
    LidarPointStructDef point[POINT_PER_PACK];
    uint16_t end_angle;
    uint16_t timestamp;
    uint8_t crc8;
} LiDARFrameTypeDef;

// micro-ROS entities
rcl_publisher_t publisher;
sensor_msgs__msg__LaserScan scan_msg;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// LiDAR data
float ranges[360];
float intensities[360];
bool new_scan_ready = false;
bool wifi_connected = false;
bool micro_ros_connected = false;

// Connection status
unsigned long last_wifi_check = 0;
unsigned long last_status_blink = 0;
bool status_led_state = false;

// CRC table from LD19 manual (abbreviated for space)
static const uint8_t CrcTable[256] = {
    0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3, 0xae, 0xf2, 0xbf, 0x68, 0x25, 0x8b, 0xc6, 0x11, 0x5c,
    0xa9, 0xe4, 0x33, 0x7e, 0xd0, 0x9d, 0x4a, 0x07, 0x5b, 0x16, 0xc1, 0x8c, 0x22, 0x6f, 0xb8, 0xf5,
    // ... (complete CRC table - truncated for brevity, include full table from manual)
};

uint8_t CalCRC8(uint8_t *p, uint8_t len) {
    uint8_t crc = 0;
    uint16_t i;
    for (i = 0; i < len; i++) {
        crc = CrcTable[(crc ^ *p++) & 0xff];
    }
    return crc;
}

// Custom transport for WiFi
bool transport_open(struct uxrCustomTransport* transport) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    return udp->begin(2019);
}

bool transport_close(struct uxrCustomTransport* transport) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    udp->stop();
    return true;
}

size_t transport_write(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, uint8_t* err) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    udp->beginPacket(agent_ip, agent_port);
    size_t sent = udp->write(buf, len);
    udp->endPacket();
    return sent;
}

size_t transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    
    uint32_t start_time = millis();
    while (millis() - start_time < timeout) {
        int packet_size = udp->parsePacket();
        if (packet_size > 0) {
            size_t bytes_read = udp->read(buf, len);
            return bytes_read;
        }
        delay(1);
    }
    return 0;
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL && new_scan_ready && micro_ros_connected) {
        publish_scan();
        new_scan_ready = false;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(STATUS_LED, OUTPUT);
    
    // Initialize LiDAR serial
    LIDAR_SERIAL.begin(LIDAR_BAUDRATE, SERIAL_8N1, LIDAR_RX_PIN, LIDAR_TX_PIN);
    
    // Initialize ranges array
    for (int i = 0; i < 360; i++) {
        ranges[i] = 12.0; // Max range
        intensities[i] = 0.0;
    }
    
    // Connect to WiFi
    connect_wifi();
    
    // Setup micro-ROS
    if (wifi_connected) {
        setup_micro_ros();
    }
    
    Serial.println("LD19 LiDAR Node 1 WiFi initialized");
}

void loop() {
    // Check WiFi connection
    check_wifi_status();
    
    // Read LiDAR data
    read_lidar_data();
    
    // Process micro-ROS if connected
    if (micro_ros_connected) {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
    }
    
    // Update status LED
    update_status_led();
    
    delay(1);
}

void connect_wifi() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        wifi_connected = true;
        Serial.println();
        Serial.print("WiFi connected! IP: ");
        Serial.println(WiFi.localIP());
    } else {
        wifi_connected = false;
        Serial.println();
        Serial.println("WiFi connection failed!");
    }
}

void check_wifi_status() {
    unsigned long now = millis();
    if (now - last_wifi_check > 5000) { // Check every 5 seconds
        if (WiFi.status() != WL_CONNECTED && wifi_connected) {
            wifi_connected = false;
            micro_ros_connected = false;
            Serial.println("WiFi disconnected! Attempting reconnection...");
            connect_wifi();
        } else if (WiFi.status() == WL_CONNECTED && !wifi_connected) {
            wifi_connected = true;
            Serial.println("WiFi reconnected!");
            setup_micro_ros();
        }
        last_wifi_check = now;
    }
}

void setup_micro_ros() {
    if (!wifi_connected) return;
    
    // Custom WiFi transport
    static WiFiUDP udp;
    rmw_uros_set_custom_transport(
        false, // framing disabled
        (void *) &udp,
        transport_open,
        transport_close,
        transport_write,
        transport_read
    );
    
    allocator = rcl_get_default_allocator();
    
    // Create init_options
    rcl_ret_t ret = rclc_support_init(&support, 0, NULL, &allocator);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize support");
        return;
    }
    
    // Create node
    ret = rclc_node_init_default(&node, "lidar1_node", "", &support);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize node");
        return;
    }
    
    // Create publisher
    ret = rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
        "lidar1/scan");
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize publisher");
        return;
    }
    
    // Create timer
    const unsigned int timer_timeout = 100; // 10Hz
    ret = rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize timer");
        return;
    }
    
    // Create executor
    ret = rclc_executor_init(&executor, &support.context, 1, &allocator);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize executor");
        return;
    }
    
    ret = rclc_executor_add_timer(&executor, &timer);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to add timer to executor");
        return;
    }
    
    // Initialize scan message
    scan_msg.header.frame_id.data = "lidar1_link";
    scan_msg.header.frame_id.size = strlen("lidar1_link");
    scan_msg.header.frame_id.capacity = scan_msg.header.frame_id.size + 1;
    
    scan_msg.angle_min = 0.0;
    scan_msg.angle_max = 2.0 * M_PI;
    scan_msg.angle_increment = M_PI / 180.0; // 1 degree
    scan_msg.time_increment = 0.0;
    scan_msg.scan_time = 0.1;
    scan_msg.range_min = 0.15;
    scan_msg.range_max = 12.0;
    
    scan_msg.ranges.data = ranges;
    scan_msg.ranges.size = 360;
    scan_msg.ranges.capacity = 360;
    
    scan_msg.intensities.data = intensities;
    scan_msg.intensities.size = 360;
    scan_msg.intensities.capacity = 360;
    
    micro_ros_connected = true;
    Serial.println("micro-ROS initialized successfully");
}

void read_lidar_data() {
    static uint8_t buffer[47]; // Size of LiDAR frame
    static int buffer_index = 0;
    static bool frame_started = false;
    
    while (LIDAR_SERIAL.available()) {
        uint8_t byte = LIDAR_SERIAL.read();
        
        if (!frame_started && byte == HEADER) {
            frame_started = true;
            buffer[0] = byte;
            buffer_index = 1;
        } else if (frame_started) {
            buffer[buffer_index++] = byte;
            
            if (buffer_index >= 47) {
                // Process complete frame
                process_lidar_frame(buffer);
                frame_started = false;
                buffer_index = 0;
            }
        }
    }
}

void process_lidar_frame(uint8_t* buffer) {
    LiDARFrameTypeDef* frame = (LiDARFrameTypeDef*)buffer;
    
    // Verify header and version
    if (frame->header != HEADER || frame->ver_len != 0x2C) {
        return;
    }
    
    // Verify CRC
    uint8_t calculated_crc = CalCRC8(buffer, 46);
    if (calculated_crc != frame->crc8) {
        return;
    }
    
    // Extract angles and distances
    float start_angle = frame->start_angle * 0.01 * M_PI / 180.0; // Convert to radians
    float end_angle = frame->end_angle * 0.01 * M_PI / 180.0;
    
    // Normalize angles
    if (end_angle < start_angle) {
        end_angle += 2 * M_PI;
    }
    
    float angle_step = (end_angle - start_angle) / (POINT_PER_PACK - 1);
    
    for (int i = 0; i < POINT_PER_PACK; i++) {
        float angle = start_angle + i * angle_step;
        if (angle >= 2 * M_PI) {
            angle -= 2 * M_PI;
        }
        
        int angle_index = (int)(angle * 180.0 / M_PI);
        if (angle_index >= 0 && angle_index < 360) {
            float distance = frame->point[i].distance / 1000.0; // Convert mm to meters
            uint8_t intensity = frame->point[i].intensity;
            
            if (distance >= 0.15 && distance <= 12.0) {
                ranges[angle_index] = distance;
                intensities[angle_index] = intensity;
            }
        }
    }
    
    new_scan_ready = true;
}

void publish_scan() {
    if (!micro_ros_connected) return;
    
    // Get current time in microseconds
    int64_t time_us = esp_timer_get_time();
    scan_msg.header.stamp.sec = time_us / 1000000;
    scan_msg.header.stamp.nanosec = (time_us % 1000000) * 1000;
    
    rcl_ret_t ret = rcl_publish(&publisher, &scan_msg, NULL);
    if (ret != RCL_RET_OK) {
        Serial.println("Error publishing scan");
        // Try to reconnect micro-ROS
        micro_ros_connected = false;
        delay(1000);
        setup_micro_ros();
    }
}

void update_status_led() {
    unsigned long now = millis();
    if (now - last_status_blink > 500) {
        status_led_state = !status_led_state;
        
        if (micro_ros_connected) {
            // Solid on when fully connected
            digitalWrite(STATUS_LED, HIGH);
        } else if (wifi_connected) {
            // Slow blink when WiFi connected but micro-ROS not
            digitalWrite(STATUS_LED, status_led_state);
        } else {
            // Fast blink when disconnected
            digitalWrite(STATUS_LED, (now % 200) < 100);
        }
        
        last_status_blink = now;
    }
}
```

## 4. ESP32 Robot 2 Code (LiDAR + M-Bot Integration)

### 4.1 ESP32 Robot 2 Main Code
```cpp
// ESP32_Robot2_Complete.ino
// Same as Robot 1 but with these key changes:

// WiFi Configuration (same network, different hostname)
const char* ssid = "MultiRobot_Network";
const char* password = "multirobot2024";
const char* agent_ip = "192.168.4.1";  // Raspberry Pi IP
const int agent_port = 8889;            // micro-ROS agent port for Robot 2

// In connect_wifi() function:
WiFi.setHostname("robot2");
Serial.print("Robot 2 connecting to WiFi: ");

// In setup_micro_ros() function:
ret = rclc_node_init_default(&node, "robot2_node", "", &support);

// Publishers and subscribers with robot2 namespace:
ret = rclc_publisher_init_default(
    &scan_publisher, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
    "/robot2/scan");

ret = rclc_publisher_init_default(
    &odom_publisher, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry),
    "/robot2/odom");

ret = rclc_subscription_init_default(
    &cmd_vel_subscriber, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "/robot2/cmd_vel");

// In init_messages() function:
scan_msg.header.frame_id.data = "robot2/lidar_link";
scan_msg.header.frame_id.size = strlen("robot2/lidar_link");

odom_msg.header.frame_id.data = "robot2/odom";
odom_msg.header.frame_id.size = strlen("robot2/odom");

odom_msg.child_frame_id.data = "robot2/base_link";
odom_msg.child_frame_id.size = strlen("robot2/base_link");

// All other code remains the same as Robot 1
```

## 5. M-Bot Arduino Code (Updated for Multi-Robot)

### 5.1 M-Bot Code for Both Robots
```cpp
// MBot_MultiRobot.ino (same for both robots)
#include <MeMCore.h>

// Motor and sensor definitions
MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);
MeUltrasonicSensor ultrasonic(PORT_3);
MeBuzzer buzzer;
MeRGBLed rgb(PORT_7);

// Communication with ESP32 (hardware serial)
// ESP32 connects to pins exposed after removing Bluetooth module

// Navigation parameters
float base_speed = 120;
float turn_speed = 150;
float safe_distance = 25.0; // cm
bool autonomous_mode = true;
bool emergency_stop = false;

// Command structure
struct Command {
    char type; // 'M' for move, 'T' for turn, 'S' for stop, 'A' for autonomous
    float value; // speed or angle
};

// Robot identification (set differently for each robot)
const int ROBOT_ID = 1; // Change to 2 for second robot

void setup() {
    Serial.begin(9600); // Communication with ESP32
    
    // Initialize RGB LED
    rgb.setpin(PORT_7);
    if (ROBOT_ID == 1) {
        rgb.setColor(0, 0, 255); // Blue for Robot 1
    } else {
        rgb.setColor(255, 0, 0); // Red for Robot 2
    }
    rgb.show();
    
    buzzer.tone(1000 + (ROBOT_ID * 200), 200); // Different startup sounds
    
    Serial.print("INIT:Robot");
    Serial.println(ROBOT_ID);
    
    delay(1000);
    
    rgb.setColor(0, 255, 0); // Green for ready
    rgb.show();
}

void loop() {
    // Check for commands from ESP32
    if (Serial.available()) {
        Command cmd = read_command();
        execute_command(cmd);
    }
    
    // Autonomous safety check
    if (autonomous_mode && !emergency_stop) {
        safety_check();
    }
    
    // Send sensor data to ESP32
    send_sensor_data();
    
    delay(50);
}

Command read_command() {
    Command cmd;
    String data = Serial.readStringUntil('\n');
    data.trim();
    
    if (data.length() > 0) {
        cmd.type = data.charAt(0);
        if (data.length() > 1) {
            cmd.value = data.substring(1).toFloat();
        } else {
            cmd.value = 0;
        }
    } else {
        cmd.type = 'S';
        cmd.value = 0;
    }
    
    return cmd;
}

void execute_command(Command cmd) {
    switch (cmd.type) {
        case 'M': // Move forward/backward
            if (!emergency_stop) {
                move_robot(cmd.value);
            }
            break;
        case 'T': // Turn left/right
            if (!emergency_stop) {
                turn_robot(cmd.value);
            }
            break;
        case 'S': // Stop
            stop_robot();
            emergency_stop = false;
            break;
        case 'A': // Set autonomous mode
            autonomous_mode = (cmd.value > 0);
            rgb.setColor(autonomous_mode ? 0 : 255, 255, 0);
            rgb.show();
            break;
        case 'E': // Emergency stop
            emergency_stop = true;
            stop_robot();
            rgb.setColor(255, 0, 0); // Red for emergency
            rgb.show();
            buzzer.tone(2000, 100);
            break;
        default:
            stop_robot();
            break;
    }
}

void move_robot(float speed) {
    if (emergency_stop) return;
    
    // Clamp speed
    speed = constrain(speed, -255, 255);
    
    // Check for immediate obstacles before moving
    float distance = ultrasonic.distanceCm();
    if (speed > 0 && distance < safe_distance && distance > 0) {
        stop_robot();
        emergency_stop = true;
        return;
    }
    
    motorLeft.run(speed);
    motorRight.run(speed);
    
    // Visual feedback
    if (speed > 0) {
        rgb.setColor(0, 255, 0); // Green for forward
    } else if (speed < 0) {
        rgb.setColor(255, 165, 0); // Orange for backward
    }
    rgb.show();
}

void turn_robot(float angle) {
    if (emergency_stop) return;
    
    // Convert angle to time-based turn
    float turn_time = abs(angle) * 8; // Calibration factor
    turn_time = constrain(turn_time, 50, 1000); // Limit turn time
    
    if (angle > 0) { // Turn right
        motorLeft.run(turn_speed);
        motorRight.run(-turn_speed * 0.9); // Slight asymmetry for better turning
        rgb.setColor(0, 0, 255); // Blue for right turn
    } else { // Turn left
        motorLeft.run(-turn_speed * 0.9);
        motorRight.run(turn_speed);
        rgb.setColor(255, 255, 0); // Yellow for left turn
    }
    rgb.show();
    
    delay(turn_time);
    stop_robot();
}

void stop_robot() {
    motorLeft.run(0);
    motorRight.run(0);
    
    if (emergency_stop) {
        rgb.setColor(255, 0, 0); // Red for emergency stop
    } else {
        rgb.setColor(255, 255, 255); // White for normal stop
    }
    rgb.show();
}

void safety_check() {
    float distance = ultrasonic.distanceCm();
    
    if (distance < safe_distance && distance > 0) {
        // Immediate obstacle - emergency stop
        emergency_stop = true;
        stop_robot();
        buzzer.tone(1500, 50);
        
        // Send emergency status to ESP32
        Serial.println("EMERGENCY:OBSTACLE");
        
        rgb.setColor(255, 0, 0); // Red for emergency
        rgb.show();
    }
}

void send_sensor_data() {
    static unsigned long last_send = 0;
    unsigned long now = millis();
    
    if (now - last_send > 100) { // Send every 100ms
        float distance = ultrasonic.distanceCm();
        
        Serial.print("SENSOR:");
        Serial.print(distance);
        Serial.print(",");
        Serial.print(autonomous_mode ? 1 : 0);
        Serial.print(",");
        Serial.print(emergency_stop ? 1 : 0);
        Serial.print(",");
        Serial.println(ROBOT_ID);
        
        last_send = now;
    }
}

// Additional functions for multi-robot coordination
void handle_robot_communication() {
    // Could be extended for direct robot-to-robot communication
    // via additional serial port or wireless module
}

void indicate_robot_status() {
    static unsigned long last_status = 0;
    unsigned long now = millis();
    
    if (now - last_status > 2000) { // Every 2 seconds
        // Brief identification flash
        for (int i = 0; i < ROBOT_ID; i++) {
            rgb.setColor(255, 255, 255);
            rgb.show();
            delay(100);
            rgb.setColor(0, 0, 0);
            rgb.show();
            delay(100);
        }
        
        // Return to status color
        if (emergency_stop) {
            rgb.setColor(255, 0, 0);
        } else if (autonomous_mode) {
            rgb.setColor(0, 255, 0);
        } else {
            rgb.setColor(255, 255, 0);
        }
        rgb.show();
        
        last_status = now;
    }
}
```

## 6. Setup Files and Configuration

### 6.1 Package Setup
```python
# setup.py
from setuptools import setup
import os
from glob import glob

package_name = 'multirobot_nav'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robot_team',
    maintainer_email='team@robots.com',
    description='Multi-robot navigation with LiDAR',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'robot_coordinator = multirobot_nav.robot_coordinator:main',
            'robot_controller = multirobot_nav.robot_controller:main',
            'multi_robot_slam = multirobot_nav.multi_robot_slam:main',
        ],
    },
)
```

```xml
<!-- package.xml -->
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypelevel="1"?>
<package format="3">
  <name>multirobot_nav</name>
  <version>0.0.0</version>
  <description>Multi-robot navigation with LiDAR sensors</description>
  <maintainer email="team@robots.com">robot_team</maintainer>
  <license>MIT</license>

  <depend>rclpy</depend>
  <depend>sensor_msgs</depend>
  <depend>geometry_msgs</depend>
  <depend>nav_msgs</depend>
  <depend>tf2_ros</depend>
  <depend>tf2_geometry_msgs</depend>
  <depend>laser_geometry</depend>

  <test_depend>ament_copyright</test_depend>
  <test_depend>ament_flake8</test_depend>
  <test_depend>ament_pep257</test_depend>
  <test_depend>python3-pytest</test_depend>

  <export>
    <build_type>ament_python</build_type>
  </export>
</package>
```

### 6.2 Configuration Files
```yaml
# config/robot_params.yaml
robot_coordinator:
  ros__parameters:
    coordination_strategy: "frontier_based"
    min_robot_distance: 1.5
    exploration_complete_threshold: 0.90
    frontier_cluster_distance: 1.0
    max_exploration_time: 1800  # 30 minutes

robot1_controller:
  ros__parameters:
    robot_name: "robot1"
    linear_speed: 0.15
    angular_speed: 0.3
    safe_distance: 0.4
    goal_tolerance: 0.3
    obstacle_avoidance_gain: 1.0

robot2_controller:
  ros__parameters:
    robot_name: "robot2"
    linear_speed: 0.15
    angular_speed: 0.3
    safe_distance: 0.4
    goal_tolerance: 0.3
    obstacle_avoidance_gain: 1.0

multi_robot_slam:
  ros__parameters:
    map_resolution: 0.05
    map_width: 2000
    map_height: 2000
    update_rate: 5.0
    raytracing_max_range: 12.0
    obstacle_inflation_radius: 0.2
```

## 7. Build and Run Instructions

### 7.1 Build Multi-Robot Package
```bash
cd ~/multirobot_ws
colcon build --packages-select multirobot_nav
source install/setup.bash
```

### 7.2 Run the Multi-Robot System

#### Terminal 1: Start micro-ROS agents
```bash
cd ~/multirobot_ws
source install/setup.bash

# Start agents for both robots
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &  # Robot 1
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8889 &  # Robot 2

echo "Multi-robot micro-ROS agents started"
```

#### Terminal 2: Launch multi-robot system
```bash
ros2 launch multirobot_nav multirobot_launch.py
```

#### Terminal 3: Monitor system
```bash
# Check robot connections
ros2 topic list | grep robot

# Monitor robot states
ros2 topic echo /robot1/odom --once
ros2 topic echo /robot2/odom --once

# Check LiDAR data
ros2 topic hz /robot1/scan
ros2 topic hz /robot2/scan

# Monitor coordination
ros2 topic echo /robot1/goal_pose
ros2 topic echo /robot2/goal_pose

# Check map generation
ros2 topic echo /map --once
```

#### Terminal 4: Visualization
```bash
# Launch RViz with multi-robot configuration
rviz2 -d ~/multirobot_ws/src/multirobot_nav/config/multirobot.rviz
```

### 7.3 Manual Robot Control (for testing)
```bash
# Control Robot 1
ros2 topic pub /robot1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.2}, angular: {z: 0.0}}" --once

# Control Robot 2  
ros2 topic pub /robot2/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.2}, angular: {z: 0.0}}" --once

# Stop both robots
ros2 topic pub /robot1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
ros2 topic pub /robot2/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
```

### 7.4 Hardware Setup Summary

#### Network Configuration:
```
WiFi Network: "MultiRobot_Network"
Password: "multirobot2024"
Raspberry Pi: 192.168.4.1 (AP + ROS2 Master)
Robot 1 ESP32: 192.168.4.10 (DHCP reserved)
Robot 2 ESP32: 192.168.4.20 (DHCP reserved)
```

#### Hardware Connections per Robot:
```
ESP32 ↔ LD19 LiDAR:
- GPIO 16 ↔ LiDAR TX
- GPIO 17 ↔ LiDAR PWM (grounded)
- 5V ↔ LiDAR VCC
- GND ↔ LiDAR GND

ESP32 ↔ M-Bot:
- GPIO 4 ↔ M-Bot RX (exposed after Bluetooth removal)
- GPIO 2 ↔ M-Bot TX (exposed after Bluetooth removal)
- GND ↔ M-Bot GND

M-Bot Components:
- Ultrasonic sensor on PORT_3
- Motors on M1 (left), M2 (right)
- RGB LED on PORT_7 for status indication
```

This completes the multi-robot system where:

## Key Features:
1. **Two Independent Robots**: Each with its own ESP32, LiDAR, and M-Bot
2. **Coordinated Exploration**: Robots work together to map the environment efficiently
3. **Collision Avoidance**: Both local (ultrasonic) and global (coordination) safety systems
4. **Wireless Communication**: All data transmitted via WiFi to central Raspberry Pi
5. **Real-time SLAM**: Combined mapping from both robots' sensor data
6. **Frontier-based Exploration**: Intelligent goal assignment to minimize overlap
7. **Robust Error Handling**: Automatic reconnection and fault tolerance

The system automatically coordinates the two robots to explore and map an environment while maintaining safe distances and avoiding collisions.
// ESP32_LD19_microROS.ino
#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <sensor_msgs/msg/laser_scan.h>
#include <HardwareSerial.h>

// LiDAR configuration
#define LIDAR_SERIAL Serial2
#define LIDAR_BAUDRATE 230400
#define LIDAR_RX_PIN 16
#define LIDAR_TX_PIN 17

// Packet structure from LD19 manual
#define POINT_PER_PACK 12
#define HEADER 0x54

typedef struct __attribute__((packed)) {
    uint16_t distance;
    uint8_t intensity;
} LidarPointStructDef;

typedef struct __attribute__((packed)) {
    uint8_t header;
    uint8_t ver_len;
    uint16_t speed;
    uint16_t start_angle;
    LidarPointStructDef point[POINT_PER_PACK];
    uint16_t end_angle;
    uint16_t timestamp;
    uint8_t crc8;
} LiDARFrameTypeDef;

// micro-ROS entities
rcl_publisher_t publisher;
sensor_msgs__msg__LaserScan scan_msg;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// LiDAR data
float ranges[360];
float intensities[360];
bool new_scan_ready = false;

// CRC table from LD19 manual
static const uint8_t CrcTable[256] = {
    0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3, 0xae, 0xf2, 0xbf, 0x68, 0x25, 0x8b, 0xc6, 0x11, 0x5c,
    // ... (complete CRC table from manual)
};

uint8_t CalCRC8(uint8_t *p, uint8_t len) {
    uint8_t crc = 0;
    uint16_t i;
    for (i = 0; i < len; i++) {
        crc = CrcTable[(crc ^ *p++) & 0xff];
    }
    return crc;
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL && new_scan_ready) {
        publish_scan();
        new_scan_ready = false;
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialize LiDAR serial
    LIDAR_SERIAL.begin(LIDAR_BAUDRATE, SERIAL_8N1, LIDAR_RX_PIN, LIDAR_TX_PIN);
    
    // Initialize ranges array
    for (int i = 0; i < 360; i++) {
        ranges[i] = 12.0; // Max range
        intensities[i] = 0.0;
    }
    
    // micro-ROS setup
    set_microros_transports();
    
    allocator = rcl_get_default_allocator();
    
    // Create init_options
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    
    // Create node
    RCCHECK(rclc_node_init_default(&node, "lidar1_node", "", &support));
    
    // Create publisher
    RCCHECK(rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
        "lidar1/scan"));
    
    // Create timer
    const unsigned int timer_timeout = 100; // 10Hz
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback));
    
    // Create executor
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_timer(&executor, &timer));
    
    // Initialize scan message
    scan_msg.header.frame_id.data = "lidar1_link";
    scan_msg.header.frame_id.size = strlen("lidar1_link");
    scan_msg.header.frame_id.capacity = scan_msg.header.frame_id.size + 1;
    
    scan_msg.angle_min = 0.0;
    scan_msg.angle_max = 2.0 * M_PI;
    scan_msg.angle_increment = M_PI / 180.0; // 1 degree
    scan_msg.time_increment = 0.0;
    scan_msg.scan_time = 0.1;
    scan_msg.range_min = 0.15;
    scan_msg.range_max = 12.0;
    
    scan_msg.ranges.data = ranges;
    scan_msg.ranges.size = 360;
    scan_msg.ranges.capacity = 360;
    
    scan_msg.intensities.data = intensities;
    scan_msg.intensities.size = 360;
    scan_msg.intensities.capacity = 360;
    
    Serial.println("LD19 LiDAR micro-ROS node initialized");
}

void loop() {
    read_lidar_data();
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
}

void read_lidar_data() {
    static uint8_t buffer[47]; // Size of LiDAR frame
    static int buffer_index = 0;
    static bool frame_started = false;
    
    while (LIDAR_SERIAL.available()) {
        uint8_t byte = LIDAR_SERIAL.read();
        
        if (!frame_started && byte == HEADER) {
            frame_started = true;
            buffer[0] = byte;
            buffer_index = 1;
        } else if (frame_started) {
            buffer[buffer_index++] = byte;
            
            if (buffer_index >= 47) {
                // Process complete frame
                process_lidar_frame(buffer);
                frame_started = false;
                buffer_index = 0;
            }
        }
    }
}

void process_lidar_frame(uint8_t* buffer) {
    LiDARFrameTypeDef* frame = (LiDARFrameTypeDef*)buffer;
    
    // Verify header and version
    if (frame->header != HEADER || frame->ver_len != 0x2C) {
        return;
    }
    
    // Verify CRC
    uint8_t calculated_crc = CalCRC8(buffer, 46);
    if (calculated_crc != frame->crc8) {
        return;
    }
    
    // Extract angles and distances
    float start_angle = frame->start_angle * 0.01 * M_PI / 180.0; // Convert to radians
    float end_angle = frame->end_angle * 0.01 * M_PI / 180.0;
    
    // Normalize angles
    if (end_angle < start_angle) {
        end_angle += 2 * M_PI;
    }
    
    float angle_step = (end_angle - start_angle) / (POINT_PER_PACK - 1);
    
    for (int i = 0; i < POINT_PER_PACK; i++) {
        float angle = start_angle + i * angle_step;
        if (angle >= 2 * M_PI) {
            angle -= 2 * M_PI;
        }
        
        int angle_index = (int)(angle * 180.0 / M_PI);
        if (angle_index >= 0 && angle_index < 360) {
            float distance = frame->point[i].distance / 1000.0; // Convert mm to meters
            uint8_t intensity = frame->point[i].intensity;
            
            if (distance >= 0.15 && distance <= 12.0) {
                ranges[angle_index] = distance;
                intensities[angle_index] = intensity;
            }
        }
    }
    
    new_scan_ready = true;
}

void publish_scan() {
    scan_msg.header.stamp.sec = rmw_uros_epoch_millis() / 1000;
    scan_msg.header.stamp.nanosec = (rmw_uros_epoch_millis() % 1000) * 1000000;
    
    rcl_ret_t ret = rcl_publish(&publisher, &scan_msg, NULL);
    if (ret != RCL_RET_OK) {
        Serial.println("Error publishing scan");
    }
}

// Error handling macro
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){Serial.printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc); return;}}
```

## 4. M-Bot Navigation Code (Arduino)

### 4.1 M-Bot Arduino Code
```cpp
// MBot_Navigation.ino
#include <MeMCore.h>
#include <SoftwareSerial.h>

// Motor and sensor definitions
MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);
MeUltrasonicSensor ultrasonic(PORT_3);
MeBuzzer buzzer;
MeRGBLed rgb(PORT_7);

// Communication with ESP32
SoftwareSerial esp32Serial(A0, A1); // RX, TX pins

// Navigation parameters
float base_speed = 100;
float turn_speed = 150;
float safe_distance = 20.0; // cm
bool autonomous_mode = true;

// Command structure
struct Command {
    char type; // 'M' for move, 'T' for turn, 'S' for stop
    float value; // speed or angle
};

void setup() {
    Serial.begin(115200);
    esp32Serial.begin(9600);
    
    // Initialize RGB LED
    rgb.setpin(PORT_7);
    rgb.setColor(0, 0, 255); // Blue for initialization
    rgb.show();
    
    buzzer.tone(1000, 200); // Startup beep
    
    Serial.println("M-Bot Navigation System Initialized");
    delay(1000);
    
    rgb.setColor(0, 255, 0); // Green for ready
    rgb.show();
}

void loop() {
    // Check for commands from ESP32/ROS
    if (esp32Serial.available()) {
        Command cmd = read_command();
        execute_command(cmd);
    }
    
    // Autonomous obstacle avoidance if enabled
    if (autonomous_mode) {
        obstacle_avoidance();
    }
    
    // Send sensor data to ESP32
    send_sensor_data();
    
    delay(50);
}

Command read_command() {
    Command cmd;
    String data = esp32Serial.readStringUntil('\n');
    data.trim();
    
    if (data.length() > 0) {
        cmd.type = data.charAt(0);
        cmd.value = data.substring(1).toFloat();
    } else {
        cmd.type = 'S'; // Stop if invalid command
        cmd.value = 0;
    }
    
    return cmd;
}

void execute_command(Command cmd) {
    switch (cmd.type) {
        case 'M': // Move forward/backward
            move_robot(cmd.value);
            break;
        case 'T': // Turn left/right
            turn_robot(cmd.value);
            break;
        case 'S': // Stop
            stop_robot();
            break;
        case 'A': // Set autonomous mode
            autonomous_mode = (cmd.value > 0);
            rgb.setColor(autonomous_mode ? 0 : 255, 255, 0);
            rgb.show();
            break;
        default:
            stop_robot();
            break;
    }
}

void move_robot(float speed) {
    // Clamp speed
    speed = constrain(speed, -255, 255);
    
    motorLeft.run(speed);
    motorRight.run(speed);
    
    // Visual feedback
    if (speed > 0) {
        rgb.setColor(0, 255, 0); // Green for forward
    } else if (speed < 0) {
        rgb.setColor(255, 0, 0); // Red for backward
    }
    rgb.show();
}

void turn_robot(float angle) {
    // Convert angle to motor differential
    float turn_time = abs(angle) * 10; // Rough calibration
    
    if (angle > 0) { // Turn right
        motorLeft.run(turn_speed);
        motorRight.run(-turn_speed);
        rgb.setColor(0, 0, 255); // Blue for turning
    } else { // Turn left
        motorLeft.run(-turn_speed);
        motorRight.run(turn_speed);
        rgb.setColor(255, 255, 0); // Yellow for turning
    }
    rgb.show();
    
    delay(turn_time);
    stop_robot();
}

void stop_robot() {
    motorLeft.run(0);
    motorRight.run(0);
    rgb.setColor(255, 255, 255); // White for stopped
    rgb.show();
}

void obstacle_avoidance() {
    float distance = ultrasonic.distanceCm();
    
    if (distance < safe_distance && distance > 0) {
        // Obstacle detected
        stop_robot();
        buzzer.tone(800, 100);
        
        // Simple avoidance: turn right
        turn_robot(45);
        delay(500);
        
        rgb.setColor(255, 165, 0); // Orange for obstacle avoidance
        rgb.show();
    }
}

void send_sensor_data() {
    static unsigned long last_send = 0;
    unsigned long now = millis();
    
    if (now - last_send > 100) { // Send every 100ms
        float distance = ultrasonic.distanceCm();
        
        esp32Serial.print("SENSOR:");
        esp32Serial.print(distance);
        esp32Serial.print(",");
        esp32Serial.print(autonomous_mode ? 1 : 0);
        esp32Serial.println();
        
        last_send = now;
    }
}
```

### 4.2 ESP32 Bridge Code (WiFi Communication with M-Bot)
```cpp
// ESP32_MBot_WiFi_Bridge.ino
#include <micro_ros_arduino.h>
#include <geometry_msgs/msg/twist.h>
#include <sensor_msgs/msg/range.h>
#include <nav_msgs/msg/odometry.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi Configuration
const char* ssid = "LiDAR_RobotNet";
const char* password = "lidar123456";
const char* agent_ip = "192.168.4.1";  // Raspberry Pi IP
const int agent_port = 8890;            // micro-ROS agent port for M-Bot bridge

// Communication with M-Bot
HardwareSerial mbotSerial(1);
#define MBOT_RX_PIN 4
#define MBOT_TX_PIN 2
#define STATUS_LED 2

// micro-ROS entities
rcl_subscription_t cmd_vel_subscriber;
rcl_publisher_t odom_publisher;
rcl_publisher_t range_publisher;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

geometry_msgs__msg__Twist cmd_vel_msg;
nav_msgs__msg__Odometry odom_msg;
sensor_msgs__msg__Range range_msg;

// Robot state
float robot_x = 0.0;
float robot_y = 0.0;
float robot_theta = 0.0;
float last_cmd_linear = 0.0;
float last_cmd_angular = 0.0;
unsigned long last_odom_time = 0;
unsigned long last_cmd_time = 0;

// Connection status
bool wifi_connected = false;
bool micro_ros_connected = false;
unsigned long last_wifi_check = 0;
unsigned long last_status_blink = 0;
bool status_led_state = false;

// Robot parameters
const float wheel_base = 0.15; // meters
const float wheel_radius = 0.03; // meters
const float max_speed = 0.5; // m/s

// Custom transport functions (same as LiDAR nodes)
bool transport_open(struct uxrCustomTransport* transport) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    return udp->begin(2020);
}

bool transport_close(struct uxrCustomTransport* transport) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    udp->stop();
    return true;
}

size_t transport_write(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, uint8_t* err) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    udp->beginPacket(agent_ip, agent_port);
    size_t sent = udp->write(buf, len);
    udp->endPacket();
    return sent;
}

size_t transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err) {
    WiFiUDP* udp = (WiFiUDP*) transport->args;
    
    uint32_t start_time = millis();
    while (millis() - start_time < timeout) {
        int packet_size = udp->parsePacket();
        if (packet_size > 0) {
            size_t bytes_read = udp->read(buf, len);
            return bytes_read;
        }
        delay(1);
    }
    return 0;
}

void cmd_vel_callback(const void * msgin) {
    const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
    
    // Store command for odometry calculation
    last_cmd_linear = msg->linear.x;
    last_cmd_angular = msg->angular.z;
    last_cmd_time = millis();
    
    // Convert Twist to motor commands
    float linear = msg->linear.x;
    float angular = msg->angular.z;
    
    // Differential drive kinematics
    float left_speed = linear - (angular * wheel_base / 2.0);
    float right_speed = linear + (angular * wheel_base / 2.0);
    
    // Convert to motor PWM values (-255 to 255)
    int left_pwm = constrain(left_speed * 255 / max_speed, -255, 255);
    int right_pwm = constrain(right_speed * 255 / max_speed, -255, 255);
    
    // Send command to M-Bot
    if (abs(left_pwm) < 10 && abs(right_pwm) < 10) {
        mbotSerial.println("S0"); // Stop
    } else {
        float avg_speed = (left_pwm + right_pwm) / 2.0;
        mbotSerial.print("M");
        mbotSerial.println(avg_speed);
        
        // Handle turning
        if (abs(angular) > 0.1) {
            float turn_angle = angular * 57.2958; // Convert to degrees
            mbotSerial.print("T");
            mbotSerial.println(turn_angle);
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(STATUS_LED, OUTPUT);
    mbotSerial.begin(9600, SERIAL_8N1, MBOT_RX_PIN, MBOT_TX_PIN);
    
    // Connect to WiFi
    connect_wifi();
    
    // Setup micro-ROS
    if (wifi_connected) {
        setup_micro_ros();
    }
    
    Serial.println("M-Bot WiFi Bridge initialized");
}

void loop() {
    // Check WiFi connection
    check_wifi_status();
    
    // Process ROS messages if connected
    if (micro_ros_connected) {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
    }
    
    // Read sensor data from M-Bot
    read_mbot_data();
    
    // Publish odometry and sensor data
    if (micro_ros_connected) {
        publish_odometry();
        publish_range_data();
    }
    
    // Update status LED
    update_status_led();
    
    delay(10);
}

void connect_wifi() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        wifi_connected = true;
        Serial.println();
        Serial.print("WiFi connected! IP: ");
        Serial.println(WiFi.localIP());
    } else {
        wifi_connected = false;
        Serial.println();
        Serial.println("WiFi connection failed!");
    }
}

void check_wifi_status() {
    unsigned long now = millis();
    if (now - last_wifi_check > 5000) { // Check every 5 seconds
        if (WiFi.status() != WL_CONNECTED && wifi_connected) {
            wifi_connected = false;
            micro_ros_connected = false;
            Serial.println("WiFi disconnected! Attempting reconnection...");
            connect_wifi();
        } else if (WiFi.status() == WL_CONNECTED && !wifi_connected) {
            wifi_connected = true;
            Serial.println("WiFi reconnected!");
            setup_micro_ros();
        }
        last_wifi_check = now;
    }
}

void setup_micro_ros() {
    if (!wifi_connected) return;
    
    // Custom WiFi transport
    static WiFiUDP udp;
    rmw_uros_set_custom_transport(
        false, // framing disabled
        (void *) &udp,
        transport_open,
        transport_close,
        transport_write,
        transport_read
    );
    
    allocator = rcl_get_default_allocator();
    
    rcl_ret_t ret = rclc_support_init(&support, 0, NULL, &allocator);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize support");
        return;
    }
    
    ret = rclc_node_init_default(&node, "mbot_bridge", "", &support);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize node");
        return;
    }
    
    // Create subscriber
    ret = rclc_subscription_init_default(
        &cmd_vel_subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "/cmd_vel");
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize cmd_vel subscriber");
        return;
    }
    
    // Create publishers
    ret = rclc_publisher_init_default(
        &odom_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry),
        "/odom");
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize odom publisher");
        return;
    }
    
    ret = rclc_publisher_init_default(
        &range_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Range),
        "/ultrasonic");
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize range publisher");
        return;
    }
    
    // Create executor
    ret = rclc_executor_init(&executor, &support.context, 1, &allocator);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to initialize executor");
        return;
    }
    
    ret = rclc_executor_add_subscription(&executor, &cmd_vel_subscriber, &cmd_vel_msg, &cmd_vel_callback, ON_NEW_DATA);
    if (ret != RCL_RET_OK) {
        Serial.println("Failed to add subscription to executor");
        return;
    }
    
    // Initialize messages
    init_messages();
    
    micro_ros_connected = true;
    Serial.println("micro-ROS bridge initialized successfully");
}

void read_mbot_data() {
    if (mbotSerial.available()) {
        String data = mbotSerial.readStringUntil('\n');
        data.trim();
        
        if (data.startsWith("SENSOR:")) {
            String sensor_data = data.substring(7);
            int comma_index = sensor_data.indexOf(',');
            
            if (comma_index > 0) {
                float distance = sensor_data.substring(0, comma_index).toFloat();
                // Store distance for range message
                range_msg.range = distance / 100.0; // Convert cm to meters
            }
        }
        // Could add encoder data parsing here if available
        else if (data.startsWith("ENCODER:")) {
            // Parse encoder data for better odometry
            // Format: "ENCODER:left_count,right_count"
        }
    }
}

void publish_odometry() {
    static unsigned long last_odom_publish = 0;
    unsigned long current_time = millis();
    
    if (current_time - last_odom_publish > 50) { // Publish at 20Hz
        float dt = (current_time - last_odom_time) / 1000.0;
        
        if (dt > 0 && last_odom_time > 0) {
            // Simple dead reckoning based on commanded velocities
            float linear_vel = last_cmd_linear;
            float angular_vel = last_cmd_angular;
            
            // Apply velocity timeout (stop if no recent commands)
            if (current_time - last_cmd_time > 500) {
                linear_vel = 0.0;
                angular_vel = 0.0;
            }
            
            // Update pose
            robot_x += linear_vel * cos(robot_theta) * dt;
            robot_y += linear_vel * sin(robot_theta) * dt;
            robot_theta += angular_vel * dt;
            
            // Normalize theta
            while (robot_theta > M_PI) robot_theta -= 2 * M_PI;
            while (robot_theta < -M_PI) robot_theta += 2 * M_PI;
        }
        
        // Populate odometry message
        int64_t time_us = esp_timer_get_time();
        odom_msg.header.stamp.sec = time_us / 1000000;
        odom_msg.header.stamp.nanosec = (time_us % 1000000) * 1000;
        
        odom_msg.pose.pose.position.x = robot_x;
        odom_msg.pose.pose.position.y = robot_y;
        odom_msg.pose.pose.position.z = 0.0;
        
        // Convert yaw to quaternion
        odom_msg.pose.pose.orientation.x = 0.0;
        odom_msg.pose.pose.orientation.y = 0.0;
        odom_msg.pose.pose.orientation.z = sin(robot_theta / 2.0);
        odom_msg.pose.pose.orientation.w = cos(robot_theta / 2.0);
        
        // Set velocity
        odom_msg.twist.twist.linear.x = last_cmd_linear;
        odom_msg.twist.twist.linear.y = 0.0;
        odom_msg.twist.twist.angular.z = last_cmd_angular;
        
        rcl_ret_t ret = rcl_publish(&odom_publisher, &odom_msg, NULL);
        if (ret != RCL_RET_OK) {
            Serial.println("Error publishing odometry");
        }
        
        last_odom_time = current_time;
        last_odom_publish = current_time;
    }
}

void publish_range_data() {
    static unsigned long last_range_time = 0;
    unsigned long current_time = millis();
    
    if (current_time - last_range_time > 100) { // 10Hz
        int64_t time_us = esp_timer_get_time();
        range_msg.header.stamp.sec = time_us / 1000000;
        range_msg.header.stamp.nanosec = (time_us % 1000000) * 1000;
        
        rcl_ret_t ret = rcl_publish(&range_publisher, &range_msg, NULL);
        if (ret != RCL_RET_OK) {
            Serial.println("Error publishing range data");
        }
        
        last_range_time = current_time;
    }
}

void init_messages() {
    // Initialize odometry message
    odom_msg.header.frame_id.data = "odom";
    odom_msg.header.frame_id.size = strlen("odom");
    odom_msg.header.frame_id.capacity = odom_msg.header.frame_id.size + 1;
    
    odom_msg.child_frame_id.data = "base_link";
    odom_msg.child_frame_id.size = strlen("base_link");
    odom_msg.child_frame_id.capacity = odom_msg.child_frame_id.size + 1;
    
    // Initialize range message
    range_msg.header.frame_id.data = "ultrasonic_link";
    range_msg.header.frame_id.size = strlen("ultrasonic_link");
    range_msg.header.frame_id.capacity = range_msg.header.frame_id.size + 1;
    
    range_msg.radiation_type = sensor_msgs__msg__Range__ULTRASOUND;
    range_msg.field_of_view = 0.26; // ~15 degrees
    range_msg.min_range = 0.02;
    range_msg.max_range = 4.0;
    range_msg.range = 4.0; // Initialize with max range
}

void update_status_led() {
    unsigned long now = millis();
    if (now - last_status_blink > 500) {
        status_led_state = !status_led_state;
        
        if (micro_ros_connected) {
            // Solid on when fully connected
            digitalWrite(STATUS_LED, HIGH);
        } else if (wifi_connected) {
            // Slow blink when WiFi connected but micro-ROS not
            digitalWrite(STATUS_LED, status_led_state);
        } else {
            // Fast blink when disconnected
            digitalWrite(STATUS_LED, (now % 200) < 100);
        }
        
        last_status_blink = now;
    }
}
```

## 5. Build and Run Instructions

### 5.1 Build ROS2 Package
```bash
cd ~/lidar_ws
colcon build --packages-select multi_lidar_nav
source install/setup.bash
```

### 5.2 Run the System
```bash
# Terminal 1: Launch micro-ROS agent and LiDAR processing
ros2 launch multi_lidar_nav multi_lidar_launch.py

# Terminal 2: Launch RViz for visualization
rviz2 -d ~/lidar_ws/src/multi_lidar_nav/config/navigation.rviz

# Terminal 3: Monitor topics
ros2 topic list
ros2 topic echo /scan
ros2 topic echo /map
```

### 5.3 Hardware Connections
```
ESP32 #1 (LiDAR 1):
- GPIO 16 -> LD19 TX
- GPIO 17 -> LD19 PWM (grounded for internal speed control)
- 5V -> LD19 VCC
- GND -> LD19 GND

ESP32 #2 (LiDAR 2): Same as above

ESP32 Bridge:
- GPIO 4 -> M-Bot RX (after removing Bluetooth module)
- GPIO 2 -> M-Bot TX
- GND -> M-Bot GND

M-Bot:
- Ultrasonic sensor on PORT_3
- Motors on M1, M2
- RGB LED on PORT_7
```

### 5.4 Configuration
```yaml
# config/lidar_config.yaml
lidar_merger:
  ros__parameters:
    lidar1_frame: "lidar1_link"
    lidar2_frame: "lidar2_link"
    merged_frame: "base_link"
    max_range: 12.0
    min_range: 0.15

navigation_controller:
  ros__parameters:
    linear_speed: 0.2
    angular_speed: 0.5
    safe_distance: 0.3
    exploration_mode: true
```

This complete implementation provides:

1. **ESP32 micro-ROS nodes** that read LD19 LiDAR data and publish to ROS2 topics
2. **ROS2 package** for merging multiple LiDAR streams and navigation
3. **M-Bot Arduino code** for motor control and basic obstacle avoidance
4. **ESP32 bridge** for ROS2-Arduino communication
5. **Launch files** to start the entire system
6. **SLAM integration** using slam_toolbox for mapping

The system supports autonomous exploration, obstacle avoidance, and real-time mapping using two LD19 LiDAR sensors.