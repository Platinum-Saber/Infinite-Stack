---
tags: 
Created: 2025-02-09 17:17
About: 
Reviewed: false
Completion: 0
---
# Take Home Assignment 01

- Name   : `Sansika Suhan Waduge`
- Index    : `220673K`
- Course : `CS3263 - Embedded Computer Networks`

<br>
<br>

## **Task**
- Use wire-shark software to capture network packets in real time.
- Analyze the network protocols and elaborate on what happens to a protocol data unit in each network layer.

> [!image] Wire-Shark
> ![[Screenshot from 2025-02-09 23-19-36.png]]
> ![[Pasted image 20250209232132.png]]



<div style="page-break-before: always;"></div>

## **Captured Network Protocols**

<br>

> [!image] Wire-Shark Captures
> 
>![Screenshot from 2025-02-09 17-06-09.png](file:///home/suhan/Pictures/Screenshots/Screenshot%20from%202025-02-09%2017-06-09.png)
>
> ![Screenshot from 2025-02-09 17-28-41.png](file:///home/suhan/Pictures/Screenshots/Screenshot%20from%202025-02-09%2017-28-41.png)
>
> - **TLSv1.3 (Transport Layer Security 1.3)**
> - **HTTP (Hypertext Transfer Protocol)**
> - **DNS (Domain Name System)**
> - **TCP (Transmission Control Protocol)**
> - **ARP (Address Resolution Protocol)**

<div style="page-break-before: always;"></div>

## **Network Protocol Analysis**

### 1. **TLSv1.3 (Transport Layer Security 1.3)**

- **TLS** (Transport Layer Security) is a cryptographic protocol that provides secure communication over a network. TLSv1.3 is the latest version, offering improved security and performance compared to previous versions.

> [!summary] **Key Features:**
> - **Perfect Forward Secrecy (PFS):** Uses ephemeral key exchange to prevent past communications from being decrypted if a key is compromised.
> - **Faster Handshake:** Reduces the number of round trips required to establish a secure connection, improving performance.
> - **Stronger Encryption:** Only supports secure cipher suites, removing weak cryptographic algorithms.
> - **Zero-Round-Trip Resumption (0-RTT):** Enables faster reconnections by allowing encrypted data transmission on the first message after a resumed session.

> [!example] **Packet Capture Observation:**
> - In network captures, TLS 1.3 traffic appears as **"Application Data"**.
> - The encrypted communication occurs between the client (`192.168.1.5`) and a remote server.
> - Key exchange and authentication occur in the initial handshake, followed by encrypted data exchange.

---

### 2. **HTTP (Hypertext Transfer Protocol)**

- **HTTP** is an application-layer protocol used for transferring hypertext documents, such as HTML pages, between clients and servers.

> [!important] **Key Features:**
> - **Request-Response Model:** The client sends an HTTP request, and the server responds with the requested resource or an error message.
> - **Stateless:** Each request is independent, requiring mechanisms like cookies or session tokens for state management.
> - **Common Methods:**
>   - `GET`: Requests a resource (e.g., webpage, image).
>   - `POST`: Sends data to the server (e.g., form submission).
>   - `PUT`: Updates a resource.
>   - `DELETE`: Removes a resource.

> [!example] **Packet Capture Observation:**
> - A `GET` request is observed from `192.168.1.5` to `91.189.91.48`.
> - The response is **`204 No Content`**, meaning the server processed the request but returned no content.

---
<div style="page-break-before: always;"></div>

### 3. **DNS (Domain Name System)**

- **DNS** is a hierarchical system that translates human-readable domain names into IP addresses.

> [!important] **Key Features:**
> - **Query Types:**
>   - `A`: Maps a domain to an IPv4 address.
>   - `AAAA`: Maps a domain to an IPv6 address.
>   - `CNAME`: Alias for another domain.
>   - `MX`: Mail exchange record for email routing.
> - **Recursive vs. Iterative Queries:**
>   - **Recursive:** The DNS server performs all lookups on behalf of the client.
>   - **Iterative:** The client queries multiple DNS servers step-by-step.

> [!example] **Packet Capture Observation:**
> - Standard queries and responses are seen for domains like `client.wns.windows.com`.
> - The client requests domain resolution, and the DNS server responds with an IP address.
> 

---

### 4. **TCP (Transmission Control Protocol)**

- **TCP** is a transport-layer protocol that ensures reliable, ordered, and error-checked data transmission.

> [!important] **Key Features:**
> - **Three-Way Handshake:**
>   1. **SYN:** The client initiates a connection.
>   2. **SYN-ACK:** The server acknowledges and responds.
>   3. **ACK:** The client acknowledges, and communication begins.
> - **Reliability Mechanisms:**
>   - Sequence numbers ensure ordered delivery.
>   - Acknowledgments (`ACK`) confirm successful reception.
>   - Retransmissions occur if packets are lost.
> 

> [!example] **Packet Capture Observation:**
> - TCP handshakes (`SYN`, `SYN-ACK`, `ACK`) establish connections.
> - Data transmission is followed by `FIN` and `ACK` to terminate the session.

---

### 5. **ARP (Address Resolution Protocol)**

ARP operates at the link layer (Layer 2) and resolves IP addresses to MAC addresses within a local network.

> [!important] **Key Features:**
> - **Process:**
>   1. A device broadcasts an ARP request: "Who has IP `192.168.1.5`? Tell `192.168.1.1`."
>   2. The target device responds with its MAC address.
> - **Types of ARP Messages:**
>   - **Request:** Sent by a device seeking the MAC address of an IP.
>   - **Reply:** The device with the requested IP responds with its MAC address.
>   - **Gratuitous ARP:** Used to announce or update an IP-MAC mapping.

> [!example] **Packet Capture Observation:**
> - ARP packets show devices requesting MAC addresses for local communication.
> - Essential for devices in the same subnet to communicate.

---
<div style="page-break-before: always;"></div>

## **PDU of a Chosen Application Layer Protocol**

> [!info] **Chosen**: `HTTP GET` *request* in packet number *45*.
> 

### **Explanation of What Happens in Each Layer of That PDU:**

> [!NOTE] **Application Layer (HTTP)**
>     
> - The user or application initiates an HTTP GET request to fetch a resource from a web server.
> - The HTTP request includes headers such as:
>```
GET / HTTP/1.1
Host: connectivity-check.ubuntu.com
Accept: */*
Connection: close
>```
>>[!image] http
>> ![[Pasted image 20250209232703.png]]




> [!NOTE] **Transport Layer (TCP)**
>     
> - The HTTP request is encapsulated in a TCP segment.
> - The PDU at this layer is called a **segment**. The TCP header is added to the HTTP request data.
> - The TCP segment contains:
> 	- **Source Port:** 58114
> 	- **Destination Port:** 80 (HTTP)
> 	- **Flags:** PSH, ACK (indicating data transmission)
> 	- **Sequence Number:** 208232948
> 
> >[!image] tcp
> >![[Pasted image 20250209232905.png]]
> 


<div style="page-break-before: always;"></div>


> [!NOTE] **Network Layer (IP)**
>     
> - The TCP segment is encapsulated in an IPv4 packet.
> - **Source IP:** `192.168.1.5` (client)
> - **Destination IP:** `91.189.91.48` (Ubuntu web server)
> - The packet is routed through the network.
> >[!image] IP
> >![[Pasted image 20250209233035.png]]
> 


> [!NOTE] **Data Link Layer (Ethernet)**
>     
> - The IP packet is encapsulated in an Ethernet frame.
> - PDU at this layer is called a *frame*.
> - The Ethernet frame is sent over the physical network.
> > [!image] ethernet
> >![[Pasted image 20250209233215.png]]
> 


> [!NOTE] **Physical Layer**
>     
> - The frame is converted into electrical signals or radio waves and transmitted over the medium (e.g., Wi-Fi or Ethernet).
> - The PDU at this layer is called **bits**. The frame is converted into electrical, optical, or radio signals for transmission.
> > [!image] physical layer
> > ![[Pasted image 20250209233312.png]]





