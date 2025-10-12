

### Histogram Operations
```python
# Calculate histogram
hist = cv2.calcHist([img], [0], None, [256], [0, 256])

# Plot histogram
plt.figure(figsize=(10, 4))
plt.subplot(1, 2, 1)
plt.imshow(img, cmap='gray')
plt.title('Original Image')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.plot(hist)
plt.title('Histogram')
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.show()

# Normalized histogram (probability)
hist_normalized = hist / (img.shape[0] * img.shape[1])

# Cumulative histogram
hist_cumulative = np.cumsum(hist_normalized)
```

### Histogram Equalization
```python
# OpenCV built-in histogram equalization
img_equalized = cv2.equalizeHist(img)

# Manual implementation
def histogram_equalization(img):
    """
    Manual histogram equalization implementation
    """
    # Calculate histogram
    hist, _ = np.histogram(img.flatten(), 256, [0, 256])
    
    # Calculate cumulative distribution function (CDF)
    cdf = hist.cumsum()
    cdf_normalized = cdf * 255 / cdf[-1]  # Normalize to 0-255
    
    # Apply transformation
    img_equalized = cdf_normalized[img]
    return img_equalized.astype(np.uint8)

img_eq_manual = histogram_equalization(img)

# Compare results
plt.figure(figsize=(15, 5))
plt.subplot(1, 3, 1)
plt.imshow(img, cmap='gray')
plt.title('Original')
plt.axis('off')

plt.subplot(1, 3, 2)
plt.imshow(img_equalized, cmap='gray')
plt.title('OpenCV Equalized')
plt.axis('off')

plt.subplot(1, 3, 3)
plt.imshow(img_eq_manual, cmap='gray')
plt.title('Manual Equalized')
plt.axis('off')
plt.show()
```

### Intensity Level Slicing
```python
def intensity_slicing(img, lower_thresh, upper_thresh, slice_value=255, with_background=True):
    """
    Intensity level slicing
    """
    img_sliced = img.copy()
    
    if with_background:
        # Highlight specific range, keep background
        mask = (img >= lower_thresh) & (img <= upper_thresh)
        img_sliced[mask] = slice_value
    else:
        # Show only specific range, set rest to 0
        mask = (img >= lower_thresh) & (img <= upper_thresh)
        img_sliced = np.zeros_like(img)
        img_sliced[mask] = slice_value
    
    return img_sliced

# Example: Highlight pixels in range 100-150
img_sliced = intensity_slicing(img, 100, 150, 255, with_background=True)
```

### Bit-plane Slicing
```python
def bit_plane_slicing(img, bit_plane):
    """
    Extract specific bit plane (0-7, where 0 is LSB, 7 is MSB)
    """
    return (img >> bit_plane) & 1

# Extract all bit planes
bit_planes = []
for i in range(8):
    bit_plane = bit_plane_slicing(img, i) * 255
    bit_planes.append(bit_plane)

# Display bit planes
plt.figure(figsize=(16, 10))
for i in range(8):
    plt.subplot(2, 4, i+1)
    plt.imshow(bit_planes[i], cmap='gray')
    plt.title(f'Bit Plane {i}')
    plt.axis('off')
plt.show()
```

### Normalization
```python
# Min-Max normalization to 0-255 range
def normalize_image(img):
    """
    Normalize image to 0-255 range
    """
    img_min = np.min(img)
    img_max = np.max(img)
    
    if img_max == img_min:
        return np.zeros_like(img)
    
    img_normalized = ((img - img_min) / (img_max - img_min)) * 255
    return img_normalized.astype(np.uint8)

img_normalized = normalize_image(img)

# OpenCV normalize function
img_norm_cv = cv2.normalize(img, None, 0, 255, cv2.NORM_MINMAX)
```

### Lookup Table (LUT) Implementation
```python
def create_lut(transform_func):
    """
    Create lookup table for any transformation function
    """
    lut = np.zeros(256, dtype=np.uint8)
    for i in range(256):
        lut[i] = np.clip(transform_func(i), 0, 255)
    return lut

def apply_lut(img, lut):
    """
    Apply lookup table to image
    """
    return lut[img]

# Example: Gamma correction LUT
def gamma_transform(pixel_val, gamma=2.2):
    return 255 * ((pixel_val / 255.0) ** (1.0 / gamma))

gamma_lut = create_lut(lambda x: gamma_transform(x, gamma=0.5))
img_gamma = apply_lut(img, gamma_lut)

# OpenCV LUT function
img_gamma_cv = cv2.LUT(img, gamma_lut)
```

### Complete Analysis Function
```python
def analyze_image(img_path):
    """
    Complete image analysis with multiple point operations
    """
    # Load image
    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
    
    # Calculate statistics
    stats = {
        'mean': np.mean(img),
        'std': np.std(img),
        'min': np.min(img),
        'max': np.max(img),
        'median': np.median(img)
    }
    
    # Apply transformations
    transformations = {
        'original': img,
        'negative': 255 - img,
        'sqrt': np.uint8(np.sqrt(img) * (255.0 / np.sqrt(255.0))),
        'log': np.uint8(255 * np.log(1 + img) / np.log(256)),
        'equalized': cv2.equalizeHist(img),
        'normalized': cv2.normalize(img, None, 0, 255, cv2.NORM_MINMAX)
    }
    
    # Plot results
    fig, axes = plt.subplots(2, 3, figsize=(15, 10))
    axes = axes.ravel()
    
    for i, (name, img_trans) in enumerate(transformations.items()):
        axes[i].imshow(img_trans, cmap='gray')
        axes[i].set_title(f'{name.title()}')
        axes[i].axis('off')
    
    plt.tight_layout()
    plt.show()
    
    return stats, transformations

# Usage
# stats, transforms = analyze_image('your_image.jpg')
```
