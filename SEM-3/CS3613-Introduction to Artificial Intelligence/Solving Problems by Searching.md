---
tags:
  - AI
  - AI/03
  - SearchAlgorithms
Reviewed: 
Created: 2024-08-19T09:57:00
About: Based on CS3613-Lecture 03 Solving problems by searching
---

Related : #AI #AI/03 #SearchAlgorithms

Reference Note : [Searching](file:///E:%5CAcademics%5CSEM%203%5CCS3613-Introduction%20to%20Artificial%20Intelligence%5CLecture%20note%5C03%20Searching.pdf)

> [!file]- Lecture Note : chapter 3
> ![[03 Searching.pdf]]
<br>

## Problem Solving Agents
>[!abstract] Functionality of a **Problem-Solving Agent** 👨‍💼
>Its an agent that plans ahead. It considers a sequence of actions that form a path to a goal.
>`Search` :  The computational process undertaken by a problem-solving agent.
>>[!example]- Search Algorithms
>>- Uninformed Algorithms
>>- Informed Algorithms

>[!info] Uses atomic representations

>[!warning] Can function only in the simplest environments
>- Episodic, single agent, fully observable, deterministic, static, and discrete.

<br>
<br>

### Problem Solving Process
>[!abstract] Components of a ***Problem Solving Process***
>>[!info]- Goal Formation 🥅
>>Goals organize the behavior by limiting the objectives and hence the actions to be considered.
>
>>[!info]- Problem Formation :FasPersonCircleQuestion:
>>The agent devises a description of states and actions necessary to reach the goal.
>
>>[!info]- Search 🔎 
>>Before taking any actions in the real world :RiEarthLine: the agent simulates sequences of actions in its model, searching until it finds a sequence of actions that reaches the goal.
>
>>[!info]- Execution ✅ 
>>The agent can now execute the actions in the solution, one at a time

>[!example]- Example 
>![[Pasted image 20240715104211.png]]

<br>

### Search Problems and Solutions
>[!abstract] components of a **Search** problem
>>[!info]- Action cost function 💰 
>>The numeric cost of applying action `a` in state `s` to reach `s'`, then `ACTION_COST(s,a,s')`
>
>>[!info]- Path :RiRoadMapLine:
>>A sequence of states connected by a sequence of actions.
>
>>[!info]- Solution :FiCheck:
>>A path from the initial state to a goal state.
>
>>[!info]- Optimal solution ✅ 
>>The path with the lowest cost among all the solutions.
>
>>[!info]- Graph :FasDiagramProject:
>>A representation of state space in which vertices are states and the directed edges between them are actions.
>
>>[!info]- Model :SiGraphql:
>>An abstract mathematical description.
>
>>[!info]- Abstraction :SiGrapheneos:
>>Removing details from the representation
>>Real world is complex and a good problem formulation has the right level of detail.

>[!example]- Example Problems
> ![[Pasted image 20240715112326.png]]
>![[Pasted image 20240715112409.png]]

<br>
<br>

## Search Algorithms
>[!info]- General terms used
>![[Pasted image 20240715113613.png]]

>[!tip] ***State Space*** :  All possible transitions among all the states.

>[!note] Redundant Paths
> If along the path of progression an action leads to meeting a top node (a previous state) again its a **Redundant Path**.
> Eliminating redundant paths leads to faster solutions.

<br>
<br>

### Measuring Problem-Solving Performance
>[!abstract]- Evaluation Criteria 
>>[!info]- Completeness :RiGalleryView:
>> Guaranteed to find a solution when there is one, and correctly reports failure when no solution exists.
>
>>[!info]- Cost optimality (admissibility) :FiDollarSign:
>>Ability to find the path with the lowest cost among all solutions.
>
>>[!info]- Time complexity :RiTimerLine:
>>The time taken to find a solution.
>
>>[!info]- Space complexity :RiSpace:
>>The amount of memory required to perform the search 

>[!note]- Terms used in Time & Space complexity
>- `b`  : maximum branching factor of the search tree (number of successors of a node that needs to be considered)
>- `d`  : depth of the least cost solution
>- `m`  : maximum number of actions in any path

<br>

### Uninformed Search Algorithms
>[!abstract]- Characteristics
>- Have access only to the problem definition.
>- No clue about how close a state is close to the goal.
>- Builds a search tree to find a solution :IbTreeMapDown1:
>- Algorithms differ based on which node they expand first

>[!example]- Algorithm Examples 
>>[!info]- [[Breadth-first Search]]
>>- Expands the shallowest nodes first.
>>- Complete.
>>- Optimal for unit action costs.
>>- Exponential space complexity.
>
>>[!info]- [[Uniform-cost Search]]
>>- Expands the node with the lowest path cost.
>>- Optimal for general action costs.
>
>>[!info]- [[Depth-first Search]]
>>- Expands the deepest unexpanded node first. 
>>- Neither complete nor optimal.
>>- Linear time complexity.
>
>>[!info]- Iterative Deepening Search
>>- Calls DFS with increasing depth limits until a goal is found.
>>- Complete when full cycle checking is done.
>>- Optimal for unit action costs.
>>- Time complexity is comparable to BFS.
>>- Space complexity is linear.
>
>>[!info]- Bidirectional Search
>>- Expands two frontiers, one around the initial state and one around the goal, stopping when the two frontiers meet.

<br>

****

<br>

Up Next : [[Local Search And Optimization Problems]]
