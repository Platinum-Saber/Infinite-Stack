---
tags:
  - math
  - FourierSeries
Reviewed: 
Created: 2024-09-24T14:28:00
About:
---

Related : #math #DIfferentialEquations #FourierSeries

Reference Note : [Chapter 2](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Note%5CChapters%5CMA2014%20Chapter%202%20(extended).pdf)
Reference Video :  [Week 4](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Video%5CWeek%204.mp4), [week 5](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Video%5Cweek%205.mp4) 
Online Resources : [Fourier Series(MIT OCW)](https://ocw.mit.edu/courses/18-03sc-differential-equations-fall-2011/pages/unit-iii-fourier-series-and-laplace-transform/fourier-series-basics/), [Fourier MIT Lectures](https://ocw.mit.edu/courses/res-18-009-learn-differential-equations-up-close-with-gilbert-strang-and-cleve-moler-fall-2015/pages/differential-equations-and-linear-algebra/fourier-and-laplace-transforms/)

---
# Content
- [[#1. Introduction]]
	- [[#1. Introduction to Fourier Series]]
	- [[#2. Complex Form of Fourier Series]]
	- [[#3. Orthogonality in Fourier Series]]
	- [[#4. Finding the Fourier Coefficients]]
	- [[#5. Example Delta Function]]
- [[#2. Solving Questions Using Fourier Series]]
	- [[#1. Odd Functions and Fourier Series]]
	- [[#2. Even Functions and Fourier Series]]
	- [[#3. Key Concepts and Observations]]
	- [[#4. Derivatives and Fourier Series]]
	- [[#5. Shifts and Fourier Series]]
	- [[#6. Summary]]

## 1. Introduction

> [!video]- Intro
> <iframe width="680" height="385" src="https://www.youtube.com/embed/vA9dfINW4Rg?si=2issH-d6sBcEZxxj" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

### 1. Introduction to Fourier Series
- The goal of Fourier series is to express a function as a sum of cosine and sine terms, which are called basis functions.
- Each term in the Fourier series is multiplied by coefficients, $a_n$ for cosines and $b_n$ for sines, which determine how much of each sine or cosine contributes to the overall function.

> [!equation]- The Fourier series of a function $f(x)$ is expressed as:
>   $$f(x) = \frac{a_0}{2} + \sum_{n=1}^{\infty} \left( a_n \cos(nx) + b_n \sin(nx) \right)$$
> - There is no $b_0$ term because $\sin(0) = 0$, making it irrelevant for $n = 0$.

### 2. Complex Form of Fourier Series
- The more elegant form involves complex exponentials, using $e^{inx}$, with coefficients $c_n$.
- The series goes from $n = -\infty$ to $n = \infty$ and simplifies the formulas.
- Euler’s formula, $e^{inx} = \cos(nx) + i\sin(nx)$, connects the real and complex forms of the Fourier series.

### 3. Orthogonality in Fourier Series
- **Key Concept:** Orthogonality, which means perpendicularity in the context of vectors, extends to functions. If the dot product (or inner product) of two vectors is zero, they are orthogonal.

> [!equation]- Orthogonality
> - For Fourier series, orthogonality refers to the integral of the product of two different basis functions being zero:
>   $$\int_{-\pi}^{\pi} \cos(mx) \cos(nx) \, dx = 0 \quad \text{for} \, m \neq n$$
>   Similarly, sine functions are orthogonal to cosine functions:
>   $$
>   \int_{-\pi}^{\pi} \sin(mx) \cos(nx) \, dx = 0
>    $$
>- This orthogonality property allows us to isolate individual coefficients from the series.

### 4. Finding the Fourier Coefficients
- To compute the Fourier coefficients, multiply the function $f(x)$ by a basis function (either cosine or sine), integrate from $-\pi$ to $\pi$, and apply orthogonality to eliminate other terms.

> [!math]- Determining Coefficient 
>   - **For cosine coefficients $a_n$**:
>     $$
>     a_n = \frac{1}{\pi} \int_{-\pi}^{\pi} f(x) \cos(nx) \, dx
>     $$
>   - **For sine coefficients $b_n$**:
>     $$
>     b_n = \frac{1}{\pi} \int_{-\pi}^{\pi} f(x) \sin(nx) \, dx
>     $$
>   - **For $a_0$** (the constant term):
>     $$
>     a_0 = \frac{1}{2\pi} \int_{-\pi}^{\pi} f(x) \, dx
>     $$
>     This represents the average value of $f(x)$ over the interval.

### 5. Example: Delta Function
- The delta function $\delta(x)$ is a highly singular function that spikes at $x = 0$ and is zero elsewhere.
- The delta function is an **even function**, meaning that all the sine coefficients $b_n$ are zero (since sine functions are odd).

> [!math]- Fourier Series for the Delta Function:
>   - All cosine coefficients $a_n$ for the delta function are constant:
>     $$
>     a_n = \frac{1}{\pi}
>     $$
>   - The series for the delta function between $-\pi$ and $\pi$ is:
>     $$
>     \delta(x) = \frac{1}{2\pi} + \frac{1}{\pi} \left( \cos(x) + \cos(2x) + \cos(3x) + \dots \right)
>     $$
>   - This result shows that the delta function contains all harmonics in equal amounts, without decay.


## 2. Solving Questions Using Fourier Series

> [!video]- Example Questions
> <iframe width="680" height="385" src="https://www.youtube.com/embed/lL0oUZGMhXc?si=oMnike7bpEJKQntB" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

### 1. Odd Functions and Fourier Series

- **Odd function**: A function is odd if $f(-x) = -f(x)$. 
- **Sine functions** are odd, while **cosine functions** are even.
- For an odd function, all cosine terms in the Fourier series vanish. Thus, only sine terms (with $b_k$ coefficients) remain in the series expansion.

#### Example: Square Wave
- Consider a square wave, alternating between $-1$ and $1$, which is an odd function.
- The Fourier series for such a function involves sine waves only.

#### Fourier Coefficients for Sine Terms:
The formula for the sine coefficients $b_k$ is given by:

$$
b_k = \frac{2}{\pi} \int_0^\pi \sin(kx) \, dx
$$

The integrals are computed over half the period, from $0$ to $\pi$, and doubled due to symmetry.

#### Calculation of $b_k$:
For $k = 1, 3, 5, \dots$, we get non-zero terms, while for $k = 2, 4, 6, \dots$, the coefficients are zero.

##### First few coefficients:
- $b_1 = \frac{4}{\pi}$
- $b_2 = 0$
- $b_3 = \frac{4}{3\pi}$
- $b_4 = 0$
- $b_5 = \frac{4}{5\pi}$

#### Fourier Series for the Square Wave:
$$
f(x) = \frac{4}{\pi} \left( \sin(x) + \frac{1}{3} \sin(3x) + \frac{1}{5} \sin(5x) + \dots \right)
$$

This series contains only odd harmonics (1st, 3rd, 5th, etc.), and the coefficients decrease slowly because the function has jumps (i.e., it is not smooth).

---

### 2. Even Functions and Fourier Series

- **Even function**: A function is even if $f(-x) = f(x)$. 
- For an even function, only cosine terms appear in the Fourier series, and all sine terms vanish.

#### Example: Ramp Function
- A ramp function is obtained by integrating the square wave. This function is even and has smoother transitions (no jumps).
- For this ramp function, we compute the cosine coefficients $a_k$ instead of the sine coefficients.

#### Fourier Series for the Ramp Function:
By integrating the square wave's Fourier series, we get:

$$
f(x) = \frac{\pi}{2} - \cos(x) - \frac{\cos(3x)}{9} - \frac{\cos(5x)}{25} - \dots
$$

This series contains only even harmonics, and the coefficients decay faster (proportional to $k^2$) because the ramp function is smoother than the square wave.

---

### 3. Key Concepts and Observations

- **Smoother functions** lead to faster decay of Fourier coefficients. For instance, the ramp function (which is smooth) has coefficients that decay faster than those of the square wave (which has jumps).
  
- **Fourier coefficients decay more slowly** for rough functions (like the square wave) and more rapidly for smooth functions (like the ramp).

---

### 4. Derivatives and Fourier Series

> [!equation] Derivative of a Fourier Series 
>   If $f(x)$ has a Fourier series $f(x) = \sum c_k e^{ikx}$, then the derivative of $f(x)$ has a Fourier series:
> 
>   $$
>   \frac{df}{dx} = \sum ik c_k e^{ikx}
>   $$
> 

  The derivative introduces a factor of $ik$, making the coefficients larger (indicating more high-frequency components, which correspond to "noisier" functions).

---

### 5. Shifts and Fourier Series

- **Shifted Function**: 
  For a shifted function $f(x - d)$, the Fourier coefficients are modified by a phase factor:

  $$
  f(x - d) = \sum c_k e^{ik(x - d)} = \sum c_k e^{ikx} e^{-ikd}
  $$

  The magnitude of the Fourier coefficients remains unchanged, but their phase is shifted by $e^{-ikd}$.

---

### 6. Summary

- Fourier series are powerful tools for representing periodic functions as sums of sine and cosine waves.
- The **smoothness** of the function directly affects how fast the Fourier coefficients decay.
- **Derivatives** and **shifts** in the function have simple rules in the Fourier domain, making Fourier series particularly useful for solving differential equations and other mathematical problems.

<br>

## 3. Solving Laplace's Equation using Fourier Series

> [!video]- Solving Laplace's Eq. using Fourier
> <iframe width="680" height="385" src="https://www.youtube.com/embed/WWphCZkdByA?si=dGjrMfmcbcVeABI4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

### Laplace's Equation
Laplace's equation in Cartesian coordinates:

$$\frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} = 0$$

This equation describes how temperature distributes itself in equilibrium.

### Problem Setup
- Domain: Inside a circle
- Boundary condition: Point source (delta function) at one point, temperature 0 elsewhere
- Goal: Solve Laplace's equation inside the circle

### Solution Approach
1. Use polar coordinates (r, θ) due to circular domain
2. General solution form:
   $$u(r,\theta) = \sum_{n=0}^{\infty} (a_n r^n \cos(n\theta) + b_n r^n \sin(n\theta))$$

3. Apply boundary condition at r = 1:
   $$u(1,\theta) = \sum_{n=0}^{\infty} (a_n \cos(n\theta) + b_n \sin(n\theta)) = \delta(\theta)$$

4. Find coefficients using Fourier series properties:
   - $a_0 = \frac{1}{2\pi}$ (average temperature)
   - $a_n = \frac{1}{\pi}$ for n ≥ 1
   - $b_n = 0$ (delta function is even)

5. Final solution:
   $$u(r,\theta) = \frac{1}{2\pi} + \frac{1}{\pi} \sum_{n=1}^{\infty} r^n \cos(n\theta)$$

### Closed-form Solution
The series can be summed to obtain a closed-form solution:

$$u(r,\theta) = \frac{1}{2\pi} \frac{1-r^2}{1+r^2-2r\cos\theta}$$

### Solution Properties
1. On the boundary (r = 1, θ = 0): Solution approaches infinity
2. At the center (r = 0): Temperature is 1/(2π), the average boundary value
3. Temperature smooths out towards the center
4. Solution always stays between the maximum and minimum boundary values

### Numerical Approximation
For complex domains, Laplace's equation is often solved numerically using the five-point scheme:

$$u_0 = \frac{1}{4}(u_E + u_W + u_N + u_S)$$

where $u_0$ is the value at a grid point, and $u_E$, $u_W$, $u_N$, $u_S$ are the values at the adjacent east, west, north, and south points respectively.

This discretization leads to a system of linear equations that can be solved to approximate the solution of Laplace's equation.