
### 1. **Overview of the Project**

In this project, you will:
- Enable user programs to **interact with the OS** via system calls.
- Implement **process management** that allows multiple processes to run concurrently.
- Ensure **memory management** for each user process and handle user-kernel interactions safely.
  
Your work will focus on the **userprog** directory, but it will interact with many other parts of Pintos, such as **process loading**, **system call handling**, **file systems**, and **virtual memory**.

You have the option to build on top of **Project 1** or start fresh. The tasks here will be independent of Project 1 code, except for the optional use of the **alarm clock** feature in future projects.

---

### 2. **Source Files for the Project**

The primary files to work on in this project are located in the **userprog** directory:

- **`process.c` & `process.h`**: Responsible for loading ELF binaries and starting processes.
- **`syscall.c` & `syscall.h`**: Handle system calls made by user programs. You will extend the skeleton implementation to implement specific system calls like `exit`, `exec`, `wait`, `read`, `write`, etc.
- **`exception.c` & `exception.h`**: Handle exceptions (such as page faults) when a user program tries to access invalid memory or perform prohibited actions.

Additionally, you will need to **interact with the file system**, although modifying file system code is not the focus of this project. Use existing file system routines to handle file operations in system calls.

---

### 3. **Setting Up the Simulated File System**

To run user programs, you'll need to work with a **simulated disk** that contains a Pintos file system. The steps are as follows:

1. **Create a simulated disk**:
   ```
   pintos-mkdisk filesys.dsk --filesys-size=2
   ```
   This command creates a 2 MB file system partition.

2. **Format the disk**:
   ```
   pintos -- -f -q
   ```
   This formats the file system on the simulated disk.

3. **Copy a program to the disk**:
   - Use the `pintos -p` (put) command to copy files into the simulated file system. Example:
     ```
     pintos -p ../../examples/echo -a echo -- -q
     ```
     This copies the `echo` program from the examples directory.

4. **Run a user program**:
   ```
   pintos -- -q run 'echo cs318'
   ```
   This command runs the `echo` program on the simulated disk with argument `cs318`.

---

### 4. **Understanding User Programs and ELF Binaries**

Pintos can run user programs written in C as long as they are compiled into **ELF binaries**. These binaries are loaded by `process.c`, and you’ll need to modify the handling of **arguments** to user programs as part of your implementation. Pintos does not support features like dynamic memory allocation (`malloc`) or floating-point operations in user programs.

The **examples** directory contains several sample user programs for testing. Use the provided **Makefile** to compile these programs and add your own test cases.

---

### 5. **Virtual Memory in Pintos**

Pintos divides memory into two parts:

- **User Virtual Memory**: Occupies the address range from `0x00000000` to `PHYS_BASE` (typically 3 GB).
- **Kernel Virtual Memory**: Occupies the range from `PHYS_BASE` to `4 GB`.

Each user process has its own **virtual address space** that is separate from the kernel's. The user stack starts at `PHYS_BASE` and grows downward. Each process is restricted to its own virtual memory space, and any attempt to access kernel memory causes a **page fault**.

---

### 6. **Suggested Implementation Order**

Here’s a step-by-step breakdown of the tasks:

#### **6.1 Argument Passing**
- Modify `process_execute()` to support **passing arguments** to user programs.
- Break the command string into individual arguments (words separated by spaces), and place them on the **user stack**.
  
  For example, the command `grep foo bar` should run the `grep` program with two arguments: `foo` and `bar`.

#### **6.2 User Memory Access**
- Implement functionality to access memory safely via pointers passed by user programs in system calls.
  - Ensure pointers are valid and refer to memory below `PHYS_BASE`.
  - You can use helper functions like `get_user()` and `put_user()` to read and write user memory safely.

#### **6.3 System Call Infrastructure**
- Extend `syscall.c` to handle different **system calls**.
  - Retrieve the system call number from the user stack and dispatch the appropriate handler.
  - Implement system calls such as `exit`, `exec`, `wait`, `write`, and file-related calls like `open`, `read`, and `create`.

#### **6.4 System Calls to Implement**
You will implement the following system calls in **syscall.c**:

1. **`halt()`**: Shuts down the Pintos system.
2. **`exit(int status)`**: Terminates the process and returns a status code.
3. **`exec(const char* cmd_line)`**: Executes a new program and returns its process ID.
4. **`wait(pid_t pid)`**: Waits for a child process to terminate and retrieves its exit status.
5. **File-related system calls** like:
   - **`open`**: Opens a file.
   - **`read`**: Reads data from a file or standard input.
   - **`write`**: Writes data to a file or standard output.
   - **`close`**: Closes a file descriptor.

#### **6.5 Process Termination Messages**
- Implement process termination messages:
  - When a process terminates, print its name and exit code in the format:
    ```
    "%s: exit(%d)\n"
    ```

#### **6.6 Modify `process_wait()`**
- Implement a proper waiting mechanism for child processes. The `wait()` system call must handle cases where processes wait for their children to terminate and retrieve their exit status.

---

### 7. **Testing Your Implementation**

Use the **Pintos test suite** to validate your implementation:

1. **Run automated tests**:
   ```
   make check
   ```
   This command runs all the tests provided with the project and outputs a **pass/fail** status for each test.

2. **Individual testing**:
   - You can run individual tests if needed, and the suite will print details on test failures to help you debug.

3. **Capture results**:
   - Take screenshots of your test results, especially the final test summary, and include them in your submission.

---

### 8. **Submission Requirements**

Before submitting, ensure the following:

1. **Updated Design Document**: Fill out the design document template and submit it as part of your source code.
2. **Source Code**: Include all your code changes.
3. **Screenshots of Test Results**: Include images showing the results of the automated test suite.

![[Pasted image 20241106194725.png]]

---

### Summary

This project focuses on extending the Pintos OS to handle user programs. You will implement key system calls, manage process execution, and interact with the file system. Follow the suggested implementation order and test your work using the provided test suite.