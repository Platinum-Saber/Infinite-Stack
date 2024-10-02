## Overview
Deadlock is a critical issue in operating systems that occurs when a set of processes is stuck waiting for each other to release resources, making it impossible for any of them to proceed. This chapter covers deadlock conditions, detection, prevention, and recovery strategies, and introduces algorithms like the Banker's algorithm for deadlock avoidance.

## Key Concepts of Deadlocks

### 1. Deadlock Definition

> [!NOTE]- Definition
> - **Deadlock** occurs when each process in a set is waiting for an event that can only be triggered by another process in the set, leading to a standstill.
> - **Example:** Two processes each holding one resource while waiting for the other resource, causing a circular wait.

### 2. Conditions for Deadlock

> [!summary]- Four conditions must hold simultaneously for a deadlock to occur:
> 1. **Mutual Exclusion:** At least one resource must be non-shareable.
> 2. **Hold and Wait:** A process holding one resource is waiting to acquire additional resources held by other processes.
> 3. **No Preemption:** Resources cannot be forcibly taken away from a process holding them.
> 4. **Circular Wait:** There must be a circular chain of processes, each waiting for a resource held by the next process in the chain.

### 3. Resource Allocation Graph (RAG)
- A **graphical representation** of processes and resources as nodes, with directed edges indicating resource requests and assignments.

> [!warning] **Cycle in RAG:** A cycle indicates the possibility of a deadlock.

### 4. Example of Deadlock in the Dining Philosophers Problem
- Five philosophers sitting at a table, alternating between thinking and eating.
- Each philosopher needs two forks (resources) to eat.
- If all philosophers pick up one fork and wait for another, a deadlock occurs as no philosopher can proceed to eat.

## Deadlock Handling Strategies

### 1. Ostrich Algorithm
- **Ignore the deadlock problem** assuming it occurs rarely, which is a risky approach but sometimes used in practice.

> [!warning] Don't use this



### 2. Deadlock Prevention

> [!summary]- Prevent deadlocks by ensuring that at least one of the four necessary conditions does not hold:
> - **Mutual Exclusion:** Make resources shareable wherever possible.
> 
> - **Hold and Wait:** Require processes to request all required resources at once, or release all resources before requesting more.
> 
> - **No Preemption:** Allow preemption of resources when needed, e.g., through resource rollback or virtual memory techniques.
> 
> - **Circular Wait:** Impose a total ordering of resources and ensure that each process requests resources in a pre-defined order.

### 3. Deadlock Avoidance
- **Banker’s Algorithm:** A well-known deadlock avoidance algorithm that works by ensuring that the system only allocates resources if doing so keeps it in a **safe state**.
  - **Safe State:** A state in which there is a sequence of processes such that each can finish execution with the currently available resources.
  - The algorithm considers the maximum potential resource needs of each process and only grants requests that leave the system in a safe state.
  
  **Banker’s Algorithm Example:**
  - Processes and resources are represented as matrices:
    - `Available`: Number of available instances of each resource type.
    - `Max`: Maximum resources each process may need.
    - `Allocation`: Current allocation of resources to each process.
    - `Need`: Remaining resources needed by each process (`Max - Allocation`).
  - The algorithm checks if granting a resource request keeps the system in a safe state. If it does, the request is granted.

### 4. Deadlock Detection
If deadlock prevention or avoidance is not used, detection techniques are necessary:
- **Single Instance of Each Resource Type:** Use a **wait-for graph** to detect cycles. A cycle in this graph indicates deadlock.
- **Multiple Instances of a Resource Type:** Use the detection algorithm based on available resources, allocation, and requests. The system periodically checks for cycles.

### 5. Deadlock Recovery
Once a deadlock is detected, recovery is needed:
- **Process Termination:** Abort one or more processes to break the cycle.
  - Criteria for process termination may include process priority, runtime, and resource usage.
- **Resource Preemption:** Preempt resources from some processes and rollback them to a safe state. The challenge here is to avoid **starvation**, where the same process is always preempted.

## Key Algorithms

### 1. Safety Algorithm (For Deadlock Avoidance)
- **Purpose:** Determines if the system is in a safe state.
- **Steps:**
  1. Initialize `Work = Available` and `Finish[i] = false` for all processes.
  2. Find an `i` such that `Finish[i] == false` and `Need[i] <= Work`. If no such `i` exists, proceed to step 4.
  3. Update `Work = Work + Allocation[i]`, set `Finish[i] = true`, and repeat step 2.
  4. If `Finish[i] == true` for all processes, the system is in a safe state.

### 2. Resource-Request Algorithm (For Deadlock Avoidance)
- **Purpose:** Handles resource requests from processes.
- **Steps:**
  1. If `Request[i] > Need[i]`, raise an error.
  2. If `Request[i] <= Available`, proceed; otherwise, the process must wait.
  3. Temporarily allocate resources and simulate execution. If the system remains in a safe state, grant the request; otherwise, revert the allocation.

### 3. Deadlock Detection Algorithm
- **Purpose:** Detect deadlock by analyzing resource allocation and requests.
- **Steps:**
  1. Initialize `Work = Available`, set `Finish[i] = true` if the process has all its resources, and `Finish[i] = false` otherwise.
  2. Find an `i` such that `Finish[i] == false` and `Request[i] <= Work`. If no such process exists, the system is in deadlock.
  3. If a cycle exists, the processes in the cycle are deadlocked.

## Glossary of Key Terms

| Term              | Definition                                                                                      |
|-------------------|-------------------------------------------------------------------------------------------------|
| **Deadlock**       | A situation where a set of processes is unable to proceed because each is waiting on the other. |
| **Mutual Exclusion** | Condition where at least one resource must be non-shareable.                                  |
| **Circular Wait**  | A condition where a circular chain of processes exists, each waiting for a resource held by the next. |
| **Banker’s Algorithm** | A deadlock avoidance algorithm that dynamically allocates resources based on maximum claims. |
| **Resource-Allocation Graph** | A graphical representation of processes and resources used to detect potential deadlocks. |
| **Wait-For Graph** | A simplified version of the resource allocation graph used for deadlock detection in systems with a single instance of each resource. |
| **Safe State**     | A state in which there exists a sequence of processes that can all finish execution without causing deadlock. |
| **Preemption**     | Forcing a process to release resources so they can be allocated to another process.             |
| **Starvation**     | A situation where a process is perpetually denied necessary resources to complete its execution. |

