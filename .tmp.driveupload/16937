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

---
<br>

# Content
- [[#Problem Solving Agents]]
	- [[#Problem Solving Process]]
	- [[#Search Problems and Solutions]]
- [[#Search Algorithms]]
	- [[#Measuring Problem-Solving Performance]]
	- [[#Uninformed Search Algorithms]]
	- [[#Informed Search algorithms]]

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

### Informed Search algorithms

Informed search algorithms leverage domain-specific knowledge in the form of a [[Heuristic Functions]] to make the search process more efficient compared to uninformed search methods. This heuristic function $h(n)$ estimates the cost of the cheapest path from a given node $n$ to a goal state. Let's dive into some of the key algorithms that fall under this category.

#### 1. [[Greedy Best-First Search]]

> [!info] Idea: 
> It uses a simple evaluation function $f(n)=h(n)$, where $h(n)$ is the heuristic estimate of the cost from the current node $n$ to the goal.

> [!NOTE]
> **Heuristic Example**: 
>- In route-finding problems, $h(n)$ could be the straight-line distance from the current location to the goal.
> 
> **Strategy**: 
>- Greedy Best-First Search expands the node that appears to be closest to the goal, i.e., the node with the smallest $h(n)$.
> 
> **Example Path**: 
>- Consider a pathfinding problem with cities connected by roads, and the goal is to reach Bucharest. The algorithm would expand nodes in a way that seems closest to Bucharest based on straight-line distances (even if the actual road cost is higher).

> [!tip] Efficiency: 
>- It is not optimal and can lead to suboptimal solutions, as shown in your example. For instance, a path might appear shorter based on the heuristic but could end up costing more in reality.
>     - Example path: $Arad→Sibiu→Fagaras→Bucharest\text{Arad} \rightarrow \text{Sibiu} \rightarrow \text{Fagaras} \rightarrow \text{Bucharest}Arad→Sibiu→Fagaras→Bucharest$ with a cost of 450.
>     - while another path $(Arad→Sibiu→Rimnicu→Pitesti→Bucharest\text{Arad} \rightarrow \text{Sibiu} \rightarrow \text{Rimnicu} \rightarrow \text{Pitesti} \rightarrow \text{Bucharest}Arad→Sibiu→Rimnicu→Pitesti→Bucharest)$ would have been shorter with a cost of 418.

> [!abstract] Evaluation:
> **Completeness**: Not complete, as it can get stuck in loops or dead ends in the tree search version.
> 
> **Time Complexity**: Worst-case time is $O(b^m)$, where $b$ is the branching factor and mmm is the depth of the search tree.
> 
> **Space Complexity**: Worst-case space complexity is also $O(b^m)$ due to storing all nodes at the frontier.
> 
> **Optimality**: Not optimal, as it doesn't consider the cost already incurred to reach the current node.

#### 2. [[A(asterisk) Search]]

> [!NOTE] Idea:
> A* improves upon Greedy Best-First Search by considering both the cost to reach a node and the estimated cost to reach the goal from that node.

> [!equation] Evaluation Function: 
> The evaluation function is $f(n)=g(n)+h(n)$, where:
> - $g(n)$: The actual cost to reach node $n$ from the start node.
> - $h(n$): The heuristic estimate of the cost from node $n$ to the goal.

> [!info] Optimality: 
> If the heuristic $h(n)$ is **admissible** (i.e., it never overestimates the cost to reach the goal), A* is guaranteed to be optimal. This is because A* prioritizes nodes that have the lowest total cost, combining the actual cost incurred so far $g(n)$ and the estimated remaining cost $h(n).$

> [!tip] Efficiency: 
> A* is both **complete** (will always find a solution if one exists) and **optimal** when $h(n)$ is admissible. However, it suffers from **bad space complexity** because it stores all generated nodes in memory, which can become a problem for large search spaces.

> [!example] Example: 
> In the same route-finding problem, A* would expand nodes considering both the actual cost to reach them and the estimated cost to reach Bucharest, ensuring it finds the optimal path.

#### 3. [[Other Variants]]

##### 1. Bidirectional A_ Search:
	
- Instead of searching from the start node to the goal, Bidirectional A* searches from both the start and the goal simultaneously, meeting somewhere in between.
- **Efficiency**: It can be more efficient than A* as it reduces the number of nodes expanded by halving the search space.

##### 2. Iterative Deepening A_ (IDA_):
    
- **Goal**: It addresses A*’s high space complexity by combining the ideas of **iterative deepening** and A*.
- **How it Works**: It performs a depth-first search up to a certain cost limit and increases this limit iteratively, similar to how iterative deepening search works but with A*'s evaluation function.
- **Efficiency**: Solves the space complexity problem while still being complete and optimal.

##### 3. Beam Search:
    
- **Idea**: It limits the size of the frontier (the set of nodes under consideration) to a fixed number of nodes.
- **Efficiency**: Beam Search is efficient in terms of time and space, but it is **incomplete** and **suboptimal** because it may discard good paths due to the size limit on the frontier.
- **Use**: It’s often used when finding an approximate solution quickly is more important than finding the optimal solution.

****

<br>

Up Next : [[Local Search And Optimization Problems]]
