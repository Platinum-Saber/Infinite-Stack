
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


### OSI (Open System Interconnect) Model
>[!note]- Functionality of OSI model
>- Provides communication regardless of the underlying architecture
>- Has 7 layers which have well defined  functions.
>- Boundaries between the layers minimizes the information flow across.
>
>![[Pasted image 20240703210655.png]]

>[!info]- Physical Layer
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

>[!info]- Data Link Layer
>>[!abstract]- Purpose
>> Provide error free transmission across a single link
>
>>[!abstract]- Functions
>>- Data framing
>>- Error detection and handling
>>- Flow control
>>- Addressing - hardware level

>[!info]- Network Layer
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
