---
Course: EN3150 Pattern Recognition
Lecturer: Dr. M. T. U. Sampath K. Perera
Created: 2025-09-10T15:41:00
Content: Fundamental probability concepts essential for understanding pattern recognition and machine learning algorithms.
---

## 1. Introduction to Pattern Recognition

> [!note] Definition
> Pattern recognition involves searching for patterns in data - a fundamental task in data analysis, machine learning, and artificial intelligence.

**Key Goals:**
- Identify regularities, trends, correlations, or meaningful structure in data
- Provide valuable insights for predictive modeling
- Enable machines to learn from data and make informed decisions

### Real-World Applications
- **Machine Vision**: Object detection, image classification
- **Speech Recognition**: Voice assistants (Siri, Google Assistant)
- **Character Recognition**: OCR, handwriting analysis
- **Medical Imaging**: Disease diagnosis, medical scan analysis
- **Robotics**: Navigation, object manipulation

---

## 2. Uncertainty in Pattern Recognition

> [!warning] Key Concept
> Uncertainty is fundamental in pattern recognition due to:
> - Noise in measurements
> - Limited size of datasets
> - Inherent variability in real-world data

**Why Probability Theory?**
- Provides a consistent framework for quantifying uncertainty
- Enables manipulation of uncertain information
- Forms the central foundation of pattern recognition algorithms

---

## 3. Probability Space

> [!abstract] Formal Definition
> A probability space consists of three components: (Ω, F, P)

### Components:

1. **Sample Space (Ω)**: Set of all possible outcomes
   - Example: Rolling a die → Ω = {1, 2, 3, 4, 5, 6}

2. **Event Space (F)**: Collection of events (subsets of Ω)
   - Example: Getting an even number → {2, 4, 6}
   - Example: Getting an odd number → {1, 3, 5}

1. **Probability Measure (P)**: Maps events to real values $[0, 1]$
   - Example: P(even number) = 3/6 = 1/2

### Probability Properties:
- **Non-negativity**: P(a) ≥ 0 for all events a
- **Normalization**: P(Ω) = 1
- **Additivity**: For mutually exclusive events a, b: P(a ∪ b) = P(a) + P(b)

---

## 4. Types of Probability

### Classical Probability
- Based on equally likely outcomes
- P(Event) = (Favorable outcomes) / (Total outcomes)
- **Example**: Drawing cards from a standard deck

### Frequentist Probability
- Based on long-run frequencies
- $$P(A) = \lim_{n \rightarrow \infty} \frac{\text{ occurrences of event}}{\text{ total occurrences}}$$
- **Example**: Estimating bias in an unknown coin

### Bayesian Probability
- Probability as measure of belief or confidence
- Updates beliefs based on new evidence
- Prior probabilities → Posterior probabilities

---

## 5. Fundamental Rules of Probability

### Sum Rule (Marginal Probability)
$$p(X) = \sum_Y p(X, Y)$$

**Meaning**: Probability of X regardless of Y

### Product Rule (Joint Probability)
$$p(X, Y) = p(Y|X)p(X) = p(X|Y)p(Y)$$

**Meaning**: Probability of both X and Y occurring

### Conditional Probability
$$p(Y|X) = \frac{p(X, Y)}{p(X)}$$

**Meaning**: Probability of Y given that X has occurred

---

## 6. Bayes' Theorem

> [!equation] Bayes' Theorem
> $$p(Y|X) = \frac{p(X|Y)p(Y)}{p(X)} = \frac{p(X|Y)p(Y)}{\sum_Y p(X|Y)p(Y)}$$

### Components:
- **Posterior**: p(Y|X) - Updated belief about Y after observing X
- **Likelihood**: p(X|Y) - How likely X is given Y
- **Prior**: p(Y) - Initial belief about Y
- **Evidence**: p(X) - Normalization factor

### Medical Testing Example:
Given:
- Disease prevalence: p(Disease = 1) = 0.2
- Test sensitivity: p(Test = 1|Disease = 1) = 0.9
- Test specificity: p(Test = 0|Disease = 0) = 0.98

**Question**: If test is positive, what's the probability of having the disease?

$$p(Disease = 1|Test = 1) = \frac{0.9 \times 0.2}{(1-0.98) \times (1-0.2) + 0.9 \times 0.2} = 0.918 = 91.8\%$$

---

## 7. Likelihood vs Probability

> [!tip] Key Distinction
> **Likelihood is not a probability** but is proportional to one.

### Likelihood Function:
$$L(H|D) = K \cdot P(D|H)$$

Where:
- H = Hypothesis
- D = Data
- K = Arbitrary positive constant

### Uses of Likelihood:
- **Parameter Estimation**: Maximize likelihood to find best parameters
- **Model Comparison**: Higher likelihood indicates better fit
- **Bayesian Inference**: Combined with priors to get posteriors

---

## 8. Independence

### Statistical Independence:
- $P(X) = P(X|Y)$ → X is independent of Y
- If independent: $P(X, Y) = P(X)P(Y)$

### Conditional Independence:
- $P(X|Z) = P(X|Y, Z)$ → X and Y are conditionally independent given Z
- $P(X, Y|Z) = P(X|Z)P(Y|Z)$

---

## 9. Probability Distributions

### Probability Density Function (PDF)
For continuous variables:
$$p(x) \geq 0, \quad \int_{-\infty}^{\infty} p(x) dx = 1$$

**Probability of interval**: $p(x \in (a,b)) = \int_a^b p(x) dx$

### Cumulative Distribution Function (CDF)
$$P(z) = \int_{-\infty}^z p(x) dx$$

> [!image] Probability distribution illustration
> ![[Pasted image 20250910172231.png]]

---

## 10. Expectations and Moments

### Expectation (Mean)

> [!math] Equation
> - **Discrete**: $\mathbb{E}[f] = \sum_x p(x)f(x)$
> - **Continuous**: $\mathbb{E}[f] = \int p(x)f(x) dx$

> [!math] Properties:
> - **Linearity**: $E[X₁ + X₂ + ... + Xₙ] = E[X₁] + E[X₂] + ... + E[Xₙ]$
> - **For independent variables**: $E[XY] = E[X]E[Y]$

### Variance (Second Moment)
$$\text{var}[f] = \mathbb{E}[(f(x) - \mathbb{E}[f(x)])^2] = \mathbb{E}[f(x)^2] - \mathbb{E}[f(x)]^2$$

### Covariance
- For 2 random variables x, y :
$$\text{cov}[x,y] = \mathbb{E}_{x,y}[\{x - \mathbb{E}[x]\}\{y - \mathbb{E}[y]\}] = \mathbb{E}_{x,y}[xy] - \mathbb{E}[x]\mathbb{E}[y]$$
- For 2 vectors of random variables X, Y :
$$\text{cov}[x,y] = \mathbb{E}_{x,y}[\{x - \mathbb{E}[x]\}\{y^T - \mathbb{E}[y^T]\}] = \mathbb{E}_{x,y}[xy^T] - \mathbb{E}[x]\mathbb{E}[y^T]$$


> [!tip] Variance Properties
> - $\text{Var}[aX+b] = a^2 \text{var}(X) \ | \ \text{a, b are constants}$
> - $\text{Var}[X+Y] = \ \text{Var}(X)+\ \text{Var}(Y)$


## 11. Gaussian Distribution

> [!note] Single Variable Gaussian
> ![[Pasted image 20250910173724.png|400]]
> $$\mathcal{N}(x|\mu, \sigma^2) = \frac{1}{(2\pi\sigma^2)^{1/2}} \exp\left\{-\frac{1}{2\sigma^2}(x-\mu)^2\right\}$$
> - $\mathcal{N}(x|\mu, \sigma^2) > 0$
> - $\int_{- \infty}^{\infty}{\mathcal{N}(x|\mu, \sigma^2)} dx = 1$ 
> - $\mathbb{E}[x] = \int_{-\infty}^{\infty} \mathcal{N}(x|\mu, \sigma^2)x\ dx = \mu$
> - $\mathbb{E}[x^2] = \int_{-\infty}^{\infty} \mathcal{N}(x|\mu, \sigma^2)x^2\ dx = \mu^2 + \sigma^2$
> - $\text{var}[x] = \mathbb{E}[x^2] - E[x]^2 = \sigma^2$

### Properties:
- **Mean**: $\mathbb{E}[x] = \mu$
- **Variance**: $\text{var}[x] = \sigma^2$
- **Precision**: $\beta = 1/\sigma^2$

### Multivariate Gaussian
$$\mathcal{N}(\mathbf{x}|\boldsymbol{\mu}, \boldsymbol{\Sigma}) = \frac{1}{(2\pi)^{D/2}|\boldsymbol{\Sigma}|^{1/2}} \exp\left\{-\frac{1}{2}(\mathbf{x}-\boldsymbol{\mu})^T\boldsymbol{\Sigma}^{-1}(\mathbf{x}-\boldsymbol{\mu})\right\}$$

Where:
- **μ**: Mean vector
- **Σ**: Covariance matrix (D × D)
- **|Σ|**: Determinant of covariance matrix

### Code Example

#### part 1
```python
import seaborn as sns
# Load the tips dataset
tips = sns.load_dataset("tips")
# Display the first few rows of the dataset
print(tips.head())
```

```text
   total_bill   tip     sex smoker  day    time  size
0       16.99  1.01  Female     No  Sun  Dinner     2
1       10.34  1.66    Male     No  Sun  Dinner     3
2       21.01  3.50    Male     No  Sun  Dinner     3
3       23.68  3.31    Male     No  Sun  Dinner     2
4       24.59  3.61  Female     No  Sun  Dinner     4
```

#### part 2
```python
import seaborn as sns
import matplotlib.pyplot as plt
# Load the tips dataset
tips = sns.load_dataset("tips")
# Create separate dataframes for lunch and dinner
lunch_data = tips[tips["time"] == "Lunch"]
dinner_data = tips[tips["time"] == "Dinner"]
# Set up the figure with two subplots side by side
fig, axes = plt.subplots(1, 2, figsize=(12, 5))
# Plot histogram for lunch data
sns.histplot(lunch_data["total_bill"], kde=True, color='blue', bins=20, ax=axes[0])
mean_lunch = lunch_data["total_bill"].mean()
axes[0].axvline(mean_lunch, color='red', linestyle='dashed', linewidth=2, label=f"Mean: {mean_lunch:.2f}")
axes[0].set_xlabel("Total Bill")
axes[0].set_ylabel("Frequency")
axes[0].set_title("Distribution of Total Bill - Lunch")
axes[0].legend()
# Plot histogram for dinner data
sns.histplot(dinner_data["total_bill"], kde=True, color='orange', bins=20, ax=axes[1])
mean_dinner = dinner_data["total_bill"].mean()
axes[1].axvline(mean_dinner, color='red', linestyle='dashed', linewidth=2, label=f"Mean: {mean_dinner:.2f}")
axes[1].set_xlabel("Total Bill")
axes[1].set_ylabel("Frequency")
axes[1].set_title("Distribution of Total Bill - Dinner")
axes[1].legend()
#Show the plot
plt.tight_layout()
plt.show()
```

> [!example] Code Output
> ![[Pasted image 20250910175514.png]]

#### Part 3

```python
import seaborn as sns
import matplotlib.pyplot as plt
# Apply the default theme
sns.set_theme()
penguins = sns.load_dataset("penguins")
# Calculate covariance matrix and variance for numeric columns only
numeric_penguins = penguins.select_dtypes(include=['number'])
cov_matrix = numeric_penguins.cov()
variance_values = numeric_penguins.var()

# Print the results
print("Covariance Matrix:")
print(cov_matrix)
print("\nVariance Values:")
print(variance_values)

# Create the pairplot with covariance plots
g = sns.pairplot(data=penguins, hue="species", diag_kind="kde")
plt.show()
```

```text
Covariance Matrix:
                   bill_length_mm  bill_depth_mm  flipper_length_mm    body_mass_g
bill_length_mm          29.807054      -2.534234          50.375765    2605.591912
bill_depth_mm           -2.534234       3.899808         -16.212950    -747.370093
flipper_length_mm       50.375765     -16.212950         197.731792    9824.416062
body_mass_g           2605.591912    -747.370093        9824.416062  643131.077327

Variance Values:
bill_length_mm           29.807054
bill_depth_mm             3.899808
flipper_length_mm       197.731792
body_mass_g          643131.077327
dtype: float64
```

> [!example] Code Output
> ![[Pasted image 20250910184032.png]]
> 

#### Part 4

```python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def create_multivariate_gaussian_plot():
    
    # Set random seed for reproducibility
    np.random.seed(123)
    
    # Create figure with two subplots
    fig = plt.figure(figsize=(16, 7))
    fig.suptitle('The Multivariate Gaussian', fontsize=18, fontweight='bold', y=0.95)
    
    # Configuration for the two plots
    configs = [
        {
            'mu': np.array([0.0, 0.0]),
            'sigma': np.array([[1.0, 0.0], [0.0, 1.0]]),
            'title': 'Cov Matrix = [[1, 0],\n                 [0, 1]]',
            'label': '(a)',
            'n_samples': 5000,
            'xlim': (-4, 4),
            'ylim': (-4, 4),
            'zlim': (0, 0.5),
            'marginal_pos': 3.5
        },
        {
            'mu': np.array([0.0, 0.0]),
            'sigma': np.array([[0.01, 0.0], [0.0, 0.01]]),
            'title': 'Cov Matrix = [[0.01, 0],\n                 [0, 0.01]]',
            'label': '(b)',
            'n_samples': 2000,
            'xlim': (-1.5, 1.5),
            'ylim': (-1.5, 1.5),
            'zlim': (0, 4),
            'marginal_pos': 1.2
        }
    ]
    
    for i, config in enumerate(configs):
        ax = fig.add_subplot(1, 2, i+1, projection='3d')
        
        # Generate random samples
        samples = np.random.multivariate_normal(config['mu'], config['sigma'], config['n_samples'])
        
        # Plot the sample points at z=0
        ax.scatter(samples[:, 0], samples[:, 1], 0, 
                  c='black', s=0.5, alpha=0.8, depthshade=False)
        
        # Calculate marginal distributions
        sigma_x = config['sigma'][0, 0]
        sigma_y = config['sigma'][1, 1]
        mu_x, mu_y = config['mu']
        
        # Create ranges for marginals
        x_range = np.linspace(config['xlim'][0]*0.9, config['xlim'][1]*0.9, 100)
        y_range = np.linspace(config['ylim'][0]*0.9, config['ylim'][1]*0.9, 100)
        
        # X-marginal distribution (Gaussian)
        x_marginal = (1/np.sqrt(2*np.pi*sigma_x)) * np.exp(-0.5 * (x_range - mu_x)**2 / sigma_x)
        
        # Y-marginal distribution (Gaussian)  
        y_marginal = (1/np.sqrt(2*np.pi*sigma_y)) * np.exp(-0.5 * (y_range - mu_y)**2 / sigma_y)
        
        # Plot X-marginal on the back wall (red)
        marginal_y_pos = config['marginal_pos']
        ax.plot(x_range, marginal_y_pos, x_marginal, color='red', linewidth=3, alpha=0.9)
        
        # Fill X-marginal with vertical lines
        for j in range(0, len(x_range), 3):
            ax.plot([x_range[j], x_range[j]], [marginal_y_pos, marginal_y_pos], 
                   [0, x_marginal[j]], color='red', alpha=0.5, linewidth=1)
        
        # Plot Y-marginal on the side wall (blue)
        marginal_x_pos = config['marginal_pos']
        ax.plot(marginal_x_pos, y_range, y_marginal, color='blue', linewidth=3, alpha=0.9)
        
        # Fill Y-marginal with vertical lines
        for j in range(0, len(y_range), 3):
            ax.plot([marginal_x_pos, marginal_x_pos], [y_range[j], y_range[j]], 
                   [0, y_marginal[j]], color='blue', alpha=0.5, linewidth=1)
        
        # Set axis properties
        ax.set_xlim(config['xlim'])
        ax.set_ylim(config['ylim'])
        ax.set_zlim(config['zlim'])
        
        # Set viewing angle
        ax.view_init(elev=25, azim=45)
        
        # Set title with label
        full_title = f"{config['label']} {config['title']}"
        ax.set_title(full_title, fontsize=12, fontweight='bold', pad=20)
        
        # Clean grid
        ax.grid(True, alpha=0.3)
        
        # Remove axis labels for cleaner look (matching the reference image)
        ax.set_xlabel('')
        ax.set_ylabel('')
        ax.set_zlabel('')
        
        # Make panes more transparent
        try:
            ax.xaxis.pane.fill = False
            ax.yaxis.pane.fill = False
            ax.zaxis.pane.fill = False
            ax.xaxis.pane.set_edgecolor('gray')
            ax.yaxis.pane.set_edgecolor('gray')
            ax.zaxis.pane.set_edgecolor('gray')
            ax.xaxis.pane.set_alpha(0.1)
            ax.yaxis.pane.set_alpha(0.1)
            ax.zaxis.pane.set_alpha(0.1)
        except:
            pass  # In case the pane attributes don't exist in some matplotlib versions
    
    plt.tight_layout()
    plt.subplots_adjust(top=0.88)
    plt.show()

if __name__ == "__main__":
    print("Creating multivariate Gaussian visualization ")
    create_multivariate_gaussian_plot()
    print_comparison()

```


> [!example] Result
> ![[Pasted image 20250910195500.png]]

---

## 12. Maximum Likelihood Estimation

### Likelihood for Gaussian:
$$p(\mathbf{x}|\mu, \sigma^2) = \prod_{n=1}^N \mathcal{N}(x_n|\mu, \sigma^2)$$
![[Pasted image 20250910195615.png]]
- The common approach for estimating the parameters in a probability distribution from an observed dataset is to identify the parameter values that maximize the likelihood function.
### Log-Likelihood:
$$\ln p(\mathbf{x}|\mu, \sigma^2) = -\frac{1}{2\sigma^2}\sum_{n=1}^N(x_n - \mu)^2 - \frac{N}{2}\ln\sigma^2 - \frac{N}{2}\ln(2\pi)$$

### ML Estimates:
- **Mean**: $\mu_{ML} = \frac{1}{N}\sum_{n=1}^N x_n$
- **Variance**: $\sigma^2_{ML} = \frac{1}{N}\sum_{n=1}^N(x_n - \mu_{ML})^2$

> [!warning] Bias in ML Estimation
> - Mean estimate is unbiased: $\mathbb{E}[\mu_{ML}] = \mu$
> - Variance estimate is biased: $\mathbb{E}[\sigma^2_{ML}] = \frac{N-1}{N}\sigma^2$
> - $N\to \infty;\ \text{Estimated Variance}\to \text{True Variance}$

---

## 13. Binary Variables and Bernoulli Distribution

### Bernoulli Distribution
For binary variable x ∈ {0, 1}:
$$\text{Bern}(x|\mu) = \mu^x(1-\mu)^{1-x}$$

Where:
- **Mean**: $\mathbb{E}[x] = \mu$
- **Variance**: $\text{var}[x] = \mu(1-\mu)$

### Binomial Distribution
- The binomial distribution is a discrete probability distribution that models the number of successes $(say x=1)$ in a fixed number of independent Bernoulli trials $(N)$. It is named "binomial" because it involves two parameters: the number of trials $(N)$ and the probability of success in each trial $(p)$.

![[Pasted image 20250920232922.png|300]]
For m successes in N trials:
$$\text{Bin}(m|N,\mu) = \binom{N}{m}\mu^m(1-\mu)^{N-m}$$

Where: $\binom{N}{m} = \frac{N!}{(N-m)!m!}$

**Properties**:
- **Mean**: $\mathbb{E}[m] = N\mu$
- **Variance**: $\text{var}[m] = N\mu(1-\mu)$

---

## 14. Log Transform in ML

> [!tip] Why Use Log-Likelihood?
> - Converts products to sums (easier optimization)
> - Numerically stable for very small/large values
> - Preserves maximum location (monotonic function)
> - Essential when dealing with many independent samples

**Example**: Instead of optimizing $\prod_{i=1}^N p(x_i)$, optimize $\sum_{i=1}^N \ln p(x_i)$

---
