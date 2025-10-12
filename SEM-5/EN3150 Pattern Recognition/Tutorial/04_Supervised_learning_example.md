---
title: 04_Supervised_learning_example
created: {date}
---

# 04 Supervised learning example

## Overview

The data set consists of samples from each of three species of Iris (Iris Setosa, Iris virginica, and Iris versicolor). Four features were measured from each sample: the length and the width of the sepals and petals, in centimeters.
https://en.wikipedia.org/wiki/Iris_flower_data_set

> [!IMPORTANT]
> This note mirrors a Jupyter notebook but is structured for Obsidian. All Python blocks are executable with **Code Emitter**. If a package is missing, install it with `micropip` in a separate block.

## One‑time setup (Code Emitter / Pyodide)

> [!TIP]
> Run this cell first to install required packages for the session. You can rerun it if you reload the note.

```python
import micropip
await micropip.install('pandas')
await micropip.install('numpy')
await micropip.install('matplotlib')
await micropip.install('seaborn')
await micropip.install('scikit-learn')
```

## Notebook notes

The data set consists of samples from each of three species of Iris (Iris Setosa, Iris virginica, and Iris versicolor). Four features were measured from each sample: the length and the width of the sepals and petals, in centimeters.
https://en.wikipedia.org/wiki/Iris_flower_data_set



## Code cells

### Cell 1

```python
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.datasets import load_iris
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical

# Load the Iris dataset
iris = load_iris()
X, y = iris.data, iris.target

#Print the class names
class_names = iris.target_names
print("Class Names:")
for i, name in enumerate(class_names):
    print(f"Class {i}: {name}")

# Get the feature names
feature_names = iris.feature_names

print(feature_names)

# Get the description of the dataset
description = iris.DESCR

# Print the description
print(description)
```

### Cell 2

```python
# Determine the unique class labels
unique_classes = np.unique(y)

# Define how many samples to print per class
samples_per_class = 2

# Print samples from each class
for cls in unique_classes:
    print(f"Class {cls} - {iris.target_names[cls]}:")
    class_indices = np.where(y == cls)[0]
    for i, idx in enumerate(class_indices[:samples_per_class]):
        print(f"Sample {i + 1}:")
        print("Features:", X[idx])
        print("Label:", y[idx])
        print()
```

### Cell 3

```python
print(X.shape)
print(y.shape)
```

### Cell 4

```python
# Convert the dataset to a pandas DataFrame for easy visualization
df = pd.DataFrame(X, columns=iris.feature_names)
df['Class'] = iris.target_names[y]

# Plot pair plots with class colors
sns.pairplot(df, hue='Class', markers=['o', 's', '^'])
plt.show()
```

### Cell 5

```python
# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

print(X_train.shape, y_train.shape  )
print(X_test.shape,  y_test.shape )
```

### Cell 6

```python
# Count the occurrences of each class label
class_counts_train = np.bincount(y_train)


# Generate class labels from 0 to 2
class_labels = np.arange(3)

# Plot the class distribution
plt.figure(figsize=(8, 6))
plt.bar(class_labels, class_counts_train, tick_label=class_labels, align='center')
plt.xlabel('Class Label')
plt.ylabel('Number of Samples')
plt.title('Class Distribution in iris Dataset (Train)')
plt.show()




# Count the occurrences of each class label
class_counts_test = np.bincount(y_test)

# Generate class labels from 0 to 2
class_labels = np.arange(3)

# Plot the class distribution
plt.figure(figsize=(8, 6))
plt.bar(class_labels, class_counts_test, tick_label=class_labels, align='center')
plt.xlabel('Class Label')
plt.ylabel('Number of Samples')
plt.title('Class Distribution in iris Dataset (Test)')
plt.show()
```

### Cell 7

```python
# Normalize the features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

print(y_train.shape, y_test.shape  )


# One-hot encode the target labels
y_train_cat = to_categorical(y_train)
y_test_cat = to_categorical(y_test)

print(y_train_cat.shape, y_test_cat.shape  )
```

### Cell 8

```python
print(y_train[1], y_train_cat[1]  )
print(y_train[99], y_train_cat[99]  )
print(y_train[101], y_train_cat[101]  )
```

### Cell 9

```python
# Build the neural network model
model = Sequential()
model.add(Dense(10, activation='relu', input_shape=(4,))) # since we have four features, input shape is  4
model.add(Dense(3, activation='softmax'))# since we have three clases output size is  3

# Visualize the model architecture
# Print the model summary
model.summary()
```

### Cell 10

```python
from tensorflow.keras.optimizers import Adam
#from tensorflow.keras.optimizers import SGD
# Compile the model


learning_rate = 0.001  # Example learning rate
# Create an Adam optimizer with the specified learning rate
optimizer = Adam(learning_rate=learning_rate)
model.compile(optimizer=optimizer, loss='categorical_crossentropy', metrics=['accuracy'])
# Train the model and store the training history
history = model.fit(X_train, y_train_cat, epochs=50, batch_size=8, validation_split=0.1)

# Plot training loss and accuracy
plt.figure(figsize=(8, 6))
plt.plot(history.history['loss'], label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend()
plt.title('Training Loss')
plt.show()



# Evaluate the model on the test set
loss, accuracy = model.evaluate(X_test, y_test_cat)
print(f"Test loss: {loss:.4f}, Test accuracy: {accuracy:.4f}")
```

### Cell 11

```python
import numpy as np
import matplotlib.pyplot as plt
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical

# Load the MNIST dataset
(X_train, y_train), (X_test, y_test) = mnist.load_data()

print(X_train.shape,  X_test.shape )
print(y_train.shape,  y_test.shape )

# Print all unique class labels in training set
unique_labels_train = np.unique(y_train)
print("Class Labels in Training Set:", unique_labels_train)

# Print all unique class labels in test set
unique_labels_test = np.unique(y_test)
print("Class Labels in Test Set:", unique_labels_test)



# Concatenate train and test labels to get the entire dataset
y_all = np.concatenate([y_train, y_test])

# Count the occurrences of each class label
class_counts = np.bincount(y_all)

# Generate class labels from 0 to 9
class_labels = np.arange(10)

# Plot the class distribution
plt.figure(figsize=(8, 6))
plt.bar(class_labels, class_counts, tick_label=class_labels, align='center')
plt.xlabel('Class Label')
plt.ylabel('Number of Samples')
plt.title('Class Distribution in MNIST Dataset')
plt.show()


# Count the occurrences of each class label
class_counts_train = np.bincount(y_train)

# Generate class labels from 0 to 9
class_labels = np.arange(10)

# Plot the class distribution
plt.figure(figsize=(8, 6))
plt.bar(class_labels, class_counts_train, tick_label=class_labels, align='center')
plt.xlabel('Class Label')
plt.ylabel('Number of Samples')
plt.title('Class Distribution in MNIST Dataset (Train)')
plt.show()




# Count the occurrences of each class label
class_counts_test = np.bincount(y_test)

# Generate class labels from 0 to 9
class_labels = np.arange(10)

# Plot the class distribution
plt.figure(figsize=(8, 6))
plt.bar(class_labels, class_counts_test, tick_label=class_labels, align='center')
plt.xlabel('Class Label')
plt.ylabel('Number of Samples')
plt.title('Class Distribution in MNIST Dataset (Test)')
plt.show()
```

### Cell 12

```python
# Flatten the images into a 1D array
X_train = X_train.reshape(-1, 784)
X_test = X_test.reshape(-1, 784)

print(X_train.shape,  X_test.shape )
print(y_train.shape,  y_test.shape )


# Normalize the pixel values to be between 0 and 1
X_train = X_train / 255.0
X_test = X_test / 255.0

# One-hot encode the target labels
y_train = to_categorical(y_train, num_classes=10)
y_test = to_categorical(y_test, num_classes=10)
```

### Cell 13

```python
# Build the neural network model
model = Sequential()
model.add(Dense(128, activation='relu', input_shape=(784,)))
model.add(Dense(64, activation='relu'))
model.add(Dense(10, activation='softmax'))

# Visualize the model architecture
# Print the model summary
model.summary()
```

### Cell 14

```python
from tensorflow.keras.optimizers import SGD
# Compile the model
# Define the learning rate
learning_rate = 0.01  # Example learning rate

# Create an optimizer with the specified learning rate
optimizer = SGD(learning_rate=learning_rate,momentum=0.9)
model.compile(optimizer=optimizer, loss='categorical_crossentropy', metrics=['accuracy'])
#model.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])


# Train the model
history = model.fit(X_train, y_train, epochs=10, batch_size=16, validation_split=0.1)

# Evaluate the model on the test set
loss, accuracy = model.evaluate(X_test, y_test)
print(f"Test loss: {loss:.4f}, Test accuracy: {accuracy:.4f}")

# Plot training loss and accuracy
plt.figure(figsize=(8, 6))
plt.plot(history.history['loss'], label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend()
plt.title('Training and Validation Loss')
plt.show()

plt.figure(figsize=(8, 6))
plt.plot(history.history['accuracy'], label='Training Accuracy')
plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.legend()
plt.title('Training and Validation Accuracy')
plt.show()
```

### Cell 15

```python
# Select random examples from the test set
num_examples = 10
random_indices = np.random.randint(0, len(X_test), num_examples)
X_examples = X_test[random_indices]
y_true = y_test[random_indices]

# Make predictions for the selected examples
y_pred = model.predict(X_examples)
y_pred_labels = np.argmax(y_pred, axis=1)

# Visualize the images and their true/predicted labels
plt.figure(figsize=(12, 6))
for i in range(num_examples):
    plt.subplot(2, num_examples, i + 1)
    plt.imshow(X_examples[i].reshape(28, 28), cmap='gray')
    plt.axis('off')
    plt.title(f"T: {np.argmax(y_true[i])}, Pr: {y_pred_labels[i]}")
plt.show()
```

### Cell 16

```python
# Find the indices of wrong predictions
y_pred = model.predict(X_test)
y_pred_labels = np.argmax(y_pred, axis=1)
y_true_labels = np.argmax(y_test, axis=1)
wrong_indices = np.where(y_pred_labels != y_true_labels)[0]

# Visualize a few wrong predictions
num_examples = min(5, len(wrong_indices))
plt.figure(figsize=(12, 6))
for i in range(num_examples):
    index = wrong_indices[i]
    plt.subplot(1, num_examples, i + 1)
    plt.imshow(X_test[index].reshape(28, 28), cmap='gray')
    plt.axis('off')
    plt.title(f"True: {y_true_labels[index]}, Pred: {y_pred_labels[index]}")
plt.show()
```

### Cell 17

```python
from sklearn.metrics import confusion_matrix
y_pred_labels = np.argmax(y_pred, axis=1)
y_true_labels = np.argmax(y_test, axis=1)

# Compute the confusion matrix
conf_matrix = confusion_matrix(y_true_labels, y_pred_labels)

# Normalize the confusion matrix to get probabilities
conf_matrix_norm = conf_matrix.astype('float') / conf_matrix.sum(axis=1)[:, np.newaxis]



# Visualize the confusion matrix
plt.figure(figsize=(8, 6))
sns.heatmap(conf_matrix, annot=True, fmt="d", cmap='Blues')
plt.xlabel('Predicted Label')
plt.ylabel('True Label')
plt.xticks(np.arange(10) + 0.5, labels=[str(i) for i in range(10)])
plt.yticks(np.arange(10) + 0.5, labels=[str(i) for i in range(10)])
plt.title('Confusion Matrix')
plt.show()


# Visualize the confusion matrix
plt.figure(figsize=(8, 6))
sns.heatmap(conf_matrix_norm, annot=True,  fmt='.2f', cmap='Blues')
plt.xlabel('Predicted Label')
plt.ylabel('True Label')
plt.xticks(np.arange(10) + 0.5, labels=[str(i) for i in range(10)])
plt.yticks(np.arange(10) + 0.5, labels=[str(i) for i in range(10)])
plt.title('Confusion Matrix')
plt.show()
```

## How the key functions work

> [!INFO] Plotting (matplotlib / seaborn)
> Matplotlib is a stateful plotting API; seaborn builds on it to provide statistical plots and nicer defaults.

> [!INFO] sklearn.preprocessing.StandardScaler
> Fits mean and standard deviation on the training set, then transforms features to zero‑mean, unit‑variance. Stores `mean_` and `scale_` to apply consistently.

> [!INFO] sklearn.model_selection.train_test_split
> Randomly partitions arrays into train/test subsets with a reproducible PRNG (`random_state`). Stratification preserves class ratios for classification.

## Why these choices

- Keep data handling in **pandas** for vectorized speed and readability.
- Use **scikit‑learn** transformers (`fit` ➜ `transform`) to prevent data leakage and to serialize preprocessing.
- Use **train_test_split** with a fixed `random_state` for reproducibility.
- Prefer simple plots (matplotlib/seaborn) for EDA; they’re widely supported and easy to customize.
