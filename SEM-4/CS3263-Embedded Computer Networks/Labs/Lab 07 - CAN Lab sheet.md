---
tags: 
Created: 2025-05-26 22:18
About: 
Reviewed: false
Completion: 0
---
- **Name** : Waduge S.S.
- **Index**: 220673K

## Learning outcomes

At the end of this lab, you will be able to, 

- Understand the basics of  CAN protocol.
- Interface Arduino Uno with MCP2515 CAN module.
- Send and receive CAN messages between two Arduino boards.

## Introduction
- CAN is a message based protocol in which a message send by one node(device) is received by all nodes(devices) connected to bus. (broadcast communication protocol).
- *ID*s are assigned to messages (not the devices) and  each node uses hardware filters and masks to decide whether to accept or ignore messages.
- Uses two lines for data transmission
	- *CAN_H*
	- *CAN_L*
## Required components 

- 2 x Arduino Uno with USB cable
- 2 x MCP2515 CAN Module (TJA1050)
	![[Pasted image 20250527135653.png|200]]
- Breadboard
- Jumper Wires (Male-to-Male)

<div style="page-break-before: always;"></div>

## Wiring diagram

- Connect the pins of the Arduino Uno to CAN bus module in the following manner.

| Arduino Uno | MCP2515 |
| ----------- | ------- |
| 5V          | VCC     |
| GND         | GND     |
| D10         | CS      |
| D11         | MOSI    |
| D12         | MISO    |
| D13         | SCK     |

#### CAN Transmitter 
> ![[WhatsApp Image 2025-05-21 at 08.47.36_541df3f7.jpg|360]]

#### CAN Receiver
> ![[WhatsApp Image 2025-05-21 at 08.47.45_561b1074.jpg|360]]

> [!tip] Tips
> - Connect the **CAN_H ↔ CAN_H** and **CAN_L ↔ CAN_L** between the two module.
> - Add a *120Ω resistor* between CAN_H and CAN_L on one end (or both ends) of the CAN bus.(to prevent signal reflections)


> [!image] Apparatus
> ![[WhatsApp Image 2025-05-26 at 22.57.57_0367f9b4.jpg|480]]

<div style="page-break-before: always;"></div>

## Method

- Go to the GitHub repository of the MCP_CAN library you want to install. https://github.com/coryjfowler/MCP_CAN_lib 
- Click the green "Code" button → Choose “Download ZIP”. 
- Open the Arduino IDE. Go to Sketch → Include Library → Add .ZIP Library. 
- Select the ZIP file you just downloaded.
- Upload the transmitter and receiver codes to the respective Arduino boards of the apparatus.
- Open 2 Serial Monitors (115200 baud) and observe messages sent from Transmitter to the Receiver.
- Connect Oscilloscope and observe the signal transmission.
#### CAN Transmitters Code
```cpp
#include <mcp_can.h>
#include <SPI.h>
MCP_CAN CAN0(10);     // Set CS to pin 10
void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

byte data[15] = {'h', 'e', 'l', 'l', 'o',' ', 0x00, 0x00, 0x00};

void loop()
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms
}
```

<div style="page-break-before: always;"></div>

#### CAN Receiver Code
```cpp
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10

void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal
  pinMode(CAN0_INT, INPUT);                     // Configuring pin for /INT input
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  if(!digitalRead(CAN0_INT)) {       // If CAN0_INT pin is low, read receive buffer

    CAN0.readMsgBuf(&rxId, &len, rxBuf);   // Read data: len = data length, buf = data byte(s)
    Serial.println(msgString);
    // Check for remote request frame
    if((rxId & 0x40000000) == 0x40000000){
      Serial.println("REMOTE REQUEST FRAME");
    }
    else{
      for (byte i = 0; i < len; i++) {
        // Only print printable characters
        if (rxBuf[i] >= 32 && rxBuf[i] <= 126)
          Serial.print((char)rxBuf[i]);
        else
          // Serial.print(".");
          continue;
      }
      Serial.println();
    }
  }
}
```

<div style="page-break-before: always;"></div>

## Observations

- Open the serial monitor and set the baud rate to 115200 and observe the messages using serial output.

> [!image] Transmitter Serial Monitor
> ![[Pasted image 20250526223928.png|400]]

> [!image] Receiver Serial Monitor
> ![[WhatsApp Image 2025-05-26 at 22.42.36_ffeaecc2.jpg|400]]

- Observe the signal transmission using Oscilloscope.

> [!image] Oscilloscope Readings
> ![[Pasted image 20250527141605.png]]

<div style="page-break-before: always;"></div>

#### Questions

1. **How can you identify the sender of a message in a CAN network?**
Each CAN message has a unique identifier (CAN ID). This ID can be used to determine the source or type of message. In multi-node networks, each node can be programmed to use a specific CAN ID, allowing receivers to filter messages based on ID.

<br>

2. **What are the two main states of the CAN bus signal, and how do they represent binary values?**  
   The two states are Dominant (logic 0) and Recessive (logic 1). A dominant bit overwrites a recessive bit during transmission.

<br>

3. **How does the arbitration process in CAN bus ensure collision-free communication between nodes?**  
   Arbitration uses the message identifier to prioritize messages. Nodes monitor the bus while transmitting; if a node detects a dominant bit when it sent a recessive bit, it stops, ensuring the highest-priority message continues without collision.

<br>

4. **What is the role of the identifier field in a CAN message frame, and how does it affect message priority?**  
   The identifier field (11 or 29 bits) determines the message's priority and destination. Lower numerical identifier values have higher priority during arbitration.

<br>

5. **Explain the difference between a standard CAN frame (11-bit identifier) and an extended CAN frame (29-bit identifier).**  
   A standard CAN frame uses an 11-bit identifier for smaller networks, while an extended CAN frame uses a 29-bit identifier for larger, more complex systems, allowing more unique message IDs.

<br>

6. **What is the significance of the CRC field in a CAN message, and how does it contribute to data integrity?**  
   The CRC (Cyclic Redundancy Check) field contains a 15-bit checksum to detect errors in the received message, ensuring data integrity by verifying the transmitted data.

<br>

7. **How does the CAN bus handle error detection, and what are the five types of errors it can detect?**  
   CAN bus uses mechanisms like CRC and bit monitoring. The five error types are: Bit Error, Stuff Error, CRC Error, Form Error, and Acknowledgment Error.

<br>

8. **What is the purpose of the ACK (Acknowledgment) field in a CAN frame, and how does it function during transmission?**  
   The ACK field confirms message receipt. A receiving node sets the ACK bit to dominant, signaling successful reception to the transmitter.

<br>

9. **What is the maximum data rate supported by the CAN bus protocol, and how does it vary with bus length?**  
   Standard CAN supports up to 1 Mbps. Longer bus lengths reduce the maximum data rate due to signal propagation delays (e.g., ~50 kbps for 1 km).

<br>

10. **Describe the role of the Start of Frame (SOF) bit in a CAN message.**  
   The SOF bit (dominant) signals the beginning of a CAN message, synchronizing all nodes on the bus.

<br>

11. **What is the difference between a data frame and a remote frame in CAN bus communication?**  
   A data frame carries data from a transmitter to receivers, while a remote frame requests data from a specific node with the same identifier, containing no data payload.

<br>

12. **What is the significance of the bit stuffing mechanism in CAN bus communication, and why is it used?**  
   Bit stuffing inserts a complementary bit after five consecutive identical bits to ensure synchronization and prevent errors due to long sequences of identical bits.
