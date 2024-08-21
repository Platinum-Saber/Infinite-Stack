Related :  #OperatingSystems #OS #OS/05 #Synchronization

[Reference Lecture](file:///E:%5CAcademics%5CSEM%203%5CCS2043-Operating%20Systems%5CLecture%20Video%5CLecture%205.mp4)

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

