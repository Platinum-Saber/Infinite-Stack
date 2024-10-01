**Genetic Algorithms (GA)** are a class of optimization algorithms inspired by the process of natural selection and genetics. They are used to solve optimization and search problems by mimicking the biological evolution process. GAs work with a population of candidate solutions and evolve them over time to find the best or optimal solution to a given problem.

> [!abstract]- Key Concepts:
> 1. **Population**: A group of candidate solutions (individuals), each represented as a chromosome (usually a string or array of bits or numbers).
> 2. **Chromosome**: A potential solution to the problem. It is made up of genes that represent parameters of the solution.
> 3. **Fitness Function**: A function that evaluates the quality of each solution. Higher fitness values correspond to better solutions.
> 4. **Selection**: The process of selecting the best individuals (parents) from the population to produce offspring for the next generation. Fitter individuals have a higher chance of being selected.
> 5. **Crossover (Recombination)**: A genetic operator that combines two parent solutions to produce offspring by swapping parts of their chromosomes.
> 6. **Mutation**: A genetic operator that randomly alters some genes of an individual to maintain genetic diversity in the population and explore new areas of the search space.
> 7. **Termination**: The algorithm stops when a termination condition is met (e.g., reaching a maximum number of generations or achieving a desired fitness level).

> [!faq]- How Genetic Algorithms Work:
> 1. **Initialization**: Start with a randomly generated population of candidate solutions.
> 2. **Evaluation**: Calculate the fitness of each individual in the population.
> 3. **Selection**: Select individuals (parents) based on their fitness to produce offspring for the next generation.
> 4. **Crossover**: Combine pairs of parents to generate new offspring.
> 5. **Mutation**: Mutate the offspring by randomly changing parts of their chromosomes.
> 6. **Replacement**: Form the new population by replacing some or all of the current population with offspring.
> 7. **Repeat**: Go back to step 2 and repeat the process until the termination condition is met.

### Python Code Example:
Let’s implement a simple Genetic Algorithm to maximize the function `f(x) = -(x - 3)^2 + 10`.

```python
import random

# Objective function: f(x) = -(x - 3)^2 + 10
def objective_function(x):
    return -(x - 3) ** 2 + 10

# Create an individual (chromosome) as a float number between -10 and 10
def create_individual():
    return random.uniform(-10, 10)

# Create a population of individuals
def create_population(pop_size):
    return [create_individual() for _ in range(pop_size)]

# Evaluate the fitness of an individual
def fitness(individual):
    return objective_function(individual)

# Selection: Roulette Wheel Selection based on fitness
def select_parents(population, fitnesses):
    total_fitness = sum(fitnesses)
    selection_probs = [f / total_fitness for f in fitnesses]
    return random.choices(population, weights=selection_probs, k=2)

# Crossover: Single-point crossover
def crossover(parent1, parent2):
    return (parent1 + parent2) / 2  # Simple arithmetic crossover

# Mutation: Small random change to an individual
def mutate(individual, mutation_rate=0.01):
    if random.random() < mutation_rate:
        return individual + random.uniform(-0.5, 0.5)  # Small mutation
    return individual

# Genetic Algorithm
def genetic_algorithm(pop_size=10, generations=100, mutation_rate=0.01):
    # Initialize population
    population = create_population(pop_size)
    
    for generation in range(generations):
        # Evaluate the fitness of the population
        fitnesses = [fitness(ind) for ind in population]

        # Select the best individual for logging
        best_individual = population[fitnesses.index(max(fitnesses))]
        best_fitness = max(fitnesses)
        print(f"Generation {generation}: Best solution = {best_individual}, Fitness = {best_fitness}")

        # Create a new population
        new_population = []
        
        for _ in range(pop_size // 2):  # Produce pop_size offspring
            # Select parents
            parent1, parent2 = select_parents(population, fitnesses)

            # Perform crossover
            child1 = crossover(parent1, parent2)
            child2 = crossover(parent2, parent1)

            # Perform mutation
            child1 = mutate(child1, mutation_rate)
            child2 = mutate(child2, mutation_rate)

            new_population.extend([child1, child2])

        population = new_population
    
    # Return the best solution
    fitnesses = [fitness(ind) for ind in population]
    best_individual = population[fitnesses.index(max(fitnesses))]
    return best_individual, max(fitnesses)

# Run the Genetic Algorithm
best_solution, best_fitness = genetic_algorithm()
print(f"Best solution: {best_solution}, Best fitness: {best_fitness}")
```

> [!NOTE]- Code Explanation:
> 1. **Initialization**: The population is initialized with a set of random individuals (solutions) within the range [-10, 10].
> 
> 2. **Fitness Function**: The fitness function evaluates each individual based on the objective function `f(x) = -(x - 3)^2 + 10`.
> 
> 3. **Selection**: We use **Roulette Wheel Selection**, where the probability of an individual being selected as a parent is proportional to its fitness.
> 
> 4. **Crossover**: The crossover function combines two parents to create offspring by averaging their values (simple arithmetic crossover). More complex crossover mechanisms can be used depending on the problem.
> 
> 5. **Mutation**: Mutation introduces random changes to some individuals with a small probability (`mutation_rate=0.01`). This prevents premature convergence and helps explore the search space more effectively.
> 
> 6. **Generations**: The algorithm runs for a fixed number of generations. In each generation, it evaluates the fitness of the population, selects parents, produces offspring through crossover, and applies mutations.
> 
> 7. **Output**: After all generations, the best solution and its fitness are printed.

### Advantages and Limitations:
- **Advantages**:
  - Good for large, complex search spaces where traditional methods struggle.
  - Avoids local optima by exploring a broader range of solutions.
  - Adaptable to many types of optimization problems.

- **Limitations**:
  - Can be slow for complex problems due to large population sizes and many generations.
  - Requires tuning of parameters like population size, mutation rate, and crossover strategy.
  - May still converge to a local optimum if not configured well.

Genetic Algorithms are widely used in machine learning, engineering, scheduling, and various optimization tasks, thanks to their flexibility and ability to solve non-convex, multimodal problems.