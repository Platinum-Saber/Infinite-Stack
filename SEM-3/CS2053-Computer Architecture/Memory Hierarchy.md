---
tags:
  - CA
  - "#CA/05"
  - ComputerArchitecture
  - "#MemoryHierarchy"
Reviewed: false
Created: 2024-09-01T01:08:00
About: Based on CS2053-Lecture 05 Memory Hierarchy part 1
---
---
# Content
1. [[#Accessing Memory]]
2. 

<br>

### Accessing Memory
- The **address bus** activates a memory cell at a particular location. This prepares the memory cell for read or write operation that will occur.
- The **control bus** specifies the action done on the particular activated memory location. Typically whether read or write action is performed.
- **Data bus** carries the relevant data to or from the memory cell depending on the control signal.

> [!tip]- Address bus & Control bus are unidirectional. The data bus can carry signals both ways but only in one direction at a time.

![[Pasted image 20240901012947.png]]
<br>

### Reading From & Writing to Memory
> [!info] Reading From Memory
> - **Address** of memory location to read is placed on *Address Bus*.
> - **Read Signal** (RD) in *Control Bus* is activated.
> - **Data** Is fetched (read) from *Data Bus*.

> [!info] Writing to Memory
> - **Address** of the memory location to write is placed on *Address Bus*.
> - **Data** is placed on *Data Bus.*
> - **Write Signal** (WR) in *Control Bus* is activated.

<br>

### Connecting Memory & CPU
- Details of handling different memory modules & memory hierarchy is *off load* to **memory controller**.

