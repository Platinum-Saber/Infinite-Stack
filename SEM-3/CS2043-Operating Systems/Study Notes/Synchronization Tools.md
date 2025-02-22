Related :  #OperatingSystems #OS #OS/05 #Synchronization

Reference Video :  [Lecture 05](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20Video%5CLecture%205.mp4)
Reference Notes :  [chapter 06](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20note%5CNew%20notes%5Cch6.pptx) , [mutual exclusion-part 1](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20note%5CNew%20notes%5Cmutualexclusion-part%201.ppt)

<br>

---
# Content

- [[#Synchronization|Synchronization]]
- [[#Shared Resources|Shared Resources]]
- [[#**1. Introduction to Synchronization**|**1. Introduction to Synchronization**]]
- [[#**2. Synchronization Motivation**|**2. Synchronization Motivation**]]
- [[#**3. Race Condition**|**3. Race Condition**]]
- [[#**4. The Critical-Section Problem**|**4. The Critical-Section Problem**]]
	- [[#**4. The Critical-Section Problem**#**Requirements for Solutions**:|**Requirements for Solutions**:]]
- [[#**5. Solutions to the Mutual Exclusion Problem**|**5. Solutions to the Mutual Exclusion Problem**]]
	- [[#**5. Solutions to the Mutual Exclusion Problem**#**5.1. The Turn Variable Approach (First Attempt)**|**5.1. The Turn Variable Approach (First Attempt)**]]
	- [[#**5. Solutions to the Mutual Exclusion Problem**#**6. Dekker’s Algorithm**|**6. Dekker’s Algorithm**]]
	- [[#**5. Solutions to the Mutual Exclusion Problem**#**Key Features**:|**Key Features**:]]
	- [[#**5. Solutions to the Mutual Exclusion Problem**#**7. Peterson’s Algorithm**|**7. Peterson’s Algorithm**]]
- [[#**8. Hardware-Assisted Mutual Exclusion**|**8. Hardware-Assisted Mutual Exclusion**]]
	- [[#**8. Hardware-Assisted Mutual Exclusion**#**8.1. Test-and-Set**|**8.1. Test-and-Set**]]
	- [[#**8. Hardware-Assisted Mutual Exclusion**#**8.2. Exchange**|**8.2. Exchange**]]
- [[#**9. Liveness**|**9. Liveness**]]
	- [[#**9. Liveness**#**Types of Liveness Failures**:|**Types of Liveness Failures**:]]
- [[#**10. Semaphores and Mutexes**|**10. Semaphores and Mutexes**]]
	- [[#**10. Semaphores and Mutexes**#**10.1. Semaphores**|**10.1. Semaphores**]]
	- [[#**10. Semaphores and Mutexes**#**10.2. Mutex Locks**|**10.2. Mutex Locks**]]
- [[#**11. Monitors**|**11. Monitors**]]
- [[#**12. Evaluation of Synchronization Tools**|**12. Evaluation of Synchronization Tools**]]
	- [[#**12. Evaluation of Synchronization Tools**#**12.1. Low Contention**:|**12.1. Low Contention**:]]
	- [[#**12. Evaluation of Synchronization Tools**#**12.2. Moderate to High Contention**:|**12.2. Moderate to High Contention**:]]
	- [[#**12. Evaluation of Synchronization Tools**#**Conclusion**|**Conclusion**]]




---

<br>

## Synchronization
> [!note] Multi-threaded programs
> Threads **cooperate** in multithreaded programs.
> - To **share resources**, access shared data structures.
> - To **coordinate** their execution.
> 
> For correctness, this *cooperation needs to be controlled.*
> 
> > [!faq]- Why do we need synchronization.
> > 1. Thread schedule is **non-deterministic**
> > 	- scheduling is **not under program control.**
> > 	- threads *interleave executions* **arbitrarily** and **at different rates**.
> > 	- behavior changes when re-run program.
> > 2. *Multi-word operations* are **not atomic**.
> > 3. Compiler/ hardware *instruction reordering*.

<br>

## Shared Resources
 > [!abstract]- Mechanisms to control access to shared resources.
 > - Locks
 > - Mutexes
 > - Semaphores
 > - Monitors
 > - Condition Variables
 
 > [!abstract]- Patterns for coordinating accesses to shared resources
 > - Bounded buffer
 > - Producer-Consumer

<br>

## **1. Introduction to Synchronization**
- Synchronization is essential in multitasking systems where processes or threads share resources or data.
- Without proper synchronization, **race conditions** occur, leading to **data inconsistency**.

---

## **2. Synchronization Motivation**
- **Concurrency**: Processes/threads may run simultaneously, leading to conflicts when accessing shared resources.
- **Non-deterministic Scheduling**: Thread execution order is determined by the OS, not by the program, leading to unpredictable interleaving of operations.
  
**Example**: Two threads updating a shared variable may overwrite each other's updates, resulting in incorrect data.

---

## **3. Race Condition**
A **race condition** happens when multiple processes/threads access and modify shared data simultaneously without proper synchronization, leading to unpredictable outcomes.

**Example**: Two processes attempting to access a shared variable `next_available_pid` may assign the same PID to different processes without synchronization.

---

## **4. The Critical-Section Problem**
The **critical section** is the part of the program where shared resources are accessed. To prevent conflicts, only one process should be in its critical section at any time.

### **Requirements for Solutions**:
1. **Mutual Exclusion**: Only one process can be in the critical section at any time.
2. **Progress**: If no process is in the critical section, a process must be allowed to enter without indefinite postponement.
3. **Bounded Waiting**: There must be a limit to how long a process can wait to enter the critical section.

---

## **5. Solutions to the Mutual Exclusion Problem**

### **5.1. The Turn Variable Approach (First Attempt)**
- A shared variable `turn` indicates which process can enter the critical section.
- **Issues**:
  - **Starvation**: If one process halts in its non-critical section, the other may be indefinitely blocked from entering its critical section.

---

### **6. Dekker’s Algorithm**
Dekker’s Algorithm ensures mutual exclusion without the problems of simpler approaches like the turn variable. It uses flags (`c1`, `c2`) and a turn variable to alternate between processes accessing the critical section.

### **Key Features**:
- **Mutual Exclusion**: Only one process enters the critical section at a time.
- **No Deadlock**: Both processes can't be stuck waiting for each other.
- **No Starvation**: Each process eventually enters the critical section.

---

### **7. Peterson’s Algorithm**
Peterson’s Algorithm refines Dekker’s approach by using both a **turn variable** and **status flags** to manage access to the critical section. A process sets its flag and gives away the turn if the other process also wants access.

**Key Features**:
- **Mutual Exclusion** is ensured.
- **Deadlock-Free**: No process is indefinitely blocked.
- **Starvation-Free**: Each process gets a turn to access the critical section.

---

## **8. Hardware-Assisted Mutual Exclusion**
Some systems provide **hardware support** for synchronization through atomic operations.

### **8.1. Test-and-Set**
- A **test-and-set** instruction is an atomic operation that checks and modifies a variable in a single, indivisible step.
- **Example**: A lock can be implemented using `test_and_set()` to ensure that a process enters the critical section only when the lock is available.

### **8.2. Exchange**
- The **exchange** instruction swaps the values of two variables atomically, ensuring mutual exclusion during the swap operation.

---

## **9. Liveness**
**Liveness** ensures that processes continue making progress in acquiring resources or entering the critical section.

### **Types of Liveness Failures**:
1. **Deadlock**: Two or more processes wait indefinitely for each other to release resources.
   
   **Example**: If two processes `P0` and `P1` each hold a resource needed by the other, they enter a deadlock waiting for each other.

2. **Starvation**: A process waits indefinitely because other processes continuously access the critical section before it.
   
3. **Priority Inversion**: A lower-priority process holds a lock needed by a higher-priority process, causing the higher-priority process to wait indefinitely.
   
   **Solution**: **Priority Inheritance Protocol**: Temporarily raises the priority of the lower-priority process to prevent priority inversion.

---

## **10. Semaphores and Mutexes**

### **10.1. Semaphores**
- A **semaphore** is a synchronization primitive that uses two atomic operations, **wait** and **signal**, to control access to shared resources.
- **Example**: A binary semaphore (similar to a mutex) ensures that only one process can access a critical section at a time.

### **10.2. Mutex Locks**
- A **mutex** (mutual exclusion) lock is a binary semaphore specifically designed to allow only one process at a time into the critical section.
- **Example**: In multithreaded applications, a mutex ensures that only one thread can modify shared data at a time.

---

## **11. Monitors**
A **monitor** is a high-level synchronization mechanism that bundles shared data and the operations on that data within a single module, with built-in mutual exclusion.

**Example**: In Java, the `synchronized` keyword ensures that only one thread can access a synchronized method at a time, providing built-in mutual exclusion.

---

## **12. Evaluation of Synchronization Tools**

### **12.1. Low Contention**: 
- When there are few processes competing for resources, simpler synchronization mechanisms like **Peterson's Algorithm** or **test-and-set** may suffice.

### **12.2. Moderate to High Contention**:
- For scenarios with moderate to high contention, more robust synchronization mechanisms like **semaphores**, **mutexes**, or **monitors** are needed to efficiently manage shared resources.

---

