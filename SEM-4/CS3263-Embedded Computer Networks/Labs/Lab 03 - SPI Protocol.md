---
tags:
  - EmbeddedNetworking
Created: 2025-03-03 16:25
About: 
Reviewed: false
Completion: 0
---
**Module** : CS3263-Embedded Computer Networks
**Name** : Waduge .S.S
**Index** : 220673K

## Lab Task

- Two Arduino boards were connected using SPI interface.
- One Arduino was programmed as the SPI **Master**, and the other as the **Slave**.
- An oscilloscope was used to capture communication signals between the two devices.

## SPI Communication

**SPI (Serial Peripheral Interface)** is a high-speed, full-duplex communication protocol used for short-distance communication between microcontrollers, sensors, displays, and other peripherals.

> [!abstract] Key Features:
> 
> - **Synchronous Communication:** Uses a clock signal (**SCK**) to synchronize data transfer.
> - **Full-Duplex:** Can send (**MOSI**) and receive (**MISO**) data simultaneously.
> - **Master-Slave Architecture:** One **Master** controls the communication, while one or more **Slaves** respond.
> - **Multiple Devices:** Each Slave is selected using a **Slave Select (SS/CS)** pin.

<div style="page-break-before: always;"></div>

### 1. MOSI (Master out Slave in)

- When the master device initiates communication, the data intended to be sent to the slave is first loaded into the SPDR (SPI data register). Upon transmission, the data is shifted out bit-by-bit from the SPDR via the MOSI line.
- Active only when **SS (Slave Select) is LOW**.
- Data is sent in synchronization with the **SCK (clock) signal**.
#### Master Code
```cpp
//SPI MASTER (ARDUINO)
#include<SPI.h>                             //Library for SPI
int x = 4;
void setup (void)
{
  Serial.begin(9600);                   //Starts Serial Communication at Baud Rate 115200                  //Sets pin 7 as Output
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
}
void loop(void)
{
  byte Mastersend,Mastereceive;
  buttonvalue = digitalRead(ipbutton);   //Reads the status of the pin 2

  digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master
  Mastersend = x;
  Mastereceive=SPI.transfer(Mastersend);
  Serial.println(Mastereceive);//Send the mastersend value to slave also receives value from slave

  delay(1000);
}

```

> [!image] The master sends integer 4 to the slave. (`binary: 00000100` )
> 
> ![[Pasted image 20250303172725.png]]
> 

<div style="page-break-before: always;"></div>

### 2. MISO (Master in Slave out)

- During a communication cycle, the slave device also utilizes the SPDR. Simultaneously as the master transmits data, the slave receives incoming data bit by-bit through the MISO line. This received data is then temporarily stored in the SPDR until the slave program retrieves and processes it.
- The Slave **only drives MISO when selected** (SS = LOW).
- When **multiple slaves exist**, only the active Slave responds; others leave MISO in a high-impedance state.

#### Slave Code

```cpp
//SPI SLAVE (Arduino)
#include <SPI.h>
volatile boolean received;
volatile byte Slavereceived, Slavesend;
int buttonvalue;
int x = 0; // Initialize x with a value
void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT); // Sets MISO as OUTPUT (Have to Send data to Master IN)
  SPCR |= _BV(SPE); // Turn on SPI in Slave Mode
  received = false;
  SPI.attachInterrupt(); // Interrupt ON is set for SPI communication
}
ISR (SPI_STC_vect) { // Interrupt routine function
  Slavereceived = SPDR; // Value received from master is stored in variable Slavereceived
  received = true; // Sets received as True
}
void loop() {
  if (received) { // If data is received from master
    // You can process the received data here if needed
    Serial.print("Received from master: ");
    Serial.println(Slavereceived);
    // Prepare the data to send back to the master
    x = Slavereceived + 1; // Example: increment the received value by 1
    Slavesend = x;
    // Send the data back to the master
    SPDR = Slavesend; // Sends the x value to master via SPDR
    received = false; // Reset the received flag
  }
  delay(100); // Delay for readability in serial monitor
}
```

> [!image] The slave receives 4 and replies with integer 5. (`binary 00000101`)
> ![[Pasted image 20250303173926.png]]
> 

<div style="page-break-before: always;"></div>

### 3. SS (Slave Select)

- SS determines **which Slave device** should communicate with the Master.
- Controlled by **Master, sent to Slave**.
- **SS = LOW** → The Slave is **active** and will communicate.
- **SS = HIGH** → The Slave is **inactive** and ignores MOSI data.

> [!image] Slave Select with clock
> 
> ![[Pasted image 20250303175337.png]]
> 

<div style="page-break-before: always;"></div>

## 2. Comparison of I2C and SPI

| Feature                  | SPI (Serial Peripheral Interface)                | I2C (Inter-Integrated Circuit)               |
| ------------------------ | ------------------------------------------------ | -------------------------------------------- |
| **Number of Wires**      | 4 (MISO, MOSI, SCK, SS)                          | 2 (SDA, SCL)                                 |
| **Speed**                | Faster (up to MHz range)                         | Slower (100 kHz, 400 kHz, 1 MHz)             |
| **Communication Type**   | Full-duplex (simultaneous TX & RX)               | Half-duplex (one direction at a time)        |
| **Addressing**           | No addressing, each device needs separate SS pin | Uses addressing, multiple slaves on same bus |
| **Complexity**           | Simple but requires more wires                   | More complex but fewer wires                 |
| **Multi-Master Support** | Not easily supported                             | Fully supports multi-master                  |



