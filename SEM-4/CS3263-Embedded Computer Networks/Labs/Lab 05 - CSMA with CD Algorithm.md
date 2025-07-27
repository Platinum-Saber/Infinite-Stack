---
tags:
  - EmbeddedNetworking
Created: 2025-04-01 11:16
About: 
Reviewed: true
Completion: 0
---
## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```

# CSMA/CD

> [!NOTE] Carrier Sense Multiple Access with Collision Detection (CSMA/CD)
>  A fundamental protocol defined in the IEEE 802.3 standard, governing how devices share a common communication medium in Ethernet networks. Its primary purpose is to manage data transmissions efficiently and minimize collisions when multiple devices attempt to communicate simultaneously.

### **Key Components of CSMA/CD:**

> [!info] 1.**Carrier Sense:**
>-  Before initiating a transmission, a device listens to the network medium to determine if it's idle. This ensures that the medium is free from other transmissions, reducing the likelihood of data collisions.

> [!info] 2.**Multiple Access:** 
> - All devices have equal access to the communication medium, allowing any device to transmit data when the medium is detected as idle. This facilitates a decentralized network where no single device has priority over others.

> [!info] 3.**Collision Detection:** 
>- While transmitting, a device monitors the network for collisions by comparing the transmitted signal with the received signal. If a discrepancy is detected, indicating a collision, the device immediately ceases transmission to prevent further data corruption.
> 

### **Operational Steps of CSMA/CD:**

> [!check] 1.**Medium Monitoring:** A device intending to send data first checks the network medium:
>    - If the medium is idle, the device proceeds to transmit.
>    - If the medium is busy, the device waits until it becomes idle.

> [!check] 2.**Data Transmission:** Once the medium is free, the device begins transmitting its data while simultaneously monitoring for potential collisions.

> [!check] 3.**Collision Handling:** If a collision is detected during transmission:
>    - The device stops transmitting immediately.
>    - It sends a jam signal to inform all network devices of the collision.
>    - The device then initiates a backoff period, waiting for a random time before attempting to retransmit. This backoff time increases exponentially with each successive collision to reduce the chance of repeated collisions.

> [!NOTE]- **Historical Context and Evolution:**
> 
> CSMA/CD was integral to early Ethernet networks, particularly those using coaxial cables and hubs, where the network operated in half-duplex mode. In such setups, devices could either send or receive data at any given time, necessitating a mechanism to manage access to the shared medium.
> 
> With advancements in network technology, the introduction of Ethernet switches enabled full-duplex communication, allowing simultaneous sending and receiving of data. This development effectively eliminated collisions, rendering CSMA/CD less critical in modern Ethernet networks. Consequently, the IEEE 802.3 standard has deprecated the use of CSMA/CD in favor of these more efficient, collision-free communication methods.

> [!example] **Practical Example:**
> 
> Consider a traditional Ethernet network with multiple computers connected via a hub:
> 
> - **Scenario:** Two computers, A and B, both detect that the network medium is idle and begin transmitting data simultaneously.
> 
> - **Collision Occurs:** The signals from A and B collide, causing data corruption. Both computers detect this collision through the collision detection mechanism.
> 
> - **Collision Resolution:** Upon detecting the collision, both computers stop transmitting and send a jam signal to notify the network of the collision. They then enter a backoff period, each waiting for a random time before attempting to retransmit. This randomness helps prevent the two computers from colliding again upon retransmission.



> [!url] For more info
> 1. [Carrier Sense Multiple Access (CSMA) | GeeksforGeeks](https://www.geeksforgeeks.org/carrier-sense-multiple-access-csma/)
> 2. [CSMA/CD | What is CSMA with collision detection? - IONOS](https://www.ionos.com/digitalguide/server/know-how/csmacd-carrier-sense-multiple-access-collision-detection/)



> [!video]- CSMA
> [Resource Video](https://www.youtube.com/embed/iKn0GzF5-IU?si=7kwfHmdlSz34TgHj)
> <iframe width="660" height="415" src="https://www.youtube.com/embed/iKn0GzF5-IU?si=7kwfHmdlSz34TgHj" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>


> [!image] CSMA/CD Algorithm
> ![[Pasted image 20250401192336.png]]