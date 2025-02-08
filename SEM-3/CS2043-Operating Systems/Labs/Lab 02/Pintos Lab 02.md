#pintos 

> [!file]- Reference Note
> ![[Project 2--User Programs.pdf]]

# Pintos OS Lab 02 Guide

## Content

- [[#1. Introduction to the Project|1. Introduction to the Project]]
- [[#2. Understanding the Source Files|2. Understanding the Source Files]]
- [[#3. Setting up the Simulated File System|3. Setting up the Simulated File System]]
	- [[#3. Setting up the Simulated File System#Step-by-Step:|Step-by-Step:]]
- [[#4. User Programs and ELF Binaries|4. User Programs and ELF Binaries]]
	- [[#4. User Programs and ELF Binaries#Key Points:|Key Points:]]
- [[#5. Virtual Memory Layout|5. Virtual Memory Layout]]
	- [[#5. Virtual Memory Layout#Memory Layout for User Programs:|Memory Layout for User Programs:]]
- [[#6. Suggested Order of Implementation|6. Suggested Order of Implementation]]
	- [[#6. Suggested Order of Implementation#6.1 Argument Passing|6.1 Argument Passing]]
	- [[#6. Suggested Order of Implementation#6.2 User Memory Access|6.2 User Memory Access]]
	- [[#6. Suggested Order of Implementation#6.3 System Call Infrastructure|6.3 System Call Infrastructure]]
	- [[#6. Suggested Order of Implementation#6.4 Implement System Calls|6.4 Implement System Calls]]
	- [[#6. Suggested Order of Implementation#6.5 Process Termination|6.5 Process Termination]]
	- [[#6. Suggested Order of Implementation#6.6 Modify `process_wait()`|6.6 Modify `process_wait()`]]
- [[#7. Testing|7. Testing]]
- [[#8. Final Submission|8. Final Submission]]



### 1. Introduction to the Project

In this project, you will:
- Enable user programs to interact with the Pintos operating system via **system calls**.
- Handle multiple user processes running concurrently.
- Work with **virtual memory**, **processes**, **system calls**, and **basic file systems**.
  
You will begin by implementing system calls and managing user process execution, moving from kernel-level code in Pintos (as done in the previous project) to handling **user-level processes**.

### 2. Understanding the Source Files

You will mainly work in the **userprog** directory, and the key source files include:

- **`process.c` and `process.h`**: Responsible for loading and starting user processes (ELF binaries).
- **`syscall.c` and `syscall.h`**: These files handle system calls made by user programs. You will extend the provided skeleton to handle different system calls.
- **`exception.c` and `exception.h`**: Handle exceptions (like page faults) that occur when a user process attempts illegal operations. You may modify this file for page faults.
- **`pagedir.c` and `pagedir.h`**: Manages 80x86 hardware page tables. You might need to call functions from here for managing memory access.
  
Start by familiarizing yourself with these files, as you’ll be modifying many of them to add the needed functionality for this project.

---

### 3. Setting up the Simulated File System

The provided **file system** in Pintos is basic, and your user programs will interact with it for tasks like reading and writing files. Here’s how to set it up:

#### Step-by-Step:

1. **Create a simulated disk**:
   - Use the `pintos-mkdisk` command to create a disk named `filesys.dsk` of size 2MB:
     ```
     pintos-mkdisk filesys.dsk --filesys-size=2
     ```

2. **Format the file system**:
   - After creating the disk, format it using the following command:
     ```
     pintos -- -f -q
     ```

3. **Copy test programs into the file system**:
   - Use the `pintos -p` (put) command to copy files into the simulated file system. For example, to copy the `echo` program:
     ```
     pintos -p ../../examples/echo -a echo -- -q
     ```

4. **Run a user program**:
   - After copying the user program, run it using the `pintos` command. Example to run the `echo` program:
     ```
     pintos -- -q run 'echo x'
     ```

   **Note**: Argument passing might not work until implemented.

5. **Summary of Combined Commands**:
   - You can combine the steps for creating the disk, formatting it, copying a program, and running it into a single command:
     ```
     pintos --filesys-size=2 -p ../../examples/echo -a echo -- -f -q run 'echo x'
     ```

---

### 4. User Programs and ELF Binaries

Pintos can run normal C programs that don’t require advanced features like dynamic memory allocation (`malloc`) or floating point operations. User programs must be compiled as **ELF binaries** (Executable and Linkable Format) using the provided tools. These programs are stored in the simulated file system and executed by the kernel.

#### Key Points:
- ELF binaries are loaded by `process.c`.
- Argument passing needs to be handled by you for proper execution of user programs.

---

### 5. Virtual Memory Layout

Pintos divides virtual memory into **user virtual memory** and **kernel virtual memory**:

- **User Virtual Memory**: Ranges from address `0` to `PHYS_BASE` (default 0xc0000000 or 3 GB).
  - Each process has its own virtual memory space.
  - A process’s **user stack** starts at `PHYS_BASE` and grows downward, while its code and data segments start lower in memory.

- **Kernel Virtual Memory**: Occupies the memory above `PHYS_BASE`. This memory is global and accessible by all kernel threads.

#### Memory Layout for User Programs:
- **Code Segment** (at address `0x08048000`).
- **Data Segments** (initialized and uninitialized).
- **Stack** (grows downward).

Pintos automatically manages the virtual memory for processes when switching between them, ensuring each process has access only to its own user memory.

---

### 6. Suggested Order of Implementation

To build the project step-by-step, follow this suggested sequence:

#### 6.1 Argument Passing
- Modify `process_execute()` to support **argument passing**. 
  - Split the command-line string into words and pass them as arguments.
  - For instance, running `grep foo bar` should execute `grep` with two arguments: `foo` and `bar`.

**Key Action**: Parse the command string and load arguments onto the stack during process setup.

#### 6.2 User Memory Access
- Before a system call can be processed, you need to safely access memory passed from user processes.
  - Implement code to validate that a pointer points to valid user memory.
  - Functions like `get_user()` and `put_user()` can be used to safely read/write from user memory.

#### 6.3 System Call Infrastructure
- **Extend `syscall.c`** to handle system calls.
  - Retrieve the system call number from the user stack.
  - Based on the number, call the appropriate system call handler (e.g., `exit`, `exec`, `wait`, etc.).

#### 6.4 Implement System Calls

You will implement the following system calls in **syscall.c**:

1. **`halt()`**: Shut down the Pintos system.
2. **`exit(int status)`**: Terminate the current user program and return a status code.
3. **`exec(const char* cmd_line)`**: Start a new process by executing the given command line.
4. **`wait(pid_t pid)`**: Wait for a child process to terminate and retrieve its exit status.
5. **File system calls** (`open`, `read`, `write`, `close`, `create`, `remove`, etc.).

**Example**: For the `write()` system call:
- Handle writing to the console (file descriptor `1` for `stdout`) or files.
- Ensure the system handles concurrent file access using synchronization primitives like locks.

#### 6.5 Process Termination
- Print a message whenever a process terminates using `exit()`.
  - The format should be: `"%s: exit(%d)\n"`, where `%s` is the process name, and `%d` is the exit status.

#### 6.6 Modify `process_wait()`
- Implement proper waiting for child processes.
  - `wait()` should only allow a parent to wait for its direct children.
  - Handle the case where a process terminates before its parent calls `wait()`.

---

### 7. Testing

1. **Automated Tests**:
   - Pintos provides a test suite located in the `src/tests` directory.
   - You can run all tests using the command:
     ```
     make check
     ```
   - Each test will report either **pass** or **fail**, along with a summary of the test results.

2. **Individual Tests**:
   - Tests can also be run individually for debugging.

3. **Capturing Results**:
   - Take screenshots of the final test summary for submission, showing all tests passed.

---

### 8. Final Submission

Before submitting your project, ensure you have the following:

1. **Updated Design Document** (`DESIGNDOC`) explaining your design decisions.
2. **Source Code** with all your changes in the Pintos system.
3. **Screenshots** of the test results from the automated test suite.

---
