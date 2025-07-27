---
tags:
  - EmbeddedNetworking
Created: 2025-05-19 17:54
About: 
Reviewed: false
Completion: 0
---

### ✅ What is `CC2530ZNP-with-SBL.hex`?

- **ZNP** stands for **Zigbee Network Processor** – a firmware mode that lets your CC2530 act as a Zigbee device (router or coordinator) and communicate with another MCU (like ESP32) over **UART**.
    
- **SBL** stands for **Serial BootLoader** – this enables firmware updates over UART, without needing a CC-Debugger after the initial flash.
    

---

### 🔍 What It Does

|Feature|Description|
|---|---|
|Acts as a Zigbee Router|Communicates with other Zigbee devices|
|UART Interface|Connects to ESP32 or other MCUs|
|Serial Bootloader Enabled|Allows future updates over UART without CC-Debugger|

---

### 🔧 When to Use It

|Use Case|Use `CC2530ZNP-with-SBL.hex`?|
|---|---|
|You want CC2530 to be used with ESP32 via UART|✅ Yes|
|You may want to update firmware later over UART|✅ Yes|
|You’re flashing for Zigbee2MQTT or ZNP usage|✅ Yes|
|You want to compile your own custom firmware|❌ Use IAR and build yourself|

---

### ⚠️ Important Notes

1. **Only flash SBL-enabled firmware once** using a CC-Debugger. After that, you can use UART to reflash.
    
2. Once this is flashed, you **must connect a bootloader tool** like `CC2530-BSL` script or Zigbee2MQTT flasher if you ever want to update over UART.
    
3. If you **don’t want UART reflashing capability**, you can use just `CC2530ZNP-Pro.hex` instead.
    

---

### 🧪 Final Verdict

> ✔️ **Yes, `CC2530ZNP-with-SBL.hex` is correct and recommended if you want to use UART bootloading and connect to ESP32.**

Great, Cryo! Flashing the **Zigbee CC2530** with the right firmware is **essential** to use it as a **Zigbee Router** or **End Device** in your ESP32 + Zigbee setup.

Here’s a **step-by-step guide** to flash the **Z-Stack firmware** onto your **CC2530**.

---

## 🔧 What You'll Need

|Item|Purpose|
|---|---|
|**CC2530 Zigbee module**|The chip to be flashed|
|**CC-Debugger**|Official TI programmer|
|**CC2530 Programming Adapter** (optional but recommended)|Makes pin connections easier|
|**Z-Stack firmware (ZNP)**|Zigbee firmware (router or coordinator)|
|**SmartRF Flash Programmer** or **Flash Programmer 2**|Official TI tool to flash firmware|
|**Wires** (if no adapter)|For manual wiring|
|**Windows PC**|Required for SmartRF tool (runs only on Windows)|

---

## 🪛 Wiring Connections

If you’re not using a programming adapter, here are the **pin connections**:

|CC-Debugger Pin|CC2530 Pin|Notes|
|---|---|---|
|VCC|VCC|3.3V|
|GND|GND|Ground|
|DD|P2_2|Debug Data|
|DC|P2_1|Debug Clock|
|RST (optional)|RESETN|Reset line|

🔌 **Power the CC2530 via the debugger (3.3V only)** — **Do NOT use 5V**, it will damage the chip.

---

## 🗂️ Download the Firmware

You can use the **Z-Stack 3.0.2** (TI's open Zigbee 3.0 stack):

1. Download from TI:
    
    - [Z-Stack 3.0.2](https://www.ti.com/tool/Z-STACK-ARCHIVE) (requires free login)
        
    - Extract it, then go to:  
        `Z-Stack 3.0.2\Projects\zstack\ZNP\CC253x`
        
2. Choose the right prebuilt hex file:
    
    - `CC2530ZNP-Pro.hex` — for **Router**/Coordinator
        
    - You can also build your own custom one with **IAR Embedded Workbench** (optional)
        

---

## 💾 Flashing with SmartRF Flash Programmer

1. **Connect the CC-Debugger** to USB and the CC2530 to it.
    
2. Download and install:
    
    - [SmartRF Flash Programmer](https://www.ti.com/tool/FLASH-PROGRAMMER)
        
    - Or [SmartRF Flash Programmer 2](https://www.ti.com/tool/FLASH-PROGRAMMER-2)
        
3. **Open the program** and wait for it to detect the debugger.
    
4. **Steps to flash**:
    
    - Select device: `CC2530`
        
    - Browse and select the `.hex` file
        
    - Tick _Erase_, _Program_, and _Verify_
        
    - Click **Perform Actions**
        
5. Once flashed, disconnect and you're done! ✅
    

---

## 🧠 Firmware Roles Summary

|Hex File|Role|Notes|
|---|---|---|
|`CC2530ZNP-Pro.hex`|Router/Coord|Use for most use cases|
|Custom compiled firmware|Router/ED|If you want to make your own logic|

---

## ✅ After Flashing

You can now connect the CC2530 to your **ESP32** via **UART** and use Zigbee communication via a library like **Zigbee2MQTT**, or custom UART protocol using ZNP serial interface.

Great, Cryo! Let’s walk through how to **connect your ESP32 to the CC2530 (flashed with `CC2530ZNP-with-SBL.hex`)** and test UART communication between them. This setup is ideal if you’re planning to use Zigbee with ESP32 for custom applications like sensor-actuator control.

---

## 🔧 Hardware Setup

### 🧩 Components Required

|Component|Quantity|
|---|---|
|ESP32 Dev Board|1|
|CC2530 Zigbee Module|1|
|Level Shifter (optional but safe)|1|
|Jumper Wires|—|
|Power Supply (3.3V)|1|

---

### ⚙️ Wiring Diagram (UART)

#### CC2530 UART (default ZNP firmware pins):

|CC2530 Pin|Connects To ESP32|Description|
|---|---|---|
|**P0_2**|RX (e.g., GPIO16)|TXD from CC2530|
|**P0_3**|TX (e.g., GPIO17)|RXD to CC2530|
|**GND**|GND|Ground|
|**VCC**|3.3V|Power (Do **NOT** use 5V)|
|**RESET**|GPIO or Button|Optional (for manual reset)|

> ⚠️ **NOTE**: The UART logic level is **3.3V**. Avoid connecting directly to 5V logic.

---

## 🧪 Step-by-Step Setup

### 1. Flash `CC2530ZNP-with-SBL.hex` (already done ✅)

### 2. Connect CC2530 to ESP32 (as above)

### 3. Use Software Serial/UART on ESP32

Use either hardware UART (e.g., UART2) or a software serial driver (less reliable). Here's the code using UART2.

---

## 🧠 ESP32 Code (Arduino Framework)

```cpp
#include <HardwareSerial.h>

HardwareSerial ZigbeeSerial(2); // UART2

#define RXD2 16  // Connect to P0_2 of CC2530 (TX)
#define TXD2 17  // Connect to P0_3 of CC2530 (RX)

void setup() {
  Serial.begin(115200);           // Debug serial
  ZigbeeSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);  // ZNP baud rate

  Serial.println("Zigbee UART test started...");
  
  // Example command: SYS version request
  byte sysVersionCmd[] = {0x01, 0x21, 0x02, 0x00}; 
  ZigbeeSerial.write(sysVersionCmd, sizeof(sysVersionCmd));
  Serial.println("Sent SYS_VERSION request.");
}

void loop() {
  if (ZigbeeSerial.available()) {
    Serial.print("Zigbee response: ");
    while (ZigbeeSerial.available()) {
      byte b = ZigbeeSerial.read();
      Serial.print("0x");
      if (b < 0x10) Serial.print("0");
      Serial.print(b, HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  delay(500);
}
```

---

## 🧪 What This Code Does

- Sends a **SYS_VERSION request** to CC2530 via UART.
    
- Waits for a response from the CC2530 and prints it to the Serial Monitor.
    

### Expected Response

You should see something like:

```
Zigbee response: 0x41 0x21 0x02 ... 
```

This confirms that your ESP32 is **talking to the CC2530** Zigbee stack over UART 🎉

---

Got it, Cryo! You're connecting each **CC2530 module to an ESP32**, and you want to implement communication between the two via Zigbee.

Here's how we'll proceed:

---

## 🧩 System Overview

- **Device 1 (Controller Node)**: ESP32 + CC2530 (ZNP Coordinator)
    
- **Device 2 (Router Node)**: ESP32 + CC2530 (ZNP Router)
    

Each ESP32 communicates with its connected CC2530 via **UART** using the **ZNP protocol**.

---

## ⚙️ Wiring (For Each ESP32 ↔ CC2530 Pair)

|**CC2530 Pin**|**ESP32 Pin**|
|---|---|
|P0_2 (RX)|TX (e.g., GPIO17)|
|P0_3 (TX)|RX (e.g., GPIO16)|
|GND|GND|
|VCC|3.3V|

---

## 📦 Firmware Expectations

- Both CC2530s are flashed with `CC2530ZNP-with-SBL.hex`.
    
- You’re using **ESP32 Arduino Framework**.
    
- Communication uses the **ZNP Serial API** (SREQ/SRSP/AREQ packets).
    

---

## 📜 Step-by-Step Implementation

---

### 📁 File: `ControllerNode.ino` (Coordinator ESP32)

```cpp
#include <HardwareSerial.h>

HardwareSerial ZigbeeSerial(2);  // Use UART2 (GPIO16 = RX, GPIO17 = TX)

void setup() {
  Serial.begin(115200);
  ZigbeeSerial.begin(115200, SERIAL_8N1, 16, 17);  // RX=16, TX=17

  Serial.println("Coordinator Node Initializing...");

  delay(1000);
  sendSysReset();
  delay(1000);
  startCoordinator();
}

void loop() {
  if (ZigbeeSerial.available()) {
    Serial.print("Received from CC2530: ");
    while (ZigbeeSerial.available()) {
      byte b = ZigbeeSerial.read();
      Serial.printf("%02X ", b);
    }
    Serial.println();
  }
}

void sendSysReset() {
  byte sysReset[] = {0x01, 0x41, 0x80, 0x01};  // SREQ SYS_RESET
  ZigbeeSerial.write(sysReset, sizeof(sysReset));
  Serial.println("Sent SYS_RESET");
}

void startCoordinator() {
  // Example: SREQ to start Zigbee network (simplified)
  byte startReq[] = {0x01, 0x26, 0x40, 0x01};  // ZDO_STARTUP_FROM_APP
  ZigbeeSerial.write(startReq, sizeof(startReq));
  Serial.println("Sent ZDO_STARTUP_FROM_APP");
}
```

---

### 📁 File: `RouterNode.ino` (Router ESP32)

```cpp
#include <HardwareSerial.h>

HardwareSerial ZigbeeSerial(2);  // Use UART2

void setup() {
  Serial.begin(115200);
  ZigbeeSerial.begin(115200, SERIAL_8N1, 16, 17);  // RX=16, TX=17

  Serial.println("Router Node Initializing...");

  delay(1000);
  sendSysReset();
  delay(1000);
  startRouter();
}

void loop() {
  if (ZigbeeSerial.available()) {
    Serial.print("Received from CC2530: ");
    while (ZigbeeSerial.available()) {
      byte b = ZigbeeSerial.read();
      Serial.printf("%02X ", b);
    }
    Serial.println();
  }
}

void sendSysReset() {
  byte sysReset[] = {0x01, 0x41, 0x80, 0x01};
  ZigbeeSerial.write(sysReset, sizeof(sysReset));
  Serial.println("Sent SYS_RESET");
}

void startRouter() {
  byte startReq[] = {0x01, 0x26, 0x40, 0x01};  // Same command used to join coordinator
  ZigbeeSerial.write(startReq, sizeof(startReq));
  Serial.println("Sent ZDO_STARTUP_FROM_APP");
}
```

---

## 📊 Output

You’ll see in the ESP32 Serial Monitor:

- Boot logs
    
- Zigbee messages (in hex)
    
- Confirmation of startup requests
    

---

## 🌐 Communication Example

Once both devices are joined:

- Use **AF_DATA_REQUEST** to send data from the router to the coordinator.
    
- I'll provide this command if you'd like to test sending actual data like “Hello”.
    

---

## 🔁 Optional: Test Message Sending

Would you like me to extend this to send actual Zigbee messages (e.g., router → controller), including the `AF_DATA_REQUEST` frame with example payload?

And do you want the **Mermaid diagram** showing this setup and the workflow as well?

Let me know and I’ll continue building the full interaction!