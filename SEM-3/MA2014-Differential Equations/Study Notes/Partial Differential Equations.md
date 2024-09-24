---
tags:
  - math
  - PartialDifferentialEquations
Reviewed: 
Created: 2024-09-24T14:30:00
About:
---
Related : #PartialDifferentialEquations 
Reference Notes :
Reference Video :

---
# Content
- [[#1. Definition of Partial Differential Equations]]
- [[#2. Classification of PDEs]]
	- [[#2.1 By Order]]
	- [[#2.2 By Linearity]]
	- [[#2.3 By Homogeneity]]
	- [[#2.4 Classification of Second-Order Linear PDEs]]
- [[#3. Techniques for Solving PDEs]]
	- [[#3.1 Direct Integration]]
	- [[#3.2 Separation of Variables]]
- [[#4. Important PDEs and Their Solutions]]
	- [[#4.1 Laplace Equation]]
	- [[#4.2 Heat Equation (One-dimensional)]]
	- [[#4.3 Wave Equation (One-dimensional)]]
- [[#5. Example Problems]]



# Partial Differential Equations 

## 1. Definition of Partial Differential Equations

A partial differential equation (PDE) is a differential equation that involves partial derivatives of one or more dependent variables with respect to one or more independent variables.

General form of a PDE:

$f(x, y, u, u_x, u_y, u_{xx}, u_{xy}, u_{yy}, ...) = 0$

where $u = u(x, y)$ is the solution.

## 2. Classification of PDEs

### 2.1 By Order

The order of a PDE is the same as that of the highest differential coefficient in it.

### 2.2 By Linearity

- **Linear PDE**: If the dependent variable and all its partial derivatives occur linearly.
- **Non-linear PDE**: If any term is non-linear in the dependent variable or its derivatives.
- **Quasi-linear PDE**: If all the terms with highest order derivatives of dependent variables occur linearly.

### 2.3 By Homogeneity

- **Homogeneous PDE**: If all terms contain the dependent variable or its partial derivatives.
- **Non-homogeneous PDE**: If at least one term does not contain the dependent variable or its derivatives.

### 2.4 Classification of Second-Order Linear PDEs

For a general second-order linear PDE:

$Au_{xx} + Bu_{xy} + Cu_{yy} + Du_x + Eu_y + Fu + G = 0$

The classification is based on the discriminant $B^2 - 4AC$:

1. **Elliptic**: If $B^2 - 4AC < 0$
2. **Hyperbolic**: If $B^2 - 4AC > 0$
3. **Parabolic**: If $B^2 - 4AC = 0$

## 3. Techniques for Solving PDEs

### 3.1 Direct Integration

Simple PDEs can be solved by direct partial integration.

### 3.2 Separation of Variables

This method assumes a solution of the form $u(x, y) = X(x)Y(y)$ and transforms the PDE into two ordinary differential equations (ODEs).

#### Steps:
1. Assume $u(x, y) = X(x)Y(y)$
2. Substitute into the PDE
3. Separate variables
4. Solve resulting ODEs
5. Apply boundary conditions

## 4. Important PDEs and Their Solutions

### 4.1 Laplace Equation

$\frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} = 0$

#### Solution in Rectangular Coordinates:

$u(x, y) = \sum_{n=1}^{\infty} A_n \sin(\frac{n\pi x}{a}) \sinh(\frac{n\pi y}{a})$

where $A_n$ are constants determined by boundary conditions.

#### Solution in Polar Coordinates:

$T(r, \theta) = \sum_{n=1}^{\infty} A_n r^n \sin(n\theta)$

### 4.2 Heat Equation (One-dimensional)

$\frac{\partial^2 u}{\partial x^2} = \frac{1}{k}\frac{\partial u}{\partial t}$

#### Solution:

$u(x, t) = \sum_{r=1}^{\infty} B_r \sin(\frac{r\pi x}{l}) e^{-\frac{r^2 \pi^2 kt}{l^2}}$

where $B_r = \frac{2}{l} \int_0^l f(x) \sin(\frac{r\pi x}{l}) dx$

### 4.3 Wave Equation (One-dimensional)

$\frac{\partial^2 y}{\partial t^2} = c^2 \frac{\partial^2 y}{\partial x^2}$

#### Solution:

$y(x, t) = \sum_{n=1}^{\infty} A_n \sin(\frac{n\pi x}{L}) \cos(\frac{n\pi ct}{L})$

where $A_n = \frac{2}{L} \int_0^L f(x) \sin(\frac{n\pi x}{L}) dx$

<br

## 5. Example Problems

### Problem 1: Classification of PDEs

> [!faq] Classify the following PDEs:
> 
> a) $u_{xx} - 7u_{xy} + 6u_{yy} = 0$
> b) $u_{xx} + u_{xy} - 6u_{yy} = 0$
> c) $4u_{xx} - 4u_{xy} + u_{yy} = 0$
> d) $2u_{xx} + 3u_{yy} = 0$
> e) $2u_{xy} + 3u_{yy} = 0$

> [!math]- Solutions:
> 
> a) $B^2 - 4AC = (-7)^2 - 4(1)(6) = 25 > 0$, so it's hyperbolic.
> b) $B^2 - 4AC = 1^2 - 4(1)(-6) = 25 > 0$, so it's hyperbolic.
> c) $B^2 - 4AC = (-4)^2 - 4(4)(1) = 0$, so it's parabolic.
> d) $B^2 - 4AC = 0^2 - 4(2)(3) = -24 < 0$, so it's elliptic.
> e) $B^2 - 4AC = 2^2 - 4(0)(3) = 4 > 0$, so it's hyperbolic.

### Problem 2: Solving a PDE by Direct Integration

> [!faq]  Solve the equation 
> $\frac{\partial^2 u}{\partial x^2} = 24x^2(t - 2)$, given that at $x = 0$, $u = e^{2t}$ and $\frac{\partial u}{\partial x} = 4t$.

> [!math]- Solution:
> 
> Integrating twice with respect to $x$:
> 
> $\frac{\partial u}{\partial x} = 8x^3(t - 2) + f(t)$
> 
> $u = 2x^4(t - 2) + f(t)x + g(t)$
> 
> Using the boundary conditions:
> 
> At $x = 0$: $u = g(t) = e^{2t}$
> 
> At $x = 0$: $\frac{\partial u}{\partial x} = f(t) = 4t$
> 
> Therefore, the solution is:
> 
> $u = 2x^4(t - 2) + 4tx + e^{2t}$
> 

### Problem 3: Solving Laplace's Equation in Rectangular Coordinates

> [!faq] A rectangular plate with insulated surfaces is 50 cm wide and infinitely long. The temperature along one short edge $y = 0$ is given by $u(x, 0) = 80$, $0 < x < 50$, while the two long edges $x = 0$ and $x = 50$, as well as the other edge, are kept at $0°C$. Find the steady-state temperature $u(x, y)$.

> [!math]- Solution:
> 
> We need to solve the Laplace equation:
> 
> $\frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} = 0$
> 
> with boundary conditions:
> 
> - $u(0, y) = u(50, y) = 0$ for all $y \geq 0$
> - $u(x, 0) = 80$ for $0 < x < 50$
> - $u(x, y) \to 0$ as $y \to \infty$
> 
> Using separation of variables, we get the general solution:
> 
> $u(x, y) = \sum_{n=1}^{\infty} A_n \sin(\frac{n\pi x}{50}) e^{-\frac{n\pi y}{50}}$
> 
> Applying the boundary condition at $y = 0$:
> 
> $80 = \sum_{n=1}^{\infty} A_n \sin(\frac{n\pi x}{50})$
> 
> This is a Fourier sine series, so:
> 
> $A_n = \frac{160}{n\pi} [1 - (-1)^n]$
> 
> Therefore, the final solution is:
> 
> $u(x, y) = \sum_{n=1, n \text{ odd}}^{\infty} \frac{320}{n\pi} \sin(\frac{n\pi x}{50}) e^{-\frac{n\pi y}{50}}$
> 
> This series converges rapidly, so the first few terms provide a good approximation of the temperature distribution.

