---
tags:
  - AI
  - SearchAlgorithms
Reviewed: true
Created: 2024-09-09T10:03:00
About: Note generated using GPT on depth-first Search algorithm
---
Depth-First Search (DFS) is another fundamental uninformed search algorithm. Unlike BFS, which explores the graph level by level, DFS dives deep into the graph, visiting nodes by following a path until it reaches a dead end, then backtracking to explore other unvisited nodes.

### Key Characteristics of DFS:

1. **Recursive or Stack-Based**: DFS can be implemented recursively or using an explicit stack. It follows a **last-in, first-out** (LIFO) order.
2. **Exploration**: DFS explores a path until it can't go any further (i.e., it reaches a leaf or a dead-end), then it backtracks to explore other possible paths.
3. **Not Optimal**: DFS does not guarantee finding the shortest path in an unweighted graph, and it may explore deeper parts of the graph first before finding the goal.
4. **Uninformed**: Like BFS, DFS has no prior knowledge of the goal's location.

### How DFS Works:

1. DFS starts at a given node and explores along each path as far as possible before backtracking to explore other paths.
2. It uses either a **stack** (explicit or recursive call stack) to keep track of nodes that need further exploration.
3. DFS continues until all nodes are visited or the goal node is found.


> [!Example]- DFS Example
> 
> ```mermaid
> flowchart LR
> A --- B
> A --- C
> B --- D
> C --- D
> B --- E
> D --- E
> ```
> 
> > [!code]- Python code
> > ```python
> > def depth_first_search(graph, start, goal, visited=None, path=None):
> >     if visited is None:
> >         visited = set()  # Keeps track of visited nodes
> >     if path is None:
> >         path = []  # To store the current path
> > 
> >     visited.add(start)  # Mark the current node as visited
> >     path.append(start)  # Add the node to the current path
> > 
> >     if start == goal:
> >         return path  # Return the path when the goal is found
> > 
> >     # Explore neighbors recursively
> >     for neighbor in graph.get(start, []):
> >         if neighbor not in visited:
> >             result = depth_first_search(graph, neighbor, goal, visited, path)
> >             if result:  # If the goal is found, return the path
> >                 return result
> > 
> >     path.pop()  # Backtrack
> >     return None  # Return None if no path is found
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
> > result = depth_first_search(graph, 'A', 'E')
> > 
> > if result:
> >     print(f"Path: {result}")
> > else:
> >     print("Path not found")
> > 
> > ```
> 
> > [!NOTE]- Explanation 
> > 1. **Recursive Call**: The function recursively explores each node and its neighbors until it reaches the goal or backtracks when necessary.
> > 2. **Visited Set**: The `visited` set ensures that nodes are not revisited during the search.
> > 3. **Path List**: The `path` list keeps track of the nodes in the current path being explored.
> > 4. **Backtracking**: When a node has no unvisited neighbors or a path doesn't lead to the goal, DFS backtracks by popping nodes from the path.
> > 
> 
> 


### Key Points:

- DFS explores as deep as possible before backtracking.
- It is simple to implement either recursively or iteratively using a stack.
- Unlike BFS, DFS may not find the shortest path.

### Advantages of DFS:

- **Memory Efficiency**: DFS requires less memory than BFS, as it doesn’t need to store all the nodes at the current level.
- **Useful for Pathfinding**: DFS is useful when you need to explore all possible paths (e.g., solving mazes or puzzles).

### Disadvantages of DFS:

- **Not Guaranteed to Find Shortest Path**: DFS doesn’t guarantee finding the shortest path, as it may explore deep paths before shallow ones.
- **Inefficient in Large Graphs**: DFS can get stuck in deep paths, especially in graphs with many nodes.








