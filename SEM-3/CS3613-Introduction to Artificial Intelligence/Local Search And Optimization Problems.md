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
- 