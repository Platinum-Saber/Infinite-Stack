
## Complete Multi-Robot Navigation Project Layout

## Main Workspace Structure

```
~/multirobot_ws/                          # Main ROS2 workspace
├── src/                                  # Source code directory
│   ├── micro_ros_setup/                 # micro-ROS setup package (auto-generated)
│   └── multirobot_nav/                  # Main navigation package
└── build/                               # Build artifacts (auto-generated)
└── install/                             # Install artifacts (auto-generated)
└── log/                                 # Build logs (auto-generated)
```

---

## Detailed Package Structure

```
~/multirobot_ws/src/multirobot_nav/
├── package.xml                          # Package metadata and dependencies
├── setup.py                            # Python package setup file
├── setup.cfg                           # Setup configuration
├── resource/                            # Package resource files
│   └── multirobot_nav                  # Empty marker file
├── multirobot_nav/                     # Python source code directory
│   ├── __init__.py                     # Python package initializer
│   ├── robot_coordinator.py           # Multi-robot coordination node
│   ├── robot_controller.py            # Individual robot control node
│   └── multi_robot_slam.py            # Multi-robot SLAM node
├── launch/                             # Launch file directory
│   ├── multirobot_launch.py           # Main system launch file
│   ├── robot1_launch.py               # Robot 1 specific launch (optional)
│   └── robot2_launch.py               # Robot 2 specific launch (optional)
├── config/                             # Configuration files
│   ├── robot_params.yaml              # Robot parameters
│   ├── slam_params.yaml               # SLAM configuration
│   └── navigation.rviz                 # RViz configuration file
├── maps/                               # Saved map files (created at runtime)
│   ├── office_map.pgm                 # Map image file
│   ├── office_map.yaml                # Map metadata file
│   └── waypoints.yaml                 # Saved waypoints (optional)
└── test/                               # Unit tests (optional)
    ├── test_coordinator.py            # Coordinator tests
    └── test_slam.py                    # SLAM tests
```

---

## File Contents and Purposes

### **Root Files**

#### **`package.xml`**
```xml
<?xml version="1.0"?>
<package format="3">
  <n>multirobot_nav</n>
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

  <export>
    <build_type>ament_python</build_type>
  </export>
</package>
```

#### **`setup.py`**
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

#### **`setup.cfg`**
```ini
[develop]
script_dir=$base/lib/multirobot_nav
[install]
install_scripts=$base/lib/multirobot_nav
```

### **Python Source Files**

#### **`multirobot_nav/__init__.py`**
```python
# Empty file marking this as a Python package
```

#### **`multirobot_nav/robot_coordinator.py`**
```python
#!/usr/bin/env python3
"""
Multi-robot coordination node
Manages exploration goals and collision avoidance between robots
"""
import rclpy
from rclpy.node import Node
# ... (full implementation as shown in previous documentation)
```

#### **`multirobot_nav/robot_controller.py`**
```python
#!/usr/bin/env python3
"""
Individual robot controller node
Handles navigation and obstacle avoidance for a single robot
"""
import rclpy
from rclpy.node import Node
# ... (full implementation as shown in previous documentation)
```

#### **`multirobot_nav/multi_robot_slam.py`**
```python
#!/usr/bin/env python3
"""
Multi-robot SLAM node
Combines LiDAR data from multiple robots for unified mapping
"""
import rclpy
from rclpy.node import Node
# ... (full implementation as shown in previous documentation)
```

### **Launch Files**

#### **`launch/multirobot_launch.py`**
```python
#!/usr/bin/env python3
"""
Main launch file for multi-robot navigation system
Starts all necessary nodes and micro-ROS agents
"""
from launch import LaunchDescription
from launch_ros.actions import Node
# ... (full implementation as shown in previous documentation)
```

#### **`launch/robot1_launch.py`** (Optional)
```python
#!/usr/bin/env python3
"""
Robot 1 specific launch file
For testing individual robot functionality
"""
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='micro_ros_agent',
            executable='micro_ros_agent',
            arguments=['udp4', '--port', '8888'],
            name='micro_ros_agent_robot1'
        ),
        
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
        )
    ])
```

### **Configuration Files**

#### **`config/robot_params.yaml`**
```yaml
# Robot Controller Parameters
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
```

#### **`config/slam_params.yaml`**
```yaml
# SLAM Configuration Parameters
multi_robot_slam:
  ros__parameters:
    map_resolution: 0.05
    map_width: 2000
    map_height: 2000
    update_rate: 5.0
    raytracing_max_range: 12.0
    obstacle_inflation_radius: 0.2
    
    # Map origin (center of map in world coordinates)
    map_origin_x: -50.0  # meters
    map_origin_y: -50.0  # meters
    
    # Publishing settings
    publish_map_updates: true
    map_update_threshold: 10  # cells changed before publishing
    
    # Quality settings  
    min_ray_length: 0.15
    max_ray_length: 12.0
    hit_probability: 0.7
    miss_probability: 0.3
```

#### **`config/navigation.rviz`**
```yaml
Panels:
  - Class: rviz_common/Displays
    Help Height: 78
    Name: Displays
    Property Tree Widget:
      Expanded:
        - /Global Options1
        - /Status1
        - /Robot1_LaserScan1
        - /Robot2_LaserScan1
        - /Map1
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
      Class: rviz_default_plugins/LaserScan
      Color: 255; 0; 0
      Name: Robot1_LaserScan
      Topic:
        Depth: 5
        Durability Policy: Volatile
        Filter size: 10
        History Policy: Keep Last
        Reliability Policy: Reliable
        Value: /robot1/scan
      Use Fixed Frame: true
      Use rainbow: true
      Value: true
      
    - Alpha: 1
      Autocompute Intensity Bounds: true
      Class: rviz_default_plugins/LaserScan
      Color: 0; 0; 255
      Name: Robot2_LaserScan
      Topic:
        Depth: 5
        Durability Policy: Volatile
        Filter size: 10
        History Policy: Keep Last
        Reliability Policy: Reliable
        Value: /robot2/scan
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
  Value: true
  Views:
    Current:
      Class: rviz_default_plugins/Orbit
      Distance: 20
      Enable Stereo Rendering:
        Stereo Eye Separation: 0.05999999865889549
        Stereo Focal Distance: 1
        Swap Stereo Eyes: false
        Value: false
      Focal Point:
        X: 0
        Y: 0
        Z: 0
      Focal Shape Fixed Size: true
      Focal Shape Size: 0.05000000074505806
      Invert Z Axis: false
      Name: Current View
      Near Clip Distance: 0.009999999776482582
      Pitch: 1.5697963237762451
      Target Frame: <Fixed Frame>
      Yaw: 0
    Saved: ~
```

### **Resource Files**

#### **`resource/multirobot_nav`**
```
# Empty marker file for ROS2 package discovery
```

---

## Build and Runtime Directories

### **Auto-Generated Directories**

#### **`build/`** - Compilation artifacts
```
build/
├── multirobot_nav/
│   ├── build.ninja
│   ├── compile_commands.json
│   └── ...build files...
└── micro_ros_setup/
    └── ...build files...
```

#### **`install/`** - Installed packages
```
install/
├── setup.bash                          # Main environment setup
├── setup.sh                           # Shell setup
├── setup.zsh                          # Zsh setup  
├── local_setup.bash                   # Local environment setup
├── multirobot_nav/
│   ├── lib/
│   │   └── multirobot_nav/
│   │       ├── robot_coordinator      # Executable
│   │       ├── robot_controller       # Executable
│   │       └── multi_robot_slam       # Executable
│   └── share/
│       └── multirobot_nav/
│           ├── launch/               # Installed launch files
│           ├── config/               # Installed config files
│           └── package.xml           # Package metadata
└── micro_ros_setup/
    └── ...installed files...
```

#### **`log/`** - Build and runtime logs
```
log/
├── build_2024-01-15_14-30-45/         # Build logs by date
│   ├── multirobot_nav/
│   │   ├── stdout.log
│   │   ├── stderr.log
│   │   └── streams.log
│   └── events.log
└── latest_build -> build_2024-01-15_14-30-45/  # Symlink to latest
```

---

## Runtime Generated Files

### **Maps Directory** (created during operation)
```
maps/
├── exploration_map_2024-01-15.pgm     # Generated map image
├── exploration_map_2024-01-15.yaml    # Map metadata
├── waypoints_robot1.yaml              # Saved waypoints for robot1
├── waypoints_robot2.yaml              # Saved waypoints for robot2
└── session_2024-01-15_14-30-45/       # Session-specific data
    ├── robot1_path.csv                # Robot 1 trajectory
    ├── robot2_path.csv                # Robot 2 trajectory
    └── coordination_log.txt           # Coordination decisions
```

---

## Setup and Build Commands

### **Creating the Workspace Structure**
```bash
# Create main workspace
mkdir -p ~/multirobot_ws/src
cd ~/multirobot_ws

# Create package structure
cd src
ros2 pkg create --build-type ament_python multirobot_nav \
    --dependencies rclpy sensor_msgs geometry_msgs nav_msgs tf2_ros

# Create additional directories
cd multirobot_nav
mkdir -p launch config maps test
```

### **Building the Workspace**
```bash
cd ~/multirobot_ws

# Build all packages
colcon build

# Build specific package only
colcon build --packages-select multirobot_nav

# Build with debug symbols
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Debug
```

### **Sourcing the Environment**
```bash
# Source ROS2 base
source /opt/ros/foxy/setup.bash

# Source workspace (after building)
source ~/multirobot_ws/install/setup.bash

# Add to ~/.bashrc for automatic sourcing
echo "source ~/multirobot_ws/install/setup.bash" >> ~/.bashrc
```

---

## Development Workflow

### **Typical Development Cycle**
```bash
# 1. Edit source files
nano ~/multirobot_ws/src/multirobot_nav/multirobot_nav/robot_coordinator.py

# 2. Build package
cd ~/multirobot_ws
colcon build --packages-select multirobot_nav

# 3. Source environment (if not in ~/.bashrc)
source install/setup.bash

# 4. Run/test
ros2 launch multirobot_nav multirobot_launch.py
```

### **Testing Individual Nodes**
```bash
# Test coordinator node
ros2 run multirobot_nav robot_coordinator

# Test with parameters
ros2 run multirobot_nav robot_controller --ros-args -p robot_name:=robot1

# Test launch file
ros2 launch multirobot_nav robot1_launch.py
```

This structure provides a clean, organized workspace that follows ROS2 conventions and supports multi-robot development, testing, and deployment.