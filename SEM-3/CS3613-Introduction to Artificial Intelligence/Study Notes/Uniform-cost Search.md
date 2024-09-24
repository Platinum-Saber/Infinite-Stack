---
tags:
  - AI
  - SearchAlgorithms
Reviewed: true
Created: 2024-09-09T09:33:00
About: Note generated using GPT on uniform-cost search algorithm
---
Uniform-Cost Search (UCS) is a type of **uninformed search algorithm** used to find the least-cost path in a graph. It is similar to Dijkstra's algorithm and is used when the path cost is not uniform, meaning some paths may have higher or lower costs than others. UCS is essentially a **BFS variant** but takes into account the **cost of edges**.

### Key Characteristics of Uniform-Cost Search:

1. **Cost-Based Expansion**: UCS expands the node with the **lowest cumulative cost** from the start node to the current node.
2. **Priority Queue**: UCS uses a priority queue (min-heap) to ensure that nodes with the least cost are expanded first.
3. **Optimal**: UCS guarantees finding the optimal path (least cost) if the cost is non-negative.
4. **Uninformed**: UCS doesn't have prior knowledge about the goal, unlike informed search algorithms like A*.

### How UCS Works:

1. UCS starts at the initial node and explores all the possible paths by expanding the least costly path at each step.
2. It uses a priority queue to store the nodes along with their cumulative costs.
3. At each step, UCS dequeues the node with the smallest cost, examines its neighbors, and adds them to the queue with their updated cumulative costs.
4. The process continues until the goal node is expanded.

> [!Example]- UCS Example
> ```mermaid
> flowchart TD
> A --1--> B
> A --4--> C
> B --2--> D
> C --1--> D
> B --5--> E
> D --3--> E
> 
> ```
> 
> > [!code]- Python code
> > ```python
> > import heapq
> > 
> > def uniform_cost_search(graph, start, goal):
> >     # Priority Queue to store (cost, node, path)
> >     pq = [(0, start, [])]  # (cumulative_cost, current_node, path)
> >     visited = set()
> > 
> >     while pq:
> >         # Pop the node with the lowest cost
> >         (cost, node, path) = heapq.heappop(pq)
> > 
> >         if node in visited:
> >             continue
> > 
> >         visited.add(node)
> >         path = path + [node]
> > 
> >         # If we reach the goal, return the cost and path
> >         if node == goal:
> >             return (cost, path)
> > 
> >         # Explore neighbors
> >         for neighbor, edge_cost in graph.get(node, []):
> >             if neighbor not in visited:
> >                 heapq.heappush(pq, (cost + edge_cost, neighbor, path))
> > 
> >     return None  # If goal not reachable
> > 
> > # Example graph as an adjacency list with edge costs
> > graph = {
> >     'A': [('B', 1), ('C', 4)],
> >     'B': [('D', 2), ('E', 5)],
> >     'C': [('D', 1)],
> >     'D': [('E', 3)],
> > }
> > 
> > # Example run: Start from A and find the least cost path to E
> > result = uniform_cost_search(graph, 'A', 'E')
> > 
> > if result:
> >     print(f"Path: {result[1]}, Total Cost: {result[0]}")
> > else:
> >     print("Path not found")
> > 
> > ```
> 
> > [!NOTE]- Explanation
> > 1. **Priority Queue (Min-Heap)**: The priority queue (`pq`) is implemented using Python's `heapq` library. The queue stores tuples of the form `(cost, node, path)`, where:
> >     
> >     - `cost` is the cumulative cost to reach the node.
> >     - `node` is the current node being processed.
> >     - `path` stores the nodes visited so far.
> > 2. **Visited Set**: The `visited` set is used to keep track of nodes that have already been expanded to prevent revisiting them.
> >     
> > 3. **Exploration**: For each node, the algorithm explores its neighbors and adds them to the priority queue with their updated cumulative costs. The node with the least cost is always processed first.
> >     
> > 4. **Stopping Condition**: When the goal node is dequeued (expanded), the algorithm returns the path and the total cost.

### Key Points:

- UCS expands nodes based on **cumulative cost**, not just proximity (like BFS).
- **Optimality**: UCS guarantees finding the least-cost path.
- **Efficiency**: UCS may explore more nodes than necessary if the graph is large, especially if there are many nodes with similar path costs.

### Advantages of UCS:

- **Guaranteed Optimality**: UCS finds the optimal (least-cost) solution, as it expands the lowest-cost node first.
- **Complete**: If a solution exists, UCS will always find it (if the edge costs are non-negative).

### Disadvantages:

- **Performance**: UCS can be slow and memory-intensive, especially for large graphs, as it explores every possible path until it finds the least-cost solution.
- **Redundant Computation**: It may explore some nodes more than once with different costs, requiring effective use of a visited set.

### Applications:

- **Route finding**: Finding the shortest or least costly route between locations.
- **Pathfinding in robotics**: To minimize energy consumption or time taken.
- **Solving puzzles**: Optimal solutions to problems where the cost of actions varies.