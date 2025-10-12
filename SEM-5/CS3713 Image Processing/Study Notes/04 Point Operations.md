
## Introduction to Point Operations

> [!note] What are point operations ?
> **Point Operations** are operations that consider and modify the intensity (gray level values) of individual pixels in isolation.

### Key Characteristics
- **Context free** - operate on individual pixels independently
- May involve statistical relation data with other pixels (e.g., image histogram)
- **Homogeneous Point Operation** - operation is independent of pixel location

---

## Lookup Tables (LUTs)

> [!info]
> A **LUT (Lookup Table)** is a table data structure that uses the current pixel value as the index and the computed (output) pixel value as the table entry.

### Advantages of LUTs
- Simple mechanism with many applications
- Support "on the fly processing" especially on hardware platforms
- **Flexible** - Operations functionality can be changed simply by altering table content

### Common Applications
- **Pseudo Coloring** - Converting grayscale to color representations
- **Compensate non-linearities** in sensor elements

> [!example]
> **Thermal Imaging Example**
> - Temperature 35.0°C → Index 123 → RGB (0, 255, 0) - Green
> - Temperature 37.0°C → Index 125 → RGB (128, 0, 0) - Red
> - Temperature 38.0°C → Index 126 → RGB (255, 0, 0) - Bright Red

---

## Basic Image Operations

### Image Transpose
For image **A** of size $(N × M)$, transpose **B** of size $(M × N)$:

$$B(j, i) = A(i, j)$$

where $i = 0, ..., N-1$ and $j = 0, ..., M-1$

### Vertical Flip
For vertical flipped image **B** of **A** (both $N × M$):

$$B(i, M - 1 - j) = A(i, j)$$

### Image Cropping
For cropped image **B** of size $(N_1 × N_2)$ from **A** starting at $(n_1, n_2)$:

$$B(k, l) = A(n_1 + k, n_2 + l)$$

where $k = 0, ..., N_1 - 1$ and $l = 0, ..., N_2 - 1$

---

## Image Statistics

> [!equation]
> **Sample Mean**: $m_A = \frac{\sum_{i=0}^{N-1} \sum_{j=0}^{M-1} A(i,j)}{NM}$

> [!equation]
> **Sample Variance**: $\sigma_A^2 = \frac{\sum_{i=0}^{N-1} \sum_{j=0}^{M-1} (A(i,j) - m_A)^2}{NM}$

> [!equation]
> **Standard Deviation**: $\sigma_A = \sqrt{\sigma_A^2}$

---

## Gray Level Histograms

> [!info]
> Gray Level Histogram shows the distribution of intensities, regardless of their coordinate positions.

### Definition
The histogram $h_A(l)$ $(l = 0, ..., 255)$ of image **A** is defined as:

$$h_A(l) = \#\{(i,j) | A(i,j) = l, i = 0, ..., N-1, j = 0, ..., M-1\}$$

### Types of Histograms

#### Normalized Histogram
Defines the probability of intensity level $k$ in the image:

$$P_i(k) = \frac{H(k)}{N}$$

#### Accumulated Histogram
Defines the accumulated probability of pixels having gray levels ≤ given level:

$$A_i(k) = \sum_{j≤k} P_i(j)$$

### Histogram Analysis

> [!warning]
> **Low Contrast Images** - Histogram concentrated in narrow range
> **Extra Bright Images** - Histogram shifted towards higher values
> **Extra Dark Images** - Histogram shifted towards lower values

---

## Point Processing Functions

General form: $B(i,j) = g(A(i,j))$ where $g(l)$ operates on each pixel independently.

### Identity Function
$$g(l) = l \quad (l = 0, ..., 255)$$
Result: $B = A$ (no change)

### Digital Negative
$$g(l) = 255 - l \quad (l = 0, ..., 255)$$
Creates inverse intensity image (bright becomes dark, dark becomes bright)

### Square-root Function
$$g(l) = \sqrt{l} \quad (l = 0, ..., 255)$$

> [!warning]
> Result may not be integers - requires rounding: $g_2(l) = \text{round}(\sqrt{l})$

---

## Contrast Manipulation

### Brightness Enhancement
Move histogram without changing its width → contrast preserved, brightness increased

### Contrast Stretching

> [!info]
> **Contrast Stretching** addresses low-contrast images resulting from poor lighting or sensor limitations.

Piecewise linear transformation:
$$s = \begin{cases}
αr & 0 ≤ r < a \\
β(r - a) + s_a & a ≤ r < b \\
γ(r - b) + s_b & b ≤ r < L
\end{cases}$$

**Parameters for stretching:**
- Dark region stretch: $α > 1$
- Mid-region stretch: $β > 1$ 
- Bright region stretch: $γ > 1$

### Image Normalization

> [!equation]
> **Normalizing Point Function**: $g_s^A(l) = \text{round}\left(\frac{l - mn_A}{mx_A - mn_A} × 255\right)$

Where:
- $mx_A = \max_{(i,j)} A(i,j)$
- $mn_A = \min_{(i,j)} A(i,j)$

---

## Advanced Point Operations

### Intensity Level Slicing

**Without background:**
$$s = \begin{cases}
L & a ≤ r ≤ b \\
0 & \text{otherwise}
\end{cases}$$

**With background:**
$$s = \begin{cases}
L & a ≤ r ≤ b \\
r & \text{otherwise}
\end{cases}$$

> [!tip]
> Used for highlighting specific intensity ranges in an image

### Clipping
Set $α = γ = 0$ in contrast stretching formula
- Useful for noise reduction when input signal range is known $[a, b]$

---

## Histogram Equalization

> [!info]
> **Histogram Equalization** attempts to make histogram distribution more uniform across all intensity levels.

**Goal:** Transform narrow histogram distribution → wide, uniform distribution

**Benefits:**
- Improves overall contrast
- Better utilization of available gray levels
- Enhanced visual appearance

**Process:** Uses cumulative distribution function (CDF) to redistribute pixel intensities

---

## Use of Image Histogram

### Auto-Focus Application

> [!tip]
> **Auto-focus Principle:**
> - Focus doesn't affect image mean
> - **Blurred image** → decreased standard deviation
> - **Sharp image** → increased standard deviation (wider histogram)

**Auto-focus algorithm:** Maximize histogram width (standard deviation) to achieve optimal focus

---

## Manual Implementation Examples (OpenCV only for loading)

### Basic Setup
```python
import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load image (only OpenCV function used)
print("start")
img = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)
```

### Image Statistics (Manual Implementation)
```python
def calculate_mean(img):
    """Calculate mean intensity manually"""
    total_sum = 0
    height, width = img.shape
    
    for i in range(height):
        for j in range(width):
            total_sum += img[i, j]
    
    return total_sum / (height * width)

def calculate_variance(img, mean_val=None):
    """Calculate variance manually"""
    if mean_val is None:
        mean_val = calculate_mean(img)
    
    total_sum = 0
    height, width = img.shape
    
    for i in range(height):
        for j in range(width):
            total_sum += (img[i, j] - mean_val) ** 2
    
    return total_sum / (height * width)

def calculate_std(img, mean_val=None):
    """Calculate standard deviation manually"""
    variance = calculate_variance(img, mean_val)
    return np.sqrt(variance)

def find_min_max(img):
    """Find minimum and maximum values manually"""
    height, width = img.shape
    min_val = img[0, 0]
    max_val = img[0, 0]
    
    for i in range(height):
        for j in range(width):
            if img[i, j] < min_val:
                min_val = img[i, j]
            if img[i, j] > max_val:
                max_val = img[i, j]
    
    return min_val, max_val

# Calculate statistics
mean_val = calculate_mean(img)
std_val = calculate_std(img, mean_val)
variance_val = calculate_variance(img, mean_val)
min_val, max_val = find_min_max(img)
```

### Basic Transformations (Manual Implementation)
```python
def image_transpose(img):
    """Manual image transpose: B(j,i) = A(i,j)"""
    height, width = img.shape
    img_transposed = np.zeros((width, height), dtype=img.dtype)
    
    for i in range(height):
        for j in range(width):
            img_transposed[j, i] = img[i, j]
    
    return img_transposed

def vertical_flip(img):
    """Manual vertical flip: B(i, M-1-j) = A(i,j)"""
    height, width = img.shape
    img_flipped = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            img_flipped[i, width-1-j] = img[i, j]
    
    return img_flipped

def horizontal_flip(img):
    """Manual horizontal flip: B(N-1-i, j) = A(i,j)"""
    height, width = img.shape
    img_flipped = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            img_flipped[height-1-i, j] = img[i, j]
    
    return img_flipped

def crop_image(img, start_row, start_col, crop_height, crop_width):
    """Manual image cropping: B(k,l) = A(n1+k, n2+l)"""
    img_cropped = np.zeros((crop_height, crop_width), dtype=img.dtype)
    
    for k in range(crop_height):
        for l in range(crop_width):
            img_cropped[k, l] = img[start_row + k, start_col + l]
    
    return img_cropped
```

### Point Operations (Manual Implementation)
```python
def digital_negative(img):
    """Manual digital negative: g(l) = 255 - l"""
    height, width = img.shape
    img_negative = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            img_negative[i, j] = 255 - img[i, j]
    
    return img_negative

def square_root_transform(img):
    """Manual square root transform: g(l) = sqrt(l)"""
    height, width = img.shape
    img_sqrt = np.zeros_like(img, dtype=np.float32)
    
    for i in range(height):
        for j in range(width):
            img_sqrt[i, j] = np.sqrt(img[i, j])
    
    # Normalize to 0-255 range
    max_val = np.sqrt(255)
    img_sqrt = (img_sqrt / max_val) * 255
    return img_sqrt.astype(np.uint8)

def logarithmic_transform(img):
    """Manual log transform: g(l) = c * log(1 + l)"""
    height, width = img.shape
    img_log = np.zeros_like(img, dtype=np.float32)
    
    # Calculate c constant
    c = 255 / np.log(1 + 255)
    
    for i in range(height):
        for j in range(width):
            img_log[i, j] = c * np.log(1 + img[i, j])
    
    return img_log.astype(np.uint8)

def power_law_transform(img, gamma):
    """Manual power law transform: g(l) = c * l^gamma"""
    height, width = img.shape
    img_power = np.zeros_like(img, dtype=np.float32)
    
    c = 255 / (255 ** gamma)  # Normalization constant
    
    for i in range(height):
        for j in range(width):
            img_power[i, j] = c * (img[i, j] ** gamma)
    
    return np.clip(img_power, 0, 255).astype(np.uint8)
```

### Histogram Operations (Manual Implementation)
```python
def calculate_histogram(img):
    """Manual histogram calculation"""
    histogram = np.zeros(256, dtype=int)
    height, width = img.shape
    
    for i in range(height):
        for j in range(width):
            intensity = img[i, j]
            histogram[intensity] += 1
    
    return histogram

def normalize_histogram(histogram, total_pixels):
    """Convert histogram to probability distribution"""
    normalized_hist = np.zeros_like(histogram, dtype=np.float32)
    
    for i in range(256):
        normalized_hist[i] = histogram[i] / total_pixels
    
    return normalized_hist

def calculate_cumulative_histogram(normalized_hist):
    """Calculate cumulative distribution function (CDF)"""
    cdf = np.zeros_like(normalized_hist)
    cdf[0] = normalized_hist[0]
    
    for i in range(1, 256):
        cdf[i] = cdf[i-1] + normalized_hist[i]
    
    return cdf

def histogram_equalization(img):
    """Manual histogram equalization implementation"""
    height, width = img.shape
    total_pixels = height * width
    
    # Step 1: Calculate histogram
    histogram = calculate_histogram(img)
    
    # Step 2: Normalize histogram (probability)
    normalized_hist = normalize_histogram(histogram, total_pixels)
    
    # Step 3: Calculate CDF
    cdf = calculate_cumulative_histogram(normalized_hist)
    
    # Step 4: Create transformation function
    transform_map = np.zeros(256, dtype=np.uint8)
    for i in range(256):
        transform_map[i] = np.round(cdf[i] * 255)
    
    # Step 5: Apply transformation
    img_equalized = np.zeros_like(img)
    for i in range(height):
        for j in range(width):
            img_equalized[i, j] = transform_map[img[i, j]]
    
    return img_equalized
```

### Contrast Stretching (Manual Implementation)
```python
def piecewise_linear_transform(img, r1, s1, r2, s2):
    """Manual piecewise linear contrast stretching"""
    height, width = img.shape
    img_stretched = np.zeros_like(img, dtype=np.float32)
    
    for i in range(height):
        for j in range(width):
            r = img[i, j]
            
            if r <= r1:
                # Region 1: slope = s1/r1
                s = (s1 / r1) * r if r1 != 0 else 0
            elif r <= r2:
                # Region 2: slope = (s2-s1)/(r2-r1)
                s = ((s2 - s1) / (r2 - r1)) * (r - r1) + s1
            else:
                # Region 3: slope = (255-s2)/(255-r2)
                s = ((255 - s2) / (255 - r2)) * (r - r2) + s2
            
            img_stretched[i, j] = s
    
    return np.clip(img_stretched, 0, 255).astype(np.uint8)

def simple_contrast_stretch(img):
    """Simple min-max contrast stretching"""
    min_val, max_val = find_min_max(img)
    
    if max_val == min_val:
        return img.copy()
    
    height, width = img.shape
    img_stretched = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            # Stretch to full 0-255 range
            new_val = ((img[i, j] - min_val) / (max_val - min_val)) * 255
            img_stretched[i, j] = int(new_val)
    
    return img_stretched
```

### Intensity Level Slicing (Manual Implementation)
```python
def intensity_slicing(img, lower_thresh, upper_thresh, slice_value=255, with_background=True):
    """Manual intensity level slicing"""
    height, width = img.shape
    img_sliced = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            pixel_val = img[i, j]
            
            if lower_thresh <= pixel_val <= upper_thresh:
                img_sliced[i, j] = slice_value
            else:
                if with_background:
                    img_sliced[i, j] = pixel_val
                else:
                    img_sliced[i, j] = 0
    
    return img_sliced
```

### Bit-plane Slicing (Manual Implementation)
```python
def extract_bit_plane(img, bit_position):
    """Extract specific bit plane (0=LSB, 7=MSB)"""
    height, width = img.shape
    bit_plane = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            # Extract bit at specified position
            bit_value = (img[i, j] >> bit_position) & 1
            bit_plane[i, j] = bit_value * 255  # Scale to 0 or 255
    
    return bit_plane

def reconstruct_from_bit_planes(bit_planes):
    """Reconstruct image from bit planes"""
    height, width = bit_planes[0].shape
    reconstructed = np.zeros((height, width), dtype=np.uint8)
    
    for i in range(height):
        for j in range(width):
            pixel_value = 0
            for bit_pos in range(8):
                if bit_planes[bit_pos][i, j] > 0:
                    pixel_value |= (1 << bit_pos)
            reconstructed[i, j] = pixel_value
    
    return reconstructed
```

### Lookup Table (LUT) Implementation
```python
def create_lookup_table(transform_function):
    """Create lookup table for any transformation"""
    lut = np.zeros(256, dtype=np.uint8)
    
    for intensity in range(256):
        transformed_val = transform_function(intensity)
        lut[intensity] = np.clip(int(transformed_val), 0, 255)
    
    return lut

def apply_lookup_table(img, lut):
    """Apply lookup table to image"""
    height, width = img.shape
    img_transformed = np.zeros_like(img)
    
    for i in range(height):
        for j in range(width):
            img_transformed[i, j] = lut[img[i, j]]
    
    return img_transformed

# Example: Gamma correction LUT
def gamma_correction_lut(gamma):
    """Create gamma correction lookup table"""
    def gamma_transform(pixel_val):
        normalized = pixel_val / 255.0
        corrected = normalized ** (1.0 / gamma)
        return corrected * 255
    
    return create_lookup_table(gamma_transform)
```

### Complete Manual Analysis
```python
def complete_manual_analysis(img_path):
    """Complete analysis using only manual implementations"""
    # Load image (only OpenCV usage)
    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
    
    print("=== Image Statistics ===")
    mean_val = calculate_mean(img)
    std_val = calculate_std(img)
    min_val, max_val = find_min_max(img)
    
    print(f"Mean: {mean_val:.2f}")
    print(f"Standard Deviation: {std_val:.2f}")
    print(f"Min: {min_val}, Max: {max_val}")
    
    # Apply transformations
    transformations = {
        'Original': img,
        'Negative': digital_negative(img),
        'Square Root': square_root_transform(img),
        'Log Transform': logarithmic_transform(img),
        'Hist Equalized': histogram_equalization(img),
        'Contrast Stretched': simple_contrast_stretch(img)
    }
    
    # Display results
    plt.figure(figsize=(15, 10))
    for i, (name, transformed_img) in enumerate(transformations.items()):
        plt.subplot(2, 3, i+1)
        plt.imshow(transformed_img, cmap='gray')
        plt.title(name)
        plt.axis('off')
    
    plt.tight_layout()
    plt.show()
    
    return transformations

# Usage example
# results = complete_manual_analysis('your_image.jpg')
```

---

## Key Formulas Summary

| Operation              | Formula                                                                  | OpenCV Implementation                               |
| ---------------------- | ------------------------------------------------------------------------ | --------------------------------------------------- |
| Mean                   | $m_A = \frac{\sum \sum A(i,j)}{NM}$                                      | `np.mean(img)`                                      |
| Variance               | $\sigma_A^2 = \frac{\sum \sum (A(i,j) - m_A)^2}{NM}$                     | `np.var(img)`                                       |
| Digital Negative       | $B(i,j) = 255 - A(i,j)$                                                  | `255 - img` or `cv2.bitwise_not(img)`               |
| Normalization          | $g_s^A(l) = \text{round}\left(\frac{l - mn_A}{mx_A - mn_A} × 255\right)$ | `cv2.normalize(img, None, 0, 255, cv2.NORM_MINMAX)` |
| Transpose              | $B(j,i) = A(i,j)$                                                        | `cv2.transpose(img)`                                |
| Vertical Flip          | $B(i, M-1-j) = A(i,j)$                                                   | `cv2.flip(img, 0)`                                  |
| Histogram Equalization | CDF-based mapping                                                        | `cv2.equalizeHist(img)`                             |