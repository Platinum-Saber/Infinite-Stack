#### Digital Negative
```python
# Method 1: Direct subtraction
img_negative = 255 - img

# Method 2: Using cv2.bitwise_not
img_negative = cv2.bitwise_not(img)
```

#### Square Root Transform
```python
# Square root transformation (enhances dark regions)
img_sqrt = np.sqrt(img.astype(np.float32))
img_sqrt = np.uint8(img_sqrt * (255.0 / np.sqrt(255.0)))

# Alternative method
img_sqrt = np.power(img/255.0, 0.5) * 255
img_sqrt = np.uint8(img_sqrt)
```

#### Logarithmic Transform
```python
# Log transformation (compresses dynamic range)
c = 255 / np.log(1 + np.max(img))
img_log = c * np.log(1 + img.astype(np.float32))
img_log = np.uint8(img_log)
```
