

---

### PART 2, Question 1: Network Design for University Building LAN Infrastructure

#### a) Subnet Allocation and IP Addressing
   - **Task**: Allocate IP addresses to three academic departments (CSE, ME, EE) and three administrative offices (Undergraduate Division, Postgraduate Division, and Dean's Office) using the IP block 192.168.0.0/20.
   - **Reasoning**: Subnetting will allow each department and office to have its own IP range, which helps in organizing the network, controlling access, and simplifying management.
   
   **Step-by-Step Allocation**:
   1. **Calculate Required Hosts**:
      - Each department and administrative office has a specified number of hosts:
         - CSE: 27 hosts
         - EE: 26 hosts
         - ME: 22 hosts
         - Combined Administrative Offices: 12 + 10 + 10 = 32 hosts
      - The total IP range of 192.168.0.0/20 provides up to 4096 IP addresses $2^{12}$, which is more than sufficient for the building’s needs.
   
   2. **Subnetting for Each LAN**:
      - Subnet each department and administrative office to ensure each has adequate IP addresses.
      - Example Subnetting:
         - **CSE**: 192.168.0.0/27, yielding 32 addresses
         - **EE**: 192.168.0.32/27, yielding 32 addresses
         - **ME**: 192.168.0.64/27, yielding 32 addresses
         - **Combined Admin Offices**: 192.168.0.96/26, yielding 64 addresses to accommodate 32 hosts plus future expansion
   
   **IP Allocation Table**:

| Location               | Network Address | Broadcast Address | First Usable IP  | Last Usable IP   | Number of IPs | Device Allocation |
| ------------------------ | ----------------- | ------------------- | ------------------ | ------------------ | --------------- | -------------------- |
| CSE                    | 192.168.0.0     | 192.168.0.31     | 192.168.0.1      | 192.168.0.30     | 32            | Computers, Printers |
| EE                     | 192.168.0.32    | 192.168.0.63     | 192.168.0.33     | 192.168.0.62     | 32            | Computers, Printers |
| ME                     | 192.168.0.64    | 192.168.0.95     | 192.168.0.65     | 192.168.0.94     | 32            | Computers, Printers |
| Admin Offices          | 192.168.0.96    | 192.168.0.159    | 192.168.0.97     | 192.168.0.158    | 64            | Computers, Printers |

#### b) Network Diagram
   - **Purpose**: Visually represents the layout and connections within the network.
   - **Components**:
     - **Routers** to connect each LAN subnet and route traffic between them.
     - **Switches** for each LAN to connect individual devices.
     - **Sample Hosts** within each department/office.
   - **Diagram Example**:
     - Each department’s subnet connects to a central router, which then allows intercommunication between LANs.
     - Label all devices and connections for clarity.

#### c) Static Routing Table
   - **Purpose**: Enables communication between different LANs by providing routes for each subnet.
   - **Routing Table Format**:
     - Define routes in each router so that packets can reach any subnet. Here’s an example structure:

| Destination Network | Subnet Mask       | Next Hop        |
| --------------------- | ------------------- | ----------------- |
| 192.168.0.0/27     | 255.255.255.224   | Router IP for CSE |
| 192.168.0.32/27    | 255.255.255.224   | Router IP for EE  |
| 192.168.0.64/27    | 255.255.255.224   | Router IP for ME  |
| 192.168.0.96/26    | 255.255.255.192   | Router IP for Admin Offices |

---

### PART 2, Question 2: Pulse Code Modulation (PCM)

#### a) Minimum Sampling Rate Calculation
   - **Formula and Explanation**: According to the Nyquist Theorem, to accurately reconstruct an analog signal, the sampling rate should be at least twice the highest frequency in the signal.
   - **Calculation**: For a signal with a frequency of 2500 Hz, the minimum sampling rate is$2 \times 2500 = 5000 Hz$.
   - **Reasoning**: Sampling at twice the frequency ensures that the signal can be fully reconstructed from the samples, avoiding aliasing errors.

#### b) Quantization Levels with 4-Bit Quantizer
   - **Formula**: $2^{\text{number of bits}}$
   - **Calculation**: With 4 bits, the number of quantization levels is $2^4 = 16$.
   - **Reasoning**: A 4-bit quantizer divides the signal range into 16 distinct levels, allowing it to represent the signal with sufficient detail.

#### c) Data Rate Calculation for PCM
   - **Formula**: Data Rate = Sampling Rate × Bits per Sample
   - **Given**:
      - Sampling rate is 5000 Hz.
      - 4 bits are used per sample.
   - **Calculation**: $5000 \text{ samples/sec} \times 4 \text{ bits/sample} = 20,000$ bits per second (bps).
   - **Reasoning**: This data rate ensures that each sample is quantized and transmitted at the required sampling rate.

#### d) Quantization Table Completion
   - **Task**: Complete the table using normalized PAM values and a 4-bit quantizer.
   - **Process**: Convert each PAM value to its nearest quantization level based on the range (1 to 15.8). Each level corresponds to a unique 4-bit binary code in the PCM encoding.
   - **Example Table**:

| PAM Value | Quantized Value | PCM Code |
|-----------|-----------------|----------|
| 1.8       | 2               | 0010     |
| 5.5       | 6               | 0110     |
| 3.2       | 3               | 0011     |
| 2.3       | 2               | 0010     |
| 14.3      | 14              | 1110     |

#### e) Effect of Equally Spaced Quantization on Weak Signals
   - **Issue**: In PCM, weak signals are often underrepresented in equally spaced quantization, as the difference between levels becomes more noticeable in low-amplitude signals.
   - **Solution**: **Non-Uniform Quantization** techniques like μ-law or A-law companding compress weak signals by allocating more quantization levels to lower amplitudes. This approach improves signal accuracy and reduces distortion, especially for low-amplitude signals.

---
