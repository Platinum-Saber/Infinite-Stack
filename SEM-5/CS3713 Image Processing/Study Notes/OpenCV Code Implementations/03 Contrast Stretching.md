### Contrast Stretching
```python
def contrast_stretch(img, low_percentile=2, high_percentile=98):
    """
    Perform contrast stretching using percentiles
    """
    # Calculate percentile values
    low_val = np.percentile(img, low_percentile)
    high_val = np.percentile(img, high_percentile)
    
    # Stretch contrast
    img_stretched = np.clip((img - low_val) * (255 / (high_val - low_val)), 0, 255)
    return img_stretched.astype(np.uint8)

# Apply contrast stretching
img_stretched = contrast_stretch(img)

# Manual contrast stretching with specific values
def manual_contrast_stretch(img, r1, s1, r2, s2):
    """
    Piecewise linear contrast stretching
    """
    img_out = np.zeros_like(img, dtype=np.float32)
    
    # Region 1: 0 to r1
    mask1 = img <= r1
    img_out[mask1] = (s1 / r1) * img[mask1]
    
    # Region 2: r1 to r2
    mask2 = (img > r1) & (img <= r2)
    img_out[mask2] = ((s2 - s1) / (r2 - r1)) * (img[mask2] - r1) + s1
    
    # Region 3: r2 to 255
    mask3 = img > r2
    img_out[mask3] = ((255 - s2) / (255 - r2)) * (img[mask3] - r2) + s2
    
    return np.clip(img_out, 0, 255).astype(np.uint8)
```
