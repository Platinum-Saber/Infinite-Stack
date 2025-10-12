
## 🖥️ **PC Side** — `lidar_udp_sender.py` (Filtered to 1m)

```python
import socket
import json
from rplidar import RPLidar

# ==== CONFIG ====
LIDAR_PORT = 'COM9'  # Change to your actual COM port
UDP_IP = '192.168.1.100'  # Replace with Raspberry Pi IP
UDP_PORT = 5005

# ==== INIT LIDAR ====
lidar = RPLidar(LIDAR_PORT)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Streaming LIDAR data (<=1m) to {UDP_IP}:{UDP_PORT}... Press Ctrl+C to stop.")

try:
    for scan in lidar.iter_scans():
        # Only keep points <= 1m
        scan_data = [
            (round(angle, 2), round(distance, 2))
            for _, angle, distance in scan
            if 0 < distance <= 1000  # ✅ Filter out >1 meter
        ]

        if not scan_data:
            continue  # Skip empty scans

        message = json.dumps(scan_data)
        sock.sendto(message.encode('utf-8'), (UDP_IP, UDP_PORT))

except KeyboardInterrupt:
    print("\nStopping...")

finally:
    lidar.stop()
    lidar.disconnect()
    sock.close()
    print("LIDAR disconnected. UDP socket closed.")
```

---

## 🍓 **Raspberry Pi Side** — `lidar_udp_receiver.py` (No Change Required)

This receiver is already set up to **only display what it receives**, so no change is needed. But for completeness:

```python
import socket
import json
import numpy as np
import matplotlib.pyplot as plt

# ==== CONFIG ====
UDP_IP = '0.0.0.0'
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
sock.settimeout(2.0)

# ==== PLOT SETUP ====
fig = plt.figure()
ax = plt.subplot(1, 1, 1, projection='polar')
plt.title("Real-time LIDAR Scan (1m radius via UDP)")
ax.set_theta_zero_location('N')  # type: ignore
ax.set_theta_direction(-1)       # type: ignore
ax.set_ylim(0, 1000)

print(f"Listening for filtered LIDAR data on {UDP_PORT}...")

def update_plot(data):
    ax.clear()
    ax.set_theta_zero_location('N')  # type: ignore
    ax.set_theta_direction(-1)       # type: ignore
    ax.set_ylim(0, 1000)
    ax.grid(True)

    if not data:
        return

    angles = np.radians([angle for angle, dist in data])
    distances = [dist for angle, dist in data]
    ax.scatter(angles, distances, s=3, c='green')
    plt.pause(0.001)

# ==== MAIN LOOP ====
try:
    while True:
        try:
            data, addr = sock.recvfrom(65535)
            scan_data = json.loads(data.decode('utf-8'))
            update_plot(scan_data)
        except socket.timeout:
            continue
        except Exception as e:
            print("Error:", e)

except KeyboardInterrupt:
    print("\nStopped by user.")

finally:
    sock.close()
    print("Socket closed.")
```

---

### ✅ Now What Happens?

- ✅ PC filters LIDAR data to **only ≤ 1000 mm**
    
- ✅ Sends only that subset via UDP
    
- ✅ Raspberry Pi plots just the close-range data — great for obstacle avoidance or tight indoor mapping
    

