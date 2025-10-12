
> [!image] Gaussian noise
> ![[Pasted image 20250917051453.png|250]]
> - dark spots distributed evenly


> [!image] Speckle
> ![[Pasted image 20250917051758.png]]
> - Salt and Pepper (white spots on black and black spots on white)



> [!image] Structural (repeating)
> ![[Pasted image 20250917052016.png|250]]
> - There is a pattern to the noise.
> - Same gray level noise lines



> [!image] Visibility of noise
> ![[Pasted image 20250917052215.png]]
> - All images contain same amount of noise.
> - But darker images appear to be more noisy.

## Properties of Noise

### Locality
- Affects locally on isolated pixels.
- Image pixels are corelated. Hence there's a high probability that the adjacent pixels are similar. (Since Nyquist ratio dictates that a feature should be sampled at least twice.)
- Noisy pixels in the corelated pixels can be identified.


### Randomness

- Noise is random and follows a probability distribution depending on it's source.

## Noise Distribution Models

### Gaussian Noise
![[Pasted image 20250917053226.png]]
- Unimodal with Mean = 0 --> Most of the pixels won't change or will have little change.
- Most common noise model.

### Uniform Noise

![[Pasted image 20250917053322.png]]
- Can't make any prediction like in others.
- No probabilistic properties.
- Rare in image noise.

### Salt & Pepper

![[Pasted image 20250917053553.png|200]]
- Bi-modal with clipping.
- 2 noise levels are common in the image noise.
- Pixel values change to extreme.(can see extreme black or white spots)


> [!NOTE] Noise in spatial and time domains
> **Spatial** - The distribution of pixel values in the X,Y coordinates.
> **Transient** - The video frames of the same thing having different pixel values.


## Noise Filters

### Frame Averaging (Time domain)
![[Pasted image 20250917054527.png]]

$$\text{Output} = \frac{1}{n}\Sigma_{i=1}^n \mathcal{Frame_{i}} = \frac{1}{n}\Sigma_{i=1}^n(F_{i} + N_{i})= F + \frac{1}{n}\Sigma_{i=1}^nN_{i}$$

- Noise is averaged.
- If noise was Gaussian it will be averaged to 0 or a very small value.
- If mean wasn't 0 and had some value the image brightness would simply shift.
### Mean Filter (Spatial domain)
- Simple straight forward but introduces a blur effect.

$$\text{Output} = \frac{1}{m}\Sigma_{i=1}^m \mathcal{f_{i}} = \frac{1}{m}\Sigma_{i=1}^m P_{i}\ +\ \frac{1}{m}\Sigma_{i=1}^mN_{i}= P + \frac{1}{m}\Sigma_{i=1}^mN_{i}$$
- Non weighted Filter Mask = $\frac{1}{9}\begin{bmatrix} 1 & 1 & 1\\ 1 & 1 & 1 \\ 1 & 1 & 1 \end{bmatrix}$

```python
import cv2 as cv
import numpy as np

def mean_filter(image, kernal_size):
    # pad the image with zeros to avoid border issues
    padded_img = cv.copyMakeBorder(image, kernal_size//2, kernal_size//2, kernal_size//2, kernal_size//2, cv.BORDER_CONSTANT)

    # create an empty image to store the filtered image
    filtered_img = np.zeros_like(image)

    # iterate over the image
    for row in range(image.shape[0]):
        for col in range(image.shape[1]):
            # get the current window
            window = padded_img[row:row+kernal_size, col:col+kernal_size]
            # apply the mean filter
            filtered_img[row, col] = np.mean(window)
    
    return filtered_img
```

#### Blur Effect

- Blurring occurs when natural variations in the region get averaged.
> [!image] Mean Filter Blur Effect
> ![[Pasted image 20250917151210.png|400]]
> - The edges of the image features blur due to getting the mean of the surrounding pixels. Having a bigger filter will reduce noise more but will increase the blur effect.
> - In image 1 the variation from the background to the feature pixel occurs in one step. Hence the edge is sharp.
> - But in image 3 and 5 the the variation happens in 3 and 5 steps respectively. This results in the blur effect where the sharp edge is dulled and averaged out with the surrounding pixels.

##### Solutions for the blur effect
- Using weighted average with more weight on the pivot pixel
	- weighted Filter Mask = $\frac{1}{16}\begin{bmatrix} 1 & 2 & 1\\ 2 & 4 & 2 \\ 1 & 2 & 1 \end{bmatrix}$
- Weights arranged according to a 2D Gaussian surface. (**Gaussian filter**)
	$$h(x,y) = \exp\left[ -\ \frac{x^2+y^2}{2\sigma^2} \right]$$
	![[Pasted image 20250917152307.png]]
	weighted Filter Mask = $\frac{1}{16}\begin{bmatrix} 1 & 2 & 3 & 2 & 1 \\ 2 & 7 & 11 & 7 & 2 \\ 3 & 11 & 17 & 11 & 3 \\ 2 & 7 & 11 & 7 & 2 \\ 1 & 2 & 3 & 2 & 1 \end{bmatrix}$


- Any line up to 2 pixels will disappear if the mask is 5x5
### Threshold Averaging
- Replace average only if the difference is small (post-condition)
- Salt and pepper noise can't be removed.

$$g(x,y) =
\begin{cases}
m_l(x,y), & \text{if } |f(x,y) - m_l(x,y)| < T \\ \\
f(x,y), & \text{otherwise}
\end{cases}$$
```python
import cv2 as cv
import numpy as np

def threshold_averaging_filter(image, kernal_size, threshold):
    # pad the image with zeros to avoid border issues
    padded_img = cv.copyMakeBorder(image, kernal_size//2, kernal_size//2, kernal_size//2, kernal_size//2, cv.BORDER_CONSTANT)

    # create an empty image to store the filtered image
    filtered_img = np.zeros_like(image)
                                        
    # iterate over the image
    for row in range(image.shape[0]):
        for col in range(image.shape[1]):
            center_pixel = image[row, col]
            # threshold = 200  we need to calculate the optimal threshold or can be set manually as well
            # _, optimal_threshold = cv.threshold(padded_img[row:row+kernal_size, col:col+kernal_size], 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)

            # print((optimal_threshold[0,0]))
            # if center pixel is less than the optimal threshold then apply the mean filter
            if center_pixel < (threshold):
            # get the current window
                window = padded_img[row:row+kernal_size, col:col+kernal_size]
                # apply the mean filter
                filtered_img[row, col] = np.mean(window)
    
    return filtered_img
```
### k-Closest Averaging
- Select $k\le M$ number of pixels that have closest values to the pivot pixel (pre-selection)
- Here, we select k number of pixels with values closest to the pivot pixel (pre-selection). We first sort the pixel values and then choose the appropriate pixels for applying this filter. The goal here is to avoid any outliers that could distort image features. While this approach is superior to threshold averaging, its only drawback lies in its higher computational demands, involving the search for k values and the sorting of pixel values.
- Salt and pepper noise can be removed.

```python
import cv2 as cv
import numpy as np

def k_closest_averaging_filter(image, kernal_size, k):

    image = image.astype(np.float32) # convert the image to float32, as there can be overflow issues with uint8

    # pad the image with zeros to avoid border issues
    padded_img = cv.copyMakeBorder(image, kernal_size//2, kernal_size//2, kernal_size//2, kernal_size//2, cv.BORDER_CONSTANT)

    # create an empty image to store the filtered image
    filtered_img = np.zeros_like(image)

    # iterate over the image
    for row in range(image.shape[0]):
        for col in range(image.shape[1]):
            center_pixel = image[row, col]

            # list to store the pixel values and their distances from the center pixel
            pixel_distance_list = []

            # iterate over the window
            for i in range(row, row+kernal_size):
                for j in range(col, col+kernal_size):
                    neighbor_pixel = padded_img[i, j]
                    distance = np.linalg.norm(center_pixel - neighbor_pixel) # calculate the distance between the center pixel and the neighbor pixel
                    pixel_distance_list.append((neighbor_pixel, distance)) # append the pixel and its distance from the center pixel
                    
            # sort the list based on the distance
            pixel_distance_list.sort(key=lambda x: x[1])
            k_nearest_values = [i[0] for i in pixel_distance_list[:k]] # get the k nearest values
            # number of closest elements that you want k = (kernal_size*kernal_size). Depends on situation you can change this k value

            # apply the mean filter
            filtered_img[row, col] = np.mean(k_nearest_values)

    return filtered_img.astype(np.uint8) # convert the image back to uint8
```