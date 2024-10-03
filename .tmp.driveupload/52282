
### 2. A* Search
A* considers both the cost to reach the current node and the estimated cost to the goal. The evaluation function is $f(n) = g(n) + h(n)$, where $g(n)$ is the actual cost to reach $n$, and $h(n)$ is the heuristic estimate to the goal.

#### Python Code:

```python
import heapq

def a_star_search(graph, start, goal, cost, heuristic):
    # Priority Queue: (priority, node, path_cost)
    frontier = [(heuristic[start], start, 0)] # f(n), node, g(n)
    heapq.heapify(frontier)
    
    explored = set()
    
    while frontier:
        # Get node with smallest f(n)
        f_n, current, g_n = heapq.heappop(frontier)
        
        if current == goal:
            return f"Goal {goal} reached with cost {g_n}!"
        
        explored.add(current)
        
        for neighbor, step_cost in graph[current].items():
            if neighbor not in explored:
                g_new = g_n + step_cost
                f_new = g_new + heuristic[neighbor]
                heapq.heappush(frontier, (f_new, neighbor, g_new))
    
    return "Goal not found"

# Graph with actual costs
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'D': 2, 'E': 5},
    'C': {'F': 3},
    'D': {},
    'E': {'G': 2},
    'F': {'G': 1},
    'G': {}
}

# Heuristic values
heuristic = {'A': 7, 'B': 6, 'C': 2, 'D': 4, 'E': 2, 'F': 1, 'G': 0}

# Running the A* algorithm
result = a_star_search(graph, 'A', 'G', graph, heuristic)
print(result)
```

#### Explanation:
- The algorithm keeps track of both $g(n)$ (the cost so far) and $h(n)$ (the estimated cost to the goal).
- It uses a priority queue to always expand the node with the smallest $f(n)$.
- This ensures that A* finds the optimal path, provided the heuristic is admissible.