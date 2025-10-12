
# Ball Trajectory Predictor

A ROS 2 package for predicting the trajectory of a red ball using physics-based simulation. This package analyzes the ball's motion to predict where it will land when it reaches 30cm in front of the camera.

## Overview

This package implements a trajectory prediction algorithm that:
- Subscribes to ball position data from the `red_ball_detector` package
- Tracks the ball's position over time to calculate velocity
- Uses kinematic equations with gravity to predict the ball's trajectory
- Determines where the ball will be when it reaches 30cm from the camera
- Provides visualization in RViz

## Features

- **Real-time trajectory prediction**: Calculates ball trajectory using physics simulation
- **Velocity estimation**: Uses position history to estimate ball velocity with smoothing
- **Configurable parameters**: Adjustable gravity, distances, and prediction parameters
- **Confidence scoring**: Provides prediction confidence based on velocity consistency
- **Visualization**: RViz markers showing predicted trajectory and landing point
- **Robust tracking**: Handles ball detection loss and resets prediction state

## Requirements

- ROS 2 Jazzy
- `red_ball_detector` package (for ball position input)
- `astra_bringup` package (for camera)
- Python dependencies: numpy, scipy (optional)

## Installation

1. Clone this package into your ROS 2 workspace:
```bash
cd ~/ros2_ws/src
# Package should already be created in the workspace
```

2. Build the workspace:
```bash
cd ~/ros2_ws
colcon build --packages-select ball_trajectory_predictor
source install/setup.bash
```

## Usage

### Complete System Launch
Launch the complete ball tracking system (camera + detection + prediction):
```bash
ros2 launch ball_trajectory_predictor complete_ball_tracking.launch.py
```

### Trajectory Predictor Only
If you already have ball detection running:
```bash
ros2 launch ball_trajectory_predictor trajectory_prediction.launch.py
```

### Parameters

Key parameters you can adjust:

- `gravity`: Gravity acceleration in m/s² (default: -9.81)
- `target_distance`: Distance from camera to make prediction (default: 0.30m)
- `launch_distance`: Expected ball launch distance (default: 6.0m)
- `prediction_trigger_distance`: Distance to start predictions (default: 3.0m)
- `position_history_size`: Number of positions to track (default: 20)
- `min_velocity_samples`: Minimum samples needed for prediction (default: 5)
- `velocity_smoothing_window`: Velocity smoothing window (default: 3)

Example with custom parameters:
```bash
ros2 launch ball_trajectory_predictor trajectory_prediction.launch.py gravity:=-9.81 target_distance:=0.25
```

## Topics

### Subscribed Topics
- `/ball_position` (geometry_msgs/PointStamped): Ball position from detector

### Published Topics
- `/predicted_landing_position` (geometry_msgs/PointStamped): Predicted landing position
- `/trajectory_markers` (visualization_msgs/MarkerArray): Trajectory visualization
- `/ball_velocity` (geometry_msgs/Vector3): Current ball velocity
- `/prediction_confidence` (std_msgs/Float32): Prediction confidence (0-1)
- `/prediction_info_text` (std_msgs/String): Detailed prediction information as text
- `/ball_velocity_point` (geometry_msgs/PointStamped): Velocity vector visualization
- `/prediction_text_marker` (visualization_msgs/Marker): Text information as 3D marker

## Algorithm

The trajectory prediction uses the following physics equations:

```
x(t) = x₀ + vₓ₀ × t
y(t) = y₀ + vᵧ₀ × t + ½ × g × t²
z(t) = z₀ + vᵧ₀ × t
```

Where:
- `(x₀, y₀, z₀)` is the initial position
- `(vₓ₀, vᵧ₀, vᵧ₀)` is the initial velocity
- `g` is gravity acceleration
- `t` is time

The algorithm:
1. Tracks ball positions over time
2. Estimates velocity using position differences
3. Applies smoothing to reduce noise
4. Calculates time to reach target distance
5. Predicts final position using kinematic equations

## Coordinate System

- **X-axis**: Left/Right (positive = right)
- **Y-axis**: Up/Down (positive = up)  
- **Z-axis**: Forward/Backward (positive = away from camera)

## Configuration

The system is configured for a ball launched from 6m away from the camera. Predictions start when the ball reaches the halfway point (3m) and predict where it will be at 30cm from the camera.

## Visualization

The RViz configuration shows:
- **Camera Images**: Live color feed and ball detection debug view
- **Ball trajectory path**: Blue to red gradient showing predicted path
- **Predicted landing point**: Red sphere at 30cm target location
- **Ball velocity vector**: Yellow point showing velocity direction
- **Prediction information**: Real-time text display with:
  - Current ball position and velocity
  - Time to target and predicted landing coordinates
  - Prediction confidence percentage
  - Ball distance and speed
- **Camera coordinate frame**: Reference axes

## Troubleshooting

**No predictions being made:**
- Check that ball detection is working (`/ball_position` topic)
- Ensure ball is detected consistently for velocity calculation
- Verify ball is moving towards camera (negative Z velocity)

**Inaccurate predictions:**
- Adjust velocity smoothing parameters
- Check camera calibration
- Verify coordinate system alignment
- Consider environmental factors (lighting, ball visibility)

**Ball tracking lost:**
- Check red ball detection parameters
- Ensure good lighting conditions
- Verify camera is functioning properly

## Future Enhancements

- Air resistance modeling
- Multiple ball tracking
- Machine learning-based prediction
- Kalman filtering for smoother tracking
- Adaptive parameter tuning