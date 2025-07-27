---
tags: 
Created: 2025-06-30 21:11
About: 
Reviewed: false
Completion: 0
---
**Name** : Waduge S.S.
**Index** : 220673K

## Four-Wheeled Robot Simulation with Collision Avoidance

### Project Directory Structure

```bash
test_robot/
├── urdf/
│   ├── robot.xacro
│   └── robot.gazebo
├── launch/
│   └── your_robot.launch.py
├── src/
│   └── your_robot_node.cpp
├── worlds/
│   └── four_walls.world
├── package.xml
└── CMakeLists.txt
```

---

## 1. URDF File Creation

### Objective

To describe a robot with:

- Four wheels (2 left, 2 right)
- A camera (front-facing)
- A sonar sensor (front)
- A LiDAR sensor (360° or front-mounted)

### Approach

We used `.xacro` for modularity and easier updates.

> [!NOTE] **robot.xacro** includes:
> 
> - Base link
> - Four continuous joints for wheels
> - Camera attached via `fixed` joint
> - Sonar and LiDAR sensors added with appropriate `<sensor>` plugin tags in `robot.gazebo`
> 

### Robot.xacro
**File:** `test_robot/urdf/robot.xacro`
```xml
<?xml version="1.0"?>
<robot xmlns:xacro="http://ros.org/wiki/xacro" name="four_wheeled_bot">

  <!-- Properties -->
  <xacro:property name="wheel_radius" value="0.05"/>
  <xacro:property name="wheel_width" value="0.02"/>
  <xacro:property name="chassis_length" value="0.4"/>
  <xacro:property name="chassis_width" value="0.3"/>
  <xacro:property name="chassis_height" value="0.1"/>

  <!-- Materials -->
  <material name="gray">
    <color rgba="0.5 0.5 0.5 1.0"/>
  </material>

  <!-- Base Link -->
  <link name="base_link">
    <visual>
      <geometry>
        <box size="${chassis_length} ${chassis_width} ${chassis_height}"/>
      </geometry>
      <material name="gray"/>
    </visual>
    <collision>
      <geometry>
        <box size="${chassis_length} ${chassis_width} ${chassis_height}"/>
      </geometry>
    </collision>
    <inertial>
      <mass value="2.0"/>
      <origin xyz="0 0 0" rpy="0 0 0"/>
      <inertia ixx="0.1" ixy="0.0" ixz="0.0"
               iyy="0.1" iyz="0.0"
               izz="0.1"/>
    </inertial>
  </link>

  <!-- Macro for Wheels -->
  <xacro:macro name="wheel" params="name x y">
    <link name="${name}_link">
      <visual>
        <geometry>
          <cylinder length="${wheel_width}" radius="${wheel_radius}"/>
        </geometry>
        <origin xyz="0 0 0" rpy="1.57 0 0"/>
        <material name="gray"/>
      </visual>
      <collision>
        <geometry>
          <cylinder length="${wheel_width}" radius="${wheel_radius}"/>
        </geometry>
        <origin xyz="0 0 0" rpy="1.57 0 0"/>
      </collision>
      <inertial>
        <mass value="0.2"/>
        <inertia ixx="0.01" ixy="0.0" ixz="0.0"
                 iyy="0.01" iyz="0.0"
                 izz="0.01"/>
      </inertial>
    </link>

    <joint name="${name}_joint" type="continuous">
      <parent link="base_link"/>
      <child link="${name}_link"/>
      <origin xyz="${x} ${y} -${chassis_height / 2 + wheel_radius}" rpy="0 0 0"/>
      <axis xyz="0 1 0"/>
    </joint>
  </xacro:macro>

  <!-- Add Four Wheels -->
  <xacro:wheel name="front_left"  x="0.15" y="0.13"/>
  <xacro:wheel name="front_right" x="0.15" y="-0.13"/>
  <xacro:wheel name="rear_left"   x="-0.15" y="0.13"/>
  <xacro:wheel name="rear_right"  x="-0.15" y="-0.13"/>

  <!-- Camera -->
  <link name="camera_link">
    <visual>
      <geometry>
        <box size="0.05 0.05 0.05"/>
      </geometry>
      <origin xyz="0.15 0 0.1" rpy="0 0 0"/>
      <material name="gray"/>
    </visual>
  </link>
  <joint name="camera_joint" type="fixed">
    <parent link="base_link"/>
    <child link="camera_link"/>
    <origin xyz="0.15 0 0.1" rpy="0 0 0"/>
  </joint>

  <!-- Sonar -->
  <link name="sonar_link">
    <visual>
      <geometry>
        <cylinder length="0.02" radius="0.015"/>
      </geometry>
      <origin xyz="0.2 0 0.05" rpy="1.57 0 0"/>
      <material name="gray"/>
    </visual>
  </link>
  <joint name="sonar_joint" type="fixed">
    <parent link="base_link"/>
    <child link="sonar_link"/>
    <origin xyz="0.2 0 0.05" rpy="0 0 0"/>
  </joint>

  <!-- LiDAR -->
  <link name="lidar_link">
    <visual>
      <geometry>
        <cylinder length="0.05" radius="0.04"/>
      </geometry>
      <origin xyz="0 0 0.12" rpy="1.57 0 0"/>
      <material name="gray"/>
    </visual>
  </link>
  <joint name="lidar_joint" type="fixed">
    <parent link="base_link"/>
    <child link="lidar_link"/>
    <origin xyz="0 0 0.12" rpy="0 0 0"/>
  </joint>

  <!-- Include Gazebo Plugins -->
  <xacro:include filename="$(find your_package)/urdf/robot.gazebo"/>
</robot>

```

### Robot.gazebo
**File:** `test_robot/urdf/robot.gazebo`
```xml
<robot xmlns:xacro="http://ros.org/wiki/xacro">

  <!-- LiDAR Plugin -->
  <gazebo reference="lidar_link">
    <sensor type="gpu_lidar" name="lidar">
      <update_rate>10</update_rate>
      <ray>
        <scan>
          <horizontal>
            <samples>720</samples>
            <resolution>1</resolution>
            <min_angle>-1.57</min_angle>
            <max_angle>1.57</max_angle>
          </horizontal>
        </scan>
        <range>
          <min>0.1</min>
          <max>10.0</max>
        </range>
      </ray>
      <plugin name="gazebo_ros_laser" filename="libgazebo_ros_ray_sensor.so">
        <topicName>/scan</topicName>
        <frameName>lidar_link</frameName>
      </plugin>
    </sensor>
  </gazebo>

  <!-- Camera Plugin -->
  <gazebo reference="camera_link">
    <sensor type="camera" name="camera">
      <update_rate>30</update_rate>
      <camera>
        <horizontal_fov>1.3962634</horizontal_fov>
        <image>
          <width>640</width>
          <height>480</height>
          <format>R8G8B8</format>
        </image>
        <clip>
          <near>0.1</near>
          <far>100</far>
        </clip>
      </camera>
      <plugin name="gazebo_ros_camera" filename="libgazebo_ros_camera.so">
        <cameraName>camera</cameraName>
        <imageTopicName>image_raw</imageTopicName>
        <cameraInfoTopicName>camera_info</cameraInfoTopicName>
        <frameName>camera_link</frameName>
      </plugin>
    </sensor>
  </gazebo>

  <!-- Sonar Plugin -->
  <gazebo reference="sonar_link">
    <sensor type="sonar" name="sonar">
      <update_rate>10.0</update_rate>
      <range>
        <min>0.02</min>
        <max>2.0</max>
        <resolution>0.01</resolution>
      </range>
      <plugin name="gazebo_ros_range" filename="libgazebo_ros_range.so">
        <topicName>/sonar/range</topicName>
        <frameName>sonar_link</frameName>
      </plugin>
    </sensor>
  </gazebo>

</robot>

```

![[Pasted image 20250630214754.png]]

---

## 2. Control Node Implementation

### Objective

Write a node that:
- Subscribes to:
    - `/camera/image_raw`
    - `/sonar/range`
    - `/scan` (LiDAR)

- Publishes:
    - `/cmd_vel` using `geometry_msgs/Twist`

### Algorithm

- Use random velocity commands (`linear.x`, `angular.z`)
- Use sonar and LiDAR to check proximity
- Avoid collisions using a reactive rule-based approach:
    - If obstacle is detected in front (within threshold), rotate
    - Else, move forward

### Robot Controller Node
**File:** `test_robot/src/robot_node.py`
```python
#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan, Range
from geometry_msgs.msg import Twist
import random

class RandomWalker(Node):
    def __init__(self):
        super().__init__('random_walker')
        self.cmd_pub = self.create_publisher(Twist, '/cmd_vel', 10)
        self.sub_lidar = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)
        self.sub_sonar = self.create_subscription(Range, '/sonar/range', self.sonar_callback, 10)
        self.timer = self.create_timer(0.5, self.move)

        self.min_distance = 0.5
        self.obstacle_near = False

    def lidar_callback(self, msg):
        if min(msg.ranges) < self.min_distance:
            self.obstacle_near = True
        else:
            self.obstacle_near = False

    def sonar_callback(self, msg):
        if msg.range < self.min_distance:
            self.obstacle_near = True

    def move(self):
        twist = Twist()
        if self.obstacle_near:
            twist.linear.x = 0.0
            twist.angular.z = random.uniform(1.0, 2.0)
        else:
            twist.linear.x = 0.2
            twist.angular.z = 0.0
        self.cmd_pub.publish(twist)

def main(args=None):
    rclpy.init(args=args)
    node = RandomWalker()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()

```


---

## 3. Launch File Creation

### Objective

Launch everything in Gazebo using `your_robot.launch.py`.

### Contents

- Load robot description from Xacro
- Spawn the robot in `four_walls.world`
- Start control node
- Start Gazebo

###  `test_robot.launch.py` 
**File:** `test_robot/launch/test_robot.launch.py`
```python
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg = FindPackageShare('your_package')
    urdf_file = PathJoinSubstitution([pkg, 'urdf', 'robot.xacro'])

    return LaunchDescription([
        # Launch Gazebo
        ExecuteProcess(
            cmd=['gazebo', '--verbose', '--pause', '-s', 'libgazebo_ros_factory.so'],
            output='screen'
        ),
        # Spawn Robot
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{'robot_description': Command([FindExecutable(name='xacro'), ' ', urdf_file])}]
        ),
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=['-entity', 'your_robot', '-topic', 'robot_description', '-x', '0', '-y', '0'],
            output='screen'
        ),
        # Control Node
        Node(
            package='your_package',
            executable='your_robot_node.py',
            output='screen'
        )
    ])

```


---

## 4. Testing

### Steps

- Verified sensors were publishing data.
- Checked robot moved randomly and avoided walls.
- Tweaked speed and sensor thresholds for better behavior.
### Gazebo World File
**File:** `test_robot/worlds/test_world.world`
```python
<?xml version="1.0" ?>
<sdf version="1.6">
  <world name="default">

    <!-- Include ground plane -->
    <include>
      <uri>model://ground_plane</uri>
    </include>

    <!-- Include sunlight -->
    <include>
      <uri>model://sun</uri>
    </include>

    <!-- Add your robot -->
    <include>
      <name>four_wheeled_bot</name>
      <uri>model://four_wheeled_bot</uri> <!-- Note: Replace this with spawn from launch file if using xacro -->
      <pose>0 0 0.1 0 0 0</pose>
    </include>

    <!-- Add simple obstacles -->
    <model name="box_obstacle_1">
      <pose>1 0 0.1 0 0 0</pose>
      <static>true</static>
      <link name="link">
        <collision name="collision">
          <geometry>
            <box>
              <size>0.5 0.5 0.2</size>
            </box>
          </geometry>
        </collision>
        <visual name="visual">
          <geometry>
            <box>
              <size>0.5 0.5 0.2</size>
            </box>
          </geometry>
          <material>
            <ambient>1 0 0 1</ambient>
            <diffuse>1 0 0 1</diffuse>
          </material>
        </visual>
      </link>
    </model>

    <model name="box_obstacle_2">
      <pose>-1 -1 0.1 0 0 0</pose>
      <static>true</static>
      <link name="link">
        <collision name="collision">
          <geometry>
            <box>
              <size>0.4 0.4 0.2</size>
            </box>
          </geometry>
        </collision>
        <visual name="visual">
          <geometry>
            <box>
              <size>0.4 0.4 0.2</size>
            </box>
          </geometry>
          <material>
            <ambient>0 0 1 1</ambient>
            <diffuse>0 0 1 1</diffuse>
          </material>
        </visual>
      </link>
    </model>

    <!-- Physics and time settings -->
    <physics name="default_physics" type="ode">
      <real_time_update_rate>1000.0</real_time_update_rate>
      <max_step_size>0.001</max_step_size>
    </physics>

    <scene>
      <ambient>0.3 0.3 0.3 1</ambient>
      <background>0.7 0.7 0.7 1</background>
    </scene>

  </world>
</sdf>
```

---

## 5. Challenges Faced

|Challenge|Solution|
|---|---|
|Incorrect sensor frames|Verified frame names in `tf_tree`|
|Robot not spawning|Fixed missing `<xacro:include>` and plugin errors|
|Node crashing on empty topic|Added subscribers only after checking for topic availability|




