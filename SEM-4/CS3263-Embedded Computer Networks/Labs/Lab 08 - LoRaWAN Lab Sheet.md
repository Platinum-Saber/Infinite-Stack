---
tags: 
Created: 2025-05-27 15:35
About: 
Reviewed: false
Completion: 0
---

**Name**: Waduge S.S.  
**Index**: 220673K

## Learning Outcomes

At the end of this lab, you will be able to:

- Understand the basics of the LoRaWAN protocol.
- Interface an ESP32 with a LoRa module .
- Send and receive LoRaWAN messages between two Arduino boards.

## Introduction

LoRaWAN (Long Range Wide Area Network) is a low-power, long-range wireless communication protocol designed for IoT applications. It uses the LoRa modulation technique to enable long-distance communication (up to 10 km in rural areas) with minimal power consumption. Unlike CAN, LoRaWAN operates in a star-of-stars topology, where end devices communicate with gateways, which forward messages to a network server. Messages are identified by device addresses and application keys, ensuring secure communication.

- Uses sub-GHz ISM bands (e.g., 868 MHz in Europe, 915 MHz in North America).
- Supports three classes of operation: Class A (low power, bidirectional), Class B (scheduled receive slots), and Class C (continuous receive).
- Employs AES-128 encryption for secure data transmission.

## Required Components

- 2 x Arduino Uno with USB cable
- 2 x RFM95W LoRa Module
- Breadboard
- Jumper Wires (Male-to-Male)
- 2 x Antennas (matched to the frequency band, e.g., 915 MHz)
- USB to Serial Adapter (optional, for debugging)
![[Pasted image 20250527160216.png|480]]

## Wiring Diagram

Connect the pins of the Arduino Uno to the RFM95W LoRa module as follows:

> [!table] Transmitter
> 
> | ESP32 | SX1278 Pins       |
> | ----- | ----------------- |
> | 3.3V  | VCC               |
> | GND   | GND               |
> | D2    | NSS (Chip Select) |
> | D23   | MOSI              |
> | D19   | MISO              |
> | D18   | SCK               |
> | D32   | DIO0              |
> | D33   | RST               |
> 


> [!table] Receiver 
> 
> | ESP32 | SX1278 Pins       |
> | ----- | ----------------- |
> | 3.3V  | VCC               |
> | GND   | GND               |
> | D5    | NSS (Chip Select) |
> | D23   | MOSI              |
> | D19   | MISO              |
> | D18   | SCK               |
> | D2   | DIO0              |
> | D14   | RST               |
> 

> [!image] Apparatus
> ![[WhatsApp Image 2025-05-15 at 18.50.21_d597793a.jpg|320]]  ![[WhatsApp Image 2025-05-15 at 18.50.19_df3c20f2.jpg|320]]
>
> **Tip**: Ensure antennas are securely connected to both LoRa modules to maximize range. Use the correct frequency band for your region (e.g., 915 MHz for North America). Avoid placing modules near metal surfaces to prevent signal interference.

## Method

- Connect two ESP32s with LoRa Module SX1278 according to the above wiring diagram.
-  Upload the above `transmitter` code to one to ESP32 and the `receiver` to other ESP32.

### LoRaWAN Transmitter Code

```cpp
#include <LoRa.h>
#define SS 2
#define RST 33
#define DIO0 32
String data = "hello";
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Sender Host");
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Error");
    delay(100);
    while (1);
  }
}
void loop()
{
  Serial.print("Sending Data: ");
  Serial.println(data);
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();
  delay(1000);
}
```

### LoRaWAN Receiver Code

```cpp
#include <LoRa.h>

#define SS    5
#define RST   14
#define DIO0  2
#define LED_PIN 13  // Pin connected to LED

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("LoRa Packet Sniffer Started");

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your wiring.");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Blink LED on message receive
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);

    Serial.println("----------- Packet Received -----------");

    Serial.print("Bytes Received: ");
    Serial.println(packetSize);

    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());

    Serial.print("SNR: ");
    Serial.println(LoRa.packetSnr());

    // Print actual message
    String receivedMsg = "";
    while (LoRa.available()) {
      receivedMsg += (char)LoRa.read();
    }

    Serial.print("Message: ");
    Serial.println(receivedMsg);

    // Also print in HEX for debugging
    Serial.print("Raw Bytes (HEX): ");
    for (int i = 0; i < receivedMsg.length(); i++) {
      byte b = receivedMsg[i];
      if (b < 0x10) Serial.print("0");
      Serial.print(b, HEX);
      Serial.print(" ");
    }

    Serial.println("\n---------------------------------------");
  }
}
```

## Observations

- Open the Serial Monitor for both Arduino boards at 115200 baud and observe the transmitted and received messages.
- Note the signal strength (RSSI) and packet delivery status in the receiver's Serial Monitor.
![[Pasted image 20250527160036.png|540]]
## Questions


1. **How does LoRaWAN differ from traditional CAN bus communication in terms of network topology and range?**  
    LoRaWAN uses a star-of-stars topology with gateways relaying messages to a network server, enabling long-range communication (up to 10 km). CAN bus uses a linear bus topology with short-range (up to 1 km) broadcast communication.
    
2. **What are the three classes of LoRaWAN devices, and how do they differ in operation?**
    
    - **Class A**: Devices transmit uplink messages and open two short receive windows, minimizing power use.
    - **Class B**: Devices have scheduled receive slots for periodic downlink messages.
    - **Class C**: Devices continuously listen for downlink messages, consuming more power.
3. **Why is the LoRa modulation technique suitable for long-range, low-power applications?**  
    LoRa uses chirp spread spectrum modulation, which provides high sensitivity and robustness against noise, enabling long-range communication with low power consumption.
    
4. **What role does the Network Session Key (NwkSKey) play in LoRaWAN communication?**  
    The NwkSKey encrypts and authenticates messages between the device and the network server, ensuring secure communication and data integrity.
    
5. **How does the Adaptive Data Rate (ADR) mechanism optimize LoRaWAN performance?**  
    ADR adjusts the data rate and transmission power based on signal conditions, optimizing range, battery life, and network capacity.
    
6. **What is the purpose of the Join procedure in LoRaWAN, and when is it used?**  
    The Join procedure authenticates a device to the network using a DevEUI, AppEUI, and AppKey, establishing session keys. It is used when a device first connects or re-joins the network.
    
7. **Explain the significance of the spreading factor in LoRa modulation.**  
    The spreading factor (SF7–SF12) controls the trade-off between data rate and range. Higher spreading factors increase range and robustness but reduce data rate.
    
8. **How does LoRaWAN ensure secure communication between devices and the network server?**  
    LoRaWAN uses AES-128 encryption with separate Network Session Key (NwkSKey) and Application Session Key (AppSKey) for integrity and confidentiality.
    
9. **What is the maximum payload size for a LoRaWAN message, and how does it vary with data rate?**  
    The maximum payload size depends on the data rate (e.g., 51 bytes for SF12, 222 bytes for SF7 in some regions). Lower data rates reduce payload size due to longer transmission times.
    
10. **Describe the role of the gateway in a LoRaWAN network.**  
    The gateway receives messages from end devices and forwards them to the network server via the internet, acting as a bridge in the star-of-stars topology.
    
11. **What are the advantages of using sub-GHz frequencies in LoRaWAN compared to 2.4 GHz?**  
    Sub-GHz frequencies offer better penetration through obstacles and longer range due to lower signal attenuation, ideal for IoT applications.
    
12. **How does LoRaWAN handle interference in crowded frequency bands?**  
    LoRaWAN uses chirp spread spectrum and multiple spreading factors to mitigate interference, along with channel hopping and low duty cycles to reduce collisions.





