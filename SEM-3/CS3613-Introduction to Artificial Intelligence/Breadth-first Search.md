---
tags:
  - AI
  - SearchAlgorithms
Reviewed: true
Created: 2024-09-09T09:53:00
About: Note generated using GPT on breadth-first Search algorithm
---


Breadth-First Search (BFS) is one of the simplest and most fundamental **uninformed search algorithms**. BFS explores all nodes at the present depth level before moving on to nodes at the next depth level. It is particularly effective for finding the shortest path in an unweighted graph, where all edges have the same cost.

### Key Characteristics of BFS:

1. **Level-wise Expansion**: BFS explores nodes level by level. Starting from the root (or any initial node), it explores all its neighbors, then moves on to their neighbors.
2. **Queue-Based**: BFS uses a **queue** (FIFO) to keep track of the order of node exploration.
3. **Complete and Optimal**: BFS is **complete** (it always finds a solution if one exists) and **optimal** when all edges have the same cost (unweighted graph).
4. **Uninformed**: Like UCS, BFS does not know anything about the goal's location and explores uniformly.

### How BFS Works:

1. BFS starts at a given node and explores all its neighbors first.
2. Nodes are placed in a queue, and at each step, BFS dequeues a node, processes it, and enqueues all its unvisited neighbors.
3. The process continues until the queue is empty or the goal is found.

> [!Example]- BFS Example
> 
> ```mermaid
> flowchart LR
> A --> B
> A --> C
> B --> D
> C --> D
> B --> E
> D --> E
> ```
> 
> > [!code]- Python code
> > ```python
> > from collections import deque
> > 
> > def breadth_first_search(graph, start, goal):
> >     # Queue for BFS (storing tuples of (node, path))
> >     queue = deque([(start, [start])])
> >     visited = set()
> > 
> >     while queue:
> >         # Dequeue the next node and path
> >         (node, path) = queue.popleft()
> > 
> >         if node == goal:
> >             return path  # Return the path when the goal is found
> > 
> >         # Mark the node as visited
> >         if node not in visited:
> >             visited.add(node)
> > 
> >             # Add unvisited neighbors to the queue
> >             for neighbor in graph.get(node, []):
> >                 if neighbor not in visited:
> >                     queue.append((neighbor, path + [neighbor]))
> > 
> >     return None  # If no path is found to the goal
> > 
> > # Example graph as an adjacency list
> > graph = {
> >     'A': ['B', 'C'],
> >     'B': ['D', 'E'],
> >     'C': ['D'],
> >     'D': ['E'],
> > }
> > 
> > # Example run: Start from A and find the path to E
> > result = breadth_first_search(graph, 'A', 'E')
> > 
> > if result:
> >     print(f"Path: {result}")
> > else:
> >     print("Path not found")
> > 
> > ```
> 
> > [!NOTE]- Explanation
> > 1. **Queue (FIFO)**: The BFS algorithm uses a `deque` (double-ended queue) from Python’s `collections` module. Each element in the queue is a tuple containing the current node and the path to that node.
> >     
> >     - This ensures that nodes are processed in the order they are discovered (FIFO behavior).
> > 2. **Visited Set**: The `visited` set keeps track of all nodes that have already been processed to avoid revisiting them.
> >     
> > 3. **Exploration**: For each node, the algorithm enqueues its unvisited neighbors by appending them to the queue.
> >     
> > 4. **Stopping Condition**: If the current node is the goal, the algorithm returns the path to that node. If the queue is exhausted without finding the goal, the algorithm returns `None`.
> 

### Key Points:

- **Queue Expansion**: BFS expands nodes in the order they were discovered, ensuring that nodes closer to the start are expanded first.
- **Shortest Path Guarantee**: In an unweighted graph, BFS guarantees the shortest path in terms of the number of edges (as in the example).
- **FIFO Queue**: The queue is central to BFS's level-wise expansion.

### Advantages of BFS:

- **Complete**: BFS will always find a solution if one exists.
- **Optimal for Unweighted Graphs**: BFS is guaranteed to find the shortest path in an unweighted graph.
- **Simple**: BFS is easy to implement and works well for simple graphs.

### Disadvantages:

- **Memory-Intensive**: BFS can use a lot of memory, as it stores all nodes at the current level in the queue before moving to the next level.
- **Slower for Large Graphs**: For graphs with many nodes, BFS may explore many nodes before finding the goal, making it slower.