Related : #AI #AI/04 #SearchAlgorithms 

Reference Note : [Local Search](file:///E:%5CAcademics%5CSEM%203%5CCS3613-Introduction%20to%20Artificial%20Intelligence%5CLecture%20note%5C04%20Local_Search.pdf)

> [!file]- Lecture Note : Chapter 04
> ![[04 Local_Search.pdf]]


---
<br>

# Content

# Local Search
> [!note] Characteristics of local search
> - It's a **Heuristic method**.
> - Use a *single current state* and move **only to neighbors**.
> - **No** track of *paths*
> - **No** track of the *set of states* that have been reached.
> - **Not systematic** :luc_tag: 
> 	- Might never explore a portion of the search space where the solution exists.

> [!tip] Advantages
> - **Use little space**.
> - Can find *reasonable solutions* in **large** or **infinite**(continuous) **state spaces** for which the *other algorithms are unsuitable*.

## Optimization
- **Local search** is often *suitable for* **optimization problems**.
- Search for the **best state** by optimizing an **objective function.**
- Moves from the **current state** to a **successor state**.
- A **successor** of state S is S with a **single element changed.**
- **Low memory requirements**, because the search tree or graph is not maintained in memory (*paths are not saved*).

> [!example]- Local search examples
> > [!info] 8-Queens Problem
> > Find a configuration of 8 queens on a chessboard such that no two queens attack each other. The state is represented by the positions of queens, and the search involves moving one queen at a time.
> > > [!image]- 8 Queens diagram
> > > ![[Pasted image 20240826112805.png]]
>  
> > [!info] Traveling Salesman Problem
> > Find the shortest possible route that visits a set of cities exactly once. The state is the order of cities, and local search involves swapping the order of cities to find a shorter route.

