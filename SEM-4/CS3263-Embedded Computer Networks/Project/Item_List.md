---
tags: 
Created: 2025-05-03 22:01
About: 
Reviewed: false
Completion: 0
---

## 🧾 **Component List**

### 🔹 **For All Nodes**

|Component|Quantity|Notes|
|---|---|---|
|ESP32 Dev Board|3|Main microcontroller for all nodes|
|3.3V Power Supply (regulated)|3|For ESP32 and Zigbee modules, avoid overvoltage|
|Breadboards or Perfboards|3|For prototyping the circuits|
|Jumper Wires (Male-Male)|~30|For connecting modules and sensors|
|USB Cables for ESP32|3|For flashing and serial monitoring|

---

### 🧭 **Controller Node**

|Component|Quantity|Notes|
|---|---|---|
|**XBee S2C Module**|1|Main Zigbee coordinator; can be used in API or AT mode|
|XBee USB Adapter or Breakout Board|1|For easy wiring to ESP32 (TX/RX, 3.3V, GND)|
|OLED Display (e.g., SSD1306)|1|To display sensor values locally|
|Resistors (pull-ups)|2–4|For I2C or safe UART use (optional, 4.7kΩ)|

---

### 🌡️ **Sensor Node**

|Component|Quantity|Notes|
|---|---|---|
|**CC2530 Zigbee Module**|1|Flash with ZNP firmware to act as Zigbee router or ED|
|**DHT22 Temperature/Humidity Sensor**|1|Digital sensor with 1 data pin|
|Logic Level Shifter|1|Recommended if CC2530 UART isn’t 3.3V tolerant|
|CC-Debugger (for flashing CC2530)**|1|Optional but needed at least once|

---

### ⚙️ **Actuator Node**

|Component|Quantity|Notes|
|---|---|---|
|**CC2530 Zigbee Module**|1|Used as router or end device|
|Relay Module (2-channel)|1|One for heating coil, one for humidifier|
|Heating Coil|1|Used for increasing temperature (low-voltage DC type)|
|Ultrasonic Humidifier Module|1|Compact humidifier, often 5V or 12V|
|Flyback Diodes (e.g., 1N4007)|2|Protection across relay coils|
|External Power Source|1|To drive actuators (5V/12V, depending on devices)|

---

### 🧰 **Optional Tools**

| Component or Tool           | Quantity | Notes                                              |
| --------------------------- | -------- | -------------------------------------------------- |
| **FTDI USB to TTL Adapter** | 1–2      | For flashing or serial monitoring (CC2530 / ESP32) |
| **X-CTU Software**          | –        | To configure XBee S2C                              |
| **Soldering Kit**           | –        | For making permanent circuits (optional)           |
| **Multimeter**              | –        | For checking connections and voltages              |

---



