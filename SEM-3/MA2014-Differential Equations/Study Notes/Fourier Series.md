Related : #math #DIfferentialEquations #FourierSeries

Reference Note : [Chapter 2](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Note%5CChapters%5CMA2014%20Chapter%202%20(extended).pdf)
Reference Video :  [Week 4](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Video%5CWeek%204.mp4), [week 5](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Video%5Cweek%205.mp4) 
Online Resources : [Fourier Series(MIT OCW)](https://ocw.mit.edu/courses/18-03sc-differential-equations-fall-2011/pages/unit-iii-fourier-series-and-laplace-transform/fourier-series-basics/), [Fourier MIT Lectures](https://ocw.mit.edu/courses/res-18-009-learn-differential-equations-up-close-with-gilbert-strang-and-cleve-moler-fall-2015/pages/differential-equations-and-linear-algebra/fourier-and-laplace-transforms/)

---
# Content

## Introduction

> [!video]- Intro
> <iframe width="680" height="385" src="https://www.youtube.com/embed/vA9dfINW4Rg?si=2issH-d6sBcEZxxj" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

### 1. Introduction to Fourier Series
- The goal of Fourier series is to express a function as a sum of cosine and sine terms, which are called basis functions.
- Each term in the Fourier series is multiplied by coefficients, $a_n$ for cosines and $b_n$ for sines, which determine how much of each sine or cosine contributes to the overall function.
- The Fourier series of a function $f(x)$ is expressed as:
  $$f(x) = \frac{a_0}{2} + \sum_{n=1}^{\infty} \left( a_n \cos(nx) + b_n \sin(nx) \right)$$
- There is no $b_0$ term because $\sin(0) = 0$, making it irrelevant for $n = 0$.

### 2. Complex Form of Fourier Series
- The more elegant form involves complex exponentials, using $e^{inx}$, with coefficients $c_n$.
- The series goes from $n = -\infty$ to $n = \infty$ and simplifies the formulas.
- Euler’s formula, $e^{inx} = \cos(nx) + i\sin(nx)$, connects the real and complex forms of the Fourier series.

### 3. Orthogonality in Fourier Series
- **Key Concept:** Orthogonality, which means perpendicularity in the context of vectors, extends to functions. If the dot product (or inner product) of two vectors is zero, they are orthogonal.
- For Fourier series, orthogonality refers to the integral of the product of two different basis functions being zero:
  $$\int_{-\pi}^{\pi} \cos(mx) \cos(nx) \, dx = 0 \quad \text{for} \, m \neq n$$
  Similarly, sine functions are orthogonal to cosine functions:
  $$
  \int_{-\pi}^{\pi} \sin(mx) \cos(nx) \, dx = 0
   $$
- This orthogonality property allows us to isolate individual coefficients from the series.

### 4. Finding the Fourier Coefficients
- To compute the Fourier coefficients, multiply the function $f(x)$ by a basis function (either cosine or sine), integrate from $-\pi$ to $\pi$, and apply orthogonality to eliminate other terms.
  - **For cosine coefficients $a_n$**:
    $$
    a_n = \frac{1}{\pi} \int_{-\pi}^{\pi} f(x) \cos(nx) \, dx
    $$
  - **For sine coefficients $b_n$**:
    $$
    b_n = \frac{1}{\pi} \int_{-\pi}^{\pi} f(x) \sin(nx) \, dx
    $$
  - **For $a_0$** (the constant term):
    $$
    a_0 = \frac{1}{2\pi} \int_{-\pi}^{\pi} f(x) \, dx
    $$
    This represents the average value of $f(x)$ over the interval.

### 5. Example: Delta Function
- The delta function $\delta(x)$ is a highly singular function that spikes at $x = 0$ and is zero elsewhere.
- The delta function is an **even function**, meaning that all the sine coefficients $b_n$ are zero (since sine functions are odd).
- **Fourier Series for the Delta Function**:
  - All cosine coefficients $a_n$ for the delta function are constant:
    $$
    a_n = \frac{1}{\pi}
    $$
  - The series for the delta function between $-\pi$ and $\pi$ is:
    $$
    \delta(x) = \frac{1}{2\pi} + \frac{1}{\pi} \left( \cos(x) + \cos(2x) + \cos(3x) + \dots \right)
    $$
  - This result shows that the delta function contains all harmonics in equal amounts, without decay.

### 6. Key Points Recap
- **Orthogonality** is essential for isolating Fourier coefficients.
- The **Fourier coefficients** $a_n$ and $b_n$ are calculated using integrals.
- The delta function example highlights how Fourier series capture the essence of a function by decomposing it into pure frequencies.

---

These notes encapsulate the fundamental concepts of Fourier series, including orthogonality, coefficient computation, and an illustrative example with the delta function.