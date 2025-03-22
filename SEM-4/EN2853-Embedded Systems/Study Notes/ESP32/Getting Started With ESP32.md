---
tags:
  - EmbeddedSystems
  - ESP32
Created: 2025-03-22 15:21
About: Important stuff to know about esp32 boards
Reviewed: true
Completion: 100
---

### Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```

---



## 1. Overview

> [!NOTE] About ESP32
> The **ESP32-DevKitC V4** is a development board designed by **Espressif Systems**, based on the **ESP32 microcontroller series**. It provides an easy-to-use platform for developing IoT applications, embedded systems, and wireless communication projects.

- This board supports **WiFi and Bluetooth (Classic & BLE)** and includes multiple GPIOs, ADCs, DACs, UARTs, and SPI/I2C/I2S interfaces.

---

## 2. ESP32-DevKitC V4 Supported ESP Models

The **ESP32-DevKitC V4** can come with different ESP32 modules soldered onto it. Here are the supported models:

|**ESP Model**|**Flash Memory**|**PSRAM**|**Special Features**|
|---|---|---|---|
|**ESP32-WROOM-32**|4MB, 8MB, 16MB|No|Standard module, widely used|
|**ESP32-WROOM-32E**|4MB, 8MB, 16MB|No|Enhanced version with better power efficiency|
|**ESP32-WROOM-32UE**|4MB, 8MB, 16MB|No|External antenna connector|
|**ESP32-WROVER**|4MB, 8MB, 16MB|Yes (8MB)|Extra PSRAM for intensive applications|
|**ESP32-WROVER-E**|4MB, 8MB, 16MB|Yes (8MB)|Improved stability and performance|
|**ESP32-WROVER-IE**|4MB, 8MB, 16MB|Yes (8MB)|External antenna option|

> [!image] ESP32-DevKitC V4 with WROOM-32 module soddered
> ![[Pasted image 20250322182901.png]]

Each of these models provides different features, such as **PSRAM (extra memory)** or **external antenna support**, making them ideal for different use cases.

---

## 3. Technical Specifications

|**Feature**|**Details**|
|---|---|
|**Microcontroller**|ESP32 (varies by module)|
|**Wireless Connectivity**|WiFi (802.11 b/g/n) & Bluetooth (BLE 4.2 / Classic)|
|**CPU**|Dual-core Xtensa® 32-bit LX6|
|**Clock Speed**|Up to 240 MHz|
|**Flash Memory**|4MB, 8MB, or 16MB (depends on module)|
|**PSRAM**|Available on WROVER variants (8MB)|
|**GPIO Pins**|Up to 34|
|**ADC Channels**|18|
|**DAC Channels**|2|
|**UART Interfaces**|3|
|**I2C Interfaces**|2|
|**SPI Interfaces**|4|
|**PWM Channels**|Up to 16|
|**USB Interface**|Micro-USB (for power and flashing)|
|**Power Supply**|5V via USB or external 5V/3.3V input|
|**Operating Voltage**|3.3V logic level|
|**Current Consumption**|~100mA (varies based on use case)|
|**Dimensions**|54mm × 27mm|

---

## 4. Key Components & Interfaces

### Power Options:

> [!info] The board can be powered in three ways:
> 
> - **Micro-USB** (default method)
> - **5V & GND pins** (external power supply)
> - **3.3V & GND pins** (regulated power input)

> [!warning]  ** Warning:** Use only **one power source** at a time to prevent damage.

### Buttons:

- **EN (Reset) Button** → Reboots the ESP32 chip.
- **BOOT Button** → Used for firmware flashing (hold while powering on).

### Pinout Diagram:

The **ESP32-DevKitC V4** provides access to most of the ESP32's **GPIOs**, which can be used for:

- **Digital I/O** (PWM, interrupts)
- **Analog Inputs (ADC)** (18 channels)
- **Analog Outputs (DAC)** (2 channels)
- **Communication Interfaces** (I2C, SPI, UART)


> [!image] ESP32 pinouts
> ![[Pasted image 20250322183144.png]]


For a full pinout, check the [official documentation](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/esp32-devkitc/user_guide.html#header-block).

---

## 5. Usage & Applications

The **ESP32-DevKitC V4** is widely used in the following applications:

### 🔹 IoT (Internet of Things) Projects

- Smart home automation
- Industrial monitoring
- Sensor networks

### 🔹 Wireless Communication

- WiFi-based projects
- Bluetooth Low Energy (BLE) applications
- Mesh networking

### 🔹 Embedded Systems Development

- Robotics
- Motor control systems
- Sensor interfacing

### 🔹 Audio & Video Processing

- Voice recognition
- Streaming audio applications
- Camera-based projects (with WROVER variants)

---

## 6. Development & Programming

### Supported IDEs:

- **Arduino IDE** (Beginner-friendly)
- **ESP-IDF (Espressif IoT Development Framework)** (Advanced)
- **PlatformIO** (VS Code extension)
- **MicroPython** (For scripting-based projects)

### Programming Languages:

- **C / C++ (Arduino & ESP-IDF)**
- **Python (MicroPython)**
- **JavaScript (Espruino, NodeMCU)**

### Getting Started:

1. **Install Drivers**: [CP210x USB-to-Serial](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
2. **Set Up Arduino IDE**:
    - Install **ESP32 Board Support** via **Boards Manager**.
    - Select **ESP32 Dev Module** as the board.
    - Connect the board via **USB** and select the correct **COM Port**.
3. **Upload a Sample Code**:
    - Open **File > Examples > WiFi > WiFiScan**.
    - Click **Upload** and check the Serial Monitor for results.


> [!tip] For ESP-IDF users
> >[!file] Guide
> >[IDFdocumentation.pdf](file:///D:%5CESP32%5CEspressif%5CIDFdocumentation%20-%20Copy.pdf)



---

## **7. Comparison with Other ESP32 Dev Kits**

|**Feature**|**ESP32-DevKitC V4**|**ESP32-S3 DevKit**|**ESP8266 NodeMCU**|
|---|---|---|---|
|**CPU**|240MHz Dual-core|240MHz Dual-core|80MHz Single-core|
|**WiFi**|✅ (802.11 b/g/n)|✅ (802.11 b/g/n)|✅ (802.11 b/g/n)|
|**Bluetooth**|✅ (BLE 4.2)|✅ (BLE 5.0)|❌|
|**PSRAM**|✅ (WROVER models)|✅ (8MB or 16MB)|❌|
|**USB-OTG Support**|❌|✅|❌|
|**GPIOs Available**|34|45|11|
|**Best For**|General IoT|Advanced AI/ML|Basic IoT|

---

> [!file]- ESP32 Datasheet
> ![[esp32_datasheet_en.pdf]]

---

For more details, visit the [official Espressif documentation](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/esp32-devkitc/user_guide.html).



