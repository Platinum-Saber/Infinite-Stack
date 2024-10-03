---
tags:
  - OS
  - OperatingSystems
  - pintos
Reviewed: 
Created: 2024-09-10T16:48:00
About: Based on CS2043 Pintos Lab series
---
Related : #pintos 

References : [Pintos Lab](https://www.cs.jhu.edu/~huang/cs318/fall20/project/pintos_3.html#SEC25), [Pintos File details](https://jhu-cs318.github.io/pintos-doxygen/html/dir_68267d1309a1af8e8297ef4c3efbcdba.html), [Pintos_Lab01 guide](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLab%5CLab%2002%5CKuppi%20%20video%5C01.%20PintOS%20Lab%2001.mp4)



# Pintos Project: Threads and Scheduling

  

## Part 1: Alarm Clock

  

### Overview

- Goal: Implement `timer_sleep(int ticks)` system call to wake up a process after a specified number of ticks

- Current implementation uses busy waiting

- Modify to use sleep/wakeup mechanism

  

### Implementation Steps

1. Define and initialize a sleep queue (`sleep_list`)

2. Modify thread structure to include wakeup time

3. Implement `thread_sleep()` function:

   - Change thread state to BLOCKED

   - Insert thread into sleep queue

   - Update global tick if necessary

4. Modify `timer_interrupt()`:

   - Check sleep list and global tick

   - Wake up threads when their time has come

   - Move awakened threads to ready list

  

### Key Functions to Modify

- `thread_init()`

- `timer_sleep()`

- `timer_interrupt()`

  

## Part 2: Priority Scheduling

  

### Overview

- Current: FIFO scheduling

- Goal: Implement priority-based scheduling

  

### Implementation Steps

1. Modify thread insertion in ready list to be priority-ordered

2. Implement preemption when higher priority thread becomes ready

3. Update synchronization primitives (semaphore, condition variable) to be priority-aware

  

### Key Functions to Modify

- `thread_create()`

- `thread_unblock()`

- `thread_yield()`

- `thread_set_priority()`

- `sema_down()`

- `sema_up()`

- `cond_wait()`

- `cond_signal()`

  

## Part 3: Priority Donation

  

### Overview

- Address priority inversion problem

- Implement priority donation mechanism

  

### Implementation Steps

1. Modify thread structure to track donations

2. Implement nested donation

3. Handle multiple donations

4. Update priority inheritance when locks are acquired and released

  

### Key Functions to Modify

- `init_thread()`

- `lock_acquire()`

- `lock_release()`

- `thread_set_priority()`

  

## Testing

- Use `make check` to run Pintos tests

- Ensure all priority-related tests pass

