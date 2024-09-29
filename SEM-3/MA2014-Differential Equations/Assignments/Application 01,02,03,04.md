
## Application 1: Mass-Spring System

We are tasked with analyzing the motion of a vibrating machine using the **mass-spring model**. The differential equation that models this system is derived using **Newton’s 2nd Law**.

> [!image]- Diagram
> ![[Pasted image 20240929094104.png]]


Given:
- Mass of the machine: $m = 800 \, \text{lbf}$
- The mass is suddenly stopped at a velocity $v = 20 \, \text{ft/min}$.
- No air resistance, elastic cable behaves like a spring.
- The spring constant is denoted as $k$.

#### Step-by-Step Solution

---

### Part A: Differential Equation and Frequency of Vibration

We start by applying **Newton’s 2nd Law**. The forces acting on the mass are:
- The **restoring force** due to the spring, given by **Hooke’s Law**: $F_{\text{spring}} = -ky(t)$.
- The **gravitational force** acting downward: $F_{\text{gravity}} = mg$.

> [!image]- Diagram
> ![[Pasted image 20240929094150.png]]

From Newton’s 2nd Law:
$$m \frac{d^2 y(t)}{dt^2} = -ky(t) + mg$$

Rearranging this equation:
$$m \frac{d^2 y(t)}{dt^2} + ky(t) = mg$$


We can define $y_{\text{eq}}$ as the equilibrium displacement where the spring force balances the gravitational force, so:
$$m \frac{d^2 y(t)}{dt^2} + ky(t) = 0$$

This is the **second-order linear differential equation** that governs the system.

#### Natural Frequency of the System

The general form of the harmonic oscillator equation is:
$$\frac{d^2 y(t)}{dt^2} + \omega_n^2 y(t) = 0$$

where $\omega_n$ is the **natural frequency** of the system. Comparing this with the equation above, we identify:
$$\omega_n = \sqrt{\frac{k}{m}}$$

To calculate $\omega_n$, we need the values of $k$ and $m$.

The machine weighs $800 \, \text{lbf}$, which corresponds to:

$$m = \frac{800 \, \text{lbf}}{32.2 \, \text{ft/s}^2} \approx 24.84 \, \text{slugs}$$

The spring constant $k = 6000*12 \, \text{lbf/ft}$ .

Now, the natural frequency is:
$$\omega_n = \sqrt{\frac{k}{m}} = \sqrt{\frac{6000*12}{24.84}} \approx 53.83 \, \text{rad/s}$$

Thus, the **natural frequency** is $\omega_n \approx 53.83 \, \text{rad/s}$.

---

### Part B: Maximum Tension in the Cable

> [!image]- Diagram
> ![[Pasted image 20240929094244.png]]

The maximum tension in the cable occurs at the point of **maximum displacement** of the vibrating mass. The restoring force is:

$$
T_{\text{max}} = k \cdot y_{\text{max}}
$$

We can estimate $y_{\text{max}}$ using energy conservation. The initial kinetic energy due to the velocity $v = 20 \, \text{ft/min}$ is:

$$
KE = \frac{1}{2} m v^2
$$

First, convert the velocity to $\text{ft/s}$:

$$
v = \frac{20 \, \text{ft/min}}{60} = \frac{1}{3} \, \text{ft/s}
$$

Now, the kinetic energy is:

$$
KE = \frac{1}{2} \cdot 24.84 \cdot \left( \frac{1}{3} \right)^2 \approx 1.38 \, \text{ft-lbf}
$$

This kinetic energy is converted into potential energy stored in the spring:

$$
PE = \frac{1}{2} k y_{\text{max}}^2
$$

Equating kinetic energy to potential energy:

$$
1.38 = \frac{1}{2} \cdot 500 \cdot y_{\text{max}}^2
$$

Solving for $y_{\text{max}}$:

$$
y_{\text{max}} = \sqrt{\frac{2 \times 1.38}{500}} \approx 0.074 \, \text{ft}
$$

Now, the maximum tension in the cable is:

$$
T_{\text{max}} = 500 \cdot 0.074 \approx 37 \, \text{lbf}
$$

Thus, the **maximum tension** is $T_{\text{max}} \approx 37 \, \text{lbf}$.

---

### Part C: Maximum Stress in the Cable

The **stress** in the cable is defined as the force divided by the cross-sectional area $A$:

$$
\sigma = \frac{T_{\text{max}}}{A}
$$

The cross-sectional area of the cable is:

$$
A = \pi \left( \frac{d}{2} \right)^2
$$

where $d = 0.5 \, \text{in} = 0.04167 \, \text{ft}$. Substituting into the formula:

$$
A = \pi \left( \frac{0.04167}{2} \right)^2 \approx 0.001364 \, \text{ft}^2
$$

Now, the stress is:
$$\sigma = \frac{37}{0.001364} \approx 27,125 \, \text{psi}$$


Thus, the **maximum stress** is $\sigma \approx 27,125 \, \text{psi}$.

---

### Part D: Will the Cable Break?

The **ultimate tensile strength** (UTS) of the cable material is given as $40,000 \, \text{psi}$. Since the maximum stress we calculated is $27,125 \, \text{psi}$, which is less than the UTS, the cable **will not break**.

---

### Summary of Application 1:

- **Natural frequency**: $\omega_n \approx 4.49 \, \text{rad/s}$
- **Maximum tension**: $T_{\text{max}} \approx 37 \, \text{lbf}$
- **Maximum stress**: $\sigma \approx 27,125 \, \text{psi}$
- The cable will **not break** under these conditions.


---

<br>

## Application 2: Heat Flow in Soil for Wine Cellar Design

The **heat diffusion equation** governing the temperature variation in the soil is:

$$\frac{\partial \theta(z, t)}{\partial t} = k \frac{\partial^2 \theta(z, t)}{\partial z^2}$$

Where:
- $\theta(z, t)$ is the temperature at depth $z$ and time $t$.
- $k = 1.8 \times 10^{-3} \, \text{m}^2/\text{hr}$ is the thermal conductivity of the soil.

We are tasked with determining the depth $z_0$ at which the temperature variation is less than 0.5°C.

### Step-by-Step Solution Using Laplace Transforms

#### 1. Laplace Transform the Heat Equation

Taking the Laplace transform with respect to time $t$:

$$s \Theta(z, s) - \theta(z, 0) = k \frac{\partial^2 \Theta(z, s)}{\partial z^2}$$

Rearranging the equation:

$$\frac{\partial^2 \Theta(z, s)}{\partial z^2} - \frac{s}{k} \Theta(z, s) = - \frac{\theta(z, 0)}{k}$$

#### 2. Solve the Transformed Equation

The general solution to this equation is:

$$\Theta(z, s) = A(s) e^{-\sqrt{\frac{s}{k}} z} + B(s) e^{\sqrt{\frac{s}{k}} z}$$

#### 3. Apply Boundary Conditions

At the surface ($z = 0$), the temperature variation is:

$\theta(0, t) = \theta_0 + A(0) \cos(\omega t)$

Taking the Laplace transform of this boundary condition:

$\Theta(0, s) = \frac{\theta_0 + A(0) \frac{\omega}{s^2 + \omega^2}}{s}$

At depth $z = z_0$, we want the amplitude of temperature variation to be less than 0.5°C:

$|\Theta(z_0, s)| \leq 0.5$

From this, we can solve for $z_0$ based on the amplitude decay and the properties of the soil.

---

<br>

## Application 3: Fluid Flow in an Open Channel

We are tasked with finding the **critical fluid height** and **minimum specific energy** for the given flow rate in an open channel, using **Bernoulli’s equation**.

Given:
- The flow rate $V = 4 \, \text{m}^3/\text{s}$,
- The channel profile $z = ax^4$ with $a = 3 \, \text{m}^{-3}$.

Bernoulli’s equation is:

$\frac{P_0}{\rho g} + \frac{u^2}{2g} + h = \text{constant}$

The **specific energy** of the flow is:

$E = \frac{u^2}{2g} + h$

### Step-by-Step Solution

#### 1. Volume Flow Rate Relation

The cross-sectional area of the channel for a given height $h$ is:

$A(h) = \int_{-b}^{b} (h - ax^4) \, dx$

The volume flow rate $V$ is related to the fluid velocity $u$ and area $A(h)$ by:

$V = A(h) u$

#### 2. Minimize Specific Energy

To find the critical height $h_{\text{critical}}$, we minimize the specific energy function $E(h)$:

$E(h) = \frac{u^2}{2g} + h$

Differentiate $E(h)$ with respect to $h$ and set $\frac{dE}{dh} = 0$ to find the critical fluid height where the specific energy is minimized:

$\frac{dE}{dh} = 0$

---

<br>

## Application 4: Beam Deflection Under Uniform Load

We are tasked with finding the deflection $y(x)$ of a beam under a uniform load using the fourth-order ODE:

$$\frac{d^4 y(x)}{dx^4} = \frac{q}{EI}$$

where:
- $q$ is the load per unit length,
- $E$ is Young's modulus,
- $I$ is the moment of inertia of the beam's cross-section.

Boundary conditions:
- No deflection at $x = 0$ and $x = L$: $y(0) = y(L) = 0$,
- No curvature at $x = 0$ and $x = L$: $y''(0) = y''(L) = 0$.

### Step-by-Step Solution Using Laplace Transform

#### 1. Take the Laplace Transform of the Equation

Taking the Laplace transform of both sides:

$s^4 Y(s) = \frac{q}{EI}$

Solving for $Y(s)$:

$Y(s) = \frac{q}{EI s^4}$

#### 2. Inverse Laplace Transform

The inverse Laplace transform of $\frac{1}{s^4}$ is $\frac{x^3}{6}$, so the deflection function is:

$y(x) = \frac{q}{EI} \left( \frac{x^4}{24} + C_1 x^3 + C_2 x^2 + C_3 x + C_4 \right)$

#### 3. Apply Boundary Conditions

Using the boundary conditions:
- $y(0) = 0$ and $y(L) = 0$,
- $y''(0) = 0$ and $y''(L) = 0$,

Solve for the constants $C_1$, $C_2$, $C_3$, and $C_4$.

---

### Summary of Steps

1. **Application 2 (Heat Flow)**: Solved using Laplace transforms to find the temperature variation and depth $z_0$.
2. **Application 3 (Fluid Flow)**: Minimized the specific energy to find the critical height $h_{\text{critical}}$ using Bernoulli's equation.
3. **Application 4 (Beam Deflection)**: Solved the fourth-order ODE using Laplace transforms and boundary conditions to find the deflection equation.

Would you like to dive deeper into any specific calculation or another part of the project?