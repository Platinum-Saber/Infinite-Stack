---
tags: 
Created: 2025-05-20 11:44
About: 
Reviewed: false
Completion: 0
---

## Code

```cpp
// 📁 CoordinatorNode.ino (ESP32)
#include <HardwareSerial.h>

HardwareSerial ZigbeeSerial(2);  // UART2 (GPIO16 = RX, GPIO17 = TX)

void setup() {
  Serial.begin(115200);
  ZigbeeSerial.begin(115120, SERIAL_8N1, 16, 17);
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
  byte sysReset[] = {0x01, 0x41, 0x80, 0x01};
  ZigbeeSerial.write(sysReset, sizeof(sysReset));
  Serial.println("Sent SYS_RESET");
}

void startCoordinator() {
  byte startReq[] = {0x01, 0x26, 0x40, 0x01};  // ZDO_STARTUP_FROM_APP
  ZigbeeSerial.write(startReq, sizeof(startReq));
  Serial.println("Sent ZDO_STARTUP_FROM_APP");
}

// Utility to print received buffer as hex
void printHexBuffer(const byte *buffer, int length) {
  for (int i = 0; i < length; i++) {
    Serial.printf("%02X ", buffer[i]);
  }
  Serial.println();
}

// TODO: Process incoming AF_INCOMING_MSG and respond accordingly
// This is a placeholder for parsing incoming Zigbee messages

```




