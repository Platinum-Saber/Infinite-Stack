
## Step 1: Launch RViz2

Since you have the desktop environment available, launch RViz2 from the terminal:

```bash
rviz2
```

This will open RViz2 in your Fluxbox desktop (accessible via web on port 6080 or VNC on port 5901).

## Step 2: Set up the Fixed Frame

1. In the **Global Options** panel (left side), set the **Fixed Frame** to `laser` (or whatever frame_id your RPLidar is publishing)
2. If `laser` doesn't work, try `base_link` or check what frame your lidar is using:

```bash
ros2 topic echo /scan --once | grep frame_id
```

## Step 3: Add LaserScan Display

1. Click the **Add** button at the bottom of the Displays panel
2. Select **By topic** tab
3. Expand the `/scan` topic
4. Select **LaserScan** and click **OK**

## Step 4: Configure LaserScan Display

In the LaserScan display properties:
- Set **Size (m)** to `0.05` (makes points more visible)
- Set **Style** to **Points** or **Flat Squares**
- Change **Color** to red or green for better visibility
- Set **Decay Time** to `0` for real-time data

## Step 5: Add additional useful displays

Add a Grid for reference:
1. Click **Add** → **By display type** → **Grid** → **OK**
2. Configure Grid:
   - **Reference Frame**: `laser`
   - **Plane Cell Count**: `20`
   - **Cell Size**: `1.0`

Add Axes for orientation:
1. Click **Add** → **By display type** → **Axes** → **OK**
2. Configure Axes:
   - **Reference Frame**: `laser`
   - **Length**: `0.5`

## Step 6: Save configuration

Save your RViz configuration for future use:
1. Go to **File** → **Save Config As**
2. Save as `lidar_config.rviz` in your workspace

## Step 7: Create a launch file with RViz config

Create a launch file that starts both RPLidar and RViz with your configuration:

````python
from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Path to your saved RViz config
    rviz_config = os.path.join('/Container', 'lidar_config.rviz')
    
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
            }],
            output='screen'
        ),
        
        # Launch RViz2 with config
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config] if os.path.exists(rviz_config) 
                      else ['-d', '/opt/ros/humble/share/rviz_common/default.rviz'],
            output='screen'
        )
    ])
````

## Step 8: Launch everything together

```bash
cd /Container/ros2_ws/src
ros2 launch lidar_viz_launch.py
```

## Troubleshooting Tips

If you don't see lidar data:

1. **Check if data is being published**:
   ```bash
   ros2 topic list | grep scan
   ros2 topic hz /scan
   ```

2. **Verify frame_id matches**:
   ```bash
   ros2 topic echo /scan --once | grep frame_id
   ```

3. **Check TF tree** (if using transforms):
   ```bash
   ros2 run tf2_tools view_frames
   ```

4. **Reset RViz views**:
   - In RViz, go to **Views** panel
   - Click **Type** dropdown and select **Orbit**
   - Use mouse to zoom and rotate the view

The lidar data should appear as colored points showing obstacles detected by the sensor. You can rotate and zoom the view to see the data from different angles.