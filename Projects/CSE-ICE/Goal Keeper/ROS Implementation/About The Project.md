# GoalKeeper
A foot ball keeper robot for IESL Techno 2025

Based on your description and the image, it appears that the goalkeeper robot is designed to rotate about a horizontal axis to intercept incoming balls. This setup aligns with your earlier explanation of the servo motor's orientation and the statue's movement.

To achieve a similar functionality, you can follow these steps:

Servo Motor Selection: Choose a servo motor with sufficient torque and speed to rotate the goalkeeper statue effectively. Ensure it can handle the weight and dimensions of the statue.

Mounting the Statue: Attach the statue securely to the servo motor's shaft, ensuring it can rotate smoothly without obstruction.

Ball Detection: Implement a system to detect the incoming ball's position and trajectory. This can be achieved using sensors or cameras.

Trajectory Prediction: Calculate the ball's predicted path to determine the optimal position for the goalkeeper to intercept it.

Servo Control: Based on the predicted trajectory, calculate the required angle for the servo motor to position the statue correctly. Use appropriate control algorithms to adjust the servo's position in real-time.

Testing and Calibration: Test the system with various ball speeds and angles to ensure the goalkeeper statue can effectively block the ball. Make necessary adjustments to the system for optimal performance.


### System design

#### 1. Hardware Design

A. Mechanical

Goalkeeper Structure:

  - Wooden or 3D-printed humanoid goalkeeper
  - Foot attached to servo shaft
  - Axis of rotation horizontal, aligned toward the ball
  - Mounted on a base for stability
  - Dimensions: roughly 20–30 cm height, enough foot width to block balls
  - Rotation Range: servo rotates ~±90° horizontally

Servo Motor:
  - High-torque hobby servo (e.g., MG996R, MG995)
  - Operates 5–7V, capable of fast rotation (~0.15–0.2 s per 60°)
  - Base Mounting: secure servo and structure so axis is horizontal
  - Optional Sensors: limit switches or potentiometer for calibration/home position

B. Electronics

  - Microcontroller: Arduino Uno, Nano, or ESP32
  - Controls servo motor
  - Communicates with ROS2 over serial (USB) or Wi-Fi (ESP32)

Camera: Intel RealSense D435 / Astra Pro
  - Mounted facing the penalty area

Power Supply:
  - Separate 5–6V for servo
  - 5V USB for microcontroller

Connections:
- Servo PWM → microcontroller
- Microcontroller ↔ ROS2 (via USB or Wi-Fi bridge)

#### 2. Software Design (ROS2 Jazzy)

| Node Name           | Input Topic                    | Output Topic     | Description                                   |
| ------------------- | ------------------------------ | ---------------- | --------------------------------------------- |
| **perception**      | Camera `/color/image_raw`      | `/Xy_depth`      | Detects ball, publishes x,y,z in camera frame |
| **transforms**      | `/Xy_depth`, `/tag_detections` | `/Goalie_coord`  | Converts ball coordinates to robot frame      |
| **motion\_control** | `/Goalie_coord`                | `/servo_command` | Calculates servo angle and commands the motor |
| **servo\_driver**   | `/servo_command`               | N/A              | Microcontroller node that sends PWM to servo  |

B. Perception Node

- Use existing RealSense camera
- Detect ball using color threshold (red)
- Publish 3D coordinates: Xy_depth(x, y, depth, flag)

C. Transform Node

- Subscribe to /Xy_depth
- If using a tag (optional):
- Get camera → tag → robot transformation
- Publish /Goalie_coord with robot-frame coordinates

D. Motion Control Node

- Subscribe to /Goalie_coord
- Calculate horizontal rotation angle:



#### References
- https://joshuasrcho.github.io/portfolio/robokeeper/
- https://github.com/joshuasrcho/final-project-robokeeper
- https://github.com/dekasari/Ball-Position-Estimation-in-Goalkeeper-Robot/