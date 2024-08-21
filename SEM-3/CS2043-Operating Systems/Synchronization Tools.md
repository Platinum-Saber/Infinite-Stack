Related :  #OperatingSystems #OS #OS/05 #Synchronization

Reference Video :  [Lecture 05](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20Video%5CLecture%205.mp4)
Reference Notes :  [chapter 06](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20note%5CNew%20notes%5Cch6.pptx) , [mutual exclusion-part 1](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20note%5CNew%20notes%5Cmutualexclusion-part%201.ppt)

<br>

> [!file]- Lecture Note : Chapter 06
> ![[L06_mod.pdf]]

---
# Content
1. [[#Synchronization]]
	- [[#Shared Resources]]
	- 

---

<br>

# Synchronization
> [!note] Multi-threaded programs
> Threads **cooperate** in multithreaded programs.
> - To **share resources**, access shared data structures.
> - To **coordinate** their execution.
> 
> For correctness, this *cooperation needs to be controlled.*
> 
> > [!faq]- Why do we need synchronization.
> > 1. Thread schedule is **non-deterministic**
> > 	- scheduling is not under program control.
> > 	- threads interleave executions arbitrarily and at different rates.
> > 	- behavior changes when re-run program.
> > 2. Multi-word operations are not atomic.
> > 3. Compiler/ hardware instruction reordering.

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

### Race Condition


<br>
<br>

# Mutual Exclusion Problem

> [!faq] What is the mutual exclusion problem
> - Eliminating undesirable interleavings  

