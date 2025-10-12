---
Course: EN3150 Pattern Recognition
Topic: Learning from Data and Related Challenges
Lecturer: Dr. M. T. U. Sampath K. Perera
University: University of Moratuwa
Created: 2025-09-20T23:58:00
---
## 1. What is Learning?

> [!quote]
> "A computer program is said to learn from experience **E** with respect to some class of tasks **T** and performance measure **P**, if its performance at tasks in **T**, as measured by **P**, improves with experience **E**" - Mitchell (1997)

### Key Components:
- **Experience (E)**: The data or information the algorithm learns from
- **Tasks (T)**: The specific problems the algorithm needs to solve
- **Performance Measure (P)**: Metrics used to evaluate success

> [!example]
> **MNIST Handwritten Digit Recognition Example:**
> - **Tasks (T)**: Classify handwritten digits (0-9)
> 	- ![[Pasted image 20250921000156.png|150]]
> - **Experience (E)**: 28×28 pixel images with labels
> 	- ![[Pasted image 20250921000119.png|250]]
> - **Performance Measure (P)**: Classification accuracy
> 
> The performance improves as training size increases from 10% to 80% of the dataset.
> ![[Pasted image 20250921000255.png|400]]

---

## 2. Types of Learning from Data

> [!info]
> The machine learning pipeline consists of: **Data Preparation** → **Model Training** → **Model Evaluation**


> [!tip] Types
> 1. Unsupervised 
> 2. Supervised
> 3. Semi-Supervised
> 4. Self-Supervised
> 5. Reinforcement Learning

### 2.1 Supervised Learning

> [!note] **Definition:** Algorithm learns from labeled training data to make predictions or decisions.

**Key Characteristics:**
- Uses **labeled training data** (input features + corresponding output labels)
- Training data consists of input examples with their correct outputs. (also called targets or ground truth)
- Goal: Learn a mapping function to predict correct output for new, unseen inputs

**MNIST Dataset Structure:**
![[Pasted image 20250921000804.png|200]]
```
Index | Pixel 0 | Pixel 1 | ... | Pixel 783 | Label
------|---------|---------|-----|-----------|-------
  0   |   0.0   |   0.0   | ... |    0.0    |   5
  1   |   0.0   |   0.0   | ... |    0.0    |   0
  2   |   0.0   |   0.0   | ... |    0.0    |   4
```

### 2.2 Unsupervised Learning

> [!info] **Definition:** Training on unlabeled data without explicit output labels to find patterns, structures, or relationships.
> ![[Pasted image 20250921000949.png]]

**Applications:**
- Clustering (grouping similar data points)
- Dimensionality reduction
- Pattern discovery

### 2.3 Semi-Supervised Learning

- Combines supervised + unsupervised learning using mixture of labeled and unlabeled examples.

### 2.4 Self-Supervised Learning

> [!note] Model trains to generate its own data through techniques like:
> - **Generative Adversarial Networks (GANs)**
> - **Variational Autoencoders (VAEs)**
> - **Contrastive Learning:** Discriminating between positive pairs (similar) and negative pairs (dissimilar)

### 2.5 Reinforcement Learning

> [!warning] **Definition:** Agent learns through interaction with environment, receiving rewards or penalties based on actions.
> ![[the-general-framework-of-reinforcement-learning.jpg|250]]![[82C36099566FC7C9B82116635F7E1F94.png|410]]

**Goal:** Learn *optimal policy* that maximizes cumulative reward over time.

#### Extra: [[02.1 Supervised vs Unsupervised Learning|Supervised vs Unsupervised Learning]]

---

## 3. Learning Challenges and Data Issues

### 3.1 Data Quality and Quantity Issues

> [!bug] **Problems:**
> - **Noisy, incomplete data** leads to inaccurate predictions
> - **Large data requirements** for effective learning
> - **Data imbalance** in classification problems

> [!example]
> **Imbalanced Dataset Example:**
> - Class A: 90% of data
> - Class B: 10% of data
> 
> This imbalance can lead to poor performance on the minority class.

### 3.2 Overfitting vs Underfitting

> [!error] **Overfitting:** Model performs exceptionally well on training data but fails to generalize to new, unseen data.
> ![[Pasted image 20250921002904.png|180]]

> [!fail] **Underfitting:** Model is too simplistic to capture underlying patterns in the data.
> ![[Pasted image 20250921002939.png|180]]

> [!NOTE] **The Goal:** Ensure models **generalize** well to new, unseen data.
> ![[Pasted image 20250921003026.png]]
> - Degree 1: Underfitting
> - Degree 3: Fits and generalized
> - Degree 16: Overfitting

---

## 4. Data Preparation Techniques

### 4.1 Data Cleaning

> [!attention] **Handling Missing Data:**
> - **Removing** missing entries
> - **Filling** with zeros/mean/median
> - **Interpolation** methods

### 4.2 Outlier Detection and Removal

> [!danger] **Definition:** Outliers are data points that deviate significantly from the majority of other data points.

> [!NOTE] **Visual Example:** 
> ![[Pasted image 20250921003357.png|300]]
> Data points that fall far outside the normal distribution of inliers.


### 4.3 Feature Scaling Methods

> [!url]
> **Reference:** [Scikit-learn Preprocessing Documentation](https://scikit-learn.org/stable/modules/preprocessing.html)

#### 4.3.1 Standardization (Z-score normalization)
$$\text{Standardization}(x) = \frac{x - \text{mean}(x)}{\text{std}(x)}$$

```python
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import numpy as np

# Generate sample data
np.random.seed(42)
data = np.random.normal(50, 15, 1000).reshape(-1, 1)

# Apply standardization
scaler = StandardScaler()
data_standardized = scaler.fit_transform(data)

# Plot comparison
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

ax1.hist(data, bins=30, alpha=0.7, color='blue')
ax1.set_title('Original Data')
ax1.set_xlabel('Value')
ax1.set_ylabel('Frequency')

ax2.hist(data_standardized, bins=30, alpha=0.7, color='green')
ax2.set_title('Standardized Data (mean=0, std=1)')
ax2.set_xlabel('Standardized Value')
ax2.set_ylabel('Frequency')

plt.tight_layout()
plt.show()
```

![[Pasted image 20250922145603.png]]

#### 4.3.2 Min-Max Scaling
$$\text{MinMaxScaler}(x) = \frac{x - \min(x)}{\max(x) - \min(x)}$$

#### 4.3.3 Max Absolute Scaling
$$\text{MaxAbsScaler}(x) = \frac{x}{\max(|x|)}$$

### 4.4 California Housing Dataset Example

> [!file]
> **Dataset Variables:**
> - **MedInc:** Median income (tens of thousands USD)
> - **HouseAge:** Median house age
> - **AveRooms:** Average rooms per household
> - **AveBedrms:** Average bedrooms per household
> - **Population:** Block group population
> - **AveOccup:** Average household members
> - **Latitude/Longitude:** Geographic coordinates

```python
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import MinMaxScaler, StandardScaler, RobustScaler
import matplotlib.pyplot as plt

# Load California housing dataset
housing = fetch_california_housing()
df = pd.DataFrame(housing.data, columns=housing.feature_names)

# Focus on MedInc and AveOccup for comparison
features = ['MedInc', 'AveOccup']
data_subset = df[features]

# Apply different scalers
min_max_scaler = MinMaxScaler()
standard_scaler = StandardScaler()
robust_scaler = RobustScaler()

data_minmax = min_max_scaler.fit_transform(data_subset)
data_standard = standard_scaler.fit_transform(data_subset)
data_robust = robust_scaler.fit_transform(data_subset)

# Create comparison plots
fig, axes = plt.subplots(2, 4, figsize=(16, 8))

# Original data
axes[0,0].scatter(data_subset.iloc[:, 0], data_subset.iloc[:, 1], alpha=0.6)
axes[0,0].set_title('Original Data')
axes[0,0].set_xlabel('MedInc')
axes[0,0].set_ylabel('AveOccup')

# Min-Max scaled
axes[0,1].scatter(data_minmax[:, 0], data_minmax[:, 1], alpha=0.6, color='orange')
axes[0,1].set_title('Min-Max Scaled')
axes[0,1].set_xlabel('MedInc (normalized)')
axes[0,1].set_ylabel('AveOccup (normalized)')

# Standard scaled
axes[0,2].scatter(data_standard[:, 0], data_standard[:, 1], alpha=0.6, color='green')
axes[0,2].set_title('Standard Scaled')
axes[0,2].set_xlabel('MedInc (standardized)')
axes[0,2].set_ylabel('AveOccup (standardized)')

# Robust scaled
axes[0,3].scatter(data_robust[:, 0], data_robust[:, 1], alpha=0.6, color='red')
axes[0,3].set_title('Robust Scaled')
axes[0,3].set_xlabel('MedInc (robust)')
axes[0,3].set_ylabel('AveOccup (robust)')

# Box plots for distribution comparison
for i, (title, data, color) in enumerate([
    ('Original', data_subset.values, 'blue'),
    ('Min-Max', data_minmax, 'orange'),
    ('Standard', data_standard, 'green'),
    ('Robust', data_robust, 'red')
]):
    axes[1,i].boxplot([data[:, 0], data[:, 1]], labels=['MedInc', 'AveOccup'])
    axes[1,i].set_title(f'{title} - Box Plot')

plt.tight_layout()
plt.show()
```

![[Pasted image 20250922145812.png]]

> [!warning]
> **Impact of Outliers on Scaling:**
> - **Min-Max Scaler:** Severely affected by outliers (inliers compressed to narrow range)
> - **Standard Scaler:** Moderately affected by outliers
> - **Robust Scaler:** Less affected by outliers (uses median and IQR)

### 4.5 Quantile Transformer

> [!equation] **Non-linear transformation** that spreads out frequent values and reduces outlier impact by mapping to uniform or normal distribution.

```python
from sklearn.preprocessing import QuantileTransformer
import matplotlib.pyplot as plt

# Apply Quantile Transformer
qt_uniform = QuantileTransformer(output_distribution='uniform')
qt_normal = QuantileTransformer(output_distribution='normal')

data_qt_uniform = qt_uniform.fit_transform(data_subset)
data_qt_normal = qt_normal.fit_transform(data_subset)

# Plot comparison
fig, axes = plt.subplots(1, 3, figsize=(15, 5))

# Original
axes[0].scatter(data_subset.iloc[:, 0], data_subset.iloc[:, 1], alpha=0.6)
axes[0].set_title('Original Data')

# Uniform distribution
axes[1].scatter(data_qt_uniform[:, 0], data_qt_uniform[:, 1], alpha=0.6, color='purple')
axes[1].set_title('Quantile Transform (Uniform)')

# Normal distribution
axes[2].scatter(data_qt_normal[:, 0], data_qt_normal[:, 1], alpha=0.6, color='brown')
axes[2].set_title('Quantile Transform (Normal)')

plt.tight_layout()
plt.show()
```

![[Pasted image 20250922145849.png]]

---

## 5. ML Training Process (Supervised Learning)

### 5.1 Data Splitting Strategy

> [!faq] **Why do we need Training, Validation, and Testing sets?**

```python
from sklearn.model_selection import train_test_split

# Split data into train/validation/test sets
X_temp, X_test, y_temp, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
X_train, X_val, y_train, y_val = train_test_split(X_temp, y_temp, test_size=0.25, random_state=42)

print(f"Training set: {X_train.shape[0]} samples")
print(f"Validation set: {X_val.shape[0]} samples") 
print(f"Test set: {X_test.shape[0]} samples")
```

### 5.2 Loss Functions

> [!info]
> **Purpose:** Measure how different model predictions are from actual correct answers.

**Common Loss Functions:**
- **Mean Squared Error (MSE)** - Regression
- **Mean Absolute Error (MAE)** - Regression
- **Binary Cross-Entropy** - Binary classification
- **Categorical Cross-Entropy** - Multi-class classification
- **Hinge Loss** - SVM classification

---

## 6. Model Evaluation Metrics

### 6.1 Classification Metrics

> [!table]
> **Confusion Matrix:**
> 
> |               | Predicted Positive | Predicted Negative | Total |
> |---------------|-------------------|-------------------|-------|
> | **True Positive** | True Pos. (TP)    | False Neg. (FN)   | P     |
> | **True Negative** | False Pos. (FP)   | True Neg. (TN)    | N     |
> | **Total**     | P*                | N*                |       |

**Key Metrics:**
$$\text{Accuracy} = \frac{TP + TN}{TP + TN + FP + FN}$$

$$\text{Precision} = \frac{TP}{TP + FP}$$

$$\text{Recall} = \frac{TP}{TP + FN}$$

$$\text{F1-Score} = \frac{2}{\frac{1}{\text{Precision}} + \frac{1}{\text{Recall}}}$$

```python
from sklearn.metrics import classification_report, confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt

# Example: Generate confusion matrix visualization
def plot_confusion_matrix(y_true, y_pred, class_names):
    cm = confusion_matrix(y_true, y_pred)
    
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                xticklabels=class_names, yticklabels=class_names)
    plt.title('Confusion Matrix')
    plt.xlabel('Predicted Label')
    plt.ylabel('True Label')
    plt.show()
    
    # Print classification report
    print(classification_report(y_true, y_pred, target_names=class_names))
```

> [!warning]
> **Important:** Accuracy can be misleading for imbalanced datasets. Use precision, recall, and F1-score for better evaluation.

---

## 7. Model Selection and Hyperparameter Tuning

### 7.1 Cross-Validation

> [!tip] **k-Fold Cross-Validation:** 
> Dataset divided into k subsets (folds). Model trained and evaluated k times, using different fold as test set each time.

```python
from sklearn.model_selection import cross_val_score, KFold
import matplotlib.pyplot as plt

# Example: 5-fold cross-validation
def plot_cross_validation_scores(model, X, y, cv=5):
    kfold = KFold(n_splits=cv, shuffle=True, random_state=42)
    scores = cross_val_score(model, X, y, cv=kfold, scoring='accuracy')
    
    plt.figure(figsize=(10, 6))
    plt.subplot(1, 2, 1)
    plt.bar(range(1, cv+1), scores, alpha=0.7, color='skyblue')
    plt.xlabel('Fold')
    plt.ylabel('Accuracy Score')
    plt.title(f'{cv}-Fold Cross-Validation Scores')
    plt.ylim(0, 1)
    
    plt.subplot(1, 2, 2)
    plt.boxplot(scores)
    plt.ylabel('Accuracy Score')
    plt.title('Score Distribution')
    
    plt.tight_layout()
    plt.show()
    
    print(f"Mean CV Score: {scores.mean():.3f} (+/- {scores.std() * 2:.3f})")
    return scores
```

**Benefits of Cross-Validation:**
- Reduces overfitting
- Evaluates model performance for various hyperparameter settings
- Maximizes data utilization
- Provides more robust performance estimates

### 7.2 Grid Search Hyperparameter Tuning

```python
from sklearn.model_selection import GridSearchCV
from sklearn.ensemble import RandomForestClassifier
import matplotlib.pyplot as plt

# Example: Grid search for Random Forest
def perform_grid_search(X_train, y_train):
    # Define parameter grid
    param_grid = {
        'n_estimators': [50, 100, 200],
        'max_depth': [3, 5, 7, None],
        'min_samples_split': [2, 5, 10]
    }
    
    # Create model
    rf = RandomForestClassifier(random_state=42)
    
    # Perform grid search
    grid_search = GridSearchCV(rf, param_grid, cv=5, scoring='accuracy', n_jobs=-1)
    grid_search.fit(X_train, y_train)
    
    # Visualize results
    results_df = pd.DataFrame(grid_search.cv_results_)
    
    plt.figure(figsize=(12, 8))
    plt.scatter(results_df['mean_test_score'], results_df['std_test_score'], 
                alpha=0.6, s=60)
    plt.xlabel('Mean Cross-Validation Score')
    plt.ylabel('Standard Deviation')
    plt.title('Grid Search Results: Mean vs Std of CV Scores')
    plt.grid(True, alpha=0.3)
    plt.show()
    
    print("Best parameters:", grid_search.best_params_)
    print("Best cross-validation score:", grid_search.best_score_)
    
    return grid_search
```

---

## 8. Model Selection: Probabilistic Approaches

### 8.1 Information Criteria

> [!equation] Akaike Information Criterion (AIC):
> $$\text{AIC} = \ln p(\mathcal{D}|\mathbf{w}_{ML}) - M$$
> 
> Where:
> - $\ln p(\mathcal{D}|\mathbf{w}_{ML})$ = Best-fit log likelihood
> - $M$ = Number of adjustable parameters

> [!equation] **Bayesian Information Criterion (BIC):**
> Similar to AIC but with stronger penalty for model complexity.

**Selection Rule:** Choose model with **largest** AIC/BIC value (balances performance and complexity).

---

## 9. Bias-Variance Trade-off

### 9.1 Mathematical Decomposition

> [!equation] Mean Squared Error Decomposition:
> $$\text{MSE} = \text{Bias}^2 + \text{Variance} + \text{Irreducible Error}$$
> 
> Where:
> - **Bias²** = $(\mathbb{E}[\hat{f}(x)] - f(x))^2$
> - **Variance** = $\mathbb{E}[(\hat{f}(x) - \mathbb{E}[\hat{f}(x)])^2]$
> - **Irreducible Error** = $\sigma_e^2$ (cannot be reduced by any model)

### 9.2 Visual Understanding

```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.pipeline import Pipeline

def demonstrate_bias_variance_tradeoff():
    # Generate true function with noise
    np.random.seed(42)
    n_samples = 100
    X = np.linspace(0, 1, n_samples).reshape(-1, 1)
    true_function = 1.5 * X.ravel() + 0.3 * np.sin(15 * X.ravel())
    noise = np.random.normal(0, 0.3, n_samples)
    y = true_function + noise
    
    # Test different polynomial degrees
    degrees = [1, 4, 15]
    
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    
    for i, degree in enumerate(degrees):
        # Create polynomial model
        poly_model = Pipeline([
            ('poly', PolynomialFeatures(degree=degree)),
            ('linear', LinearRegression())
        ])
        
        # Fit model
        poly_model.fit(X, y)
        
        # Generate smooth curve for prediction
        X_plot = np.linspace(0, 1, 100).reshape(-1, 1)
        y_pred = poly_model.predict(X_plot)
        true_y_plot = 1.5 * X_plot.ravel() + 0.3 * np.sin(15 * X_plot.ravel())
        
        # Plot
        axes[i].scatter(X, y, alpha=0.6, s=20, label='Training Data')
        axes[i].plot(X_plot, true_y_plot, 'g-', linewidth=2, label='True Function')
        axes[i].plot(X_plot, y_pred, 'r-', linewidth=2, label=f'Degree {degree} Fit')
        axes[i].set_title(f'Polynomial Degree {degree}')
        axes[i].set_xlabel('X')
        axes[i].set_ylabel('y')
        axes[i].legend()
        axes[i].grid(True, alpha=0.3)
        
        # Calculate and display MSE
        mse = np.mean((poly_model.predict(X) - y) ** 2)
        axes[i].text(0.05, 0.95, f'MSE: {mse:.3f}', transform=axes[i].transAxes, 
                    bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.8))
    
    plt.tight_layout()
    plt.show()

demonstrate_bias_variance_tradeoff()
```

![[Pasted image 20250922150743.png]]

### 9.3 Bias-Variance Characteristics

> [!attention] High Bias (Underfitting):
> - Inability to capture true relationship
> - Too simplistic model
> - High bias, low variance

> [!warning] High Variance (Overfitting):
> - Inability to generalize to different datasets
> - Too complex model  
> - Low bias, high variance

```python
def plot_bias_variance_illustration():
    """Create dartboard visualization of bias-variance trade-off"""
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    
    # Set up dartboard parameters
    circle_center = (0.5, 0.5)
    target_radius = 0.1
    dart_radius = 0.02
    
    scenarios = [
        ("Low Bias, Low Variance", "Ideal case", "green"),
        ("Low Bias, High Variance", "Overfitting", "orange"), 
        ("High Bias, Low Variance", "Underfitting", "blue"),
        ("High Bias, High Variance", "Worst case", "red")
    ]
    
    positions = [(0,0), (0,1), (1,0), (1,1)]
    
    for idx, ((title, subtitle, color), (row, col)) in enumerate(zip(scenarios, positions)):
        ax = axes[row, col]
        
        # Draw dartboard
        circle = plt.Circle(circle_center, target_radius, color='red', alpha=0.3)
        ax.add_patch(circle)
        
        # Generate dart positions based on bias-variance
        np.random.seed(42 + idx)
        
        if "Low Bias" in title:
            center_x, center_y = 0.5, 0.5  # Near target
        else:
            center_x, center_y = 0.3, 0.3  # Away from target
            
        if "Low Variance" in title:
            spread = 0.03  # Tight cluster
        else:
            spread = 0.08  # Wide spread
            
        dart_x = np.random.normal(center_x, spread, 10)
        dart_y = np.random.normal(center_y, spread, 10)
        
        # Plot darts
        ax.scatter(dart_x, dart_y, s=50, c=color, alpha=0.7, edgecolor='black')
        
        # Format plot
        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)
        ax.set_aspect('equal')
        ax.set_title(f"{title}\n{subtitle}", fontsize=12, fontweight='bold')
        ax.grid(True, alpha=0.3)
        
        # Add target center
        ax.plot(0.5, 0.5, 'ko', markersize=8, markerfacecolor='red')
    
    plt.tight_layout()
    plt.show()

plot_bias_variance_illustration()
```

![[Pasted image 20250922150819.png|500]]

### 9.4 Model Complexity vs Error

```python
def plot_model_complexity_curve():
    """Plot the classic bias-variance trade-off curve"""
    
    # Simulate model complexity vs error relationship
    complexity = np.linspace(0.1, 2, 100)
    
    # Bias decreases with complexity (exponential decay)
    bias_squared = 0.8 * np.exp(-2 * complexity) + 0.1
    
    # Variance increases with complexity (exponential growth)
    variance = 0.1 * np.exp(1.5 * complexity) - 0.05
    
    # Irreducible error (constant)
    irreducible_error = np.full_like(complexity, 0.15)
    
    # Total error
    total_error = bias_squared + variance + irreducible_error
    
    # Find optimal complexity
    optimal_idx = np.argmin(total_error)
    optimal_complexity = complexity[optimal_idx]
    
    # Plot
    plt.figure(figsize=(12, 8))
    
    plt.plot(complexity, bias_squared, 'b-', linewidth=2, label='Bias²')
    plt.plot(complexity, variance, 'r-', linewidth=2, label='Variance')
    plt.plot(complexity, irreducible_error, 'g--', linewidth=2, label='Irreducible Error')
    plt.plot(complexity, total_error, 'k-', linewidth=3, label='Total Error')
    
    # Mark optimal point
    plt.axvline(optimal_complexity, color='orange', linestyle=':', linewidth=2, 
                label=f'Optimal Complexity = {optimal_complexity:.2f}')
    plt.plot(optimal_complexity, total_error[optimal_idx], 'o', 
             markersize=10, color='orange')
    
    # Add regions
    plt.axvspan(0, 0.5, alpha=0.2, color='blue', label='Underfitting Region')
    plt.axvspan(1.5, 2, alpha=0.2, color='red', label='Overfitting Region')
    
    plt.xlabel('Model Complexity', fontsize=12)
    plt.ylabel('Error', fontsize=12)
    plt.title('Bias-Variance Trade-off', fontsize=14, fontweight='bold')
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)
    plt.xlim(0, 2)
    plt.ylim(0, 2)
    
    # Add text annotations
    plt.text(0.25, 1.5, 'High Bias\nLow Variance', ha='center', va='center',
             bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.7))
    plt.text(1.75, 1.5, 'Low Bias\nHigh Variance', ha='center', va='center',
             bbox=dict(boxstyle='round', facecolor='lightcoral', alpha=0.7))
    
    plt.tight_layout()
    plt.show()

plot_model_complexity_curve()
```

![[Pasted image 20250922150907.png]]

---

## 10. Key Takeaways and Best Practices


1. **Choose appropriate learning type** based on available data and problem requirements
2. **Data preprocessing is crucial** - handle missing values, outliers, and scale features appropriately
3. **Use robust scaling methods** when outliers are present
4. **Implement proper data splitting** strategy (train/validation/test)
5. **Apply cross-validation** to get reliable model performance estimates
6. **Balance bias and variance** through appropriate model complexity
7. **Use multiple evaluation metrics** especially for imbalanced datasets
8. **Consider computational complexity** when choosing models and hyperparameters

> [!url] **Additional Resources:**
> - [Scikit-learn Cross-validation Guide](https://scikit-learn.org/stable/modules/cross_validation.html)
> - [Hyperparameter Tuning Documentation](https://scikit-learn.org/stable/modules/grid_search.html)
> - [Validation Curves Tutorial](https://scikit-learn.org/stable/modules/learning_curve.html)

---

