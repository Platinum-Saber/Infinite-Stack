Related : #OS #OS/02 #SystemServices
Reference Note : [L02.pdf](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20note%5CL02.pdf)


# Content

- [[#1. Introduction to Operating System Services|1. Introduction to Operating System Services]]
	- [[#1. Introduction to Operating System Services#Key Services Provided by an Operating System:|Key Services Provided by an Operating System:]]
- [[#2. Operating System Functions|2. Operating System Functions]]
	- [[#2. Operating System Functions#2.1. Program Execution|2.1. Program Execution]]
	- [[#2. Operating System Functions#2.2. I/O Operations|2.2. I/O Operations]]
	- [[#2. Operating System Functions#2.3. File-System Manipulation|2.3. File-System Manipulation]]
	- [[#2. Operating System Functions#2.4. Communications|2.4. Communications]]
	- [[#2. Operating System Functions#2.5. Error Detection|2.5. Error Detection]]
	- [[#2. Operating System Functions#2.6. Resource Allocation|2.6. Resource Allocation]]
	- [[#2. Operating System Functions#2.7. Logging and Accounting|2.7. Logging and Accounting]]
	- [[#2. Operating System Functions#2.8. Protection and Security|2.8. Protection and Security]]
- [[#3. User and Operating-System Interface|3. User and Operating-System Interface]]
	- [[#3. User and Operating-System Interface#3.1. Command-Line Interface (CLI)|3.1. Command-Line Interface (CLI)]]
	- [[#3. User and Operating-System Interface#3.2. Graphical User Interface (GUI)|3.2. Graphical User Interface (GUI)]]
	- [[#3. User and Operating-System Interface#3.3. Touchscreen Interfaces|3.3. Touchscreen Interfaces]]
- [[#4. System Calls|4. System Calls]]
	- [[#4. System Calls#4.1. Definition|4.1. Definition]]
	- [[#4. System Calls#4.2. Examples of System Calls|4.2. Examples of System Calls]]
	- [[#4. System Calls#4.3. System Call Implementation|4.3. System Call Implementation]]
- [[#5. Operating System Design and Structure|5. Operating System Design and Structure]]
	- [[#5. Operating System Design and Structure#5.1. Monolithic Structure|5.1. Monolithic Structure]]
	- [[#5. Operating System Design and Structure#5.2. Layered Approach|5.2. Layered Approach]]
	- [[#5. Operating System Design and Structure#5.3. Microkernel|5.3. Microkernel]]
	- [[#5. Operating System Design and Structure#5.4. Modules|5.4. Modules]]
	- [[#5. Operating System Design and Structure#5.5. Hybrid Systems|5.5. Hybrid Systems]]
- [[#6. System Programs|6. System Programs]]
	- [[#6. System Programs#6.1. File Manipulation|6.1. File Manipulation]]
	- [[#6. System Programs#6.2. Status Information|6.2. Status Information]]
	- [[#6. System Programs#6.3. Programming Language Support|6.3. Programming Language Support]]
	- [[#6. System Programs#6.4. Communications|6.4. Communications]]
- [[#7. Building and Booting an Operating System|7. Building and Booting an Operating System]]
	- [[#7. Building and Booting an Operating System#7.1. Boot Process|7.1. Boot Process]]
	- [[#7. Building and Booting an Operating System#7.2. Booting Linux|7.2. Booting Linux]]
- [[#8. Operating System Debugging|8. Operating System Debugging]]
	- [[#8. Operating System Debugging#8.1. Tools for Debugging|8.1. Tools for Debugging]]


## 1. Introduction to Operating System Services
Operating systems (OS) provide an essential environment for programs and users to execute tasks. These services are crucial for ensuring smooth execution, managing resources, and enhancing user experience.

### Key Services Provided by an Operating System:

> [!NOTE] User Interface (UI)
> The system provides a UI that can be:
>-  **Command-Line Interface (CLI)**: Users input commands directly.
>-   **Graphical User Interface (GUI)**: Users interact with icons, windows, and menus.
>-  **Touch Interface**: Common in mobile devices, using gestures for interaction.

---

## 2. Operating System Functions

### 2.1. Program Execution
The OS is responsible for loading programs into memory and executing them. It manages program execution from start to finish, including normal and abnormal (error) terminations.

### 2.2. I/O Operations
Programs often require input/output (I/O) operations. The OS provides mechanisms to perform I/O with files and devices efficiently.

### 2.3. File-System Manipulation
The OS manages files and directories by allowing operations such as creating, deleting, reading, and writing files. It also controls file permissions and access.

**Example**: Windows Explorer for file manipulation through the GUI or `cp`, `mv` commands in UNIX for CLI-based file operations.

### 2.4. Communications
- **Purpose**: Facilitates communication between processes either on the same computer or across networks.
- **Methods**:
  - **Shared Memory**: Multiple processes share a portion of memory.
  - **Message Passing**: The OS moves packets (messages) between processes.

**Example**: Socket programming in networking allows two systems to communicate over a network.

### 2.5. Error Detection
The OS must constantly monitor the system for possible errors in hardware, I/O devices, or software programs. When an error is detected, it takes appropriate action to ensure the system remains stable.

**Example**: Disk read errors can result in log entries that the OS can use for diagnostics.

### 2.6. Resource Allocation
When multiple processes or users are running concurrently, the OS must allocate resources efficiently, including CPU time, memory, and I/O devices.

**Example**: A multi-user environment where each user needs CPU time and memory for their tasks.

### 2.7. Logging and Accounting
The OS logs resource usage to track how much of each resource (CPU, memory, I/O) is used by each process or user. This can be used for auditing or billing in environments where resources are billed.

### 2.8. Protection and Security
Protection and security services ensure that unauthorized users or processes do not access the system’s resources. This is especially important in multi-user systems where data confidentiality is key.

**Example**: User authentication through passwords or biometric data.

---

## 3. User and Operating-System Interface

### 3.1. Command-Line Interface (CLI)
- The CLI allows users to interact with the OS by typing commands directly into the command shell.
- Popular shells include **Bash** for Linux and **Command Prompt** for Windows.

### 3.2. Graphical User Interface (GUI)
- The GUI uses icons and windows to allow users to interact with the OS visually. Actions can be performed by clicking icons or dragging objects.
  
**Example**: macOS uses the Aqua GUI, and Windows uses its own GUI with a taskbar and windows for application management.

### 3.3. Touchscreen Interfaces
- Many devices today use touchscreens, where gestures replace mouse clicks and keyboard commands.
- **Examples**: iPads and Android tablets.

---

## 4. System Calls
System calls provide a way for programs to interact with the operating system.

### 4.1. Definition
System calls are the interface between a program and the OS. They are often wrapped in high-level APIs for simplicity and portability.

### 4.2. Examples of System Calls
- **Process Control**: `fork()`, `exec()`, `exit()`
- **File Management**: `open()`, `close()`, `read()`, `write()`
- **Device Management**: `ioctl()`, `read()`, `write()`
- **Information Maintenance**: `getpid()`, `time()`
- **Communications**: `pipe()`, `shmget()`, `mmap()`
- **Protection**: `chmod()`, `chown()`

> [!image] Screen shot
> ![[Pasted image 20241002234720.png]]

### 4.3. System Call Implementation
- **Process**: When a system call is made, the OS uses a table of system call numbers to execute the corresponding function. 
- **API**: Application Programming Interfaces (API) like POSIX or Win32 are used to make system calls easier for developers to use.
  
**Example**: Copying a file using `open()`, `read()`, `write()`, and `close()` system calls.

---

## 5. Operating System Design and Structure

### 5.1. Monolithic Structure
- **Definition**: All OS functionality is bundled into one large block of code.
  
**Example**: Early UNIX systems followed a monolithic structure.

### 5.2. Layered Approach
- **Definition**: The OS is divided into layers, with each layer providing services to the one above it.

**Example**: The OSI model for networking.

### 5.3. Microkernel
- **Definition**: A minimal kernel that provides only basic services like process management and message passing, with other services running in user space.

**Example**: Mach kernel, used in macOS.

### 5.4. Modules
- Many modern OSes like Linux allow for **modular structures**, where kernel functionality is extended by loading and unloading kernel modules dynamically.

### 5.5. Hybrid Systems
- **Definition**: Combines various design structures to balance performance, security, and flexibility.
  
**Example**: Windows and macOS use hybrid kernel designs, with aspects of monolithic, microkernel, and modular architectures.

---

## 6. System Programs

### 6.1. File Manipulation
System programs allow users to create, delete, copy, rename, and manage files and directories.

**Example**: Linux commands like `cp`, `mv`, `rm`.

### 6.2. Status Information
System programs provide the user with information about the system’s status, such as date, time, memory usage, and disk space.

**Example**: `top` command in Linux shows system resource usage.

### 6.3. Programming Language Support
The OS provides tools like compilers, debuggers, and interpreters to support program development.

**Example**: GCC compiler in Linux for C/C++.

### 6.4. Communications
These programs allow users to communicate between systems through mechanisms like email, remote login, and file transfer.

**Example**: SSH (Secure Shell) allows remote system access.

---

## 7. Building and Booting an Operating System

### 7.1. Boot Process
- **Steps**:
  - **BIOS/UEFI** initializes the system and loads the bootloader.
  - The **bootloader** loads the OS kernel into memory.
  - The kernel initializes hardware and system processes.

**Example**: GRUB bootloader in Linux systems.

### 7.2. Booting Linux
- Download the Linux source code from [kernel.org](https://kernel.org).
- Configure, compile, and install the Linux kernel using `make` commands.

---

## 8. Operating System Debugging
Debugging is the process of identifying and fixing errors in software.

### 8.1. Tools for Debugging
- **strace**: Tracks system calls made by processes.
- **gdb**: A source-level debugger for programs.
- **perf**: Performance analysis tool for Linux.
  
**Example**: Using `strace` to troubleshoot I/O issues in a Linux program.

---
