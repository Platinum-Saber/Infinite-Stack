---
tags: 
Created: 2025-05-21 08:40
About: 
Reviewed: false
Completion: 0
---
## 1. CAN Bus Overview

> [!NOTE] **CAN** Bus
> The Controller Area Network (CAN) bus is a robust, serial communication protocol designed for reliable data exchange between electronic control units (ECUs) in real-time systems. Initially developed for automotive applications, CAN has become a standard in various industries due to its efficiency and fault-tolerant design.

- **Development**: CAN was developed by Robert Bosch GmbH in 1983 to address the need for a reliable communication system in automotive environments.
- **Standardization**: The protocol was standardized in 1986, with the first CAN specification (CAN 1.0) published in 1987. CAN 2.0, released in 1991, became widely adopted and is still in use today.
- **Evolution**: Extensions like CAN FD (Flexible Data Rate) were introduced in 2012 to support higher data rates and larger payloads.

## 2. Technical Information

### 2.1. Protocol Features

- **Bus Topology**: CAN uses a multi-master, differential signaling bus, allowing multiple devices to communicate without a central host.
- **Message-Based Communication**: Data is transmitted in frames identified by unique identifiers (11-bit or 29-bit in extended mode) rather than node addresses.
- **Arbitration**: Non-destructive bitwise arbitration ensures collision-free communication, prioritizing messages with lower identifiers.
- **Data Rate**: Standard CAN supports up to 1 Mbps, while CAN FD extends this to 8 Mbps with payloads up to 64 bytes.
- **Error Detection**: CAN includes mechanisms like CRC checks, bit stuffing, and acknowledgment to ensure reliable data transmission.

### 2.2. Frame Types

- **Data Frame**: Carries data from a transmitter to receivers.
- **Remote Frame**: Requests data from a specific node.
- **Error Frame**: Signals errors detected on the bus.
- **Overload Frame**: Delays bus communication to manage traffic.

## 3. Applications

- **Automotive**: Used in engine control, transmission, airbags, and infotainment systems.
- **Industrial Automation**: Employed in factory automation, robotics, and machinery control.
- **Medical Devices**: Facilitates communication in diagnostic and monitoring equipment.
- **Aerospace and Marine**: Supports reliable data exchange in avionics and ship systems.
- **IoT and Embedded Systems**: Enables communication in smart devices and sensor networks.

## 4. Advantages

- **Reliability**: Robust error detection and fault confinement minimize communication failures.
- **Efficiency**: Prioritized message arbitration optimizes bandwidth usage.
- **Flexibility**: Supports multiple devices on a single bus without complex wiring.
- **Cost-Effectiveness**: Reduces wiring complexity, lowering installation and maintenance costs.
- **Scalability**: CAN FD enhances performance for modern high-data-rate applications.

## 5. Limitations

- **Bandwidth Constraints**: Standard CAN’s 1 Mbps limit is insufficient for some modern applications, though CAN FD mitigates this.
- **Complexity**: Implementing CAN requires specialized hardware and software expertise.
- **Distance Limitation**: Signal integrity degrades over long distances (typically up to 40 meters at 1 Mbps).

## 6. CAN Bus Lab Observations
### 6.1 Lab Setup

> [!image] Apparatus 
> ![[WhatsApp Image 2025-05-21 at 08.46.35_e846ed9c.jpg]]

#### Transmitter
> [!image] CAN Transmitter 
> ![[WhatsApp Image 2025-05-21 at 08.47.36_541df3f7.jpg]]

> [!code] Sender Code
> ```cpp
> #include <SPI.h>
> #include "mcp2515_can.h"
> onst int SPI_CS_PIN = 10;
> mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
> void setup() {
>    Serial.begin(115200);
>    while(!Serial){};
>    // init can bus : baudrate = 500k
>    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
>       Serial.println("CAN init fail, retry...");
>       delay(100);
>    }
>    Serial.println("CAN init ok!");
> }
> unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
> void loop() {
>    // send data: id = 0x00, standrad frame, data len = 8, stmp: data buf
>    stmp[7] = stmp[7] + 1;
>    if (stmp[7] == 100) {
>       stmp[7] = 0;
>       stmp[6] = stmp[6] + 1;
>       if (stmp[6] == 100) {
>          stmp[6] = 0;
>          stmp[5] = stmp[5] + 1;
>       }
>    }
>    CAN.sendMsgBuf(0x00, 0, 8, stmp);
>    delay(100); // send data per 100ms
>    Serial.println("CAN BUS sendMsgBuf ok!");
> }
> ```


#### Receiver
> [!image] CAN Receiver
> ![[WhatsApp Image 2025-05-21 at 08.47.45_561b1074.jpg]]

> [!code] Receiver Code
> ```cpp
> #include <SPI.h>
> #include "mcp2515_can.h"
> const int SPI_CS_PIN = 10;
> const int CAN_INT_PIN = 2;
> mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
> unsigned char flagRecv = 0;
> unsigned char len = 0;
> unsigned char buf[8];
> char str[20];
> void setup() {
>    Serial.begin(115200);
>    while (!Serial) {
>       ; // wait for serial port to connect. Needed for native USB port only
>    }
>    // start interrupt
>    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), MCP2515_ISR, FALLING);
>    // init can bus : baudrate = 500k
>    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
>       Serial.println("CAN init fail, retry...");
>       delay(100);
>    }
>    Serial.println("CAN init ok!");
> }
> void MCP2515_ISR() {
>    flagRecv = 1;
> }
> void loop() {
>    if (flagRecv) {
>       // check if get data
>       flagRecv = 0; // clear flag
>       Serial.println("into loop");
>       // iterate over all pending messages
>       // If either the bus is saturated or the MCU is busy,
>       // both RX buffers may be in use and reading a single
>       // message does not clear the IRQ conditon.
>       while (CAN_MSGAVAIL == CAN.checkReceive()) {
>          // read data, len: data length, buf: data buf
>          Serial.println("checkReceive");
>          CAN.readMsgBuf(&len, buf);
>          // print the data
>          for (int i = 0; i < len; i++) {
>             Serial.print(buf[i]); Serial.print("\t");
>          }
>          Serial.println();
>       }
>    }
> }
> ```

### 6.2 Observations

> [!image] Oscilloscope Readings
> ![[WhatsApp Image 2025-05-21 at 08.46.33_2505aa68.jpg]]

## 7. Conclusion

The CAN bus remains a cornerstone of real-time, reliable communication in automotive and industrial systems. Its evolution into CAN FD ensures it meets modern demands for higher data rates and larger payloads. As industries like autonomous vehicles and IoT grow, CAN’s role as a dependable, efficient protocol continues to expand.






