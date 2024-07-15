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

### Measuring Problem-Solving Performance
>[!abstract]- Evaluation Criteria 
>>[!info]- Completeness :RiGalleryView:
>> Guaranteed to find a solution when there is one, and correctly reports failure when no solution exists.
>
>>[!info]- Cost optimality (admissibility) :dolla
>>Ability to find the path with the lowest cost among all solutions.
>
>>[!info]- Time complexity
>>The time taken to find a solution.
>
>>[!info]- Space complexity
>>The amount of memory required to perform the search 