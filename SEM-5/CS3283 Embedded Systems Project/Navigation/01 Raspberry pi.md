# Raspberry Pi 4 Multi-Robot Navigation System

## 1. System Setup and Installation

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
```

Add to `/etc/dhcpcd.conf`:
```
interface wlan0
static ip_address=192.168.4.1/24
nohook wpa_supplicant
```

### 1.3 Configure dnsmasq
```bash
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
sudo nano /etc/dnsmasq.conf
```

Content for `/etc/dnsmasq.conf`:
```
interface=wlan0
dhcp-range=192.168.4.10,192.168.4.50,255.255.255.0,24h
dhcp-option=3,192.168.4.1
dhcp-option=6,192.168.4.1

# Reserve IPs for robots
dhcp-host=robot1,192.168.4.10
dhcp-host=robot2,192.168.4.20
```

### 1.4 Configure hostapd
```bash
sudo nano /etc/hostapd/hostapd.conf
```

Content for `/etc/hostapd/hostapd.conf`:
```
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
# Configure hostapd daemon
sudo nano /etc/default/hostapd
# Uncomment and edit: DAEMON_CONF="/etc/hostapd/hostapd.conf"

# Enable IP forwarding
sudo nano /etc/sysctl.conf
# Uncomment: net.ipv4.ip_forward=1

# Configure iptables for NAT
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

### 1.6 Setup ROS2 Environment
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

## 2. Create ROS2 Package

### 2.1 Create Package Structure
```bash
cd ~/multirobot_ws/src
ros2 pkg create --build-type ament_python multirobot_nav --dependencies rclpy sensor_msgs geometry_msgs nav_msgs tf2_ros tf2_geometry_msgs laser_geometry

cd multirobot_nav
mkdir -p launch config
```

### 2.2 Robot Coordinator Node
Create `multirobot_nav/robot_coordinator.py`:
```python
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import OccupancyGrid, Odometry
import math
import numpy as np

class RobotCoordinator(Node):
    def __init__(self):
        super().__init__('robot_coordinator')
        
        # Parameters
        self.declare_parameter('coordination_strategy', 'frontier_based')
        self.declare_parameter('min_robot_distance', 1.5)
        self.declare_parameter('exploration_complete_threshold', 0.90)
        
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
        self.coordination_timer = self.create_timer(2.0, self.coordinate_robots)
        
        # Safety timer for collision avoidance
        self.safety_timer = self.create_timer(0.2, self.safety_check)
        
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
        
        # Find frontier cells
        for y in range(1, height-1):
            for x in range(1, width-1):
                index = y * width + x
                if self.current_map.data[index] == -1:  # Unknown cell
                    # Check if adjacent to free space
                    adjacent_free = False
                    for dx in [-1, 0, 1]:
                        for dy in [-1, 0, 1]:
                            if dx == 0 and dy == 0:
                                continue
                            adj_index = (y+dy) * width + (x+dx)
                            if 0 <= adj_index < len(self.current_map.data):
                                if self.current_map.data[adj_index] == 0:
                                    adjacent_free = True
                                    break
                        if adjacent_free:
                            break
                    
                    if adjacent_free:
                        world_x = x * resolution + origin_x
                        world_y = y * resolution + origin_y
                        frontiers.append((world_x, world_y))
        
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
            
            if len(cluster) >= 3:
                center_x = sum(f[0] for f in cluster) / len(cluster)
                center_y = sum(f[1] for f in cluster) / len(cluster)
                clusters.append((center_x, center_y))
        
        return clusters

    def coordinate_robots(self):
        if not all([self.robot1_pose, self.robot2_pose]):
            return
        
        if self.is_exploration_complete():
            self.stop_robots()
            self.get_logger().info('Exploration complete!')
            return
        
        if self.coordination_strategy == 'frontier_based':
            self.assign_frontier_goals()

    def assign_frontier_goals(self):
        if len(self.exploration_frontiers) < 2:
            return
        
        robot1_pos = (self.robot1_pose.position.x, self.robot1_pose.position.y)
        robot2_pos = (self.robot2_pose.position.x, self.robot2_pose.position.y)
        
        best_assignment = None
        min_cost = float('inf')
        
        for i, frontier1 in enumerate(self.exploration_frontiers):
            for j, frontier2 in enumerate(self.exploration_frontiers):
                if i == j:
                    continue
                
                dist1_to_f1 = math.sqrt((robot1_pos[0] - frontier1[0])**2 + 
                                      (robot1_pos[1] - frontier1[1])**2)
                dist2_to_f2 = math.sqrt((robot2_pos[0] - frontier2[0])**2 + 
                                      (robot2_pos[1] - frontier2[1])**2)
                
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
        
        dist = math.sqrt((self.robot1_pose.position.x - self.robot2_pose.position.x)**2 + 
                        (self.robot1_pose.position.y - self.robot2_pose.position.y)**2)
        
        if dist < self.min_robot_distance:
            self.emergency_stop()
            self.get_logger().warn(f'Robots too close ({dist:.2f}m)! Emergency stop.')

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

### 2.3 Robot Controller Node
Create `multirobot_nav/robot_controller.py`:
```python
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
            if self.is_goal_reached():
                self.goal_reached = True
                self.get_logger().info(f'{self.robot_name} reached goal!')
                self.publish_cmd_vel(cmd)
                return
            
            goal_angle = math.atan2(
                self.current_goal[1] - self.current_pose.position.y,
                self.current_goal[0] - self.current_pose.position.x
            )
            
            current_yaw = self.get_yaw_from_pose(self.current_pose)
            angle_diff = self.normalize_angle(goal_angle - current_yaw)
            
            obstacle_detected, obstacle_direction = self.detect_obstacles()
            
            if obstacle_detected:
                cmd = self.obstacle_avoidance_behavior(obstacle_direction)
            else:
                if abs(angle_diff) > 0.2:
                    cmd.angular.z = self.angular_speed if angle_diff > 0 else -self.angular_speed
                    cmd.linear.x = 0.05
                else:
                    cmd.linear.x = self.linear_speed
                    cmd.angular.z = 0.3 * angle_diff
        else:
            cmd.linear.x = 0.0
            cmd.angular.z = 0.0
        
        self.publish_cmd_vel(cmd)

    def detect_obstacles(self):
        if self.current_scan is None:
            return False, 0
        
        ranges = np.array(self.current_scan.ranges)
        ranges = np.where(np.isfinite(ranges), ranges, self.current_scan.range_max)
        
        front_ranges = ranges[len(ranges)//3:2*len(ranges)//3]
        min_front_dist = np.min(front_ranges)
        
        if min_front_dist < self.safe_distance:
            left_ranges = ranges[:len(ranges)//4]
            right_ranges = ranges[3*len(ranges)//4:]
            
            avg_left = np.mean(left_ranges)
            avg_right = np.mean(right_ranges)
            
            direction = 'left' if avg_left > avg_right else 'right'
            return True, direction
        
        return False, None

    def obstacle_avoidance_behavior(self, obstacle_direction):
        cmd = Twist()
        
        if obstacle_direction == 'left':
            cmd.angular.z = -self.angular_speed
        else:
            cmd.angular.z = self.angular_speed
        
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

### 2.4 Multi-Robot SLAM Node
Create `multirobot_nav/multi_robot_slam.py`:
```python
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import OccupancyGrid
import tf2_ros
import numpy as np
import math

class MultiRobotSLAM(Node):
    def __init__(self):
        super().__init__('multi_robot_slam')
        
        # Parameters
        self.declare_parameter('map_resolution', 0.05)
        self.declare_parameter('map_width', 2000)
        self.declare_parameter('map_height', 2000)
        self.declare_parameter('update_rate', 5.0)
        
        self.map_resolution = self.get_parameter('map_resolution').value
        self.map_width = self.get_parameter('map_width').value
        self.map_height = self.get_parameter('map_height').value
        self.update_rate = self.get_parameter('update_rate').value
        
        # Publishers
        self.map_pub = self.create_publisher(OccupancyGrid, '/map', 10)
        
        # Subscribers
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
            transform = self.tf_buffer.lookup_transform(
                'map', f'{robot_name}/base_link', rclpy.time.Time())
            
            robot_x = transform.transform.translation.x
            robot_y = transform.transform.translation.y
            
            qx = transform.transform.rotation.x
            qy = transform.transform.rotation.y
            qz = transform.transform.rotation.z
            qw = transform.transform.rotation.w
            
            siny_cosp = 2 * (qw * qz + qx * qy)
            cosy_cosp = 1 - 2 * (qy * qy + qz * qz)
            robot_yaw = math.atan2(siny_cosp, cosy_cosp)
            
            self.update_map_with_scan(scan_msg, robot_x, robot_y, robot_yaw)
            
        except Exception as e:
            self.get_logger().warn(f'Failed to process scan from {robot_name}: {e}')

    def update_map_with_scan(self, scan, robot_x, robot_y, robot_yaw):
        for i, range_val in enumerate(scan.ranges):
            if not (scan.range_min <= range_val <= scan.range_max):
                continue
            
            angle = scan.angle_min + i * scan.angle_increment + robot_yaw
            
            end_x = robot_x + range_val * math.cos(angle)
            end_y = robot_y + range_val * math.sin(angle)
            
            self.ray_trace(robot_x, robot_y, end_x, end_y)
            self.mark_obstacle(end_x, end_y)

    def ray_trace(self, x0, y0, x1, y1):
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        
        steps = max(int(dx / self.map_resolution), int(dy / self.map_resolution))
        
        if steps == 0:
            return
        
        x_step = (x1 - x0) / steps
        y_step = (y1 - y0) / steps
        
        for i in range(steps):
            x = x0 + i * x_step
            y = y0 + i * y_step
            
            grid_x = int((x - self.map_origin_x) / self.map_resolution)
            grid_y = int((y - self.map_origin_y) / self.map_resolution)
            
            if 0 <= grid_x < self.map_width and 0 <= grid_y < self.map_height:
                if self.occupancy_grid[grid_y, grid_x] == -1:
                    self.occupancy_grid[grid_y, grid_x] = 0

    def mark_obstacle(self, x, y):
        grid_x = int((x - self.map_origin_x) / self.map_resolution)
        grid_y = int((y - self.map_origin_y) / self.map_resolution)
        
        if 0 <= grid_x < self.map_width and 0 <= grid_y < self.map_height:
            self.occupancy_grid[grid_y, grid_x] = 100

    def publish_map(self):
        map_msg = OccupancyGrid()
        map_msg.header.stamp = self.get_clock().now().to_msg()
        map_msg.header.frame_id = 'map'
        
        map_msg.info.resolution = self.map_resolution
        map_msg.info.width = self.map_width
        map_msg.info.height = self.map_height
        map_msg.info.origin.position.x = self.map_origin_x
        map_msg.info.origin.position.y = self.map_origin_y
        map_msg.info.origin.position.z = 0.0
        map_msg.info.origin.orientation.w = 1.0
        
        map_msg.data = self.occupancy_grid.flatten().tolist()
        
        self.map_pub.publish(map_msg)

def main(args=None):
    rclpy.init(args=args)
    node = MultiRobotSLAM()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

### 2.5 Launch File
Create `launch/multirobot_launch.py`:
```python
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
    return LaunchDescription([
        # micro-ROS agents
        Node(
            package='micro_ros_agent',
            executable='micro_ros_agent',
            arguments=['udp4', '--port', '8888'],
            name='micro_ros_agent_robot1'
        ),
        
        Node(
            package='micro_ros_agent',
            executable='micro_ros_agent',
            arguments=['udp4', '--port', '8889'],
            name='micro_ros_agent_robot2'
        ),
        
        # Robot coordinator
        Node(
            package='multirobot_nav',
            executable='robot_coordinator',
            name='robot_coordinator',
            parameters=[{
                'coordination_strategy': 'frontier_based',
                'min_robot_distance': 1.5,
                'exploration_complete_threshold': 0.90
            }]
        ),
        
        # Robot controllers
        Node(
            package='multirobot_nav',
            executable='robot_controller',
            name='robot1_controller',
            parameters=[{
                'robot_name': 'robot1',
                'linear_speed': 0.15,
                'angular_speed': 0.3,
                'safe_distance': 0.4,
                'goal_tolerance': 0.3
            }]
        ),
        
        Node(
            package='multirobot_nav',
            executable='robot_controller',
            name='robot2_controller',
            parameters=[{
                'robot_name': 'robot2',
                'linear_speed': 0.15,
                'angular_speed': 0.3,
                'safe_distance': 0.4,
                'goal_tolerance': 0.3
            }]
        ),
        
        # Multi-robot SLAM
        Node(
            package='multirobot_nav',
            executable='multi_robot_slam',
            name='multi_robot_slam',
            parameters=[{
                'map_resolution': 0.05,
                'map_width': 2000,
                'map_height': 2000,
                'update_rate': 5.0
            }]
        ),
        
        # Static transforms
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'robot1/odom'],
            name='map_to_robot1_odom'
        ),
        
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'robot2/odom'],
            name='map_to_robot2_odom'
        ),
        
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0.1', '0', '0', '0', 'robot1/base_link', 'robot1/lidar_link'],
            name='robot1_base_to_lidar'
        ),
        
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0.1', '0', '0', '0', 'robot2/base_link', 'robot2/lidar_link'],
            name='robot2_base_to_lidar'
        )
    ])
```

### 2.6 Package Configuration Files

Create `setup.py`:
```python
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
    description='Multi-robot navigation with LiDAR sensors',
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

Create `package.xml`:
```xml
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

## 3. Build and Run Instructions

### 3.1 Build the Package
```bash
cd ~/multirobot_ws
colcon build --packages-select multirobot_nav
source install/setup.bash
```

### 3.2 Start the System
```bash
# Terminal 1: Launch the multi-robot system
cd ~/multirobot_ws
source install/setup.bash
ros2 launch multirobot_nav multirobot_launch.py

# Terminal 2: Monitor system status
watch -n 2 'echo "=== Robot Topics ===" && ros2 topic list | grep robot && echo "=== WiFi Status ===" && iwconfig wlan0 | grep "Access Point"'

# Terminal 3: Visualize with RViz
rviz2
```

### 3.3 Manual Control (for testing)
```bash
# Control Robot 1
ros2 topic pub /robot1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.2}, angular: {z: 0.0}}" --once

# Control Robot 2
ros2 topic pub /robot2/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.2}, angular: {z: 0.0}}" --once

# Stop both robots
ros2 topic pub /robot1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
ros2 topic pub /robot2/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}" --once
```

### 3.4 System Monitoring
```bash
# Check robot data rates
ros2 topic hz /robot1/scan
ros2 topic hz /robot2/scan
ros2 topic hz /robot1/odom
ros2 topic hz /robot2/odom

# Check map generation
ros2 topic echo /map --once

# Monitor WiFi connections
sudo tail -f /var/log/syslog | grep dnsmasq
```

## 4. Troubleshooting

### 4.1 WiFi Issues
```bash
# Check AP status
sudo systemctl status hostapd
sudo systemctl status dnsmasq

# Restart WiFi services
sudo systemctl restart hostapd
sudo systemctl restart dnsmasq

# Check connected devices
arp -a | grep 192.168.4
```

### 4.2 ROS2 Issues
```bash
# Check micro-ROS agents
ps aux | grep micro_ros_agent

# Restart agents if needed
killall micro_ros_agent
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8889 &
```

### 4.3 Network Configuration
- **WiFi Network**: MultiRobot_Network
- **Password**: multirobot2024  
- **Raspberry Pi**: 192.168.4.1
- **Robot 1**: 192.168.4.10
- **Robot 2**: 192.168.4.20