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

## Mass-Storage Management
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

## Caching

▪ Information in use copied from *slower to faster storage* **temporarily**. 
▪ Faster storage (cache) *checked first* to determine if information is there 
• If it is, information used directly from the cache (fast) 
• If not, data copied to cache and used there 
▪ Cache smaller than storage being cached 
• Cache management important design problem 
• Cache size and replacement policy