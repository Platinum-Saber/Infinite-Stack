
## 1. Arduino Board Overview

Arduino is an open-source electronics platform that consists of microcontroller boards and an easy-to-use development environment (Arduino IDE). It is widely used for embedded systems, robotics, automation, and IoT projects.

### **Arduino Uno (R3)** Specifications

- **Microcontroller:** ATmega328P
- **Clock Speed:** 16 MHz
- **Digital I/O Pins:** 14 (6 PWM)
- **Analog Input Pins:** 6
- **Flash Memory:** 32 KB
- **SRAM:** 2 KB
- **EEPROM:** 1 KB
- **Operating Voltage:** 5V
- **Power Supply:** 7-12V (recommended)



## **Arduino Uno**

### Pin Layout


> [!image] Arduino Pin Layout Diagram
> ![[Pasted image 20250513100533.png]]


### Schematic 

> [!image] Arduino Uno R3 Schematic Diagram
> ![[Pasted image 20250322143202.png]]


- For more info about Arduino: [UNO R3 | Arduino Documentation](https://docs.arduino.cc/hardware/uno-rev3/#features)

## 2. Setting Up Arduino

### 2.1 Required Components

To get started, you need the following:

- **Arduino Board (e.g., Uno, Nano, Mega, etc.)**
- **USB Cable (A to B for Uno, Micro USB for Nano)**
- **Computer (Windows, macOS, or Linux)**
- **LED, Resistors, Breadboard, Jumper Wires (for testing)**

### 2.2 Installing Arduino IDE

The Arduino IDE (Integrated Development Environment) is used to write and upload code to the board.

#### Steps to Install Arduino IDE

1. **Download**: Visit [Arduino’s official website](https://www.arduino.cc/en/software) and download the latest version for your OS.
2. **Install**: Follow the installation process.
3. **Launch IDE**: Open the Arduino IDE after installation.

#### Alternative: Using Arduino Web Editor

If you don’t want to install the IDE, you can use the **Arduino Web Editor** from [create.arduino.cc](https://create.arduino.cc/editor).

---

<div style="page-break-before: always;"></div>

## 3. Connecting Arduino to Your Computer

1. **Plug in the Arduino board** to your computer using the USB cable.
2. **Open the Arduino IDE**.
3. **Select the correct board**:
    - Go to **Tools > Board > Arduino Uno (or your board model)**.
4. **Select the correct COM port**:
    - Go to **Tools > Port > Select the available port** (e.g., COM3 for Windows or `/dev/ttyUSB0` for Linux/Mac).
5. **Install Drivers (If Needed)**:
    - Windows usually installs drivers automatically.
    - On macOS and Linux, no additional drivers are required.

---

## 4. Writing Your First Arduino Program

- The **Blink** example is the first basic program used to test Arduino.

### 4.1 Understanding the Code

Open the Arduino IDE and paste the following code:

```cpp
// Define the LED pin
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin 13 as an output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn on the LED
  delay(1000); // Wait for 1 second
  digitalWrite(ledPin, LOW); // Turn off the LED
  delay(1000); // Wait for 1 second
}
```

### 4.2 Uploading the Code

1. Click the **Verify (✓)** button to compile the code.
2. Click the **Upload (→)** button to send the code to Arduino.
3. If successful, the onboard **LED at pin 13** should blink.

## 5. Basics of Arduino Programming

### 5.1 Structure of an Arduino Sketch

An Arduino program is called a **sketch** and has two main functions:

- `void setup() {}` → Runs once when the board is powered on.
- `void loop() {}` → Runs repeatedly.

### 5.2 Important Functions

- `pinMode(pin, mode);` → Sets pin as INPUT or OUTPUT.
- `digitalWrite(pin, HIGH/LOW);` → Turns pin ON/OFF.
- `digitalRead(pin);` → Reads digital pin state (HIGH/LOW).
- `analogRead(pin);` → Reads analog value from a sensor.
- `delay(ms);` → Pauses execution for `ms` milliseconds.
