
**1. Training a Custom Object Detection Model** If YOLOv5's default model doesn’t detect specific objects relevant to **LYSIA-Prime** , you need to **train a custom model** .**Steps to Train YOLOv5 on Raspberry Pi** **Step 1: Install Dependencies**  
On Raspberry Pi:

```bash
sudo apt update && sudo apt upgrade -y
pip3 install ultralytics opencv-python numpy torch torchvision matplotlib
```

**Step 2: Collect & Label Images**

- Capture images using the **Pi Camera** :

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

- Label images using [LabelImg](https://github.com/heartexlabs/labelImg) :

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

- Modify **data.yaml** :

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

- **After training** , your custom weights are saved in **runs/train/exp/weights/best.pt** .  
    **Step 4: Use the Custom Model**

```python
model = YOLO("best.pt")  # Load trained model
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    results = model(frame)  # Run detection
    results.show()  # Display results
```

✅ **Next Steps:** Do you need help with **dataset creation** or **fine-tuning the model** ?

---

**2. Fine-Tuning Motor Control for Precise Movement** Since **LYSIA-Prime** will navigate and interact with objects, we need precise motor and servo movements.**Motor Control with L298N Motor Driver** Since Raspberry Pi doesn’t have **hardware PWM** , we use **software PWM** to control speed.**Basic Movement**

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

**Servo Arm Control** Use **PWM to control servo** :

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

✅ **Next Steps:** Would you like to add **PID control** for smoother movement?

---

**3. Adding Depth Sensing for Better Navigation** LYSIA-Prime needs **depth perception** to avoid obstacles and navigate efficiently.**Option 1: Time-of-Flight (ToF) Sensor (VL53L1X)**

- Measures distance **up to 4 meters** .
    
- Use **I2C communication** .  
    **Wiring (I2C)** | VL53L1X Pin | Raspberry Pi Pin |  
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

👉 **Modify motor control** based on distance:

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

- Provides **RGB + depth data** .
    
- Requires **USB connection** .  
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