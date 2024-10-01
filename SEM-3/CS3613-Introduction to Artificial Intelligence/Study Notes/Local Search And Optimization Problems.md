---
tags:
  - AI
  - AI/04
  - SearchAlgorithms
  - LocalSearch
Reviewed: false
Created: 2024-08-26T10:15:00
About: Based on CS3613-Lecture 05 Local Search & Optimization Problems
---
---
Related : #AI #AI/04 #SearchAlgorithms #LocalSearch
Previously : [[Solving Problems by Searching]]
Reference Lecture : 
Reference Note : [Local Search](file:///E:%5CAcademics%5CSEM%203%5CCS3613-Introduction%20to%20Artificial%20Intelligence%5CLecture%20note%5C04%20Local_Search.pdf)

> [!file]- Lecture Note : Chapter 04
> ![[04 Local_Search.pdf]]


---
<br>

# Content
1. [[#Local Search]]
	- [[#Optimization]]
	- [[#Comparison With Tree Search]]
	- [[#Visualization]]
	- [[#Local Search Algorithms]]
		- [[#Hill Climbing Algorithm]]
		- [[#Simulated Annealing Algorithm]]
		- [[#Local Beam Search]]
		- [[#Generic Algorithms]]
2. [[#Questions]]
	- [[#Question 1]]
	- [[#Question 2]]
	- [[#Question 3]]
	- [[#Question 4]]
	- [[#Question 5]]


---
<br>
<br>

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

## Comparison With Tree Search
> [!info] Tree Search 🔎 : 
>- Typically **doesn't** start with a complete configuration.
>- Has binary goal tests.
>- Saves paths.

> [!info] Local Search 🔎 :
> Starts with a complete configuration.
> Focuses on optimizing an objective function.
> **Does not** save **paths**.

<br>

## Visualization
- A one-dimensional state-space landscape in which elevation corresponds to the objective function. The aim is to find the global maximum

> [!image]- Visualization diagram
> ![[Pasted image 20240826115501.png]]

<br>

## Local Search Algorithms
#### [[Hill Climbing Algorithm]]
- A **greedy** local search that moves to the best neighboring state. Variants include **stochastic** *hill climbing*, **first-choice** *hill climbing*, and **random-restart** *hill climbing*.
#### [[Simulated Annealing Algorithm]]
- Combines hill climbing with random moves to avoid local maxima by *occasionally* **allowing worse moves**, with a probability that decreases over time.
#### [[Local Beam Search]]
- Keeps track of **multiple states** (k states) and explores their neighbors, selecting the best k successors.
#### [[Genetic Algorithms]]
- Inspired by natural evolution, this method generates successors by **combining** *two parent states* using operations like **crossover** and **mutation**.


# Questions
### Question 1
> [!faq]- What is the main difference between local search and traditional search algorithms?
> - Local search focuses on a single current state and its neighbors, without keeping track of paths or multiple states, while traditional search algorithms keep track of paths and can backtrack.

### Question 2
> [!faq]- How does hill climbing differ from simulated annealing?
> - Hill climbing is a greedy algorithm that always moves to a better state, while simulated annealing allows occasional moves to worse states to escape local maxima.

### Question 3
> [!faq]- What is the role of the objective function in local search?
> The objective function measures the quality or preference of a state, guiding the search towards the best configuration.

### Question 4
> [!faq]- In what scenarios might random-restart hill climbing be effective?
> It is effective in search spaces with many local maxima, as restarting the search from different points increases the chances of finding the global maximum.

### Question 5
> [!faq]- Explain the concept of ‘genetic algorithms’ and how they differ from other local search methods.
> Genetic algorithms simulate evolution by generating new states through crossover and mutation of parent states, unlike other local search methods that typically move from one state to its neighbor.

<br>

---
Up Next : [[Constraint Satisfaction Problem]]
