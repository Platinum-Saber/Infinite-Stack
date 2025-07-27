---
tags:
  - Robotics
Created: 2025-04-03 16:33
About: PID and other robot dynamics
Reviewed: false
Completion: 0
---

### Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```



## 🔧 What is a PID Controller?

A **PID controller** is a feedback loop mechanism that continuously calculates an error value and applies corrections based on **Proportional**, **Integral**, and **Derivative** terms.

> [!NOTE] PID Overview
> - Describe how the error term is handled.
> - It tries to **minimize the error** between a **desired setpoint** and the **measured process variable**.
> - **Example**: In a self-balancing robot, the setpoint is "standing perfectly upright." If it tilts, the PID controller tries to bring it back upright by calculating how far it’s tilted (error) and how fast it’s falling (rate of change of error), and then commands the motors accordingly.
> 
> **P** : Proportional $K_{p}$
> **I** : Integral $K_{I}$
> **D** : Derivative $K_{}$
> ![[Pasted image 20250403172910.png]]


---

## 📐 The PID Equation

> [!equation] The PID output $u(t)$ is given by:
> 
> $$
> u(t) = K_p \cdot e(t) + K_i \cdot \int_0^t e(\tau) d\tau + K_d \cdot \frac{de(t)}{dt}
> $$
> 
> Where:
> - $e(t)$: Error = Desired value − Actual value
> - $K_p$: Proportional gain
> - $K_i$: Integral gain
> - $K_d$: Derivative gain

---

## 🔍 Components Explained

### 1. **Proportional (P)**
- Acts based on **present error**.
- The larger the error, the stronger the correction.
  

> [!warning] **Effect**: Faster response but may overshoot.

> [!example] **Example**: If your AC is set to 25°C and the room is 30°C, the larger the temperature gap, the harder it works to cool.

---

### 2. **Integral (I)**
- Acts on **accumulated past error**.
- Helps eliminate **steady-state error** (when output stays slightly off from the setpoint).

> [!warning] **Effect**: Increases accuracy but can cause oscillations if too high.

> [!example] **Example**: Over time, if the AC doesn’t quite reach 25°C, the integral term "remembers" the error and increases power to close the gap.

---

### 3. **Derivative (D)**
- Acts on the **rate of change of error** (predicts future error).
- Dampens the system, reducing overshoot and oscillations.

> [!warning] **Effect**: Makes the system stable and less "jumpy."

> [!example] **Example**: If the room temperature is dropping too fast, the AC slows down cooling before it overshoots.

---

## 🎯 Tuning a PID Controller

Tuning involves adjusting $K_p$, $K_i$, and $K_d$ to get a **stable** and **responsive** system.

> [!tip] Popular tuning methods:
> - **Manual tuning**: Adjusting one gain at a time.
> - **Ziegler-Nichols method**: Empirical tuning based on oscillation tests.
> - **Software-based**: Using auto-tuning tools in simulation environments like MATLAB or Python.

---

## 🤖 Real-World Applications

- **Robotics**: Balancing robots, motor speed control
- **Drones**: Stabilizing pitch, yaw, and roll
- **Temperature Control**: Thermostats
- **Industrial Automation**: Conveyor belt speed, fluid levels

---

## 🧪 Code Example: Python PID Controller

```python
class PID:
    def __init__(self, Kp, Ki, Kd):
        self.Kp = Kp
        self.Ki = Ki
        self.Kd = Kd
        self.integral = 0
        self.previous_error = 0

    def compute(self, setpoint, measured_value, dt):
        error = setpoint - measured_value
        self.integral += error * dt
        derivative = (error - self.previous_error) / dt
        self.previous_error = error

        return (self.Kp * error) + (self.Ki * self.integral) + (self.Kd * derivative)
```

---

## 📚 Summary 

> [!summary] PID Table
> 
> | Term | Meaning                     | Effect                          |
> |------|-----------------------------|----------------------------------|
> | P    | Proportional                | Reacts to current error         |
> | I    | Integral                    | Reacts to cumulative error      |
> | D    | Derivative                  | Reacts to error change rate     |
> 

> [!image] PID functionality
> ![[Pasted image 20250403170433.png]]


