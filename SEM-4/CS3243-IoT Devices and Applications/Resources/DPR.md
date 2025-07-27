
---

# Drive Parameter Recording Unit (DPR) Design Report 

## 1. Microcontroller Selection

### Comparative Analysis of Microcontrollers

|Parameter|ESP32-WROOM-32|STM32F407VGT6|Arduino Mega 2560|
|---|---|---|---|
|**Core**|Dual-core Tensilica LX6|ARM Cortex-M4|ATmega2560|
|**Clock Speed**|240 MHz|168 MHz|16 MHz|
|**Flash Memory**|4 MB|1 MB|256 KB|
|**SRAM**|520 KB|192 KB|8 KB|
|**GPIO Pins**|34|82|54|
|**ADC Channels**|18 (12-bit)|16 (12-bit)|16 (10-bit)|
|**UART**|3|4|4|
|**SPI**|4|3|1|
|**I2C**|2|3|1|
|**WiFi/Bluetooth**|Yes|No|No|
|**RTC**|Yes|Yes|No|
|**Power Consumption**|240mA|200mA|300mA|
|**Cost (USD)**|$4-6|$8-12|$15-20|
|**Ease of Development**|Easy|Moderate|Very Easy|

### **Selected MCU: ESP32-WROOM-32**

**Reasons**:

- **Superior connectivity**: Built-in WiFi and Bluetooth for local access point
- **Higher processing power**: 240MHz dual-core vs 168MHz single-core (STM32) and 16MHz (Arduino)
- **Better memory**: 4MB Flash and 520KB SRAM vs limited Arduino Mega resources
- **IoT-ready**: Native support for WiFi access point functionality
- **Cost-effective**: Lowest cost while providing maximum functionality
- **Real-time capabilities**: FreeRTOS support for multitasking applications

---

## 2. Physical Interface Components

| Parameter               | Sensor/Component     | Interface Type    | Connection Method         |
| ----------------------- | -------------------- | ----------------- | ------------------------- |
| **Date/Time**           | DS3231 RTC           | I2C               | Battery-backed module     |
| **Accelerator Pedal**   | Rotary Potentiometer | Analog/ADC        | Mechanically coupled      |
| **Brake Pedal**         | Linear Potentiometer | Analog/ADC        | Mechanically coupled      |
| **Engine RPM**          | Hall Effect Sensor   | Digital Interrupt | Near flywheel + magnets   |
| **GPS/Speed**           | SIM7600G-H Module    | UART              | With external GPS antenna |
| **3-Axis Acceleration** | MPU6050              | I2C               | Mounted on chassis        |
### Interface Specifications:

- **Analog Inputs**: 0-3.3V range (ESP32 ADC limitation)
- **Digital Inputs**: 3.3V logic level compatible
- **Hall Effect**: Interrupt-driven pulse counting
- **I2C**: 400kHz fast mode for sensor communication
- **UART**: 9600-115200 baud for GPS communication


## 3. GPS and Storage Modules

### GPS: SIM7600G-H Module

- **GPS**: Integrated GNSS (GPS, GLONASS, BeiDou)
- **Interface**: UART (AT commands)
- External antenna required
- **Power**: 3.8V @ 2A peak

### Storage: Adafruit SD Card Breakout

- **Interface**: SPI
- **Capacity**: 32GB SanDisk High Endurance)
- **Backup Power**: Supercapacitor (5.5V, 1F)
- **File System**: FAT32 for compatibility
- **Write Protection**: Hardware switch

---

## 4. Engine RPM Measurement

### **Hall Effect Sensor **

- **Sensor**: A3144 Hall Effect Switch
- **Installation**: Mount near engine flywheel or crankshaft pulley
- **Target**: Attach small neodymium magnets to flywheel teeth (or use existing teeth)
- **Signal Processing**: ESP32 interrupt-driven pulse counting
- **Calculation**: RPM = (Pulse Count × 60) / (Time × Number of Magnets)
- **Accuracy**: ±5 RPM with proper calibration
- **Update Rate**: Real-time (interrupt-based)

### **Implementation Details:**

- **Mounting**: Secure bracket to engine block, 2-5mm gap from flywheel
- **Wiring**: Shielded cable to prevent electromagnetic interference
- **Signal Conditioning**: Pull-up resistor and noise filtering capacitor
- **Calibration**: Count flywheel teeth during installation for accurate RPM calculation
- **Backup Method**: Secondary sensor for redundancy in critical applications

**Formula**:

```text
RPM = (Pulse Count × 60) / (Time × Number of Magnets)
```

---

## 5. Peripherals and Interfaces

### **ESP32 Peripherals Used:**

- **UART0**: Debug
- **UART1**: GPS (SIM7600G)
- **SPI**: SD Card
- **I2C**: IMU (MPU6050) + RTC (DS3231)
- **ADC**: Pedal potentiometers
- **Interrupt GPIO**: Hall sensor for RPM
### **External Components Required:**

- **Voltage level shifters**: 3.3V ↔ 5V interfaces for pedal sensors
- **Signal conditioning**: Pull-up resistors, noise filtering for Hall sensor
- **Voltage regulators**: Multiple rail power supply
- **Antenna switches**: For GPS
- **Protection circuits**: ESD protection for all interfaces
---

## 6. Communication Protocol to App

### **Primary: ESP32 WiFi Access Point**

- **Mode**: ESP32 acts as a WiFi access point
- **Protocol**: HTTP server for data download
- **Data Access**: Android app connects to ESP32's local network (SSID: DPR_BUS_XXX, Password: WPA2-PSK)
- **Security**: WPA2-PSK encryption for WiFi
- **Functionality**: SD card data retrieval, firmware updates
- **Implementation**: ESP32 hosts a web server to serve SD card files
- **Data Format**: JSON with timestamp, stored on SD card
```json
{
  "device_id": "BUS_001",
  "timestamp": "2025-07-08T10:30:00Z",
  "location": {"lat": 6.7965, "lon": 79.9019},
  "vehicle_data": {
    "rpm": 1800,
    "speed": 45,
    "accelerator": 35,
    "brake": 0,
    "acceleration": {"x": 0.2, "y": 0.1, "z": 9.8}
  }
}
```

---

## 7. Power Circuit Design 

### **Input**: 12V Bus Battery

### **Power Requirements:**

- ESP32: 3.3V, 240mA
- SIM7600G: 3.8V, 2A peak
- SD Card Module: 3.3V, 100mA
- IMU Sensor: 3.3V, 3.5mA
- Backup Battery: 3.7V, 3000mAh

### **Power Circuit Design:**

1. **Input Protection**:
    - Fuse: 5A automotive blade fuse
    - TVS Diode: SMAJ24A (24V protection)
    - Reverse polarity: P-channel MOSFET
2. **Multi-Rail Supply:**
    - **12V→ 5V**: LM2596 switching regulator (3A)
    - **5V → 3.8V**: LM2596 adjustable (2.5A for SIM module)
    - **5V → 3.3V**: AMS1117-3.3 linear regulator (1A)
3. **Backup Power:**
    - **Battery**: 18650 Li-ion with protection PCB
    - **Charger**: TP4056 with load sharing
    - **Monitoring**: INA219 current/voltage sensor
4. **Supercapacitor Backup:**
    - **Capacity**: 5.5V, 1F supercapacitor
    - **Purpose**: SD card write completion during power loss
    - **Duration**: 5-10 seconds write protection



### Component Cost (🇱🇰 LKR)

| Component                   | Qty | Approx USD | Rate | Cost (LKR)    |
| --------------------------- | --- | ---------- | ---- | ------------- |
| LM2596 Buck Converter (5V)  | 1   | $2.00      | 305  | LKR 610       |
| LM2596 Adj Converter (3.8V) | 1   | $2.50      | 305  | LKR 763       |
| AMS1117-3.3                 | 1   | $1.00      | 305  | LKR 305       |
| TP4056 Module               | 1   | $1.50      | 305  | LKR 458       |
| 5.5V 1F Supercapacitor      | 1   | $5.00      | 305  | LKR 1,525     |
| 18650 Battery + holder      | 1   | $6.00      | 305  | LKR 1,830     |
| Fuse + Holder               | 1   | $1.00      | 305  | LKR 305       |
| TVS Diode                   | 1   | $0.80      | 305  | LKR 244       |
| P-Channel MOSFET            | 1   | $0.75      | 305  | LKR 229       |
| **Total**                   |     |            |      | **LKR 6,727** |

---

## 8. System Block Diagram (Updated)


---

## 9. Software Algorithm Flowchart



---

## 10. Cost Estimate (Updated)

### Hardware

|Component|Qty|Unit Price (USD)|Total|
|---|---|---|---|
|ESP32 Dev Board|1|$6.00|$6.00|
|SIM7600G-H Module|1|$45.00|$45.00|
|A3144 Hall Sensor|1|$2.00|$2.00|
|Potentiometers (2x)|2|$3.50|$7.00|
|MPU6050 IMU|1|$3.00|$3.00|
|DS3231 RTC|1|$2.00|$2.00|
|SD Card + Breakout|1|$13.00|$13.00|
|18650 Battery + TP4056|1|$10.00|$10.00|
|Supercapacitor|1|$5.00|$5.00|
|Voltage Regulator Set|1|$15.00|$15.00|
|GPS Antenna|1|$8.00|$8.00|
|PCB + Wiring + Enclosure|1|$35.00|$35.00|
|**Total**|||**$151.00**|

### Development Cost (same as original): $18,250.00

---

**Total Prototype Development**: ~$18,400

**Per Unit Hardware Cost**: ~$151.00 or **~LKR 46,000**

---

**Note**: Prices sourced from Waveshare, SparkFun, DigiKey, LankaTronics





