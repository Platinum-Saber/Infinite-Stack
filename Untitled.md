Informed search algorithms use heuristic functions to guide the search toward the goal more efficiently. Here’s a detailed explanation of some key informed search algorithms, followed by Python code implementations for each, along with explanations.




### 3. **Bidirectional A* Search**
Bidirectional A* searches from both the start and goal simultaneously, meeting in the middle. This reduces the number of nodes expanded.

#### Python Code (Conceptual):

```python
def bidirectional_a_star(graph, start, goal, cost, heuristic):
    frontier_f = [(heuristic[start], start, 0)]  # Forward search frontier
    frontier_b = [(heuristic[goal], goal, 0)]    # Backward search frontier
    heapq.heapify(frontier_f)
    heapq.heapify(frontier_b)

    explored_f = set()  # Forward explored
    explored_b = set()  # Backward explored
    
    def expand(frontier, explored, direction):
        f_n, current, g_n = heapq.heappop(frontier)
        explored.add(current)
        return current, g_n

    while frontier_f and frontier_b:
        # Forward and backward expansions
        fwd_node, g_fwd = expand(frontier_f, explored_f, 'forward')
        bwd_node, g_bwd = expand(frontier_b, explored_b, 'backward')
        
        # If paths meet
        if fwd_node in explored_b or bwd_node in explored_f:
            return "Paths met, solution found!"
    
    return "Goal not found"

# Use the same graph and heuristic
result = bidirectional_a_star(graph, 'A', 'G', graph, heuristic)
print(result)
```

#### Explanation:
- Two searches run simultaneously, one from the start and one from the goal.
- When the two searches meet, the path is found. This reduces the search space significantly.
- This is an efficient approach for large graphs.

### 4. **Iterative Deepening A* (IDA*)**
This algorithm performs depth-first searches with increasing cost thresholds, solving the memory overhead of A* while maintaining optimality.

#### Python Code:

```python
def ida_star(graph, start, goal, cost, heuristic):
    def dfs(node, g_n, threshold):
        f_n = g_n + heuristic[node]
        if f_n > threshold:
            return f_n
        if node == goal:
            return g_n
        
        min_threshold = float('inf')
        for neighbor, step_cost in graph[node].items():
            result = dfs(neighbor, g_n + step_cost, threshold)
            if isinstance(result, int) and result == g_n:
                return g_n
            if result < min_threshold:
                min_threshold = result
        
        return min_threshold

    threshold = heuristic[start]
    while True:
        result = dfs(start, 0, threshold)
        if result == goal:
            return "Goal reached!"
        if result == float('inf'):
            return "Goal not found!"
        threshold = result

# Same graph and heuristic
result = ida_star(graph, 'A', 'G', graph, heuristic)
print(result)
```

#### Explanation:
- IDA* avoids memory overhead by using depth-first search but applies a cost threshold that increases iteratively.
- It behaves like A* in that it expands nodes based on cost, but it doesn't store all nodes in memory.

---

### Conclusion
Each algorithm has its own use case:
- **Greedy Best-First Search** is fast but not optimal.
- **A\*** is optimal and complete but can be memory-intensive.
- **Bidirectional A\*** and **IDA\*** aim to reduce the space complexity of A\*.