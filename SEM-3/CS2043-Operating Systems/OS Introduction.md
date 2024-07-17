
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

### I/O Structure
>[!info]- Interrupt drive I/O Cycle
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

### Storage Structure
- > [!note]- Main Memory
- 