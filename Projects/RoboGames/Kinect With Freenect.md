

> [!NOTE] Objective
> 
> 1. **Detect a specific color** in a selected region of the pixel grid.
> 2. **Retrieve depth data** from the Kinect sensor.

---

## 1. Color Recognition in a Specific Region

> [!warning] The script captures an RGB image from the Kinect's color camera, processes it using OpenCV, and detects a specified color in a **region of interest (ROI)**.

### Code

```python
import freenect
import cv2
import numpy as np

# Define the color range (HSV format) to detect (e.g., red)
LOWER_COLOR = np.array([0, 120, 70])   # Lower bound for red
UPPER_COLOR = np.array([10, 255, 255]) # Upper bound for red

# Define the region of interest (ROI) in pixels (x1, y1, x2, y2)
ROI = (200, 150, 300, 250)

def get_video():
    """Fetches an RGB frame from Kinect"""
    frame, _ = freenect.sync_get_video()
    return cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

while True:
    frame = get_video()

    # Extract the region of interest (ROI)
    x1, y1, x2, y2 = ROI
    roi = frame[y1:y2, x1:x2]

    # Convert to HSV for better color detection
    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)

    # Create a mask for the defined color range
    mask = cv2.inRange(hsv, LOWER_COLOR, UPPER_COLOR)

    # Count non-zero pixels in the mask (indicates how much of the color is detected)
    color_detected = cv2.countNonZero(mask)

    # Draw the ROI box
    cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
    
    # Display a message if color is detected
    if color_detected > 100:  # Threshold to ignore noise
        cv2.putText(frame, "Color Detected!", (x1, y1 - 10), 
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    # Show the processed frames
    cv2.imshow("Kinect RGB", frame)
    cv2.imshow("Mask", mask)

    # Press 'q' to exit
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
cv2.destroyAllWindows()
```

---
<div style="page-break-before: always;"></div>

### Explanation of Functions

> [!info] `freenect.sync_get_video()`
> - Fetches a single RGB frame from the Kinect.
> - Returns an image in RGB format.

> [!info] `cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)`
>    - Converts the RGB image from Kinect into OpenCV's BGR format.

> [!info] `cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)`
>    - Converts the region of interest to the HSV color space for better color segmentation.

> [!info] `cv2.inRange(hsv, LOWER_COLOR, UPPER_COLOR)`
>    - Creates a binary mask where pixels within the color range are white (255) and others are black (0).

> [!info] `cv2.countNonZero(mask)`
>    - Counts the number of pixels detected in the defined color range.

> [!info] `cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)`
>    - Draws a rectangle around the selected region.

> [!info] `cv2.putText()`
>    - Displays a message when the color is detected.

---
<div style="page-break-before: always;"></div>

## 2. Getting Depth Data

> [!warning] The script captures depth frames from the Kinect and displays the depth feed in grayscale.

### Code:

```python
import freenect
import cv2
import numpy as np

def get_depth():
    """Fetches a depth frame from Kinect and processes it."""
    depth, _ = freenect.sync_get_depth()
    
    # Convert to 8-bit grayscale for better visualization
    depth_scaled = (depth / depth.max() * 255).astype(np.uint8)
    
    return depth_scaled

while True:
    depth_frame = get_depth()

    # Show the depth frame
    cv2.imshow("Kinect Depth Feed", depth_frame)

    # Press 'q' to exit
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
```

---

### Explanation of Functions

> [!info] `freenect.sync_get_depth()`
> - Fetches a depth frame from the Kinect sensor.
> - Returns an array with depth values in millimeters.

> [!info] `depth / depth.max() * 255`
> - Normalizes the depth values (which range from 0 to 2047) to fit in an 8-bit grayscale range (0-255).

> [!info] `astype(np.uint8)`
>    - Converts the floating-point depth values to 8-bit integers for display.

> [!info] `cv2.imshow("Kinect Depth Feed", depth_frame)`
>    - Displays the depth image in grayscale.

---
<div style="page-break-before: always;"></div>


## 3. Overlaying Depth on the RGB Feed

> [!tip] To overlay depth data on the RGB feed, we must:
> - Capture **both depth and RGB** frames from the Kinect.
> - Normalize the depth data to 8-bit grayscale.
> - Apply a **colormap** to make depth values more visually distinguishable.
> - Blend the depth frame with the RGB frame.

### Code

```python
import freenect
import cv2
import numpy as np

def get_video():
    """Fetch RGB frame from Kinect."""
    frame, _ = freenect.sync_get_video()
    return cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

def get_depth():
    """Fetch and normalize depth frame from Kinect."""
    depth, _ = freenect.sync_get_depth()
    
    # Normalize depth to fit into 8-bit range
    depth_scaled = (depth / depth.max() * 255).astype(np.uint8)
    
    # Apply a colormap for better visibility
    depth_colored = cv2.applyColorMap(depth_scaled, cv2.COLORMAP_JET)

    return depth_colored

while True:
    rgb_frame = get_video()
    depth_frame = get_depth()

    # Overlay depth on RGB using transparency
    overlay = cv2.addWeighted(rgb_frame, 0.6, depth_frame, 0.4, 0)

    # Display output
    cv2.imshow("RGB + Depth Overlay", overlay)
    
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
```

---

> [!NOTE] Explanation of Functions
> 
> 1. **`cv2.applyColorMap(depth_scaled, cv2.COLORMAP_JET)`**
>     - Converts the grayscale depth image into a color heatmap to visualize depth differences.
> 1. **`cv2.addWeighted(rgb_frame, 0.6, depth_frame, 0.4, 0)`**
>     - Blends the RGB frame (60% opacity) with the depth frame (40% opacity).
> 1. **`cv2.imshow("RGB + Depth Overlay", overlay)`**
>     - Displays the overlaid depth-RGB feed.

---
<div style="page-break-before: always;"></div>

## 4. Tracking Multiple Colors in the Kinect RGB Feed

> [!tip] To track multiple colors, we:
> - Define multiple **HSV color ranges** (e.g., Red, Green, Blue).
> - Process the RGB feed and detect these colors.
> - Draw **bounding boxes** around detected objects.

### Code

```python
import freenect
import cv2
import numpy as np

# Define color ranges in HSV format (Lower and Upper bounds)
COLOR_RANGES = {
    "Red":   [(0, 120, 70), (10, 255, 255)],  # Red
    "Green": [(35, 100, 100), (85, 255, 255)], # Green
    "Blue":  [(100, 150, 0), (140, 255, 255)]  # Blue
}

def get_video():
    """Fetch RGB frame from Kinect."""
    frame, _ = freenect.sync_get_video()
    return cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

while True:
    frame = get_video()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    for color_name, (lower, upper) in COLOR_RANGES.items():
        # Create a mask for the color
        mask = cv2.inRange(hsv, np.array(lower), np.array(upper))
        
        # Find contours of detected areas
        contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        for contour in contours:
            if cv2.contourArea(contour) > 500:  # Ignore small objects
                x, y, w, h = cv2.boundingRect(contour)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
                cv2.putText(frame, color_name, (x, y - 10), 
                            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    cv2.imshow("Multi-Color Tracking", frame)

    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
```

---
<div style="page-break-before: always;"></div>

### Explanation of Functions

> [!info] HSV Color Ranges:
> - `"Red": [(0, 120, 70), (10, 255, 255)]`
> - `"Green": [(35, 100, 100), (85, 255, 255)]`
> - `"Blue": [(100, 150, 0), (140, 255, 255)]`
> - Defines **lower and upper HSV bounds** for red, green, and blue.

> [!info] `cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)`
>    - Finds the contours of detected objects.

> [!info] `cv2.boundingRect(contour)`
>    - Gets the (x, y, width, height) of the detected object.

> [!info] `cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)`
>    - Draws a rectangle around detected colors.

> [!info] `cv2.putText(frame, color_name, (x, y - 10), ...)`
>    - Labels the detected color on the video feed.


---

