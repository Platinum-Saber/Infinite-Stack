Simulated Annealing (SA) is an optimization algorithm inspired by the annealing process in metallurgy, where materials are heated and then slowly cooled to remove defects. The algorithm allows occasional "bad" moves to escape local optima, which makes it more robust than Hill Climbing in avoiding local maxima or minima.

### Key Concepts:
1. **State**: The current solution of the problem.
2. **Neighbors**: Solutions close to the current one, which are explored.
3. **Energy/Cost Function**: An objective function that you want to minimize or maximize. In SA, it's often referred to as the "energy" of the system.
4. **Temperature**: A control parameter that decreases over time. At higher temperatures, the algorithm allows worse solutions to be accepted to escape local optima. As the temperature decreases, the algorithm becomes more conservative, behaving similarly to hill climbing.
5. **Acceptance Probability**: A mechanism that decides whether to accept a new solution, even if it's worse than the current one. This probability decreases as the temperature decreases.

### Simulated Annealing Process:
1. Start with an initial solution and an initial temperature.
2. Generate a neighboring solution and evaluate its objective function.
3. If the new solution is better, accept it. If it's worse, accept it with a probability depending on the temperature and how much worse it is.
4. Gradually reduce the temperature.
5. Stop when the temperature is low or a certain number of iterations have been performed.

### Python Code Example:
Let's apply Simulated Annealing to the same objective function we used in the Hill Climbing example.

```python
import math
import random

# Function to optimize: f(x) = -(x - 3)^2 + 10
def objective_function(x):
    return -(x - 3) ** 2 + 10

# Simulated Annealing algorithm
def simulated_annealing():
    # Initialize with a random solution
    current_solution = random.uniform(-10, 10)
    current_value = objective_function(current_solution)

    # Initial temperature and cooling rate
    temperature = 1000
    cooling_rate = 0.99
    min_temperature = 0.01
    max_iterations = 1000

    for iteration in range(max_iterations):
        # Generate neighboring solution
        next_solution = current_solution + random.uniform(-0.1, 0.1)
        next_value = objective_function(next_solution)

        # Calculate the change in objective function (energy difference)
        delta_value = next_value - current_value

        # Accept the new solution if it is better, or with a probability if worse
        if delta_value > 0 or random.uniform(0, 1) < math.exp(delta_value / temperature):
            current_solution, current_value = next_solution, next_value

        # Cool down the temperature
        temperature = max(temperature * cooling_rate, min_temperature)

        print(f"Iteration {iteration}: Solution = {current_solution}, Value = {current_value}, Temperature = {temperature}")

        # Stop if temperature is very low
        if temperature <= min_temperature:
            break

    return current_solution, current_value

# Run the algorithm
best_solution, best_value = simulated_annealing()
print(f"Best solution: {best_solution}, Best value: {best_value}")
```

### Code Explanation:
1. **Objective Function**: The same as before, `f(x) = -(x - 3)^2 + 10`, which we aim to maximize.

2. **Initial Solution and Temperature**: The algorithm starts with a random solution between -10 and 10 and initializes the temperature to 1000. The temperature controls how much randomness is allowed in accepting worse solutions.

3. **Simulated Annealing Loop**:
   - **Neighbor Generation**: In each iteration, the algorithm generates a new neighboring solution by adding a random value within a small range (±0.1) to the current solution.
   - **Energy/Objective Comparison**: The algorithm calculates the change in the objective function (`delta_value`). If the new solution is better, it is accepted. If it’s worse, it is accepted with a probability that depends on the current temperature and `delta_value`. The probability of accepting worse solutions decreases as the temperature cools down.
   - **Cooling Schedule**: After each iteration, the temperature is reduced by multiplying it by a cooling rate (0.99). This gradual reduction of temperature ensures that the algorithm becomes more conservative over time, reducing the likelihood of accepting worse solutions.

4. **Stopping Condition**: The algorithm stops when either the maximum number of iterations is reached or the temperature becomes very low (`min_temperature = 0.01`).

5. **Output**: The algorithm prints the current solution, value, and temperature at each step and eventually returns the best solution found.

### Why Simulated Annealing?
Unlike Hill Climbing, which only moves to better neighboring solutions, Simulated Annealing can sometimes accept worse solutions, helping it escape local optima and potentially find a global optimum. The randomness is controlled by the temperature, which decreases over time, making the algorithm increasingly focused on refining solutions near the current optimum as the temperature cools.