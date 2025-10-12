
## 🎯 Goal:

- Plot LIDAR scan data in **real-time** as a **2D polar map**.
- Data will be displayed as **points (X, Y)** computed from angle & distance.
---

## 🐍 Python Script: Real-time 2D LIDAR Plot

### ✅ Requirements:

Install the required libraries:

```bash
pip install rplidar matplotlib numpy
```

### 📜 Full Python Script:

```python
from rplidar import RPLidar
import matplotlib.pyplot as plt
import matplotlib.projections.polar as polar
import numpy as np

# ==== CONFIGURATION ====
PORT_NAME = 'COM9'  # Change this to your actual COM port

# ==== SETUP ====
lidar = RPLidar(PORT_NAME)
lidar.connect()
print("Connected to LIDAR")
info = lidar.get_info()
print("Device Info:", info)
health = lidar.get_health()
print("Health:", health)

# ==== PLOTTING SETUP ====
fig = plt.figure()
ax = plt.subplot(1, 1, 1, projection='polar')
plt.title("RPLIDAR A2 - Real-Time Scan (1 Meter Radius)")

# ==== FUNCTION TO UPDATE PLOT ====
def update_plot(scan_data):
    ax.clear()
    ax.set_theta_zero_location('N')  # type: ignore
    ax.set_theta_direction(-1)       # type: ignore
    ax.grid(True)
    ax.set_ylim(0, 600)  # ✅ Limit to 600 mm

    if len(scan_data) == 0:
        return

    # Filter points within 600 mm
    filtered = [(angle, dist) for angle, dist in scan_data if 0 < dist <= 600]
    if not filtered:
        return

    angles = np.radians([angle for angle, dist in filtered])
    distances = [dist for angle, dist in filtered]

    ax.scatter(angles, distances, s=3, c='blue')
    plt.pause(0.001)

# ==== MAIN LOOP ====
try:
    print("Starting real-time scan... Press Ctrl+C to stop.")
    scan_data = []
    for scan in lidar.iter_scans():
        scan_data = [(angle, distance) for _, angle, distance in scan]
        update_plot(scan_data)

except KeyboardInterrupt:
    print("\nStopping...")

finally:
    lidar.stop()
    lidar.disconnect()
    print("LIDAR disconnected.")
```

---

## 🧠 How It Works:

- The LIDAR returns a stream of `(quality, angle, distance)` data.
- We extract `angle` and `distance`, convert angle to **radians**.
- Plot in **polar coordinates** using `matplotlib`.

---

