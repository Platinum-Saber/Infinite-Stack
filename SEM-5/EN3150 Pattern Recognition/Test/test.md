---
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

```python
print("why")
```


```python
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# Apply the default theme
sns.set_theme()

penguins = sns.load_dataset("penguins")

# Get the feature names (column names) from the DataFrame
feature_names = penguins.columns[:-1]  # Exclude the last column ("species")

# Get the unique class names (species)
class_names = penguins["species"].unique()

# Print the feature names and class names
print("Feature Names:", feature_names)
print("Class Names:", class_names)
```

```python
print("First few rows of the penguins dataset:")
print(penguins.head())
```
