
A ROS 2 launch package for Orbbec Astra Pro depth cameras, providing easy-to-use launch files for camera initialization, visualization, and integration with computer vision applications.

## Overview

- The `astra_bringup` package provides simplified launch files for Orbbec Astra series cameras, specifically optimized for the **Astra Pro** and **Astra Pro 2** models. 
- This package wraps the official `orbbec_camera` driver with convenient default configurations and RViz visualization.

## Camera Specifications

### Supported Models
- **Orbbec Astra Pro**
- **Orbbec Astra Pro 2** 
- **Orbbec Astra** (basic model)
- **Orbbec Astra 2**

### Technical Specifications

#### Astra Pro / Pro 2
| Specification | Details |
|--------------|---------|
| **RGB Camera** | 640×480 @ 30 FPS |
| **Depth Camera** | 640×480 @ 30 FPS |
| **Depth Range** | 0.3m - 8.0m |
| **Depth Technology** | Structured Light |
| **FOV (Depth)** | 60° H × 49.5° V |
| **FOV (RGB)** | 60° H × 49.5° V |
| **Interface** | USB 2.0/3.0 |
| **Power** | USB Bus Powered |
| **Operating Range** | 0.3m - 8.0m |

#### Depth Accuracy
- **@ 1m**: ±3mm
- **@ 2m**: ±6mm  
- **@ 3m**: ±15mm
- **@ 5m**: ±50mm

## Package Structure

```
astra_bringup/
├── package.xml                    # Package metadata
├── setup.py                      # Python package setup
├── launch/
│   ├── astra_local.launch.py     # Basic camera launch
│   └── astra_with_rviz.launch.py # Camera + RViz visualization
├── rviz/
│   └── astra_visualization.rviz  # RViz configuration
└── resource/
    └── astra_bringup            # Resource marker
```

## Launch Files

### 1. `astra_local.launch.py`
Basic camera launcher without visualization.

**Default Configuration:**
```yaml
RGB Stream:
  - Resolution: 640×480
  - FPS: 30
  - Format: MJPG
  - Enabled: true

Depth Stream:
  - Resolution: 640×480  
  - FPS: 30
  - Format: Y11 (11-bit)
  - Enabled: true

Other:
  - IR Stream: Disabled
  - Point Cloud: Disabled
  - Depth Registration: Disabled
```

### 2. `astra_with_rviz.launch.py`
Camera launcher with RViz visualization for immediate visual feedback.

**Includes:**
- All features from `astra_local.launch.py`
- Pre-configured RViz with RGB, depth, and point cloud displays
- Camera frame visualization

## Published Topics

### Camera Topics
| Topic | Type | Description |
|-------|------|-------------|
| `/camera/color/image_raw` | `sensor_msgs/Image` | Raw RGB image stream |
| `/camera/color/camera_info` | `sensor_msgs/CameraInfo` | RGB camera calibration |
| `/camera/depth/image_raw` | `sensor_msgs/Image` | Raw depth image (16-bit) |
| `/camera/depth/camera_info` | `sensor_msgs/CameraInfo` | Depth camera calibration |
| `/camera/ir/image_raw` | `sensor_msgs/Image` | Infrared image (if enabled) |
| `/camera/ir/camera_info` | `sensor_msgs/CameraInfo` | IR camera calibration |

### Point Cloud Topics (when enabled)
| Topic | Type | Description |
|-------|------|-------------|
| `/camera/points` | `sensor_msgs/PointCloud2` | 3D point cloud |
| `/camera/colored_points` | `sensor_msgs/PointCloud2` | RGB colored point cloud |

### Transform Topics
| Topic | Type | Description |
|-------|------|-------------|
| `/tf` | `geometry_msgs/TransformStamped` | Camera coordinate frames |
| `/tf_static` | `geometry_msgs/TransformStamped` | Static transforms |

## Camera Frames

The camera publishes several coordinate frames:
- `camera_link` - Physical camera base frame
- `camera_color_frame` - RGB camera frame  
- `camera_color_optical_frame` - RGB optical frame (ROS standard)
- `camera_depth_frame` - Depth camera frame
- `camera_depth_optical_frame` - Depth optical frame (ROS standard)
- `camera_ir_frame` - IR camera frame (if enabled)
- `camera_ir_optical_frame` - IR optical frame (if enabled)

## Usage

### Basic Launch Commands

#### Launch Camera Only
```bash
# Basic camera launch
ros2 launch astra_bringup astra_local.launch.py

# Camera with visualization
ros2 launch astra_bringup astra_with_rviz.launch.py
```

#### Custom Parameters
```bash
# Custom resolution and frame rate
ros2 launch astra_bringup astra_local.launch.py \
    color_width:=1280 \
    color_height:=720 \
    color_fps:=15 \
    depth_fps:=15

# Enable point cloud
ros2 launch astra_bringup astra_local.launch.py \
    enable_point_cloud:=true \
    enable_colored_point_cloud:=true

# Disable RViz in visualization launch
ros2 launch astra_bringup astra_with_rviz.launch.py \
    use_rviz:=false
```

### Advanced Configuration
```bash
# Multiple cameras (specify serial number)
ros2 launch astra_bringup astra_local.launch.py \
    serial_number:=YOUR_CAMERA_SERIAL \
    camera_name:=camera1

# Depth registration (align depth to RGB)
ros2 launch astra_bringup astra_local.launch.py \
    depth_registration:=true

# Enable IR stream
ros2 launch astra_bringup astra_local.launch.py \
    enable_ir:=true \
    ir_width:=640 \
    ir_height:=480 \
    ir_fps:=30
```

## Useful ROS Commands

### Camera Information
```bash
# List camera topics
ros2 topic list | grep camera

# Check camera info
ros2 topic echo /camera/color/camera_info --once
ros2 topic echo /camera/depth/camera_info --once

# Monitor topic frequencies
ros2 topic hz /camera/color/image_raw
ros2 topic hz /camera/depth/image_raw

# Check image resolution
ros2 topic echo /camera/color/image_raw --once | grep -E "(width|height)"
```

### Diagnostics
```bash
# Check camera node status
ros2 node list | grep camera
ros2 node info /camera/camera

# View camera parameters
ros2 param list /camera/camera
ros2 param get /camera/camera depth_width
ros2 param get /camera/camera color_fps

# Check transform tree
ros2 run tf2_tools view_frames.py
ros2 run tf2_ros tf2_echo camera_link camera_color_optical_frame
```

### Image Visualization
```bash
# View images using image_view
ros2 run image_view image_view --ros-args --remap image:=/camera/color/image_raw
ros2 run image_view image_view --ros-args --remap image:=/camera/depth/image_raw

# Display disparity image
ros2 run image_view disparity_view --ros-args --remap image:=/camera/depth/image_raw

# Save images
ros2 run image_view image_saver --ros-args --remap image:=/camera/color/image_raw
```

### Point Cloud Operations
```bash
# View point cloud in RViz
rviz2 &
# Add PointCloud2 display, set topic to /camera/points

# Save point cloud to PCD file
ros2 run pcl_ros pointcloud_to_pcd --ros-args --remap input:=/camera/points

# Check point cloud info
ros2 topic echo /camera/points --once | head -20
```

## Integration Examples

### With Ball Detection Packages
```bash
# Launch camera with red ball detector
ros2 launch astra_bringup astra_local.launch.py &
ros2 launch red_ball_detector red_ball_detection.launch.py

# Launch camera with football detector  
ros2 launch astra_bringup astra_local.launch.py &
ros2 launch football_detector football_detection.launch.py

# Complete ball tracking system
ros2 launch ball_trajectory_predictor complete_ball_tracking.launch.py
```

### With SLAM/Navigation
```bash
# Launch camera for SLAM
ros2 launch astra_bringup astra_local.launch.py \
    enable_point_cloud:=true \
    depth_registration:=true

# Use with RTAB-Map SLAM
ros2 launch rtabmap_ros rtabmap.launch.py \
    rgb_topic:=/camera/color/image_raw \
    depth_topic:=/camera/depth/image_raw \
    camera_info_topic:=/camera/color/camera_info
```

## Troubleshooting

### Common Issues

#### Camera Not Detected
```bash
# Check USB connection
lsusb | grep 2bc5  # Orbbec vendor ID

# Check permissions
sudo usermod -a -G plugdev $USER  # Add user to plugdev group
# Logout and login again

# Check udev rules
ls /etc/udev/rules.d/ | grep orbbec
```

#### Low Frame Rate
```bash
# Check USB version (should be 3.0 for full performance)
ros2 param set /camera/camera retry_on_usb3_detection_failure false

# Reduce resolution or frame rate
ros2 launch astra_bringup astra_local.launch.py \
    color_width:=320 \
    color_height:=240 \
    color_fps:=15
```

#### Depth Quality Issues
```bash
# Check depth range
ros2 topic echo /camera/depth/image_raw --once

# Adjust depth format
ros2 launch astra_bringup astra_local.launch.py \
    depth_format:=Y16  # Try different format

# Enable depth registration for alignment
ros2 launch astra_bringup astra_local.launch.py \
    depth_registration:=true
```

#### Multiple Cameras
```bash
# List connected cameras
ros2 run orbbec_camera list_devices_node

# Launch with specific serial number
ros2 launch astra_bringup astra_local.launch.py \
    serial_number:=CAMERA_SERIAL_NUMBER \
    camera_name:=camera1
```

## Available Parameters

### Camera Selection
- `camera_name`: Camera namespace (default: 'camera')
- `serial_number`: Specific camera serial number
- `device_num`: Device number for multiple cameras
- `usb_port`: Specific USB port

### RGB Stream
- `enable_color`: Enable RGB stream (true/false)
- `color_width`: RGB width (320, 640, 1280)
- `color_height`: RGB height (240, 480, 720)
- `color_fps`: RGB frame rate (5, 10, 15, 30)
- `color_format`: RGB format (RGB, BGR, UYVY, MJPG)

### Depth Stream  
- `enable_depth`: Enable depth stream (true/false)
- `depth_width`: Depth width (320, 640)
- `depth_height`: Depth height (240, 480)
- `depth_fps`: Depth frame rate (5, 10, 15, 30)
- `depth_format`: Depth format (Y11, Y16)

### Point Cloud
- `enable_point_cloud`: Enable point cloud (true/false)
- `enable_colored_point_cloud`: Enable RGB colored points (true/false)
- `cloud_frame_id`: Point cloud frame ID

### Advanced
- `depth_registration`: Align depth to RGB (true/false)
- `connection_delay`: Camera connection delay (ms)
- `enable_ir`: Enable infrared stream (true/false)

## Performance Tips

### Optimization for Real-Time Applications
1. **Reduce Resolution**: Use 320×240 for high-speed applications
2. **Lower Frame Rate**: 15 FPS often sufficient for most applications
3. **Disable Unused Streams**: Turn off IR or point cloud if not needed
4. **USB 3.0**: Ensure camera connected to USB 3.0 port
5. **QoS Settings**: Use appropriate QoS profiles for your network setup

### Memory Usage
- RGB stream: ~1MB/frame (640×480 MJPG)
- Depth stream: ~600KB/frame (640×480 Y11)
- Point cloud: ~2-5MB/frame (depends on range)

## Applications

The Astra Pro camera launcher is ideal for:
- **Robotics**: Mobile robot navigation and SLAM
- **Computer Vision**: Object detection and tracking
- **Augmented Reality**: 3D scene reconstruction
- **Gaming**: Gesture recognition and motion capture  
- **Industrial**: Quality inspection and measurement
- **Research**: Computer vision algorithm development

## Dependencies

### Required Packages
- `orbbec_camera`: Official Orbbec ROS 2 driver
- `sensor_msgs`: Standard sensor message types
- `geometry_msgs`: Transform and pose messages
- `tf2_ros`: Transform framework
- `rviz2`: Visualization (for rviz launch file)

### System Requirements
- **OS**: Ubuntu 20.04+ (ROS 2 Foxy+)
- **USB**: USB 2.0+ (USB 3.0 recommended)
- **Memory**: 4GB+ RAM
- **CPU**: Multi-core processor recommended