---
tags: 
Created: 2025-05-20 11:44
About: 
Reviewed: false
Completion: 0
---

## Code

```cpp
// 📁 RouterNode.ino (ESP32 connected to CC2530)
#include <HardwareSerial.h>

HardwareSerial ZigbeeSerial(2);  // UART2 (GPIO16 = RX, GPIO17 = TX)

void setup() {
  Serial.begin(115200);
  ZigbeeSerial.begin(115200, SERIAL_8N1, 16, 17);
  Serial.println("Router Node Initializing...");
  delay(1000);
  sendSysReset();
  delay(1000);
  startRouter();
  delay(3000);
  sendTestData();
}

void loop() {
  // Could listen for messages from Coordinator if required
}

void sendSysReset() {
  byte sysReset[] = {0x01, 0x41, 0x80, 0x01};
  ZigbeeSerial.write(sysReset, sizeof(sysReset));
  Serial.println("Sent SYS_RESET");
}

void startRouter() {
  byte startReq[] = {0x01, 0x26, 0x40, 0x01};
  ZigbeeSerial.write(startReq, sizeof(startReq));
  Serial.println("Sent ZDO_STARTUP_FROM_APP");
}

void sendTestData() {
  // Example: Send "Hello" to endpoint 1, shortAddr 0x0000 (Coordinator), clusterId 0x0011
  byte helloData[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};  // "Hello"

  byte afDataReq[] = {
    0x01,             // SOF
    0x24, 0x44,       // CMD0, CMD1 (AF_DATA_REQUEST)
    0x0F,             // Length of data
    0x00, 0x00,       // DstAddr (Coordinator short address)
    0x01,             // Dest endpoint
    0x01,             // Src endpoint
    0x11, 0x00,       // Cluster ID (0x0011)
    0x00,             // TransID
    0x00,             // Options
    0x30,             // Radius
    0x05              // Data length
  };

  ZigbeeSerial.write(afDataReq, sizeof(afDataReq));
  ZigbeeSerial.write(helloData, sizeof(helloData));
  Serial.println("Sent AF_DATA_REQUEST with Hello");
}
```


