## Overview
CPU scheduling is a fundamental operating system function that decides which process runs at any given time. The main objectives are to maximize CPU utilization and optimize various performance metrics like throughput, turnaround time, waiting time, and response time.

## Basic Concepts

### 1. **Multiprogramming**
- **Objective:** Maximize CPU utilization by keeping the CPU busy with multiple processes.
- **CPU-I/O Burst Cycle:** A process alternates between CPU bursts (where the process executes) and I/O bursts (where the process waits for I/O operations).

### 2. **CPU Burst Distribution**
- Most CPU bursts are short, with a few long bursts. This pattern plays a significant role in designing efficient CPU scheduling algorithms.

## CPU Scheduler

### Functionality
- The **CPU scheduler** selects a process from the ready queue to allocate CPU time.
- Scheduling decisions are made in the following scenarios:
  1. Process switches from **running** to **waiting** state.
  2. Process switches from **running** to **ready** state.
  3. Process switches from **waiting** to **ready** state.
  4. Process **terminates**.
  
- For cases 1 and 4, scheduling must occur because the current process is no longer eligible to run. For cases 2 and 3, there is flexibility in choosing which process to run next.

## Preemptive vs. Nonpreemptive Scheduling

### 1. **Nonpreemptive Scheduling**
- The process keeps control of the CPU until it voluntarily releases it (by terminating or switching to a waiting state).
  
### 2. **Preemptive Scheduling**
- A process can be interrupted and replaced by another process even if it hasn't finished executing. Most modern operating systems (e.g., Windows, Linux, macOS) use preemptive scheduling.

### 3. **Race Conditions and Preemptive Scheduling**
- Preemptive scheduling can lead to race conditions, where shared data might be accessed by one process while being modified by another, leading to inconsistencies.

## Dispatcher

### Role of the Dispatcher
- The dispatcher is responsible for handing over control of the CPU to the selected process. Its functions include:
  - **Context switching**: Saving the state of the old process and loading the state of the new one.
  - **Switching to user mode**: Changing the mode of the CPU from kernel mode to user mode.
  - **Program jump**: Jumping to the correct memory location in the new process to start or resume execution.

### Dispatch Latency
- The time it takes for the dispatcher to switch from one process to another is called **dispatch latency**. This should be minimized for efficient scheduling.

## Scheduling Criteria

The following criteria are used to assess the performance of scheduling algorithms:

### 1. **CPU Utilization**
- The goal is to keep the CPU as busy as possible.

### 2. **Throughput**
- The number of processes completed per unit time.

### 3. **Turnaround Time**
- The total time taken for a process to complete, from submission to completion.

### 4. **Waiting Time**
- The total time a process spends in the ready queue waiting for CPU time.

### 5. **Response Time**
- The time between submitting a request and the first response being produced.

## Optimization Criteria for Scheduling Algorithms
When designing or evaluating a scheduling algorithm, the following factors are typically optimized:

- **Maximize CPU utilization**: Ensures the CPU is working as much as possible.
- **Maximize throughput**: Aim to complete as many processes as possible in a given period.
- **Minimize turnaround time**: Reduce the total time from submission to completion for each process.
- **Minimize waiting time**: Shorten the time processes spend waiting in the queue.
- **Minimize response time**: Ensure processes quickly begin producing output after their request is submitted.

## Glossary of Key Terms

| Term                  | Definition                                                                                  |
|-----------------------|----------------------------------------------------------------------------------------------|
| **CPU Scheduler**      | A component of the operating system that selects which process runs on the CPU at any time.  |
| **Preemptive Scheduling** | A type of scheduling where a process can be interrupted and replaced by another process.  |
| **Nonpreemptive Scheduling** | A type of scheduling where a process runs to completion or until it voluntarily releases the CPU. |
| **Context Switching**  | The process of saving the state of a currently running process and loading the state of the next process to be run. |
| **Dispatch Latency**   | The time taken to switch from one process to another.                                         |
| **CPU Utilization**    | A measure of how effectively the CPU is used.                                                |
| **Throughput**         | The number of processes completed per unit of time.                                          |
| **Turnaround Time**    | The total time taken for a process to complete, from submission to termination.              |
| **Waiting Time**       | The total time a process spends waiting in the ready queue.                                   |
| **Response Time**      | The time it takes for a system to start producing output after receiving a request.           |
