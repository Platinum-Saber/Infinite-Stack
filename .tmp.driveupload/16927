**Local Beam Search** is another type of local search optimization algorithm, but unlike Hill Climbing, it keeps track of multiple candidate solutions (states) at once. This makes it more robust because it can explore different parts of the search space simultaneously, reducing the likelihood of getting stuck in local optima.

> [!summary]- Key Concepts:
> 1. **States/Beams**: Instead of tracking just one solution, the algorithm keeps track of `k` states (beams) at the same time.
> 2. **Neighbors**: For each state in the beam, the algorithm generates all possible neighboring states.
> 3. **Selection**: Out of all neighbors of all current states, the `k` best ones are selected to form the next beam.
> 4. **Exploration**: This approach reduces the risk of getting stuck in local optima, as multiple solutions are explored in parallel.
> 5. **Greedy Strategy**: Local Beam Search is still greedy because it only focuses on the best `k` solutions at each step, which might still cause it to overlook better solutions in distant parts of the search space.

### Process of Local Beam Search:
1. Start with `k` random initial solutions.
2. Generate all possible neighbors for each solution.
3. Select the best `k` neighbors from all the neighbors combined.
4. Repeat the process until an optimal solution is found or a stopping condition is met.

### Python Code Example:
Let’s use Local Beam Search to find the maximum of the same objective function, `f(x) = -(x - 3)^2 + 10`.

```python
import random

# Function to optimize: f(x) = -(x - 3)^2 + 10
def objective_function(x):
    return -(x - 3) ** 2 + 10

# Local Beam Search algorithm
def local_beam_search(k=3, max_iterations=100):
    # Initialize k random solutions
    current_solutions = [random.uniform(-10, 10) for _ in range(k)]
    current_values = [objective_function(x) for x in current_solutions]

    for iteration in range(max_iterations):
        # Generate all neighbors
        all_neighbors = []
        all_neighbor_values = []
        
        for solution in current_solutions:
            # Generate neighbors of the current solution
            neighbors = [solution + random.uniform(-0.1, 0.1) for _ in range(10)]  # 10 neighbors per solution
            neighbor_values = [objective_function(x) for x in neighbors]

            all_neighbors.extend(neighbors)
            all_neighbor_values.extend(neighbor_values)

        # Select the best k neighbors
        best_k_indices = sorted(range(len(all_neighbor_values)), key=lambda i: all_neighbor_values[i], reverse=True)[:k]
        current_solutions = [all_neighbors[i] for i in best_k_indices]
        current_values = [all_neighbor_values[i] for i in best_k_indices]

        print(f"Iteration {iteration}: Best solution = {current_solutions[0]}, Value = {current_values[0]}")

    return current_solutions[0], current_values[0]

# Run the algorithm
best_solution, best_value = local_beam_search(k=3, max_iterations=50)
print(f"Best solution: {best_solution}, Best value: {best_value}")
```

> [!NOTE]- Code Explanation:
> 1. **Objective Function**: We’re still trying to maximize the function `f(x) = -(x - 3)^2 + 10`.
> 
> 2. **Initialization**: The algorithm starts with `k` random solutions. For example, `k=3` means that the algorithm tracks three different solutions simultaneously.
> 
> 3. **Neighborhood Generation**:
>    - For each solution in the current beam, the algorithm generates a set of neighboring solutions by adding a small random value (±0.1) to the current solution.
>    - In this case, each solution generates 10 neighbors.
> 
> 4. **Selection of Best Neighbors**: After generating all the neighbors, the algorithm sorts them based on the objective function's value and selects the best `k` neighbors to form the next beam.
> 
> 5. **Iteration**: This process continues for a fixed number of iterations (`max_iterations=50`).
> 
> 6. **Stopping Condition**: The algorithm stops after a fixed number of iterations. In this implementation, you could also introduce other stopping conditions, such as stopping when the improvement in the best solution is below a threshold.
> 
> 7. **Output**: After every iteration, the best solution in the beam is printed, and at the end of the process, the best solution found is returned.

### Advantages and Limitations:
- **Advantages**:
  - It can explore multiple areas of the search space simultaneously.
  - Less likely to get stuck in local optima compared to Hill Climbing.
  
- **Limitations**:
  - It still follows a greedy approach, focusing only on the best solutions at each step, which might miss better solutions farther away.
  - If all beams converge to the same local optimum, the search becomes equivalent to Hill Climbing.

Local Beam Search can be extended with stochastic elements, where random neighbors are chosen instead of the best ones, making it more exploratory, similar to **Stochastic Beam Search**.