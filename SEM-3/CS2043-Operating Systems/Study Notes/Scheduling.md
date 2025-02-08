

---

### 1. Basic Concepts

> [!NOTE]- CPU-I/O Burst Cycle: 
> Processes alternate between CPU bursts (time spent executing instructions) and I/O bursts (waiting for input/output). The CPU scheduler focuses on optimizing the CPU burst cycles, aiming to keep the CPU as busy as possible.


> [!summary]- CPU Scheduler: 
> This module selects which process from the ready queue should be executed next. The scheduling decisions occur in the following scenarios:
> 
>   1. Process switches from running to waiting (e.g., due to I/O request).
>   2. Process switches from running to ready (e.g., due to time quantum expiration).
>   3. Process switches from waiting to ready (e.g., after an I/O operation completes).
>   4. Process terminates.
>
  > For scenarios 1 and 4, scheduling is mandatory. For 2 and 3, scheduling can be preemptive, meaning another process may take control of the CPU.


> [!important]- Preemptive vs. Non-preemptive Scheduling:
> 
>   - **Non-preemptive Scheduling**: Once a process has the CPU, it holds onto it until it either finishes or voluntarily releases the CPU (e.g., by switching to a waiting state). This leads to simpler process management but can cause longer wait times for other processes.
>
>   - **Preemptive Scheduling**: The CPU can be forcibly taken away from a running process if a higher-priority process arrives or a time quantum expires. Preemptive scheduling improves response time but can lead to complications like **race conditions** if processes share resources.

---

### 2. Scheduling Criteria

To evaluate the effectiveness of a scheduling algorithm, the following metrics are considered:
- **CPU Utilization**: Measures how efficiently the CPU is kept busy. Ideally, the CPU should be active nearly all the time.
- **Throughput**: The number of processes that complete their execution per time unit.
- **Turnaround Time**: The total time taken to complete a process, from submission to the completion of execution.
- **Waiting Time**: The total time a process spends waiting in the ready queue.
- **Response Time**: The time it takes from submitting a process request until the first response is produced.

The goal of most scheduling algorithms is to maximize CPU utilization and throughput while minimizing turnaround, waiting, and response times.

---

### 3. CPU Scheduling Algorithms

#### First-Come, First-Served (FCFS) Scheduling
- This is the simplest type of CPU scheduling. Processes are executed in the order they arrive.

> [!example]- Example:
> - Process Burst Times: P1 = 24ms, P2 = 3ms, P3 = 3ms.
> - If processes arrive in the order P1 → P2 → P3:
>  - **Gantt Chart**: P1 [0-24] → P2 [24-27] → P3 [27-30].
>  - **Waiting Time**: P1 = 0ms, P2 = 24ms, P3 = 27ms.
>  - **Average Waiting Time** = (0 + 24 + 27) / 3 = 17ms.

> [!success] Advantages:
> - Simple to implement.
> - Suitable for batch systems.

> [!fail] Disadvantages:
> - Leads to **convoy effect**, where shorter processes wait behind longer ones, increasing the overall waiting time.

> [!warning]- Example with Reordered Processes:
> If processes arrive in the order P2 → P3 → P1:
>   - **Gantt Chart**: P2 [0-3] → P3 [3-6] → P1 [6-30].
>   - **Waiting Time**: P1 = 6ms, P2 = 0ms, P3 = 3ms.
>   - **Average Waiting Time** = (6 + 0 + 3) / 3 = 3ms.
> 
> This demonstrates that the arrival order can significantly impact performance in FCFS.

---

#### Shortest Job First (SJF) Scheduling
- In SJF, the process with the shortest CPU burst time is executed first. This can be **preemptive** or **non-preemptive**.
	- **Preemptive SJF (Shortest Remaining Time First)**: A new process can preempt the currently running process if its burst time is shorter.

> [!example]-  Example:
> - Process Arrival Times and Burst Times: P1 (0ms, 6ms), P2 (2ms, 8ms), P3 (4ms, 7ms), P4 (5ms, 3ms).
> - **Gantt Chart**: P1 [0-6] → P4 [6-9] → P3 [9-16] → P2 [16-24].
> - **Average Waiting Time**: (3 + 16 + 9 + 0) / 4 = 7ms.

> [!success] Advantages:
> - SJF produces the **minimum average waiting time** for a set of processes.
>   

> [!error] Challenges:
> - It’s hard to predict the length of the next CPU burst.
> - May lead to **starvation** if short processes continually arrive, leaving longer processes waiting indefinitely.

---

#### Round Robin (RR) Scheduling
- Each process is assigned a small unit of CPU time called a **time quantum** (typically 10-100ms). After this time, the process is preempted, and the CPU is given to the next process in the ready queue.

> [!example]-  Example:
> - Process Burst Times: P1 = 24ms, P2 = 3ms, P3 = 3ms.
> - Time Quantum = 4ms.
> - **Gantt Chart**: P1 [0-4] → P2 [4-7] → P3 [7-10] → P1 [10-14] → P1 [14-18] → P1 [18-22] → P1 [22-26] → P1 [26-30].
>   
> - **Average Waiting Time** = (6ms + 4ms + 7ms) / 3 = 5.67ms.

> [!check]- Advantages:
> - Fairness: Each process gets equal time, preventing starvation.
> - Suitable for time-sharing systems where responsiveness is crucial.
> 

> [!error]- Disadvantages:
> - Choosing an optimal **time quantum** is challenging:
>  - If the quantum is too large, RR behaves like FCFS.
>  - If it’s too small, frequent context switching may lead to overhead.

---

#### Priority Scheduling
Each process is assigned a priority. The CPU is allocated to the process with the highest priority (smallest integer value). Priority scheduling can be **preemptive** or **non-preemptive**.

**Example**:
- Process Arrival Times, Burst Times, and Priorities: P1 (0ms, 10ms, 3), P2 (1ms, 1ms, 1), P3 (2ms, 2ms, 4), P4 (3ms, 1ms, 5).
- **Gantt Chart**: P2 [1-2] → P1 [2-12] → P3 [12-14] → P4 [14-15].
- **Average Waiting Time** = (10ms + 0ms + 12ms + 14ms) / 4 = 9ms.

**Challenges**:
- **Starvation**: Low-priority processes might never execute if higher-priority processes keep arriving.
- **Solution – Aging**: Gradually increase the priority of processes that wait in the queue for a long time.

---

#### Multilevel Queue Scheduling
In this approach, processes are divided into different queues based on their priority or process type (e.g., system processes, interactive processes). Each queue can use a different scheduling algorithm (FCFS, RR, etc.).

**Example**:
- Queue Q0 uses Round Robin with a time quantum of 8ms.
- Queue Q1 uses Round Robin with a time quantum of 16ms.
- Queue Q2 uses FCFS.

New processes start in Q0, and if they do not complete within their quantum, they are moved to the next queue.

---

#### Multilevel Feedback Queue
This algorithm allows processes to move between queues. It’s a dynamic version of multilevel queue scheduling, where a process may be promoted or demoted based on its behavior (e.g., long-running processes may move to lower-priority queues).

**Example**:
- If a process uses too much CPU time in Q0 (Round Robin with 8ms quantum), it is moved to Q1.
- In Q1, it’s given more time (16ms quantum). If it still doesn’t complete, it is moved to Q2 (FCFS).

---

### 4. Multiple-Processor Scheduling

With multiple CPUs, scheduling becomes more complex as the operating system must ensure efficient load balancing.

- **Symmetric Multiprocessing (SMP)**: Each processor is self-scheduling and uses the same algorithm. Processes or threads can run on any available processor.
  
- **Load Balancing**: Necessary to ensure all CPUs are equally loaded. This can be done through:
  - **Push Migration**: A periodic task moves processes from overloaded CPUs to less busy ones.
  - **Pull Migration**: Idle processors pull tasks from busy CPUs.

- **Processor Affinity**: Ensures that a process remains on the same CPU to take advantage of cache memory. However, this can conflict with load balancing.

---

### 5. Real-Time CPU Scheduling

Real-time systems require strict timing

 constraints. They are divided into:
- **Soft Real-Time Systems**: Critical tasks are prioritized, but deadlines are not guaranteed.
- **Hard Real-Time Systems**: Tasks must be completed before a strict deadline.

**Rate Monotonic Scheduling (RMS)** assigns priorities based on the period of tasks: shorter periods get higher priority. **Earliest Deadline First (EDF)** schedules tasks based on their deadlines, with the closest deadlines having the highest priority.

---

### 6. Linux, Windows, and Solaris Scheduling

#### Linux Scheduling (Completely Fair Scheduler - CFS)
- CFS divides CPU time among tasks based on their priorities.
- Each task’s **virtual run time** is tracked. The task with the lowest virtual run time is selected next.
  
#### Windows Scheduling
- Uses a **priority-based preemptive scheduler**. The highest-priority thread runs next.
- Threads are divided into priority classes, with real-time threads having higher priorities.
  
#### Solaris Scheduling
- Supports **priority-based scheduling** with six scheduling classes: time-sharing (TS), interactive (IA), real-time (RT), system (SYS), fair-share (FSS), and fixed-priority (FP).
- Time-sharing uses a **multilevel feedback queue**, dynamically adjusting process priorities.

---

