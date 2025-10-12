This ROS 2 package detects red balls using the Astra camera's color feed and measures their distance using the depth camera.

## Features

- **Real-time red ball detection** using HSV color space filtering
- **3D position estimation** using synchronized color and depth images
- **Distance measurement** from camera to detected ball
- **ROI (Region of Interest) visualization** with bounding boxes around detected balls
- **Color analysis and display** showing detected color values (BGR/HSV)
- **Enhanced debug visualization** with detection overlay, ROI boxes, and color information
- **Configurable parameters** for tuning detection sensitivity

## Topics

### Subscribed Topics
- `/camera/color/image_raw` (sensor_msgs/Image) - RGB camera feed
- `/camera/depth/image_raw` (sensor_msgs/Image) - Depth camera feed  
- `/camera/color/camera_info` (sensor_msgs/CameraInfo) - Camera calibration

### Published Topics
- `/ball_position` (geometry_msgs/PointStamped) - 3D position of detected ball
- `/ball_distance` (std_msgs/Float32) - Distance to ball in meters
- `/ball_detection_debug` (sensor_msgs/Image) - Debug image with detection overlay

## Parameters

- `min_radius` (int, default: 10) - Minimum ball radius in pixels
- `max_radius` (int, default: 100) - Maximum ball radius in pixels  
- `min_area` (int, default: 500) - Minimum contour area for detection
- `publish_debug_image` (bool, default: true) - Whether to publish debug images
- `hsv_lower_red1` (int array) - Lower HSV range for red detection
- `hsv_upper_red1` (int array) - Upper HSV range for red detection
- `hsv_lower_red2` (int array) - Lower HSV range for red detection (second range)
- `hsv_upper_red2` (int array) - Upper HSV range for red detection (second range)

## Usage

### 1. Launch Camera + Ball Detection + RViz
```bash
cd ~/ROS_Jazzy/ros2_ws
source install/setup.zsh
ros2 launch red_ball_detector red_ball_detection.launch.py
```

### 2. Launch without RViz
```bash
ros2 launch red_ball_detector red_ball_detection.launch.py use_rviz:=false
```

### 3. Run only the detector node
```bash
# First start the camera
ros2 launch astra_bringup astra_local.launch.py

# Then start the detector
ros2 run red_ball_detector red_ball_detector_node
```

### 4. Monitor detection results
```bash
ros2 run red_ball_detector monitor_node
```

### 5. Check detection topics
```bash
# View ball position
ros2 topic echo /ball_position

# View ball distance  
ros2 topic echo /ball_distance

# List all topics
ros2 topic list
```

## Tuning Detection Parameters

You can tune the HSV color ranges for better red ball detection. Use the debug visualization to see the detected color values and adjust parameters accordingly:

```bash
# Adjust HSV ranges based on debug color display
ros2 param set /red_ball_detector hsv_lower_red1 "[0, 120, 120]"
ros2 param set /red_ball_detector hsv_upper_red1 "[10, 255, 255]"

# Adjust detection area and size constraints
ros2 param set /red_ball_detector min_area 500
ros2 param set /red_ball_detector min_radius 10
ros2 param set /red_ball_detector max_radius 100
```

### Using Color Information for Tuning
1. **View debug image**: `ros2 run rqt_image_view rqt_image_view /ball_detection_debug`
2. **Check displayed BGR/HSV values**: Use these to refine HSV ranges
3. **Adjust parameters**: Modify HSV bounds based on actual detected colors
4. **Test in different lighting**: Lighting conditions affect color detection significantly

## Dependencies

- OpenCV (cv2)
- cv_bridge
- message_filters  
- sensor_msgs
- geometry_msgs
- std_msgs

## Algorithm Overview

1. **Color Detection**: Converts RGB to HSV and applies color filtering for red objects
2. **Contour Detection**: Finds contours in the filtered image
3. **Circle Fitting**: Fits minimum enclosing circles to detected contours
4. **ROI Analysis**: Calculates bounding rectangles and extracts color information
5. **Depth Lookup**: Uses synchronized depth image to get 3D coordinates
6. **Distance Calculation**: Computes Euclidean distance from camera to ball

## Debug Visualization Features

The debug image (`/ball_detection_debug` topic) provides comprehensive visual feedback:

### Visual Elements
- **Green ROI Box**: Rectangular bounding box around detected ball
- **Yellow Circle**: Detection circle showing ball center and radius
- **Red Center Point**: Precise center location of detected ball
- **Distance Text**: Real-time distance measurement above ROI
- **Color Sample**: Rectangle showing the actual detected color
- **Color Values**: BGR and HSV numerical values for color analysis

### Visual Layout
```
[Distance: 0.05m]     ← Distance measurement
┌─────────────────┐   ← ROI bounding box (green)
│   ● Red Ball    │   ← Ball with detection circle
└─────────────────┘
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓   ← Color sample rectangle
BGR: (45, 52, 198)    ← Blue-Green-Red values (0-255)
HSV: (2, 227, 198)    ← Hue-Saturation-Value for tuning
```

## Coordinate System

- Frame: `camera_color_optical_frame`
- X: Right (from camera perspective)
- Y: Down  
- Z: Forward (away from camera)

## Troubleshooting

### No detections?
1. Check if the ball is truly red and well-lit
2. **Use debug visualization**: `ros2 run rqt_image_view rqt_image_view /ball_detection_debug`
3. **Check color values**: Look at BGR/HSV values in debug image to understand detected colors
4. **Adjust HSV parameters**: Use actual detected color values to refine HSV ranges
5. Verify camera topics: `ros2 topic list | grep camera`
6. **Check ROI size**: Ensure ball is large enough (min_area parameter)

### Poor depth readings?
1. Ensure ball is within depth camera range (0.3-8m for Astra)
2. Check depth image: `ros2 run rqt_image_view rqt_image_view /camera/depth/image_raw` 
3. Verify camera calibration is loaded

### Performance issues?
1. Reduce image resolution in camera launch parameters
2. Set `publish_debug_image:=false` 
3. Increase `min_area` parameter to filter small detections

## Recent Updates (v1.1)

### New ROI and Color Display Features
- **Enhanced Visualization**: Added ROI bounding boxes around detected balls
- **Real-time Color Analysis**: Display actual detected color values (BGR and HSV)
- **Improved Debug Information**: Better visual feedback for parameter tuning
- **Color Sample Display**: Visual rectangle showing detected color beneath ROI
- **Structured Layout**: Organized information display with distance, ROI, and color data

### Technical Improvements
- **Modified Detection Function**: `detect_red_ball()` now returns bounding rectangle and color information
- **Enhanced Debug Images**: Comprehensive visual overlay with multiple information layers  
- **Better Parameter Tuning**: Use displayed color values to optimize HSV detection ranges
- **Improved User Experience**: Clear visual feedback for understanding detection behavior

### Usage Tips
- Use the color display to understand what colors are being detected
- Adjust HSV parameters based on the displayed BGR/HSV values
- The ROI box shows the exact detection area for better understanding
- Color information helps debug lighting and color detection issues