---
tags:
  - EmbeddedNetworking
Created: 2025-02-21 17:49
About: |-
  Lab 02 of CS3263-Embedded Computer Networks.
  Created by Suhan (220673K)
Reviewed: true
Completion:
---
**Module** : CS3263-Embedded Computer Networks 
**Name** : Waduge S.S.
**Index** : 220673K

<br>

### Task 1 : 
- Draw the SDA and SCL logic levels for Start and Stop bit representation in I2C

> [!image] SDA and SCL diagram
> ![[Pasted image 20250221205805.png]]

- **Start Condition** : Transition of SDA **from HIGH to LOW** while SCL is **HIGH**
- **Stop Condition** : Transition of SDA **from LOW to HIGH** while SCL is **HIGH**

<br>

### Task 2:

> [!faq] What is the relationship between SDA and SCL when transferring data?
> In I2C communication, the SDA (Serial Data) line carries the actual data being transmitted, while the SCL (Serial Clock) line provides the timing for data transfer.
> - Data on **SDA** must be **stable** when **SCL is HIGH**. `(valid regions in the diagram)`
> - Data **can only change** when **SCL is LOW**.
> - Each data bit is transferred per clock pulse on the SCL line.
> - The **receiver** samples the data when SCL is HIGH.

<br>

<div style="page-break-before: always;"></div>

### Task 3:

> [!faq] Demonstrate the sequence of actions when, 
> >[!info] a) Master is a transmitter
> > > [!image] Bits
> > > ![[Pasted image 20250221220716.png]]
> > - The master initiates communication with a start condition. 
> > - It sends the 7-bit address of the slave it wants to communicate with, along with the write bit set to 0 (indicating a write operation). 
> > - The slave acknowledges the address by pulling the ACK bit LOW. 
> > - The master then sends data to the slave in sequences of 8 bits (a byte), expecting an ACK bit from the slave after each byte transmission. 
> > - This process continues until the slave does not send an ACK bit (keeping it HIGH), indicating the end of data reception. 
> > - Finally, the master sends a stop condition to terminate the communication.
> 
> 
> >[!info] b) Master is a receiver
> >> [!image] Bits
> >> ![[Pasted image 20250222225909.png]]
> >
> > - The master initiates communication with a start condition. 
> > - Then, it transmits the 7-bit address of the slave it wants to communicate with, setting the read/write bit to 1 (indicating a read operation). 
> > - The slave acknowledges the address by pulling the ACK bit LOW. 
> > - Subsequently, the slave sends data to the master in 8-bit sequences (bytes). 
> > - The master responds with an ACK bit after receiving each byte. 
> > - This process continues until the master does not send an ACK bit (keeping it HIGH), signaling the end of data reception. 
> > - Finally, the master sends a stop condition to conclude the communication

<br>

<div style="page-break-before: always;"></div>

### Task 4:

> [!note] Demonstrate the purpose of ACK bits.
> ACK (Acknowledge) bits are used for **synchronization and error checking** in I²C communication.
> - **ACK (0)**: The receiver acknowledges successful data reception (`SDA` is pulled `LOW`).
> - **NACK (1)**: The receiver signals it does not acknowledge (`SDA` remains `HIGH`).
> - Slave acknowledges address reception.
> - Master acknowledges received data from slave.
> - **Master sends NACK** for the last received byte to indicate the end of reading.

> [!image] Diagram
> ![[Pasted image 20250221222832.png]]

