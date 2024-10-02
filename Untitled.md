
# Chapter 7: Synchronization

## Overview
This chapter focuses on synchronization in operating systems, particularly how processes manage shared resources concurrently without conflict or deadlock. It addresses classical synchronization problems, solutions in different operating systems, and specific APIs used for synchronization, including POSIX and Java.

## Classical Problems of Synchronization

### 1. **Bounded-Buffer Problem**
- **Problem Definition:** There are `n` buffers, each capable of holding one item. The challenge is synchronizing producer and consumer processes such that the producer cannot add to a full buffer and the consumer cannot remove from an empty buffer.
  
- **Key Variables:**
  - `mutex`: Ensures mutual exclusion.
  - `full`: Semaphore initialized to 0, representing the number of full buffers.
  - `empty`: Semaphore initialized to `n`, representing the number of empty buffers.

- **Producer Process Pseudocode:**
  ```c
  while (true) {
      // produce an item in next_produced
      wait(empty);
      wait(mutex);
      // add item to the buffer
      signal(mutex);
      signal(full);
  }
  

- **Consumer Process Pseudocode:**
  ```c
  while (true) {
      wait(full);
      wait(mutex);
      // remove an item from the buffer
      signal(mutex);
      signal(empty);
      // consume the item
  }
  ```

### 2. **Readers-Writers Problem**
- **Problem Definition:** A data set is shared among several concurrent processes. Some processes only read (readers), and others may read and write (writers). The goal is to allow multiple readers to read simultaneously while only one writer can access the data set at a time.
  
- **Key Variables:**
  - `rw_mutex`: Controls access for writers (initialized to 1).
  - `mutex`: Controls access to `read_count`.
  - `read_count`: Tracks the number of active readers.

- **Writer Process Pseudocode:**
  ```c
  while (true) {
      wait(rw_mutex);
      // perform writing
      signal(rw_mutex);
  }
  ```

- **Reader Process Pseudocode:**
  ```c
  while (true) {
      wait(mutex);
      read_count++;
      if (read_count == 1) 
          wait(rw_mutex); // First reader locks the writers out
      signal(mutex);
      
      // perform reading
      
      wait(mutex);
      read_count--;
      if (read_count == 0)
          signal(rw_mutex); // Last reader unlocks the writers
      signal(mutex);
  }
  ```

- **Variations:**
  - **First Readers-Writers Problem:** Prioritizes readers, but writers may starve.
  - **Second Readers-Writers Problem:** Prioritizes writers, preventing newly arriving readers from gaining access until writers are finished.

### 3. **Dining-Philosophers Problem**
- **Problem Definition:** `N` philosophers sit at a round table with a bowl of rice. They alternate between thinking and eating. To eat, a philosopher must pick up two chopsticks (shared between neighbors). The challenge is to prevent deadlock and ensure all philosophers get a chance to eat.
  
- **Semaphore Solution Pseudocode:**
  ```c
  while (true) {
      wait(chopstick[i]);
      wait(chopstick[(i+1) % N]);
      // eat
      signal(chopstick[i]);
      signal(chopstick[(i+1) % N]);
      // think
  }
  ```

- **Monitor Solution:**
  A monitor structure can solve this problem by using condition variables and a state machine with three states: THINKING, HUNGRY, and EATING. It avoids deadlock, but starvation is possible.

## Synchronization in Different Operating Systems

### 1. **Windows**
- **Mechanisms:**
  - Uses **interrupt masks** on uniprocessor systems.
  - Uses **spinlocks** on multiprocessor systems.
  - Provides **dispatcher objects** (mutexes, semaphores, events, and timers) in user-land.
    - **Events**: Condition variable equivalent.
    - **Timers**: Notify threads when a timer expires.

### 2. **Linux**
- **Preemption:** Fully preemptive from kernel version 2.6.
- **Mechanisms:**
  - **Semaphores**, **atomic integers**, and **spinlocks**.
  - **Reader-writer versions** of synchronization primitives.

### 3. **POSIX Synchronization**
- **APIs Provided:**
  - **Mutex locks** for mutual exclusion.
  - **Semaphores** (named and unnamed) for signaling.
  - **Condition variables** to manage synchronization based on conditions.

### 4. **Java Synchronization**
- **Mechanisms:**
  - **Monitors**: Each object in Java has a lock.
  - **Reentrant locks**: Provide explicit locking mechanisms.
  - **Semaphores**: Control access to resources.
  - **Condition variables**: Associated with reentrant locks, allow threads to wait for conditions.

## Alternative Synchronization Approaches

### 1. **Transactional Memory**
- **Concept:** A sequence of read-write operations performed atomically. Operations within a transaction are guaranteed to execute without interference.
- **Example:** Atomic blocks in transactional memory ensure that all operations within the block execute atomically.

### 2. **OpenMP**
- **Concept:** A set of compiler directives supporting parallel programming.
- **Example:**
  ```c
  void update(int value) {
      #pragma omp critical
      {
          count += value;
      }
  }
  ```

### 3. **Functional Programming**
- **Concept:** Functional languages like Erlang and Scala avoid state and mutable variables, offering a model where data races are inherently avoided due to immutability.

## Glossary of Key Terms

| Term                  | Definition                                                                                  |
|-----------------------|----------------------------------------------------------------------------------------------|
| **Semaphore**          | A synchronization primitive used to control access to a common resource by multiple processes.|
| **Mutex**              | A mutual exclusion lock used to prevent concurrent access to a resource.                     |
| **Spinlock**           | A lock where the thread waits in a loop ("spins") until the lock becomes available.          |
| **Monitor**            | A high-level synchronization construct that allows threads to have both mutual exclusion and the ability to wait for a condition to become true. |
| **Reentrant Lock**     | A lock that allows the thread holding the lock to reenter it without causing a deadlock.     |
| **Condition Variable** | A synchronization primitive that allows threads to wait until a particular condition is true. |
| **Bounded Buffer**     | A fixed-size buffer where producers insert items and consumers remove items, synchronizing via semaphores. |
| **Deadlock**           | A situation where a set of processes are blocked because each process holds a resource and waits for another resource held by another process. |
| **Starvation**         | A situation where a process waits indefinitely because it never gets the resources it needs.  |
