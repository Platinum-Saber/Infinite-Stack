### Basic Setup
```python
import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load image
img = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)
```

### Image Statistics
```python
# Calculate mean and standard deviation
mean_val = np.mean(img)
std_val = np.std(img)
variance = np.var(img)

print(f"Mean: {mean_val:.2f}")
print(f"Standard Deviation: {std_val:.2f}")
print(f"Variance: {variance:.2f}")

# Min and max values
min_val = np.min(img)
max_val = np.max(img)
```

### Basic Transformations
```python
# Image transpose
img_transpose = cv2.transpose(img)

# Vertical flip
img_vflip = cv2.flip(img, 0)  # 0 for vertical flip

# Horizontal flip
img_hflip = cv2.flip(img, 1)  # 1 for horizontal flip

# Image cropping
height, width = img.shape
x, y, w, h = 100, 50, 200, 150  # x, y, width, height
img_cropped = img[y:y+h, x:x+w]
```
