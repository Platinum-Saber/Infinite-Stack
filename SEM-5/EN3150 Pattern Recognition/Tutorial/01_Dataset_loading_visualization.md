---
About: Dataset Loading & Visualization
Created: 2025-08-12T18:01:00
jupyter:
  jupytext:
    cell_metadata_filter: -all
    formats: ipynb,md
    main_language: python
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.17.2
---

## Overview

Off-diagonal Plots: Each off-diagonal plot will be a scatter plot showing the relationship between pairs of variables.

> [!IMPORTANT]
> This note mirrors a Jupyter notebook but is structured for Obsidian. All Python blocks are executable with **Code Emitter**. If a package is missing, install it with `micropip` in a separate block.

## One‑time setup (Code Emitter / Pyodide)

> [!TIP]
> Run this cell first to install required packages for the session. You can rerun it if you reload the note.

```python
import micropip
await micropip.install('numpy')
await micropip.install('matplotlib')
await micropip.install('seaborn')
await micropip.install('pandas')
await micropip.install('scikit-learn')
```

## Notebook notes

Off-diagonal Plots: Each off-diagonal plot will be a scatter plot showing the relationship between pairs of variables.

Diagonal Plots: The diagonal plots will show the distribution of each variable. Since diag_kind="kde", these plots will display smoothed density estimates (KDE plots) instead of histograms. This allows you to see the distribution of each variable while considering the species differentiation provided by the colors.

Box: The box itself represents the interquartile range (IQR), which is the range between the first quartile (Q1) and the third quartile (Q3). It spans the middle 50% of the data.

The whiskers extend to 1.5 times the IQR from the quartiles. Data points beyond this range are considered outliers and are plotted individually

If there are no outliers beyond this range, the whiskers extend to the minimum and maximum values within this range.

## Code cells

### Cell 1

```python
# Works in Code Emitter (no internet needed)
import io
import numpy as np
import pandas as pd

# Try seaborn for theming if available (but don't rely on it for data)
try:
    import seaborn as sns
    import matplotlib.pyplot as plt
    sns.set_theme()
except Exception:
    import matplotlib.pyplot as plt  # fallback to matplotlib only

def _offline_penguins_sample():
    csv = """species,island,bill_length_mm,bill_depth_mm,flipper_length_mm,body_mass_g,sex
Adelie,Torgersen,39.1,18.7,181,3750,MALE
Adelie,Torgersen,39.5,17.4,186,3800,FEMALE
Adelie,Torgersen,40.3,18.0,195,3250,FEMALE
Gentoo,Biscoe,46.1,13.2,211,4500,FEMALE
Gentoo,Biscoe,50.0,16.3,230,5700,MALE
Chinstrap,Dream,46.5,17.9,192,3500,FEMALE
Chinstrap,Dream,50.0,19.5,196,3900,MALE
"""
    return pd.read_csv(io.StringIO(csv))

# Try to load via seaborn; fall back to embedded CSV
penguins = None
try:
    import seaborn as sns  # may be present already
    penguins = sns.load_dataset("penguins")
except Exception:
    penguins = _offline_penguins_sample()

# Basic cleaning: drop completely empty columns and rows with all NaNs
penguins = penguins.dropna(how="all", axis=1).dropna(how="all", axis=0)

# Feature names: exclude the target column ("species")
feature_names = [c for c in penguins.columns if c != "species"]
class_names = pd.unique(penguins["species"])

print("Feature Names:", feature_names)
print("Class Names:", class_names)
```


### Cell 2

```python
print("First few rows of the penguins dataset:")
print(penguins.head())
```

### Cell 3

```python
# Check for missing values in the DataFrame
missing_values = penguins.isnull()

# Count missing values in each column
missing_counts = penguins.isnull().sum()


# Display the counts of missing values in each column
print("\nCounts of missing values in each column:")
print(missing_counts)
```

### Cell 4

```python
# Remove rows with any missing values (NaN)
penguins = penguins.dropna()

# Count the number of missing values after removing
print("\nNumber of missing values after removing:")
print(penguins.isnull().sum())
```

### Cell 5

```python
# Plot the class distribution
plt.figure(figsize=(8, 6))
sns.countplot(data=penguins, x="species")
plt.xlabel('Species')
plt.ylabel('Count')
plt.title('Class Distribution of Penguins Species')
plt.show()
```

### Cell 6

```python
# Display information about the dataset
print(penguins.info())
```

### Cell 7

```python
# Calculate covariance matrix and variance for each variable

numeric_columns = penguins.select_dtypes(include=[np.number])
cov_matrix = numeric_columns.cov()
variance_values = numeric_columns.var()

# Create the pairplot with covariance plots
g = sns.pairplot(data=penguins, hue="species", diag_kind="kde")


plt.show()
```


### Cell 8

```python
# Summary statistics for the penguins DataFrame
summary_stats = penguins.describe()

# Print the summary statistics
print(summary_stats)
```

### Cell 9

```python
# Create a box plot using seaborn
plt.figure(figsize=(10, 8))
sns.boxplot(x='species', y='bill_length_mm', data=penguins)
plt.title('Bill Length Distribution by Species')
plt.xlabel('Species')
plt.ylabel('Bill Length (mm)')
plt.show()
```

### Cell 10

```python
# Create a box plot using seaborn
plt.figure(figsize=(10, 8))
sns.boxplot(x='species', y='body_mass_g', data=penguins)
plt.title('Bill Length Distribution by Species')
plt.xlabel('Species')
plt.ylabel('body mass ')
plt.show()
```

### Cell 11

```python
print(variance_values)
```

### Cell 12

```python
print(cov_matrix)
```

### Cell 13

```python
from sklearn.preprocessing import StandardScaler
import pandas as pd
scaler = StandardScaler()
numeric_columns_standardized = scaler.fit_transform(numeric_columns)

# Convert the standardized array back to a DataFrame with column names
numeric_columns_standardized = pd.DataFrame(numeric_columns_standardized, columns=numeric_columns.columns)

# Calculate covariance matrix and variance for standardized variables
cov_matrix = numeric_columns_standardized.cov()
variance_values = numeric_columns_standardized.var()

print(variance_values)
print(cov_matrix)
```

## How the key functions work

> [!INFO] DataFrame.head()
> Returns the first `n` rows—useful for quick schema checks without scanning the full dataset.

> [!INFO] Quick profiling
> `DataFrame.describe()` computes summary stats; `Series.value_counts()` does frequency tallies using hash maps for O(n) counting.

> [!INFO] Plotting (matplotlib / seaborn)
> Matplotlib is a stateful plotting API; seaborn builds on it to provide statistical plots and nicer defaults.

> [!INFO] sklearn.preprocessing.StandardScaler
> Fits mean and standard deviation on the training set, then transforms features to zero‑mean, unit‑variance. Stores `mean_` and `scale_` to apply consistently.

## Why these choices

- Keep data handling in **pandas** for vectorized speed and readability.
- Use **scikit‑learn** transformers (`fit` ➜ `transform`) to prevent data leakage and to serialize preprocessing.
- Use **train_test_split** with a fixed `random_state` for reproducibility.
- Prefer simple plots (matplotlib/seaborn) for EDA; they’re widely supported and easy to customize.
