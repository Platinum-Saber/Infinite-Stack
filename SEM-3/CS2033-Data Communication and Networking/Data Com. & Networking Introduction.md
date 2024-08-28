Related : #DataCommunication #Networking #Networking/01

Reference Video : 
Reference Notes : 

---
<br>

# Content

# Data Communication & Networking

<br>

### Communication

>[!FAQ]- What is communication
>Sending information from one place to another.

>[!note]- Types of communication 
>Communication can be done using video, text, voice, data & multimedia
>>[!info] Direction of information flow
>>- One way
>>- Interactive - Non real time
>>- Interactive - real time
>
>>[!info] Number of parties involved
>>- Two-party
>>- Multi-party

<br>

### Network
>[!FAQ]- What is a Network
>A system that connects devices for communication
>>[!example] Examples for Networks
>> - `PSTN` : Public Switched Telephone Network
>> - `LAN` : Local Area Network
>> - Television Networks
>> - Vehicular Networks
>> - Internet

>[!abstract]- Components of a Network
>- Terminal for Access (📱, 🖥)
>- Equipment for Switching 
>- Media for Transmission 

>[!danger]- Challenges in Networking
>- Different architecture
>- Different languages
>- Different data formats
>- Different communication rates

>[!success]- Solutions
>- Modularization
>- Layering
>- Standardization

<br>

### Layered Architecture
>[!FAQ]- What is Layered Architecture
>Dividing the entire network process into abstract separate functional layers
>

>[!abstract]- Benefits of Layered Architecture
>- Transparent implementation
>- Flexible to modify
>- Independent design and testing ability

>[!example]- Examples for Layered Architecture Models
>- `OSI` reference model
>- `TCP/IP` model

<br>

### OSI (Open System Interconnect) Model
>[!note]- Functionality of OSI model
>- Provides communication regardless of the underlying architecture
>- Has 7 layers which have well defined  functions.
>- Boundaries between the layers minimizes the information flow across.
>
>![[Pasted image 20240703210655.png]] ![[Pasted image 20240703214541.png]]

1. >[!info]- Physical Layer
>>[!abstract]- Purpose
>>Accept a raw string of bits and deliver it across a link
>
>>[!abstract]- Functions
>>- Encoding signals
>>- Data transmission and reception
>>- Topology and physical network design
>
>>[!abstract]- Hardware Specifications
>>Operation of cables, connectors, wireless radio transceivers

2. >[!info]- Data Link Layer
>>[!abstract]- Purpose
>> Provide error free transmission across a single link
>
>>[!abstract]- Functions
>>- Data framing
>>- Error detection and handling
>>- Flow control
>>- Addressing - hardware level

3. >[!info]- Network Layer
>>[!abstract]- Purpose
>>- deliver packets (`datagrams`) from sender to the receiver (`host-to-host`) across a communication network.
>>- Shields higher layers from the details of how the packets got to their destination.
>
>>[!abstract]- Functions
>>- Logical addressing  :  which machine to send the packets to
>>- Routing  : How to get there
>>- Datagram encapsulation
>>- Congestion control  : manage lots of packets in the network core
>>- Quality of Service  : Guarantee levels of service

4. >[!info]- Transport Layer
>>[!abstract]- Purpose
>> Provides end-to-end delivery from one host to the other
>
>>[!abstract]- Functions
>>- Connection establishment, management and termination
>>- Multiplexing and demultiplexing
>>- Error detection and correction
>>- Flow control
>>- Quality service

5. >[!info]- Session Layer
>>[!abstract]- Purpose
>> Provide a means of controlling the dialog between two end-to-end users (applications)
>
>>[!abstract]- Functions
>>- Dialog control (full 🆚 half duplex)
>>- Token management
>>- Synchronization
>>- Recovery management
>
>>[!warning] Not often implemented in real systems

6. >[!info]- Presentation Layer
>>[!abstract]- Purpose
>> Formatting data for transmission
>
>>[!abstract]- Functions
>>- Translation
>>- Compression
>>- Encryption
>
>>[!warning] In practice not implemented in a separate layer but included else where (in the applications)

7. >[!info]- Application Layer
>>[!abstract]- Purpose
>>Provide network based applications for users
>
>>[!abstract]- Functional Applications
>>- File transfer
>>- Electronic mail
>>- World wide web
>>- Instant messaging
>>- Directory services
>>- Remote file systems
>
>>[!warning] Some widely used applications are standardized



