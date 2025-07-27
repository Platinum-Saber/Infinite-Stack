---
tags: 
Created: 2025-04-04 10:09
About: 
Reviewed: false
Completion: 0
---

### Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```



## 🤖 **Controlling the Velocity and Position of a Manipulator's End Effector Using PID Controllers**  

To control the **velocity and position** of a **robotic manipulator’s end effector**, we use **PID controllers** in different ways. The type of PID controller and tuning process depend on whether we are controlling **position** or **velocity**.

---

### 🏗 **Types of PID Controllers Used**
1. **Position Control (Joint-Space or Task-Space Control)**  
   - **Type of PID**: **P, PI, or PD** control is preferred because full PID (with integral action) may lead to oscillations.  
   - **Why?** Position control focuses on **accurate endpoint movement**, and excessive integral action could cause overshoot and instability.  
   - **How it works?** The PID controller calculates **torque or force** required at each joint to move the end effector to the desired position.

2. **Velocity Control**  
   - **Type of PID**: **PI or PID** is used because the integral term helps eliminate steady-state errors.  
   - **Why?** Velocity control ensures smooth motion by regulating **joint speed**, avoiding jerks.  
   - **How it works?** The PID controller adjusts **motor speed (PWM or torque)** to track a velocity reference.

---

## 🎛 **How to Tune PID Gains?**
Tuning the PID gains (**Kp, Ki, Kd**) is crucial for stable and precise control. Here’s how the gains affect performance:

- **Proportional Gain (Kp)**  
  - **Increases responsiveness** (faster movement to the desired position).  
  - **Too high?** Overshoot and oscillations.  
  - **Too low?** Slow movement, poor tracking.  

- **Integral Gain (Ki)**  
  - **Eliminates steady-state error** in velocity control.  
  - **Too high?** Causes oscillations and lag.  
  - **Too low?** Persistent small errors.  

- **Derivative Gain (Kd)**  
  - **Damps oscillations and improves stability**.  
  - **Too high?** Can cause noise sensitivity.  
  - **Too low?** Might lead to overshoot.  

### 🔧 **Tuning Methods**
1. **Manual Tuning**
   - Increase **Kp** until oscillations occur.
   - Adjust **Kd** to reduce oscillations.
   - Increase **Ki** carefully to eliminate steady-state errors.

2. **Ziegler-Nichols Method**  
   - Increase **Kp** until the system oscillates.  
   - Use the oscillation period to set **Ki** and **Kd** values.  

---

## 🎯 **Mapping PID to Manipulator Control**
### **1. Joint Space Control (Direct Control of Each Joint)**
- Each **joint** has a PID controller that determines the **torque/force** required to move it to a desired angle.  
- **Example**: Controlling a robotic arm’s **elbow** to move from **30° to 90°**.  
- PID calculates the necessary **motor torque** to reach this position.

### **2. Task Space Control (End-Effector Control)**
- Uses **Inverse Kinematics (IK)** to convert **end-effector position** into **joint angles**.  
- PID controllers regulate **joint velocities** to follow a desired **trajectory**.

### **3. Hybrid Position-Velocity Control**
- Uses **velocity PID** for **smooth movements** and **position PID** for precise endpoint accuracy.  
- **Example**: A robotic gripper approaching an object slowly before grasping it.

---

## 🔬 **Real-World Example: Robotic Arm**
1. **Position Control**  
   - Move the end effector to (X, Y, Z).  
   - PID controls **joint angles** (θ1, θ2, θ3) to achieve this.  

2. **Velocity Control**  
   - Ensure smooth speed when moving.  
   - PID regulates **motor speed (rad/s)** to follow a trajectory.  

---

## 🏎 **Conclusion**
- **Position control** → PID adjusts **joint torques**.  
- **Velocity control** → PID adjusts **motor speed**.  
- **Fine-tuning PID gains** is necessary for **accuracy & stability**.  
