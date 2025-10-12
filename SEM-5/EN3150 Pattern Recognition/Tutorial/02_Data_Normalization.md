---
title: 02_Data_Normalization
created:
  date:
---

# 02 Data Normalization 

## Overview

Loading the California Housing  Dataset and visualizing statistics (using pandas)

> [!IMPORTANT]
> This note mirrors a Jupyter notebook but is structured for Obsidian. All Python blocks are executable with **Code Emitter**. If a package is missing, install it with `micropip` in a separate block.

## One‑time setup (Code Emitter / Pyodide)

> [!TIP]
> Run this cell first to install required packages for the session. You can rerun it if you reload the note.

```python
import micropip
await micropip.install('pandas')
await micropip.install('scikit-learn')
await micropip.install('numpy')
await micropip.install('matplotlib')
```

## Notebook notes

Loading the California Housing  Dataset and visualizing statistics (using pandas)

https://scikit-learn.org/stable/modules/preprocessing.html#standardization-or-mean-removal-and-variance-scaling

Loading the California Housing  Dataset and visualizing statistics (without using pandas)

Visualizing data after and before the normalization

Scale features using statistics that are robust to outliers.

It involves eliminating the median and rescaling the data based on the interquartile range (IQR), which is the range between the 25th and 75th percentiles (1st quartile and 3rd quartile, respectively).

https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.RobustScaler.html#sklearn.preprocessing.RobustScaler


QuantileTransformer (uniform output)

## Code cells

### Cell 1

```python
import pandas as pd
import io
#from sklearn.datasets import fetch_california_housing

# Load the California housing dataset
def fetch_california_housing():
    csv_data = """MedInc,HouseAge,AveRooms,AveBedrms,Population,AveOccup,Latitude,Longitude,MedHouseVal
1.6812,25.0,4.192200557103064,1.0222841225626742,1392.0,3.877437325905293,36.06,-119.01,0.477
2.5313,30.0,5.039383561643835,1.1934931506849316,1565.0,2.679794520547945,35.14,-119.46,0.458
3.4801,52.0,3.977154724818276,1.185877466251298,1310.0,1.3603322949117342,37.8,-122.44,5.00001
5.7376,17.0,6.163636363636364,1.02020202020202,1705.0,3.4444444444444446,34.28,-118.72,2.186
3.725,34.0,5.492990654205608,1.02803738317757,1063.0,2.483644859813084,36.62,-121.93,2.78
4.7147,12.0,5.251482799525504,0.9750889679715302,2400.0,2.846975088967972,34.08,-117.61,1.587
5.0839,36.0,6.221719457013575,1.0950226244343892,670.0,3.0316742081447963,33.89,-118.02,1.982
3.6908,38.0,4.962825278810409,1.0483271375464684,1011.0,3.758364312267658,33.92,-118.08,1.575
4.8036,4.0,3.9246575342465753,1.0359589041095891,1050.0,1.797945205479452,37.39,-122.08,3.4
8.1132,45.0,6.87905604719764,1.0117994100294985,943.0,2.781710914454277,34.18,-118.23,4.466
2.5417,30.0,5.086021505376344,1.1720430107526882,242.0,2.6021505376344085,38.01,-120.37,1.232
3.0,35.0,3.6141479099678455,0.9887459807073956,1762.0,2.832797427652733,34.08,-118.12,2.539
2.8594,20.0,4.151458137347131,1.118532455315146,4818.0,4.532455315145814,33.76,-117.91,2.151
3.3409,18.0,4.646983311938382,1.0937098844672657,3171.0,4.070603337612323,34.2,-119.19,2.205
5.3668,27.0,6.702898550724638,1.0289855072463767,1793.0,3.2481884057971016,33.92,-117.98,2.198
3.8201,22.0,5.01119104716227,1.0223820943245403,5587.0,4.466027178257394,34.02,-117.91,1.362
3.9063,41.0,4.633540372670807,0.9006211180124224,387.0,2.4037267080745344,37.69,-122.1,1.784
4.1346,26.0,5.626506024096385,1.120481927710843,244.0,2.9397590361445785,37.48,-121.02,1.875
3.8233,36.0,5.18974358974359,1.0461538461538462,1030.0,2.641025641025641,32.75,-117.05,1.398
2.1875,27.0,5.267175572519084,1.0305343511450382,810.0,3.0916030534351147,37.43,-120.97,1.375
4.2297,47.0,3.873741994510522,1.0576395242451968,1808.0,1.6541628545288198,37.45,-122.16,4.25
4.3667,50.0,4.881782945736434,1.0406976744186047,1117.0,2.1647286821705425,34.07,-118.37,4.056
5.3478,8.0,6.210344827586207,0.943103448275862,1959.0,3.377586206896552,36.83,-119.73,1.388
6.1323,32.0,6.28951048951049,1.020979020979021,1846.0,2.581818181818182,37.59,-122.39,5.00001
4.2234,16.0,4.682678311499272,1.042212518195051,2054.0,2.98981077147016,32.9,-117.14,1.621
1.9602,38.0,4.3720136518771335,1.0136518771331058,1423.0,4.856655290102389,36.53,-119.38,0.514
2.5504,26.0,3.725552050473186,1.1093585699263933,2742.0,2.883280757097792,33.96,-118.36,1.513
3.25,38.0,5.978021978021978,0.978021978021978,240.0,2.6373626373626373,40.55,-124.13,0.948
3.65,22.0,5.531481481481482,1.0425925925925923,1420.0,2.6296296296296298,37.96,-121.98,2.041
6.2028,35.0,6.326530612244898,1.0136054421768708,1167.0,2.6462585034013606,33.72,-118.3,3.615
1.6196,38.0,3.83011583011583,1.0772200772200773,732.0,2.8262548262548264,37.75,-122.17,0.851
1.23,47.0,5.36734693877551,1.0081632653061223,785.0,3.204081632653061,34.03,-118.31,1.384
3.4286,5.0,4.28169014084507,1.1948356807511735,892.0,2.0938967136150235,32.75,-117.23,1.375
7.1108,29.0,6.335051546391752,0.9896907216494846,707.0,3.644329896907216,37.37,-122.08,4.65
3.4919,44.0,5.138418079096045,1.0310734463276836,1137.0,3.211864406779661,37.75,-122.5,2.718
5.5061,17.0,6.923128792987188,1.1348617666891436,4956.0,3.341874578556979,34.46,-118.5,2.394
4.375,34.0,4.532051282051282,1.0192307692307692,381.0,2.4423076923076925,37.6,-122.39,3.409
3.4115,35.0,5.193548387096774,1.0099255583126552,1755.0,4.354838709677419,34.03,-117.96,1.504
3.0917,48.0,6.059139784946237,1.010752688172043,530.0,2.849462365591398,38.87,-121.13,1.281
2.7321,41.0,3.5660377358490565,0.9198113207547168,873.0,4.117924528301887,33.98,-118.17,1.56
6.6073,17.0,6.771498771498772,0.9398034398034398,2734.0,3.3587223587223587,34.29,-118.75,2.581
3.7917,24.0,5.3580246913580245,0.9547325102880658,693.0,2.851851851851852,36.61,-119.45,0.905
2.2679,25.0,3.9716981132075473,0.9622641509433962,303.0,2.858490566037736,37.78,-120.85,0.713
3.4679,18.0,3.8483935742971886,1.0602409638554218,2192.0,2.200803212851405,33.73,-117.98,2.197
3.9336,15.0,5.553191489361702,1.0687397708674304,2039.0,3.337152209492635,34.04,-117.65,1.51
3.0221,28.0,4.5943012211668925,1.1058344640434192,2240.0,3.039348710990502,34.2,-118.43,2.901
3.5096,34.0,5.1525,0.9775,1169.0,2.9225,32.73,-117.03,1.42
3.0875,31.0,5.680890538033395,1.1057513914656771,1263.0,2.3432282003710574,32.77,-117.09,2.915
2.7451,42.0,4.295285359801489,1.0794044665012408,866.0,2.1488833746898264,33.73,-118.3,2.554
3.2216,34.0,6.252615844544096,1.0493273542600896,1891.0,2.82660687593423,40.86,-124.06,0.981
"""
    df = pd.read_csv(io.StringIO(csv_data))
    feature_names = [c for c in df.columns if c != "MedHouseVal"]
    X = df[feature_names].to_numpy()
    y = df["MedHouseVal"].to_numpy()
    from sklearn.utils import Bunch
    return Bunch(
        data=X,
        target=y,
        feature_names=feature_names,
        target_names=["MedHouseVal"]
    )
    
dataset = fetch_california_housing()
X_full, y_full = dataset.data, dataset.target
feature_names = dataset.feature_names

# Access the target variable (data labels)
target = dataset.target
target_names = dataset.target_names

# Print the name of the target variable
print("target_names")
print(target_names)
# Print the feature names
print("Feature Names:")
print(feature_names)

df = pd.DataFrame(X_full, columns=feature_names)

# Calculate statistics for each feature using the describe() function
statistics = df.describe()

# Display the statistics for each feature
print(statistics)
```

> [!code]- 
> ```python
> import pandas as pd
> 
> # Adjust the path if your CSV is elsewhere in the vault
> csv_path = "data/california_housing.csv"
> 
> df = pd.read_csv(csv_path)
> 
> # Reconstruct X, y, feature names, and target name exactly like scikit-learn returns
> feature_names = [c for c in df.columns if c != "MedHouseVal"]
> target_name = "MedHouseVal"
> X_full = df[feature_names].to_numpy()
> y_full = df[target_name].to_numpy()
> 
> print("Feature Names:", feature_names)
> print("Target Name:", target_name)
> print("Shape X:", X_full.shape, "| Shape y:", y_full.shape)
> 
> print("\nDescriptive Stats:")
> print(df[feature_names + [target_name]].describe())
> 
> ```

### Cell 2

```python
import pandas as pd
#from sklearn.datasets import fetch_california_housing

# Load the California housing dataset
#dataset = fetch_california_housing()
X_full, y_full = dataset.data, dataset.target
feature_names = dataset.feature_names

# Select the desired features
features = ["MedInc", "AveOccup"]
features_idx = [list(feature_names).index(feature) for feature in features]
X = X_full[:, features_idx]

# Create a pandas DataFrame with the selected features
df = pd.DataFrame(X, columns=features)


# Calculate statistics for each feature using the describe() function
statistics = df.describe()

# Display the statistics for each feature
print(statistics)
```

### Cell 3

```python
# based on https://scikit-learn.org/stable/auto_examples/preprocessing/plot_all_scaling.html#sphx-glr-auto-examples-preprocessing-plot-all-scaling-py
import matplotlib as mpl
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt

#from sklearn.datasets import fetch_california_housing
#dataset = fetch_california_housing()
#X_full, y_full = dataset.data, dataset.target
#feature_names = dataset.feature_names

feature_mapping = {
    "MedInc": "Median income in block",
    "HouseAge": "Median house age in block",
    "AveRooms": "Average number of rooms",
    "AveBedrms": "Average number of bedrooms",
    "Population": "Block population",
    "AveOccup": "Average house occupancy",
    "Latitude": "House block latitude",
    "Longitude": "House block longitude",
}
features = ["MedInc", "AveOccup"]
features_idx = [feature_names.index(feature) for feature in features]
X = X_full[:, features_idx]

means = np.mean(X, axis=0)
stds = np.std(X, axis=0)
percentiles_25 = np.percentile(X, 25, axis=0)
percentiles_50 = np.percentile(X, 50, axis=0)
percentiles_75 = np.percentile(X, 75, axis=0)

maximums = np.max(X, axis=0)
minimums = np.min(X, axis=0)

# Display the statistics for each feature
for i, feature in enumerate(features):
    print("Feature:", feature)
    print("Mean:", means[i])
    print("Standard Deviation:", stds[i])
    print("25th Percentile:", percentiles_25[i])
    print("50th Percentile (Median):", percentiles_50[i])
    print("75th Percentile:", percentiles_75[i])
    print("Maximum:", maximums[i])
    print("Minimum:", minimums[i])
    print("-" * 40)
```

### Cell 4

```python
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import MinMaxScaler
# Load the California housing dataset
#dataset = fetch_california_housing()
#X_full, y_full = dataset.data, dataset.target
#feature_names = dataset.feature_names

# Select the desired features
features = ["MedInc", "AveOccup"]
features_idx = [list(feature_names).index(feature) for feature in features]
X = X_full[:, features_idx]
df = pd.DataFrame(X_full, columns=feature_names)
# Initialize the MinMaxScaler
scaler = MinMaxScaler()

# Apply Min-Max Scaling to the selected features
X_scaled = scaler.fit_transform(X)

# Plot the data before and after normalization
plt.figure(figsize=(10, 5))

# Plot the data before normalization
plt.subplot(1, 2, 1)
plt.scatter(df["MedInc"], df["AveOccup"])
plt.xlabel("Median Income")
plt.ylabel("Average Occupancy")
plt.title("Data Before Normalization")

# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After Min-Max Scaling")

plt.tight_layout()
plt.show()

df_scaled = pd.DataFrame(X_scaled, columns=features)
statistics = df_scaled.describe()
pd.options.display.float_format = '{:.3f}'.format
# Display the statistics for each feature
print(statistics)

X_MinMaxScaler=X_scaled
```

### Cell 5

```python
# Plot the data before and after normalization
plt.figure(figsize=(10, 5))


# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_MinMaxScaler[:, 0], X_MinMaxScaler[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After MinMaxScaler")
plt.ylim(-0.01, 0.05)  # Set the y-axis limits for zooming
plt.xlim(-0.1, 1.1)  # Set the x-axis limits for zooming
plt.tight_layout()
plt.show()
```

### Cell 6

```python
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import StandardScaler

# Load the California housing dataset
#dataset = fetch_california_housing()
#X_full, y_full = dataset.data, dataset.target
#feature_names = dataset.feature_names

# Select the desired features
features = ["MedInc", "AveOccup"]
features_idx = [list(feature_names).index(feature) for feature in features]
X = X_full[:, features_idx]
df = pd.DataFrame(X_full, columns=feature_names)

# Initialize the StandardScaler
scaler = StandardScaler()

# Apply StandardScaler Scaling to the selected features
X_scaled = scaler.fit_transform(X)

# Plot the data before and after normalization
plt.figure(figsize=(10, 5))

# Plot the data before normalization
plt.subplot(1, 2, 1)
plt.scatter(df["MedInc"], df["AveOccup"])
plt.xlabel("Median Income")
plt.ylabel("Average Occupancy")
plt.title("Data Before Normalization")

# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After StandardScaler")

plt.tight_layout()
plt.show()


df_scaled = pd.DataFrame(X_scaled, columns=features)
statistics = df_scaled.describe()

pd.options.display.float_format = '{:.3f}'.format

# Display the statistics for each feature
print(statistics)

X_StandardScaler=X_scaled
```

### Cell 7

```python
# Plot the data before and after normalization
plt.figure(figsize=(10, 5))


# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_StandardScaler[:, 0], X_StandardScaler[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After StandardScaler")
plt.ylim(-0.3, 0.3)  # Set the x-axis limits for zooming
plt.xlim(-2.1, 4.4)  # Set the y-axis limits for zooming
plt.tight_layout()
plt.show()
```

### Cell 8

```python
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import RobustScaler

# Load the California housing dataset
#dataset = fetch_california_housing()
#X_full, y_full = dataset.data, dataset.target
#feature_names = dataset.feature_names

# Select the desired features
features = ["MedInc", "AveOccup"]
features_idx = [list(feature_names).index(feature) for feature in features]
X = X_full[:, features_idx]
df = pd.DataFrame(X_full, columns=feature_names)
# Initialize the RobustScaler
scaler = RobustScaler(quantile_range=(25, 75))


# Apply RobustScaler Scaling to the selected features
X_scaled = scaler.fit_transform(X)

# Plot the data before and after normalization
plt.figure(figsize=(10, 5))

# Plot the data before normalization
plt.subplot(1, 2, 1)
plt.scatter(df["MedInc"], df["AveOccup"])
plt.xlabel("Median Income")
plt.ylabel("Average Occupancy")
plt.title("Data Before Normalization")

# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After RobustScaler")

plt.tight_layout()
plt.show()


df_scaled = pd.DataFrame(X_scaled, columns=features)
statistics = df_scaled.describe()

pd.options.display.float_format = '{:.3f}'.format

# Display the statistics for each feature
print(statistics)

X_RobustScaler=X_scaled
```

### Cell 9

```python
# Plot the data before and after normalization
plt.figure(figsize=(10, 5))


# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_RobustScaler[:, 0], X_RobustScaler[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After RobustScaler")
plt.ylim(-2, 4)  # Set the y-axis limits for zooming
plt.xlim(-2, 4)  # Set the x-axis limits for zooming
plt.tight_layout()
plt.show()
```

### Cell 10

```python
# Plot the data after different scaling methods
plt.figure(figsize=(15, 5))

# Plot the data after Min-Max Scaling
plt.subplot(1, 3, 1)
plt.scatter(X_MinMaxScaler[:, 0], X_MinMaxScaler[:, 1])
plt.xlim(-5, 5)  # Set the x-axis limits for zooming
plt.ylim(-5, 5)  # Set the y-axis limits for zooming
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After Min-Max Scaling")

# Plot the data after Standard Scaling
plt.subplot(1, 3, 2)
plt.scatter(X_StandardScaler[:, 0], X_StandardScaler[:, 1])
plt.xlim(-5, 5)  # Set the x-axis limits for zooming
plt.ylim(-5, 5)  # Set the y-axis limits for zooming
plt.xlabel("Standardized Median Income")
plt.ylabel("Standardized Average Occupancy")
plt.title("Data After Standard Scaling")

# Plot the data after Robust Scaling
plt.subplot(1, 3, 3)
plt.scatter(X_RobustScaler[:, 0], X_RobustScaler[:, 1])
plt.xlim(-5, 5)  # Set the x-axis limits for zooming
plt.ylim(-5, 5)  # Set the y-axis limits for zooming
plt.xlabel("Robustly Scaled Median Income")
plt.ylabel("Robustly Scaled Average Occupancy")
plt.title("Data After Robust Scaling")

plt.tight_layout()
plt.show()
```

### Cell 11

```python
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import QuantileTransformer

# Load the California housing dataset
#dataset = fetch_california_housing()
#X_full, y_full = dataset.data, dataset.target
#feature_names = dataset.feature_names

# Select the desired features
features = ["MedInc", "AveOccup"]
features_idx = [list(feature_names).index(feature) for feature in features]
X = X_full[:, features_idx]
df = pd.DataFrame(X_full, columns=feature_names)
# Initialize the Scaler
scaler =  QuantileTransformer(output_distribution="uniform")

# Apply Scaling to the selected features
X_scaled = scaler.fit_transform(X)

# Plot the data before and after normalization
plt.figure(figsize=(10, 5))

# Plot the data before normalization
plt.subplot(1, 2, 1)
plt.scatter(df["MedInc"], df["AveOccup"])
plt.xlabel("Median Income")
plt.ylabel("Average Occupancy")
plt.title("Data Before Normalization")

# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After Quantile Transformer Scaling (Uniform)")

plt.tight_layout()
plt.show()

df_scaled = pd.DataFrame(X_scaled, columns=features)
statistics = df_scaled.describe()
pd.options.display.float_format = '{:.3f}'.format
# Display the statistics for each feature
print(statistics)

X_QuantileTransformer=X_scaled
```

### Cell 12

```python
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import QuantileTransformer

# Load the California housing dataset
#dataset = fetch_california_housing()
#X_full, y_full = dataset.data, dataset.target
#feature_names = dataset.feature_names

# Select the desired features
features = ["MedInc", "AveOccup"]
features_idx = [list(feature_names).index(feature) for feature in features]
X = X_full[:, features_idx]
df = pd.DataFrame(X_full, columns=feature_names)
# Initialize the Scaler
scaler =  QuantileTransformer(output_distribution="normal")

# Apply Scaling to the selected features
X_scaled = scaler.fit_transform(X)

# Plot the data before and after normalization
plt.figure(figsize=(10, 5))

# Plot the data before normalization
plt.subplot(1, 2, 1)
plt.scatter(df["MedInc"], df["AveOccup"])
plt.xlabel("Median Income")
plt.ylabel("Average Occupancy")
plt.title("Data Before Normalization")

# Plot the data after normalization
plt.subplot(1, 2, 2)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1])
plt.xlabel("Normalized Median Income")
plt.ylabel("Normalized Average Occupancy")
plt.title("Data After Quantile Transformer Scaling (Normal)")

plt.tight_layout()
plt.show()

df_scaled = pd.DataFrame(X_scaled, columns=features)
statistics = df_scaled.describe()
pd.options.display.float_format = '{:.3f}'.format
# Display the statistics for each feature
print(statistics)

X_QuantileTransformer=X_scaled
```

## How the key functions work

> [!INFO] Quick profiling
> `DataFrame.describe()` computes summary stats; `Series.value_counts()` does frequency tallies using hash maps for O(n) counting.

> [!INFO] Plotting (matplotlib / seaborn)
> Matplotlib is a stateful plotting API; seaborn builds on it to provide statistical plots and nicer defaults.

> [!INFO] sklearn.preprocessing.StandardScaler
> Fits mean and standard deviation on the training set, then transforms features to zero‑mean, unit‑variance. Stores `mean_` and `scale_` to apply consistently.

> [!INFO] sklearn.preprocessing.MinMaxScaler
> Rescales features to a range (default [0,1]) using min/max learned from training data.

## Why these choices

- Keep data handling in **pandas** for vectorized speed and readability.
- Use **scikit‑learn** transformers (`fit` ➜ `transform`) to prevent data leakage and to serialize preprocessing.
- Use **train_test_split** with a fixed `random_state` for reproducibility.
- Prefer simple plots (matplotlib/seaborn) for EDA; they’re widely supported and easy to customize.
