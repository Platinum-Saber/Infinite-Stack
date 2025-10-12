---
tags: 
Created: 2025-07-29 18:09
About: 
Reviewed: false
Completion: 0
---

### ✅ Goal: Test communication continuously

We’ll write **two Python scripts**:

- `router_send_loop.py`: Repeatedly sends data from the Router (COM10).
    
- `coordinator_receive_loop.py`: Continuously receives and prints data from the Coordinator (COM3).
    

---

## 🔁 `router_send_loop.py` (Send from Router / COM10)

```python
import serial
import time

router = serial.Serial('COM10', 9600, timeout=1)  # Change COM port if needed
time.sleep(2)  # Give time to stabilize

count = 1

try:
    while True:
        message = f"Ping {count}\n"
        router.write(message.encode('utf-8'))
        print("Sent:", message.strip())
        count += 1
        time.sleep(2)  # Send every 2 seconds

except KeyboardInterrupt:
    print("Stopped by user.")
finally:
    router.close()
```

---

## 📥 `coordinator_receive_loop.py` (Receive on Coordinator / COM3)

```python
import serial

coordinator = serial.Serial('COM3', 9600, timeout=1)  # Change COM port if needed

print("Listening for messages from Router...\n")

try:
    while True:
        if coordinator.in_waiting > 0:
            data = coordinator.readline().decode('utf-8', errors='ignore').strip()
            if data:
                print("Received:", data)

except KeyboardInterrupt:
    print("Stopped by user.")
finally:
    coordinator.close()
```

---

## 🧪 How to Run

1. Run `coordinator_receive_loop.py` first to start listening.
    
2. Then run `router_send_loop.py` to start sending.
    
3. You should see messages like:
    
    ```
    Received: Ping 1
    Received: Ping 2
    ...
    ```
    

---

### 📌 Extra Tips

- Ensure the **DH (Destination High)** and **DL (Destination Low)** on each module are correctly set to the other module’s **SH** and **SL**.
    
    - On **Router (COM10)**: `DH = 13A200`, `DL = 24538888` (Coordinator's address).
        
    - On **Coordinator (COM3)**: `DH = 13A200`, `DL = 423467EB` (Router's address).
        

You can set this in XCTU under **Networking & Security** > `DH` / `DL`.

Would you like to expand this into a **bidirectional chat system** between the two modules?



