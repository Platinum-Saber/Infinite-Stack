---
tags:
  - EmbeddedNetworking
Created: 2025-04-01 21:10
About: Embedded Networks Assignment
Reviewed: true
Completion: 100
---
**Name** : Waduge S.S.
**Index** : 220673K

> [!NOTE]  Introduction
> IEEE 802.3 is the standard for Ethernet, defining the physical and data link layers. The Medium Access Control (MAC) sublayer within the Data Link Layer is responsible for controlling how data packets are placed onto the network medium. The MAC frame format ensures reliable communication by incorporating essential fields that facilitate error detection, addressing, and synchronization.

## 1. MAC Frame Structure
The IEEE 802.3 MAC frame consists of multiple fields that ensure proper transmission and reception of data. The primary fields are:

### 1.1 Preamble (7 Bytes)
The preamble consists of a 7-byte pattern of alternating 1s and 0s. This field allows the receiving device to synchronize its clock with the incoming frame.

### 1.2 Start Frame Delimiter (SFD) (1 Byte)
The SFD is a sequence of 10101011, marking the end of the preamble and indicating the beginning of a valid frame.

### 1.3 Destination Address (6 Bytes)
This field contains the MAC address of the intended recipient. It may be a unicast, multicast, or broadcast address.

### 1.4 Source Address (6 Bytes)
This field holds the MAC address of the sender, identifying the source of the frame.

### 1.5 Length/Type (2 Bytes)
- If the value is **≤ 1500**, it represents the length of the payload in bytes.
- If the value is **≥ 1536**, it indicates the protocol type (such as IPv4 or ARP) being carried in the payload.

### 1.6 Data/Payload (46-1500 Bytes)
The data field carries the actual network payload, typically containing higher-layer protocol data such as an IP packet. If the data is less than 46 bytes, padding is added to meet the minimum frame size requirement.

### 1.7 Frame Check Sequence (FCS) (4 Bytes)
The FCS contains a Cyclic Redundancy Check (CRC) value that helps detect transmission errors. The receiving node recalculates the CRC and compares it with the transmitted value to verify data integrity.

<div style="page-break-before: always;"></div>

## 2. Frame Size Considerations
- **Minimum frame size**: 64 bytes (including preamble and SFD)
- **Maximum frame size**: 1518 bytes (excluding additional VLAN tags or jumbo frames in extended Ethernet standards)

## 3. MAC Frame Structure

> [!image] MAC
> ```mermaid
> packet-beta
> 0-55: "Preamble"
> 56-63: "Start Frame Delimiter (SFD)"
> 64-111: "Destination Address"
> 112-159: "Source Address"
> 160-175: "Length/Type"
> 176-215: "Data/Payload (Variable Length)"
> 216-279: "Frame Check Sequence (FCS)"
> ```
> 
