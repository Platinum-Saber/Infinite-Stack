## Heuristic Function

> [!NOTE] Definition
> A **heuristic function** is a key component in informed search algorithms. It estimates the cost or distance from a given state to the goal state, guiding the search to find a solution efficiently. A good heuristic provides "hints" to steer the algorithm in the right direction, reducing the number of nodes that need to be expanded. Heuristic functions are denoted as $h(n)$, where $n$ is the current node or state.

### 1. Properties of Heuristic Functions

> [!info]  Admissibility: 
>    A heuristic is **admissible** if it never overestimates the cost to reach the goal from any node. 
> >[!equation] In other words:
> >    $$
> >    h(n) \leq h^*(n)
> >$$
>    Where $h^*(n)$ is the true cost from node $n$ to the goal. Admissibility ensures that algorithms like **A\*** find the optimal solution because the search is not "fooled" by overestimated costs.


> [!info] Consistency (or Monotonicity):
>    A heuristic is **consistent** if for every node $n$ and its neighbor $n'$, 
> >[!equation] the following condition holds:
> >    $$
> >    h(n) \leq c(n, n') + h(n')
> >    $$
>    Where $c(n, n')$ is the cost of transitioning from node $n$ to node $n'$. Consistency implies that as you move closer to the goal, the estimated cost $h(n)$ gets smaller or stays the same, ensuring optimality in A* search.

> [!info] Informedness:
>    A heuristic is more **informed** if it provides closer estimates to the true cost. A more informed heuristic helps prune the search space more aggressively.

---

### 2. Examples of Heuristic Functions

#### 1. Straight-Line Distance (Euclidean Distance)
In route-finding problems, the **straight-line distance** (SLD) between two points is a common heuristic. It gives an optimistic estimate of the actual travel distance, assuming no obstacles.

> [!example]-  Example:
> - In the context of the Romania route-finding problem (finding the shortest path between cities), the straight-line distance between two cities (e.g., from Arad to Bucharest) is a common heuristic.

#### 2. Manhattan Distance
In grid-based pathfinding, **Manhattan distance** is the sum of the absolute differences in the x and y coordinates between two points. It assumes movement is restricted to a grid, like a city with perpendicular streets.

> [!equation] Formula:
> $$
> h(n) = |x_1 - x_2| + |y_1 - y_2|
> $$
>Where $(x_1, y_1)$ and $(x_2, y_2)$ are the coordinates of two points.

#### 3. Hamming Distance
In problems like the **8-puzzle** or string matching, the **Hamming distance** counts the number of misplaced tiles (or characters) compared to the goal state. It's a simple heuristic that estimates how far you are from the solution based on the number of wrong placements.

> [!example]- Example for an 8-puzzle:
> If the goal state is:
> ```
> 1 2 3
> 4 5 6
> 7 8 0
> ```
> and the current state is:
> ```
> 1 2 3
> 4 6 5
> 7 8 0
> ```
> The Hamming distance is 2, because 5 and 6 are misplaced.

#### 4. Misplaced Tiles Heuristic (For Puzzle Problems)
This heuristic counts how many tiles are in the wrong position in a sliding tile puzzle like the 8-puzzle. It’s simple and admissible but not always very informed.

#### 5. Manhattan Distance for Puzzle Problems
The **Manhattan distance** heuristic can also be used for sliding tile puzzles. It computes the sum of the horizontal and vertical distances each tile is from its goal position. This tends to be more informed than counting misplaced tiles.

> [!example]- Example for an 8-puzzle:
> If the goal state is:
> ```
> 1 2 3
> 4 5 6
> 7 8 0
> ```
> and the current state is:
> ```
> 1 2 3
> 4 6 5
> 7 8 0
> ```
> The Manhattan distance would be 2 (as tile 6 and tile 5 each need to move one step).
> 

#### 6. Chebyshev Distance
In chess or grid-based pathfinding where diagonal movements are allowed, the **Chebyshev distance** is a suitable heuristic. It is the maximum of the absolute differences between the x and y coordinates.

> [!equation] Formula:
> $$
> h(n) = \max(|x_1 - x_2|, |y_1 - y_2|)
> $$
> 

---

### How Heuristics Influence Search Algorithms

> [!math] Greedy Best-First Search: 
> This algorithm uses the heuristic $h(n)$ to select the next node that appears closest to the goal. However, since it only considers the heuristic and ignores the cost so far, it may find suboptimal solutions.

> [!math] A* Search: 
> A* combines the actual cost $g(n)$ and the heuristic estimate $h(n)$ in the evaluation function $f(n) = g(n) + h(n)$. This allows A* to find the optimal solution, provided the heuristic is admissible.
> 

---

### Python Example for Manhattan Distance Heuristic

Let’s consider a grid-based pathfinding problem where you need to find the shortest path between two points using **A*** with the **Manhattan distance** heuristic.

```python
import heapq

# Manhattan Distance Heuristic
def manhattan_heuristic(current, goal):
    return abs(current[0] - goal[0]) + abs(current[1] - goal[1])

# A* Search with Manhattan Distance
def a_star_search_with_manhattan(grid, start, goal):
    rows, cols = len(grid), len(grid[0])
    frontier = [(0, start, 0)]  # (f(n), current node, g(n))
    heapq.heapify(frontier)
    explored = set()

    while frontier:
        f_n, current, g_n = heapq.heappop(frontier)

        if current == goal:
            return f"Goal reached with cost {g_n}!"

        explored.add(current)
        row, col = current

        # Define possible moves: right, left, down, up
        moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        for move in moves:
            new_row, new_col = row + move[0], col + move[1]
            new_pos = (new_row, new_col)

            # Check if new position is within bounds and not blocked
            if 0 <= new_row < rows and 0 <= new_col < cols and grid[new_row][new_col] == 0:
                if new_pos not in explored:
                    g_new = g_n + 1  # Assuming uniform step cost
                    f_new = g_new + manhattan_heuristic(new_pos, goal)
                    heapq.heappush(frontier, (f_new, new_pos, g_new))

    return "Goal not found"

# Example grid (0 = open space, 1 = obstacle)
grid = [
    [0, 0, 0, 0],
    [1, 1, 0, 1],
    [0, 0, 0, 0],
    [0, 1, 1, 0],
]

start = (0, 0)
goal = (3, 3)

# Running A* with Manhattan distance
result = a_star_search_with_manhattan(grid, start, goal)
print(result)
```

#### Explanation:
- The **Manhattan distance** heuristic is used to calculate the cost from the current node to the goal.
- The grid represents a map where `0` indicates walkable space and `1` represents obstacles.
- The search expands nodes based on the combined cost $g(n)$ and heuristic $h(n)$, ensuring an optimal solution, as Manhattan distance is admissible in grid-based pathfinding.

---
