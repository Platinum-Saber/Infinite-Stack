---
tags: 
Created: 2025-05-21 09:41
About: 
Reviewed: false
Completion: 0
---
## 1. Learning Outcomes

By the end of this lab, students will be able to:

- Understand the fundamentals of the MQTT protocol and its role in IoT communication.
- Configure an ESP32 to publish and subscribe to MQTT messages.
- Integrate MQTT with a Node-RED dashboard for real-time data visualization.

## 2. Overview of MQTT

MQTT (Message Queuing Telemetry Transport) is a lightweight, publish-subscribe messaging protocol designed for resource-constrained devices and low-bandwidth networks. It is widely used in IoT applications for efficient, reliable communication.

### Key Features:

- **Publish-Subscribe Model**: Devices publish messages to topics, and other devices subscribe to those topics to receive messages.
- **Broker**: A central server (e.g., Mosquitto) manages message distribution.
- **QoS Levels**: Supports three Quality of Service levels (0, 1, 2) for message delivery assurance.
- **Low Overhead**: Minimal protocol overhead, ideal for IoT devices.
- **Applications**: Used in smart homes, industrial automation, and remote monitoring.

## 3. Apparatus Setup


> [!image] setup
> ![[WhatsApp Image 2025-05-21 at 09.55.58_42a9e5d1.jpg]]

### 3.1. Components

- **ESP32 Microcontroller**: Acts as the main controller to read RFID data and handle MQTT communication.
- **RFID RC522 Module**: Reads RFID cards and tags.
- **LCD Display (I2C)**: Displays validation messages.
- **LED**: Indicates invalid card status (lights up when invalid).
- **Breadboard and Jumper Wires**: For circuit connections.
- **Node-RED Dashboard**: Visualizes MQTT messages on a computer.
- **MQTT Broker**: A local or cloud-based broker (e.g., Mosquitto) to manage MQTT messages.
- **Computer with Arduino IDE**: For programming the ESP32.

### 3.2. Circuit Description

The setup, as shown in the image, includes:

- An ESP32 connected to a breadboard.
- An RFID RC522 module interfaced with the ESP32 via SPI pins.
- An I2C LCD display connected to the ESP32 to show messages.
- A red LED connected to a GPIO pin on the ESP32 for invalid card indication.
- Jumper wires connecting all components, with the ESP32 likely powered via USB.

### 3.3. Steps

1. **Connect the RFID RC522 to ESP32**:
    - SDA → GPIO 5
    - SCK → GPIO 18
    - MOSI → GPIO 23
    - MISO → GPIO 19
    - IRQ → Not connected
    - GND → GND
    - RST → GPIO 4
    - 3.3V → 3.3V
2. **Connect the I2C LCD to ESP32**:
    - SDA → GPIO 21
    - SCL → GPIO 22
    - VCC → 5V
    - GND → GND
3. **Connect the LED**:
    - Anode → GPIO 2 (via a 220Ω resistor)
    - Cathode → GND
4. **Set Up MQTT Broker**:
    - Install Mosquitto on your computer or use a cloud broker (e.g., HiveMQ).
    - Ensure the broker is running and accessible.
5. **Set Up Node-RED**:
    - Install Node-RED on your computer.
    - Add an MQTT input node to subscribe to the topic `rfid/access`.
    - Add a dashboard node to display the RFID card status.
6. **Program the ESP32**:
    - Use the Arduino IDE with the following libraries: `PubSubClient`, `MFRC522`, `LiquidCrystal_I2C`.
    - Write a program to:
        - Read RFID card data using the RC522 module.
        - Publish the card ID to the MQTT topic `rfid/access`.
        - Subscribe to a response topic (e.g., `rfid/validation`) for validation feedback.
        - Display "Access Granted" on the LCD if valid, or "Access Denied" and light the LED if invalid.

### 3.4. Workflow

- When an RFID card is scanned, the ESP32 reads the card’s ID.
- The ESP32 publishes the ID to the MQTT topic `rfid/access`.
- Node-RED receives the message, validates the ID (e.g., against a predefined list), and publishes a response ("valid" or "invalid") to `rfid/validation`.
- The ESP32 receives the response:
    - If "valid", the LCD displays "Access Granted".
    - If "invalid", the LCD displays "Access Denied", and the LED lights up for 3 seconds.

## 4. Record Observations

| **Trial No.** | **RFID Card ID** | **Published Message** | **Received Response** | **LCD Display** | **LED Status** | **Remarks** |
| ------------- | ---------------- | --------------------- | --------------------- | --------------- | -------------- | ----------- |
| 1             |                  |                       |                       |                 |                |             |
| 2             |                  |                       |                       |                 |                |             |
| 3             |                  |                       |                       |                 |                |             |
| 4             |                  |                       |                       |                 |                |             |
|               |                  |                       |                       |                 |                |             |

## 5. Questions

1. **Question**: What is the primary communication model used by MQTT?
    
    - **Answer**: Publish-subscribe model.
        
2. **Question**: What is the role of an MQTT broker?
    
    - **Answer**: The MQTT broker is a central server that manages the distribution of messages between publishers and subscribers.
        
3. **Question**: Name the three Quality of Service (QoS) levels in MQTT.
    
    - **Answer**: QoS 0 (At most once), QoS 1 (At least once), QoS 2 (Exactly once).
        
4. **Question**: What type of devices is MQTT best suited for?
    
    - **Answer**: Resource-constrained devices and those on low-bandwidth networks, such as IoT devices.
        
5. **Question**: What is the transport layer protocol MQTT is based on?
    
    - **Answer**: **TCP**


