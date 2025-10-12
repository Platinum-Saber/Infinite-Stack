
## Method 1: List and inspect topics

First, check what topics are available:

```bash
# List all active topics
ros2 topic list

# Get detailed info about the laser scan topic
ros2 topic info /scan

# Show the message type and structure
ros2 interface show sensor_msgs/msg/LaserScan
```

> [!image] What to expect
> ![[Pasted image 20250801121113.png]]

## Method 2: Echo topic data in terminal

View the raw laser scan data:

```bash
# View laser scan data (this will be quite verbose)
ros2 topic echo /scan

# View just a few messages
ros2 topic echo /scan --once

# View with reduced output
ros2 topic echo /scan --field ranges
```

#### Results

> [!image] What to expect
> ![[Pasted image 20250801121245.png]]


## Method 3: Use RViz2 for visualization

RViz2 is the best tool for visualizing lidar data:

```bash
# Launch RViz2
rviz2

# Or launch with a pre-configured setup
ros2 run rviz2 rviz2 -d /opt/ros/humble/share/rviz_common/default.rviz
```

In RViz2:
1. Click **Add** → **By topic** → **LaserScan** → **OK**
2. Set **Fixed Frame** to `laser` or `base_link`
3. The lidar data should appear as red dots showing detected obstacles

> [!image] What to expect
> - The docker container will forward the RViz window through a port to a web view using `noVNC` (Because no GUI for the docker environment)
> - Open the port in the browser.
> ![[Pasted image 20250801123253.png]]
> ![[lidar_rviz_test.png]]

## Method 4: Plot data with rqt

Use rqt tools for plotting and analysis:

```bash
# Launch rqt with plot plugin
rqt_plot

# Or launch full rqt suite
rqt
```

In rqt_plot:
- Add `/scan/ranges[0]` to plot the first range measurement
- Add `/scan/ranges[180]` to plot the front-facing measurement

## Method 5: Monitor topic frequency and bandwidth

Check if data is being published correctly:

```bash
# Check publishing frequency
ros2 topic hz /scan

# Check bandwidth usage
ros2 topic bw /scan

# Get topic statistics
ros2 topic info /scan --verbose
```

## Method 6: Create a simple subscriber node

Create a Python script to process lidar data:

````python
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
import numpy as np

class LidarViewer(Node):
    def __init__(self):
        super().__init__('lidar_viewer')
        self.subscription = self.create_subscription(
            LaserScan,
            '/scan',
            self.scan_callback,
            10)
        
    def scan_callback(self, msg):
        # Convert ranges to numpy array
        ranges = np.array(msg.ranges)
        
        # Filter out invalid readings
        valid_ranges = ranges[(ranges > msg.range_min) & (ranges < msg.range_max)]
        
        # Print basic statistics
        if len(valid_ranges) > 0:
            self.get_logger().info(f'Valid points: {len(valid_ranges)}, '
                                 f'Min distance: {np.min(valid_ranges):.2f}m, '
                                 f'Max distance: {np.max(valid_ranges):.2f}m')

def main():
    rclpy.init()
    node = LidarViewer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
````

Save this as `lidar_viewer.py`, make it executable, and run:

```bash
chmod +x lidar_viewer.py
python3 lidar_viewer.py
```

## Method 7: Launch everything together

Create a launch file to start RPLidar and RViz2 together:

````python
# Create file: launch_lidar_viz.py
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Launch RPLidar
        Node(
            package='rplidar_ros',
            executable='rplidar_node',
            name='rplidar_node',
            parameters=[{
                'serial_port': '/dev/ttyUSB0',
                'frame_id': 'laser',
                'inverted': False,
                'angle_compensate': True,
            }]
        ),
        
        # Launch RViz2
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', '/opt/ros/humble/share/rviz_common/default.rviz']
        )
    ])
````

Run with:
```bash
ros2 launch launch_lidar_viz.py
```

The most user-friendly approach is **Method 3** using RViz2, as it provides a real-time visual representation of the lidar data. The GUI will open on the desktop that you can access via VNC or web browser.