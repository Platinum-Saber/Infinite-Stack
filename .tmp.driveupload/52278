### 1. Greedy Best-First Search
This algorithm selects the node that appears to be closest to the goal based on a heuristic function $h(n)$, ignoring the cost already accumulated to reach the node.

#### Example
In a route-finding problem, if $h(n)$ is the straight-line distance to the goal, the algorithm chooses the next node that minimizes $h(n)$.

#### Python Code:

```python
import heapq

def greedy_best_first_search(graph, start, goal, heuristic):
    # Priority Queue: (priority, node)
    frontier = [(heuristic[start], start)]
    heapq.heapify(frontier)
    
    explored = set()
    
    while frontier:
        # Get node with smallest heuristic value
        _, current = heapq.heappop(frontier)
        
        if current == goal:
            return f"Goal {goal} reached!"
        
        explored.add(current)
        
        for neighbor in graph[current]:
            if neighbor not in explored:
                # Add neighbor to frontier with its heuristic value
                heapq.heappush(frontier, (heuristic[neighbor], neighbor))
    
    return "Goal not found"

# Graph and heuristic (Straight-line distance example)
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': [],
    'E': ['G'],
    'F': ['G'],
    'G': []
}
heuristic = {'A': 10, 'B': 6, 'C': 4, 'D': 6, 'E': 3, 'F': 5, 'G': 0}

# Running the algorithm
result = greedy_best_first_search(graph, 'A', 'G', heuristic)
print(result)
```

#### Explanation:
- We use a priority queue (`frontier`) where nodes are selected based on their heuristic values.
- `heapq` helps maintain the order of nodes with the smallest heuristic value.
- The algorithm explores nodes in a way that appears closest to the goal but might not yield the optimal path.