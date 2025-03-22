
You: 




> [!NOTE]- Can an Arduino board handle these components without considering AI processing
> 
> ChatGPT: 
> 
> If you are **not considering AI processing**  (object detection, deep learning, etc.), then an **Arduino board**  can handle most of LYSIA-Prime's components, but with some limitations.**Can Arduino Handle These Components?** ✅ **Yes, for:**  
> - **Depth Sensors (VL53L1X, Ultrasonic, etc.)**  – Simple distance measurement.
>  
> - **Motor Control (DC motors, servos, stepper motors)**  – Needs motor drivers.
>  
> - **Robotic Arms (Servos like MG995, MG996R)**  – Controlled via PWM.
> ❌ **No, or Limited for:**  
> - **Camera (Object & Color Detection)**  – **Arduino cannot process camera feeds** . You’d need an external processor like **Raspberry Pi** .
>  
> - **Advanced Depth Sensors (Intel RealSense, LIDAR)**  – Require more processing power.
> **Best Arduino Board Choices**  
> 1. **Arduino Mega 2560** 
>   - ✅ More I/O pins for multiple sensors, motors, and actuators.
> 
>   - ✅ Handles multiple servos (good for robotic arms).
> 
>   - ❌ No built-in wireless connectivity (ESP32 is better for that).
>  
> 1. **Arduino Due** 
>   - ✅ Faster than Mega 2560.
> 
>   - ✅ More RAM and processing power.
> 
>   - ❌ 3.3V logic (some components might need level shifting).
>  
> 1. **ESP32 (If you need wireless capabilities)** 
>   - ✅ Built-in Wi-Fi/Bluetooth for remote control.
> 
>   - ✅ More powerful than standard Arduinos.
> 
>   - ❌ Limited PWM outputs (but expandable).
> **Recommended Configuration (No AI)**  
> - **Main Controller** : Arduino Mega or ESP32.
>  
> - **Camera Processing** : Offloaded to **Raspberry Pi**  (if required).
>  
> - **Motor Driver** : **L298N or TB6612FNG**  for DC motors, **PCA9685**  for multiple servos.
>  
> - **Depth Sensors** : VL53L1X or Ultrasonic (HC-SR04) for simple obstacle detection.

You: 

yes can you provide me

ChatGPT: 

I'll provide a **connection diagram**  for an **Arduino Mega-based setup**  that includes: 
- **Motor control (DC motors & servos for robotic arms)**
 
- **Depth sensing (VL53L1X & Ultrasonic HC-SR04)**
 
- **Basic power management**
I'll generate a **wiring schematic**  and share it shortly! 🚀Arduino Robot Wiring

```
# Connection Diagram for Arduino Mega-Based Robot (LYSIA-Prime)
# Components Used:# - Arduino Mega 2560 (Main Controller)# - L298N Motor Driver (For DC motors)# - PCA9685 Servo Driver (For multiple servos in robotic arm)# - VL53L1X Time-of-Flight Sensor (For distance measurement)# - HC-SR04 Ultrasonic Sensor (For obstacle avoidance)# - 12V LiPo Battery (Power Source)# - 5V Step-Down Converter (For Arduino and Sensors)
# Wiring Details:
# Motor Driver (L298N) - Controlling 2 DC MotorsL298N IN1 -> Arduino Mega D7L298N IN2 -> Arduino Mega D8L298N IN3 -> Arduino Mega D9L298N IN4 -> Arduino Mega D10L298N ENA -> Arduino Mega PWM D6L298N ENB -> Arduino Mega PWM D5L298N GND -> Arduino GNDL298N VCC -> 12V Battery PositiveL298N GND -> 12V Battery Ground
# Servo Motor (via PCA9685 Driver for multiple servos)PCA9685 SDA -> Arduino Mega SDA (Pin 20)PCA9685 SCL -> Arduino Mega SCL (Pin 21)PCA9685 VCC -> 5V Step-Down ConverterPCA9685 GND -> Arduino GND
# VL53L1X Time-of-Flight Sensor (I2C for Depth Sensing)VL53L1X SDA -> Arduino Mega SDA (Pin 20)VL53L1X SCL -> Arduino Mega SCL (Pin 21)VL53L1X VCC -> 5V Arduino MegaVL53L1X GND -> GND Arduino Mega
# HC-SR04 Ultrasonic Sensor (Obstacle Detection)HC-SR04 Trig -> Arduino Mega D11HC-SR04 Echo -> Arduino Mega D12HC-SR04 VCC -> 5V Arduino MegaHC-SR04 GND -> GND Arduino Mega
# Power Management12V LiPo Battery -> Step-Down Converter (5V output) -> Arduino Mega & PCA9685
```


I've created a detailed wiring guide for your **Arduino Mega-based robot**  with motor control, sensors, and power management. Let me know if you need modifications or a **visual schematic** ! 🚀

You: 

```
# Connection Diagram for Arduino Mega-Based Robot (LYSIA-Prime)
# Components Used:# - Arduino Mega 2560 (Main Controller)# - L298N Motor Driver (For DC motors)# - PCA9685 Servo Driver (For multiple servos in robotic arm)# - VL53L1X Time-of-Flight Sensor (For distance measurement)# - HC-SR04 Ultrasonic Sensor (For obstacle avoidance)# - 12V LiPo Battery (Power Source)# - 5V Step-Down Converter (For Arduino and Sensors)
# Wiring Details:
# Motor Driver (L298N) - Controlling 2 DC MotorsL298N IN1 -> Arduino Mega D7L298N IN2 -> Arduino Mega D8L298N IN3 -> Arduino Mega D9L298N IN4 -> Arduino Mega D10L298N ENA -> Arduino Mega PWM D6L298N ENB -> Arduino Mega PWM D5L298N GND -> Arduino GNDL298N VCC -> 12V Battery PositiveL298N GND -> 12V Battery Ground
# Servo Motor (via PCA9685 Driver for multiple servos)PCA9685 SDA -> Arduino Mega SDA (Pin 20)PCA9685 SCL -> Arduino Mega SCL (Pin 21)PCA9685 VCC -> 5V Step-Down ConverterPCA9685 GND -> Arduino GND
# VL53L1X Time-of-Flight Sensor (I2C for Depth Sensing)VL53L1X SDA -> Arduino Mega SDA (Pin 20)VL53L1X SCL -> Arduino Mega SCL (Pin 21)VL53L1X VCC -> 5V Arduino MegaVL53L1X GND -> GND Arduino Mega
# HC-SR04 Ultrasonic Sensor (Obstacle Detection)HC-SR04 Trig -> Arduino Mega D11HC-SR04 Echo -> Arduino Mega D12HC-SR04 VCC -> 5V Arduino MegaHC-SR04 GND -> GND Arduino Mega
# Power Management12V LiPo Battery -> Step-Down Converter (5V output) -> Arduino Mega & PCA9685
```

ChatGPT: 

Can you explain what a connection diagram is and how to interpret it

You: 

**What is a Connection Diagram?** A **connection diagram**  (also called a wiring diagram or circuit diagram) is a **visual representation of how components in an electrical circuit are connected** . It shows the interconnections between various components like microcontrollers, sensors, motors, power supplies, and other peripherals using lines (representing wires) and symbols.**How to Interpret a Connection Diagram**  
1. **Identify the Components**  
  - The diagram contains symbols representing each component (e.g., **Arduino Mega, sensors, motor drivers, power supply** ).
 
  - Each component is labeled with its **name and pin connections** .
 
2. **Understand the Wiring**  
  - **Lines represent electrical connections (wires).**

  - Components have input/output pins that are connected to each other based on function.
 
  - Some pins may require **pull-up resistors or logic-level shifting**  if voltage levels differ.
 
3. **Follow the Power Flow**  
  - Identify the **power source**  (e.g., **12V LiPo battery, 5V step-down converter** ).
 
  - Check which components receive **direct power**  and which are powered via a **regulator or driver module** .
 
4. **Locate Signal Wires**  
  - Components like sensors and motors have **signal pins**  connected to **Arduino’s digital or analog pins** .
 
  - Example: The **VL53L1X depth sensor**  uses **SDA/SCL for I2C communication** , meaning it connects to Arduino's **I2C pins (SDA = 20, SCL = 21)** .
 
5. **Motor and Servo Connections**  
  - **Motor drivers (L298N) control DC motors** , so they connect to both the **Arduino and motors** .
 
  - **Servos use PWM signals** , so they are connected through a **PCA9685 driver module**  to an Arduino’s **I2C pins** .
 
6. **Grounding (GND) is Critical**  
  - All components must share a **common ground (GND)**  to ensure proper operation.
 
  - Example: **Motor driver GND, Arduino GND, and sensor GND should all be connected** .
**Example Interpretation of LYSIA-Prime's Connection Diagram**  
- **L298N Motor Driver** : Controls DC motors. Connected to **Arduino Mega's digital pins (D5–D10)**  for direction and speed control.
 
- **VL53L1X Depth Sensor** : Uses **I2C communication (SDA & SCL on pins 20, 21)** .
 
- **Ultrasonic Sensor (HC-SR04)** : Uses **Trig (D11) and Echo (D12) pins**  to measure distance.
 
- **PCA9685 Servo Driver** : Manages **multiple servos**  using **PWM signals** . Connected via **I2C (SDA/SCL)** .
 
- **Power Distribution** : A **12V LiPo battery powers the system** , stepped down to **5V for Arduino and sensors** .
**How to Use the Connection Diagram**  
- **Use it as a reference while wiring**  your robot.
 
- **Double-check connections before powering up**  to avoid shorts.
 
- If troubleshooting, **trace each connection**  to identify potential issues.
Would you like a **visual version**  of this diagram for better clarity? 🚀

ChatGPT: 

How can I get the visual version of the diagram

You: 

I can generate a **visual schematic**  of your **Arduino Mega-based robot wiring**  using Fritzing or another circuit design tool.
Here’s how you can get it:
 
1. **I create the schematic and share it as an image** .
 
2. **You can modify or expand it**  using Fritzing (free software for electronics design).
 
3. **If you want a PCB layout** , I can guide you on designing one.
Let me know if you want a **block diagram, a detailed circuit schematic, or both** ! 🚀

ChatGPT: 

Then can you use fritzing and create the schematic

You: 

I can't run Fritzing directly, but I can **design the schematic layout**  and guide you on creating it in Fritzing. Alternatively, I can generate a **hand-drawn digital schematic**  and share it as an image.
Let me know which option works best for you:
 
1. **Step-by-step guide for Fritzing**  (so you can build and modify it yourself).
 
2. **A schematic image**  (I generate and send it to you).
 
3. **Both**  (I provide an image and a guide for Fritzing).

Which one would you prefer? 🚀

ChatGPT: 

both

You: 

Great! 🚀 I'll do both:
 
1. **Generate a schematic image**  of the **Arduino Mega-based wiring** .
 
2. **Provide a step-by-step guide**  on how to create the schematic using **Fritzing**  so you can modify or expand it.
I'll start by generating the **schematic image**  and will share it shortly! 🎯
![A detailed circuit schematic for a small robotic system using Arduino Mega 2560. The schematic should include:

- Arduino Mega 2560 (Main Controller)
- L298N Motor Driver controlling two DC motors
- PCA9685 Servo Driver connected to multiple servo motors
- VL53L1X Time-of-Flight Sensor for depth sensing (I2C connection)
- HC-SR04 Ultrasonic Sensor for obstacle detection
- 12V LiPo Battery as the main power source
- 5V Step-Down Converter powering the Arduino and sensors

The wiring should clearly show:
- Connections between Arduino Mega and motor driver (PWM and digital pins)
- I2C connections for the VL53L1X and PCA9685
- Power and ground connections for all components
- Proper wire labeling for easy interpretation

The schematic should be neat and organized, making it easy to follow for electronics and robotics enthusiasts.](https://files.oaiusercontent.com/file-EkGqwMpRjheMpcg6H2jJ7C?se=2025-02-26T11%3A34%3A56Z&sp=r&sv=2024-08-04&sr=b&rscc=max-age%3D604800%2C%20immutable%2C%20private&rscd=attachment%3B%20filename%3Dc8f7d934-58cc-46ba-9007-96c748f40a2b.webp&sig=3A9R21wpFyEALf4R3ACbFLwAZHJ5FjnuBmC5GqwVMo0%3D) 

Here is the **schematic image**  for your Arduino Mega-based robot wiring. Now, I'll provide a **step-by-step guide**  so you can create and modify it using Fritzing.**How to Create the Schematic in Fritzing**  
1. **Download & Install Fritzing**  
  - Get it from [fritzing.org](https://fritzing.org/) .

  - Install it on your computer.
 
2. **Add Components to the Workspace**  
  - Open Fritzing and switch to the **"Schematic"**  view.
 
  - Drag and drop the following components from the library: 
    - **Arduino Mega 2560**  (Main controller)
 
    - **L298N Motor Driver**  (For DC motors)
 
    - **PCA9685 Servo Driver**  (For servos)
 
    - **VL53L1X ToF Sensor**  (For depth sensing)
 
    - **HC-SR04 Ultrasonic Sensor**  (For obstacle detection)
 
    - **12V LiPo Battery**
 
    - **5V Step-Down Converter**  (For power regulation)
 
3. **Make the Wiring Connections**  
  - **Motor Driver (L298N) to Arduino** 
    - IN1 → D5, IN2 → D6 (Motor A control)

    - IN3 → D9, IN4 → D10

ChatGPT: 

I want to integrate object detection using the camera to the robot which has a raspberri pi 4 microprocessor. How should I do it and what are the prerequisites that I have to learn

You: 

# Important


 
- Train a **custom YOLO model**  if you need to detect specific objects.
Would you like guidance on a **specific object detection framework**  or **Pi-Arduino communication** ? 🚀

ChatGPT: 

The robot doesn't have an arduino. I plan on only using a raspberry pi 4 for LYSIA-Prime

You: 

Since **LYSIA-Prime**  will only use a **Raspberry Pi 4** , here's how you can integrate **object detection**  and control everything directly through the Pi.

---

# Setting Up Object Detection

**1. Prerequisites to Learn** 
Since you’re using only a Raspberry Pi 4, focus on:
 
- **Linux & Raspberry Pi OS**  (Command-line usage, SSH)
 
- **Python Programming**  (For AI and robotics control)
 
- **OpenCV & NumPy**  (For image processing)
 
- **Deep Learning (YOLO, TensorFlow, PyTorch)**  (For object detection)
 
- **GPIO & PWM Control on Raspberry Pi**  (For motor and servo control)
 
- **I2C & UART Communication**  (For sensors like depth sensors)
 
- **Multi-threading in Python**  (For handling vision and motion simultaneously)


---

**2. Hardware Components** 
Since Raspberry Pi handles everything:
 
- **Raspberry Pi 4 (4GB/8GB RAM)**
 
- **Pi Camera Module v2 (or USB Camera)**
 
- **Motor Driver (L298N or DRV8833)**
 
- **DC Motors (For movement)**
 
- **Servo Motors (For arms)**
 
- **Depth Sensors (VL53L1X or Intel Realsense D435)**
 
- **LiPo Battery + Step-down Converter (5V 3A for Pi)**
 
- **GPIO Expansion Board (For easy wiring)**


---

**3. Software Setup** 
On Raspberry Pi, install:


```bash
sudo apt update && sudo apt upgrade -y
sudo apt install python3-opencv python3-pip
pip3 install numpy torch torchvision picamera RPi.GPIO
```
If using **YOLOv5**  for object detection:

```bash
pip3 install ultralytics
```


---

**4. Object Detection Implementation** Using **YOLOv5**  on the Pi Camera:

```python
from ultralytics import YOLO
import cv2

model = YOLO("yolov5s.pt")  # Load a pre-trained model
cap = cv2.VideoCapture(0)  # Open the camera

while True:
    ret, frame = cap.read()
    results = model(frame)  # Perform object detection
    results.show()  # Display results
```
 
- You can modify it to **detect specific objects** .
 
- Instead of `.show()`, you can extract **bounding box coordinates**  to determine the object's position.


---

**5. Controlling Motors & Servos** Since Raspberry Pi lacks **PWM motor control** , use **L298N Motor Driver** :

```python
import RPi.GPIO as GPIO

# Motor control pins
IN1, IN2, ENA = 17, 27, 22

GPIO.setmode(GPIO.BCM)
GPIO.setup([IN1, IN2, ENA], GPIO.OUT)
pwm = GPIO.PWM(ENA, 100)  # Enable PWM
pwm.start(50)

def move_forward():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)

def stop():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.LOW)

move_forward()  # Move the robot forward
```
For **servo control (arm movement)** :

```python
import time
import RPi.GPIO as GPIO

servo_pin = 18
GPIO.setup(servo_pin, GPIO.OUT)
pwm = GPIO.PWM(servo_pin, 50)  # 50 Hz
pwm.start(7.5)  # Neutral position

def move_servo(angle):
    duty = (angle / 18) + 2
    pwm.ChangeDutyCycle(duty)
    time.sleep(0.5)

move_servo(90)  # Move arm to 90 degrees
```


---

**6. Integrating Everything**  
- Object detection determines if an object is **left, center, or right** .
 
- Based on position, adjust **motor movement**  to navigate toward it.
 
- If object is **detected within reach** , activate **servo arms**  to pick it up.
Example **navigation logic** :

```python
if object_detected == "left":
    turn_left()
elif object_detected == "right":
    turn_right()
elif object_detected == "center":
    move_forward()
else:
    stop()
```


---

**7. Advanced Features**  
- Add **depth estimation**  using **stereo cameras**  (like Intel RealSense D435).
 
- Implement **ROS (Robot Operating System)**  for better AI-based control.
 
- Use **Edge TPU (Google Coral)**  for **faster**  AI processing.


---

**Next Steps** 
Would you like help with:
 
1. **Training a custom object detection model?**
 
2. **Fine-tuning motor control for precise movement?**
 
3. **Adding depth sensing for better navigation?**

Let me know how you want to proceed! 🚀

ChatGPT: 

yes tell me about all 3

You: 

Alright, let's go step by step on each of these:


---

**1. Training a Custom Object Detection Model** If YOLOv5's default model doesn’t detect specific objects relevant to **LYSIA-Prime** , you need to **train a custom model** .**Steps to Train YOLOv5 on Raspberry Pi** **Step 1: Install Dependencies** 
On Raspberry Pi:


```bash
sudo apt update && sudo apt upgrade -y
pip3 install ultralytics opencv-python numpy torch torchvision matplotlib
```
**Step 2: Collect & Label Images**  
- Capture images using the **Pi Camera** :

```python
import cv2
cap = cv2.VideoCapture(0)
while True:
    ret, frame = cap.read()
    cv2.imshow("Frame", frame)
    if cv2.waitKey(1) & 0xFF == ord('s'):  # Press 's' to save an image
        cv2.imwrite(f"images/image_{count}.jpg", frame)
cap.release()
cv2.destroyAllWindows()
```
 
- Label images using [LabelImg](https://github.com/heartexlabs/labelImg) :

```bash
pip3 install labelImg
labelImg  # Manually draw bounding boxes and save labels
```
**Step 3: Train YOLOv5**  
- Organize dataset:


```kotlin
dataset/
├── images/
│   ├── train/ (Training images)
│   ├── val/ (Validation images)
├── labels/
│   ├── train/ (YOLO format labels)
│   ├── val/ (YOLO format labels)
├── data.yaml (Dataset config)
```
 
- Modify **data.yaml** :

```yaml
train: /home/pi/dataset/images/train
val: /home/pi/dataset/images/val
nc: 2  # Number of object classes
names: ['object1', 'object2']
```
 
- Start training:


```bash
python3 train.py --img 640 --batch 8 --epochs 50 --data data.yaml --weights yolov5s.pt
```
 
  - **After training** , your custom weights are saved in **runs/train/exp/weights/best.pt** .
**Step 4: Use the Custom Model** 

```python
model = YOLO("best.pt")  # Load trained model
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    results = model(frame)  # Run detection
    results.show()  # Display results
```
✅ **Next Steps:**  Do you need help with **dataset creation**  or **fine-tuning the model** ?

---

**2. Fine-Tuning Motor Control for Precise Movement** Since **LYSIA-Prime**  will navigate and interact with objects, we need precise motor and servo movements.**Motor Control with L298N Motor Driver** Since Raspberry Pi doesn’t have **hardware PWM** , we use **software PWM**  to control speed.**Basic Movement** 

```python
import RPi.GPIO as GPIO
import time

IN1, IN2, ENA = 17, 27, 22  # Motor 1 pins
IN3, IN4, ENB = 23, 24, 25  # Motor 2 pins

GPIO.setmode(GPIO.BCM)
GPIO.setup([IN1, IN2, ENA, IN3, IN4, ENB], GPIO.OUT)

pwmA = GPIO.PWM(ENA, 100)
pwmB = GPIO.PWM(ENB, 100)
pwmA.start(50)  # Set speed (0-100%)
pwmB.start(50)

def move_forward():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.HIGH)
    GPIO.output(IN4, GPIO.LOW)

def turn_left():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.HIGH)
    GPIO.output(IN3, GPIO.HIGH)
    GPIO.output(IN4, GPIO.LOW)

move_forward()
time.sleep(2)
turn_left()
```
**Servo Arm Control** Use **PWM to control servo** :

```python
servo_pin = 18
GPIO.setup(servo_pin, GPIO.OUT)
servo_pwm = GPIO.PWM(servo_pin, 50)  # 50 Hz

servo_pwm.start(7.5)  # Neutral position
def move_servo(angle):
    duty = (angle / 18) + 2
    servo_pwm.ChangeDutyCycle(duty)
    time.sleep(0.5)

move_servo(90)  # Move to 90 degrees
move_servo(0)   # Move to 0 degrees
```
✅ **Next Steps:**  Would you like to add **PID control**  for smoother movement?

---

**3. Adding Depth Sensing for Better Navigation** LYSIA-Prime needs **depth perception**  to avoid obstacles and navigate efficiently.**Option 1: Time-of-Flight (ToF) Sensor (VL53L1X)**  
- Measures distance **up to 4 meters** .
 
- Use **I2C communication** .
**Wiring (I2C)** | VL53L1X Pin | Raspberry Pi Pin | 
| --- | --- | 
| VCC | 3.3V | 
| GND | GND | 
| SDA | GPIO 2 | 
| SCL | GPIO 3 | 
**Code** 

```python
import time
import board
import busio
import adafruit_vl53l1x

i2c = busio.I2C(board.SCL, board.SDA)
sensor = adafruit_vl53l1x.VL53L1X(i2c)

while True:
    distance = sensor.distance
    print(f"Distance: {distance} mm")
    time.sleep(0.1)
```
👉 **Modify motor control**  based on distance:

```python
if distance < 300:
    stop()  # Stop if too close
elif distance < 600:
    slow_down()  # Reduce speed
else:
    move_forward()  # Normal speed
```


---

**Option 2: Stereo Camera (Intel RealSense D435)**  
- Provides **RGB + depth data** .
 
- Requires **USB connection** .
**Installation** 

```bash
sudo apt install librealsense2-utils librealsense2-dev
pip3 install pyrealsense2 opencv-python numpy
```
**Code to Get Depth Data** 

```python
import pyrealsense2 as rs
import numpy as np
import cv2

pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

pipeline.start(config)

while True:
    frames = pipeline.wait_for_frames()
    depth_frame = frames.get_depth_frame()
    color_frame = frames.get_color_frame()
    if not depth_frame or not color_frame:
        continue

    depth_image = np.asanyarray(depth_frame.get_data())
    color_image = np.asanyarray(color_frame.get_data())

    cv2.imshow("Depth", depth_image)
    cv2.imshow("Color", color_image)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

pipeline.stop()
```
✅ **Next Steps:**  Would you like help integrating **depth perception with object detection**  for better navigation?

---

**Final Steps & What’s Next** 
You now have:
 
1. **Custom object detection**  (YOLOv5)
 
2. **Precise motor & servo control**
 
3. **Depth sensing for better navigation**

📌 Let me know if you want:
 
- Full **ROS (Robot Operating System)**  integration.
 
- A **real-time AI model**  that adjusts movement dynamically.
 
- Help in designing an **optimal robot movement algorithm** .

What’s your next priority? 🚀
