Related : #OperatingSystems #OS #OS/01

Reference Video :  [Reference Lecture](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20Video%5Clecture%201.mp4) , [Introduction to Operating Systems](https://www.youtube.com/watch?v=dOiA2nNJpc0)
Reference Notes : [Chapter 01](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20note%5CNew%20notes%5Cch1%20.pptx)

> [!file]- Lecture Note : Chapter 1
> ![[L01.pdf]]

<br>

---
# Content
1. [[#Computer System Structure]]
	- [[#I/O Structure]]
	- [[#Storage Structure]]
		- [[#Storage Hierarchy]]
		- [[#Direct Memory Access Structure]]
	- [[#Operating System Operations]]
	- [[#Multiprogramming (Batch System)]]
	- [[#Multitasking (Timesharing)]]
	- [[#Dual-mode Operation]]
	- [[#Timer]]
	- [[#Process Management]]
	- [[#Memory Management]]
		- [[#Mass-Storage Management]]
		- [[#Caching]]
		- [[#Migration of Data From Disk to Register]]
	- [[#File-System Management]]
	- [[#I/O Subsystem]]
	- [[#Protection And Security]]
	- [[#Virtualization]]
	- [[#Distributed Systems]] 
2. [[#Computer System Architecture]]
	- [[#Symmetric Multiprocessing Architecture]]
		- [[#Dual-Core Design]]
	- [[#Non-Uniform Memory Access System]]
	- [[#Clustered Systems]]
	- [[#PC Motherboard]]
3. [[#Computer System Environments]]
	- [[#Traditional]]
	- [[#Mobile]]
	- [[#Client Server]]
	- [[#Peer-to-Peer]]
	- [[#Cloud Computing]]
	- [[#Real-Time Embedded Systems]]
	- [[#Free and Open-Source Operating Systems]]
4. [[#Kernel Data Structures]]

<br>

---


>[!example]- Components of a modern computer
>- One or more processors
>- Main memory
>- Disk
>- Printers
>- Keyboard
>- Mouse
>- Display
>- Network interfaces
>- I/O devices
>
>![[Pasted image 20240717110629.png]]

>[!FAQ]- What is an Operating System
>A program that acts as an intermediary between a user and the computer hardware.
>
>![[Pasted image 20240717104857.png]]

<br>

# Computer System Structure

>[!abstract]- Components of a *Computer System Structure*
>>[!info]- Hardware
>>provides basic computing resources like CPU, memory, I/O devices
>
>>[!info]- Operating System
>>Controls & coordinates use of hardware among various users and applications.
>
>>[!info]- Application Program
>>Define the ways in which the system resources are used to solve the computing problems of the users.
>
>>[!info]- Users
>>People, machines, other computers

>[!note]- Overview of *Computer system organization* :RiStickyNoteFill:
> One or more CPUs, and device controllers connect through common `bus` providing access to shared memory.
> Concurrent execution of CPUs and devices competing for memory cycles
> 
> ![[Pasted image 20240717121021.png]]
> **********************************************************************
> >[!info]- How a modern computer works
> >![[Pasted image 20240717144912.png]]

>[!note]- Computer Startup
>- `Bootstrap program` is loaded at power up or reboot
>	- Typically stored in ROM or EPROM generally known as `firmware`
>	- Initializes all aspects of system
>	- Loads operating system kernel and starts execution


>[!EXAMPLE]- Computer system operations 
>- I/O devices and the CPUs can execute concurrently
>- Each device controller is in charge of a particular type
>- Each device controller has a `local buffer`
>- Each device controller type has an operating system `device driver` to manage it.
>- CPUs move data from/to main memory to/from local buffers
>- I/O is from device to local buffer of controller
>- Device controller informs CPU that it has finished its operation by causing an `interrupt`
>- The operating system preserves the state of the CPU by storing the registers and the program counter
>- Determines which type of interrupt has occurred
>- Separate segments of code determine what action should be taken for each type of interrupt

<br>

## I/O Structure
>[!image]- Interrupt drive I/O Cycle
>![[Pasted image 20240717134458.png]]

>[!abstract]- Methods of handling I/O
>>[!info]- After I/O starts, control returns to user program only upon I/O completion
>>- Wait instruction idles the CPU until the next interrupt 
>>- Wait loop (contention for memory access)
>>- At most one I/O request is outstanding at a time, no simultaneous I/O processing
>
>>[!info]- After I/O starts, control returns to user program without waiting for I/O completion
>>- `system call` - request to the OS to allow user to wait for I/O completion
>>- `Device status table` contains entry for each I/O device indicating its type, address and state
>>- OS indexes into I/O device table to determine device status and to modify table entry to include interrupt

<br>
<br>

## Storage Structure
> [!note]- Main Memory :FasNoteSticky:
>Only large storage media that the CPU can access directly
>- Random access
>- Typically volatile 
>- Typically random access memory in the form of Dynamic Random Access Memory (DRAM)

>[!note]- Secondary storage :FasNoteSticky:
>An extension of main memory that provides large nonvolatile storage capacity
>>###### :FiHardDrive: Hard Disk Drive (HDD)
>> - Rigid metal or glass platters covered with magnetic recording material
>> - Disk surface is logically divided into `tracks` which are subdivided into `sectors`
>> - The `disk controller` determines the logical interaction between the device and the computer
>
>>###### :RiHardDrive3Line: Non volatile Memory (NVM) devices
>>- Faster than hard disks

<br>

### Storage Hierarchy
>[!info] **Caching**  :  copying information into faster storage system; main memory can be viewed as a cache for secondary storage

>[!info]- **Device Driver**  :  Manage I/O for each device controller
>Provides uniform interface between controller and kernel

>[!image]- Storage Device Hierarchy
>![[Pasted image 20240717144728.png]]

> [!image]- How a modern computer works
> ![[Pasted image 20240820204106.png]]

<br>

### Direct Memory Access Structure
- Used for **high speed I/O devices** able to *transmit information at close to* **memory speeds**.
- **Device controller** transfers blocks of data *from buffer storage directly to main memory* **without CPU intervention**.
- Only **one interrupt** is generated *per block* , *rather than the one interrupt* **per byte**.

<br>
<br>

## Operating System Operations
- **Bootstrap program** :  Simple code to initialize the system. Loads the `kernel`
- Kernel loads
- Starts [[System Daemons]] (services provided outside of the kernel)
- Kernel *interrupt driven* hardware and software
	- Hardware interrupt by one of the devices.
	- Software interrupt (Exception or Trap)

<br>

## Multiprogramming (Batch System)

> [!NOTE] Characteristics
> - Single user cannot always keep CPU and I/O devices busy 
> -  Multiprogramming *organizes jobs* (code and data) so CPU always has one to execute 
> -  A **subset of total jobs** *in system is kept in memory* 
> -  One job selected and run via **job scheduling** 
> -  When job has to wait (for I/O for example), OS switches to another job

> [!image]- Memory Layout For Multi-programmed System
> ![[Pasted image 20240821150244.png]]


## Multitasking (Timesharing)

> [!NOTE] Characteristics
> **A logical extension of Batch systems**.
> The CPU switches jobs so frequently that users can *interact with each job while it is running*, creating interactive computing.
> - **Response time** should be < 1 second 
> - Each user has at least one program executing in memory :luc_arrow_big_right: **process** 
> - If several jobs ready to run at the same time :luc_arrow_big_right: **CPU scheduling** 
> - If processes don’t fit in memory, **swapping** *moves them in and out to run* 
> - **Virtual memory** allows execution of processes not completely in memory


## Dual-mode Operation
- Dual-mode operation allows OS to *protect itself and other system components* 
	- **User mode** and **kernel mode** 

- **Mode bit** *provided by hardware* 
	-  Provides ability to distinguish when system is running user code or kernel code. 
	-  When a user is running :luc_arrow_big_right: *mode bit is* `user`
	-  When kernel code is executing :luc_arrow_big_right: *mode bit is* `kernel`.

> [!info] **System call** changes mode to `kernel`, return from call resets it to `user`.

> [!image]- Transition from User to Kernel Mode
> ![[Pasted image 20240821151441.png]]

> [!warning] Instructions designated as **privileged** are only executable in `kernel` mode.

<br>

## Timer
- Timer to **prevent infinite loop** (or process hogging resources) 
	- Timer is set to *interrupt the computer after some time period* 
	-  Keep a **counter** that is *decremented by the physical clock* 
	-  Operating system set the counter (==privileged instruction==) 
	-  When counter zero, generate an interrupt 
	-  Set up before scheduling process to regain control or **terminate program** *that exceeds allotted time*

<br>

## Process Management

> [!NOTE]- Characteristics Of a Process
> - A process is a program in execution. (A unit of work within the system)
> - **Program** is a *Passive entity*.
> - **Process** is an *active entity*.
> - Process needs resources to accomplish its tasks. (CPU, memory, I/O, initialization data)
> - **Single-threaded process** *has one program counter specifying location of next instruction to execute* 
> 	- Process *executes instructions sequentially*, one at a time, until completion 
> - **Multi-threaded process** *has one program counter per thread* 
> - Typically system has many processes, some user, some operating system running *concurrently on one or more CPUs* 
> 	- Concurrency by multiplexing the CPUs among the processes / threads

> [!abstract] Process Management activities
> - **Creating** and **deleting** both *user and system* processes 
> -  **Suspending** and **resuming** processes 
> - Providing mechanisms for process **synchronization** 
> - Providing mechanisms for process **communication** 
> - Providing mechanisms for **deadlock handling**

<br>

## Memory Management
- To execute a program all (or part) of the *instructions* **must be in memory** 
- All (or part) of the *data* that is needed by the program **must be in memory** 
- Memory management *determines what is in memory and when* 
	- Optimizing CPU utilization and computer response to users.

> [!tip] Memory management activities 
> - Keeping track of which parts of memory are currently being used and by whom.
> - Deciding which *processes* (or parts thereof) and *data* to **move into and out of memory**.
> - **Allocating** and **deallocating** memory space as needed.

<br>

### Mass-Storage Management
- Usually disks used to *store data that* **does not fit in main memory** or data that must be **kept for a “long” period of time** 
 - Proper management is of central importance 
- Entire **speed** of computer operation **hinges on** *disk subsystem and its algorithms* 

> [!abstract] OS activities
> - Mounting and unmounting 
> - Free-space management 
> - Storage allocation 
> - Disk scheduling 
> - Partitioning 
> - Protection

<br>

### Caching

- Information in use copied from *slower to faster storage* **temporarily**. 
- Faster storage (cache) *checked first* to determine if information is there 
	- *If it is*, information **used directly** from the cache (fast) 
	- *If not*, **data copied to cache** and used there

> [!image]- Characteristics of various types of storage
> ![[Pasted image 20240821164057.png]]

<br>

### Migration of Data From Disk to Register

- Multitasking environments must be careful to use **most recent value**, *no matter where it is stored* in the storage hierarchy
- Multiprocessor environment must provide **cache coherency** in hardware such that all *CPUs have the most recent value in their cache*

> [!image]- Data migration
> ![[Pasted image 20240821164508.png]]
<br>

## File-System Management
- OS provides *uniform, logical view* of information storage 
	- ==Abstracts physical properties to logical storage unit== :- **file** 
	- Each medium is controlled by device (i.e., disk drive, tape drive) 
		:luc_arrow_big_right: Varying properties include access speed, capacity, data-transfer rate, access method (sequential or random) 

> [!info] File-System management 
> - Files usually *organized into directories* 
> - **Access control** on most systems to determine who can access what 
> - OS activities include 
> 	:luc_arrow_big_right: **Creating** and **deleting** *files and directories* 
> 	:luc_arrow_big_right: Primitives to manipulate files and directories 
> 	:luc_arrow_big_right: **Mapping files** onto secondary storage 
> 	:luc_arrow_big_right: **Backup files** onto stable (non-volatile) storage media.

<br>

## I/O Subsystem
- One purpose of OS is to hide peculiarities of hardware devices from the user.

> [!abstract] Responsibilities of I/O subsystem
> - Memory management of I/O including **buffering** (storing data temporarily while it is being transferred), **caching** (storing parts of data in faster storage for performance), **spooling** (the overlapping of output of one job with input of other jobs)
> - General **device-driver interface**
> - **Drivers** for specific hardware devices

<br>

## Protection And Security
> [!info] Protection
> Any mechanism for controlling access of processes or users to resources defined by the OS

> [!info] Security
> defense of the system against internal and external attacks
> - **Examples** : denial-of-service, worms, viruses, identity theft, theft of service

> [!note] Process of distinguishing users
> -  User identities (user IDs, security IDs) include name and associated number, **one per user**.
> - User ID then associated with all files, processes of that user to determine **access control**.
> - **Group identifier** (group ID) allows set of users to be defined and controls managed, then also associated with each process, file.
> - **Privilege escalation** allows user to change to effective ID with more rights.

<br>

## Virtualization
- Allows operating systems to run applications *within other OSes*

> [!tip] Emulation
> - Used when source CPU type different from target type (i.e. PowerPC to Intel x86)
> - Generally **slowest** method
> - When computer language not compiled to native code :– **Interpretation**

> [!tip] Virtualization
> - OS natively compiled for CPU, running **guest** OSes also natively compiled.
> - Consider *VMware* running *WinXP guests*, each running applications, all on *native WinXP host OS*
> - **VMM** (virtual machine Manager) provides virtualization services

- **VMM** can run natively, in which case they are **also the host**
	- There is no general-purpose host then (VMware ESX and Citrix XenServer)

> [!image]- Computer environments - virtualization
> ![[Pasted image 20240821170358.png]]

<br>

## Distributed Systems
- Collection of **separate**, possibly **heterogeneous**, systems networked together.
- **Network** is a communications path
	- Local Area Network (**LAN**)
	- Wide Area Network (**WAN**)
	- Metropolitan Area Network (**MAN**)
	- Personal Area Network (**PAN**)

> [!info] Network Operating System
> - Provides features between systems across network.
> - Communication scheme allows systems to exchange messages
> - Creates an illusion of a single system

<br>
<br>

# Computer System Architecture
> [!note] Multiprocessors
> - AKA **parallel systems**, **tightly coupled systems**.
> - Advantages
> 	1. *Increased throughput*
> 	2. *Economy of scale*
> 	3. *Increased reliability* (graceful degradation or fault tolerance)
> > [!example] Types
> > 1. **Asymmetric Multiprocessing** – each processor is assigned a specie task.
> > 2. **Symmetric Multiprocessing** – each processor performs all tasks

<br>

## Symmetric Multiprocessing Architecture
> [!image]- Symmetric Multiprocessing Architecture
> ![[Pasted image 20240821174846.png]]

### Dual-Core Design
- Multi-chip and multicore.
- Systems containing all chips.
- Chassis containing multiple separate systems

> [!image]- Dual-Core design
> ![[Pasted image 20240821175406.png]]

<br>

## Non-Uniform Memory Access System
> [!image]- Non-uniform memory access system diagram
> ![[Pasted image 20240821175550.png]]

<br>

## Clustered Systems
- Like multiprocessor systems, but *multiple systems working together*.

> [!abstract] Characteristics of clustered systems
> - Usually sharing storage via a **storage-area network** (SAN)
> - Provides a *high-availability service* which survives failures
> 	- **Asymmetric clustering** has one machine in hot-standby mode 
> 	- **Symmetric clustering** has multiple nodes running applications, monitoring each other
> - Some clusters are for **high-performance computing** (HPC)
> 	- Applications must be written to use **parallelization**
> - Some have **distributed lock manager** (DLM) to *avoid conflicting operations*

> [!image]- Clustered system diagram
> ![[Pasted image 20240821180149.png]]

<br>

## PC Motherboard
> [!image]- Motherboard diagram
> ![[Pasted image 20240821180325.png]]

<br>

# Computer System Environments
> [!example] Computing Environments
> - Traditional
> - Mobile
> - Client Server
> - Peer-to-Peer
> - Cloud computing
> - Real-time Embedded

<br>

## Traditional
> [!summary] Characteristics
> - *Stand-alone general-purpose* machines
> - But blurred as most systems interconnect with others (i.e., the Internet)
> - **Portals** provide *web access* to internal systems
> - **Network computers** (thin clients) are like *Web terminals*
> - Mobile computers interconnect via wireless networks
> - Networking becoming **ubiquitous** – even home systems use *firewalls* to protect home computers from Internet attacks

<br>

## Mobile
> [!summary]  Characteristics
> - Handheld smartphones, tablets, etc.
> - Extra feature – more OS features (GPS, gyroscope)
> - Allows new types of apps like **augmented reality**
> - Use **IEEE 802.11** wireless, or cellular data networks for connectivity

<br>

## Client Server
> [!summary]  Client-Server Computing
> - Dumb terminals supplanted by smart PCs
> - Many systems now **servers**, responding to requests generated by **clients**
> 	- **Compute-server system** provides an interface to client to request services (i.e., database)
> 	- **File-server system** provides interface for clients to store and retrieve files

> [!image]- Cloud server computing diagram
> ![[Pasted image 20240821181238.png]]

<br>

## Peer-to-Peer
> [!summary] Characteristics
> - Another model of **distributed system**
> - P2P *does not distinguish* clients and servers.
> - Can act as client, server or both.
> - Node must join P2P network.
> 	- Registers its service with **central lookup service** on network,
> 	- Broadcast request for service and respond to requests for service via **discovery protocol**
> - *Examples* :- Napster and Gnutella, **Voice over IP** (VoIP) such as Skype

> [!image]- Peer-to-Peer system diagram
> ![[Pasted image 20240821182354.png]]

<br>

## Cloud Computing
- Delivers *computing*, *storage*, even *apps* as a service across a network.
- *Logical extension* of **virtualization** because it uses virtualization as the base for it functionality.
- *Cloud computing environments* composed of **traditional OSes**, plus **VMMs**, plus **cloud management tools**
	- Internet connectivity requires security like firewalls
	- Load balancers spread traffic across multiple applications


> [!summary] Types of cloud computing
> - **Public cloud** – available via Internet to anyone willing to pay
> - **Private cloud** – run by a company for the company’s own use
> - **Hybrid cloud** – includes both public and private cloud components
> - **Software as a Service** (*SaaS*) – one or more applications available via the Internet (i.e., word processor)
> - **Platform as a Service** (*PaaS*) – software stack ready for application use via the Internet (i.e., a database server)
> - **Infrastructure as a Service** (*IaaS*) – servers or storage available over Internet (i.e., storage available for backup use)

> [!image]- Cloud computing diagram
> ![[Pasted image 20240821183124.png]]

<br>

## Real-Time Embedded Systems
- Vary considerable, special purpose, limited purpose OS, real-time OS
- Real-time OS has **well-defined fixed time constraints**
	- Processing must be done within constraint
	- Correct operation only if constraints met

<br>

## Free and Open-Source Operating Systems
- Operating systems made *available in source-code format* rather than just binary **closed-source** and **proprietary**.
- Counter to the **copy protection** and **Digital Rights Management** (DRM) movement
- Started by **Free Software Foundation** (FSF), which has “*copyleft*” **GNU Public License** (GPL).
- *Examples* :- GNU/Linux, BSD UNIX.

<br>
<br>

# Kernel Data Structures
- Many similarities to standard programming data structures.

> [!image]- Kernel data structure diagrams
> ![[Pasted image 20240821184015.png]]
> ![[Pasted image 20240821184032.png]]
> ![[Pasted image 20240821184049.png|664]]

> [!info] Binary Search Tree (left <= right)
> - Search performance :  O(n)
> 	- **Balanced binary search tree** is O(lg n)
> 
> > [!image]- Binary Search Tree diagram
> > ![[Pasted image 20240821184631.png]]

> [!info] Hash Map
> - **Hash function** can create a **hash map**
> - **Bitmap** – string of n binary digits representing the status of n items
> - Linux data structures defined in include files `<linux/list.h>, <linux/kfifo.h>, <linux/rbtree.h>`
> 
> > [!image]- Hash map diagram
> > ![[Pasted image 20240821185020.png]]

<br>

---
Up Next : [[Operating System Services]]