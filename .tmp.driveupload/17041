---
tags:
  - math
  - Laplace
  - DIfferentialEquations
Reviewed: 
Created: 2024-09-24T14:27:00
About:
---
Related : #math #DIfferentialEquations #Laplace 

Reference Note : [Chapter 1](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Note%5CChapters%5CMA2014%20Chapter%201%20(updated).pdf)
Reference Video : [Week 2](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Video%5CWeek%202.mp4), [Week 3](file:///E:%5CAcademics%5CSEM%203%5CMA2014-Differential%20Equations%5CLecture%20Video%5CWeek%203%20Lecture.mp4)
Online Resources : [Khan Academy - Laplace Transformations](https://www.khanacademy.org/math/differential-equations/laplace-transform)


---
# Content
- [[#Introduction]]
- [[#Theorems and Properties of Laplace Transform]]
	- [[#1. Linearity Theorem]]
	- [[#2. First Shifting Theorem (Time Shifting)]]
	- [[#3. Second Shifting Theorem (Frequency Shifting)]]
	- [[#4. Differentiation Theorem]]
- [[#Common Laplace Transforms]]
	- [[#Basic Functions]]
	- [[#Trigonometric Functions]]
	- [[#Hyperbolic Functions]]
	- [[#Inverse Trigonometric Functions]]
	- [[#Inverse Hyperbolic Functions]]
	- [[#Special Functions]]
- [[#Inverse Laplace Transform]]
- [[#Example Questions with Answers]]


# Laplace Transformations

## Introduction

The **Laplace Transform** is a powerful integral transform used to convert a function of time, $f(t)$, into a function of a complex variable, $s$, simplifying the analysis of linear time-invariant systems.

> [!equation] The **Laplace Transform** of a function $f(t)$ is defined as:
> 
> $$
> \mathcal{L}\{f(t)\} = F(s) = \int_0^{\infty} e^{-st} f(t) \, dt
> $$
> 
> where $s$ is a complex variable, $s = \sigma + j\omega$.

<br>

## Theorems and Properties of Laplace Transform

### 1. Linearity Theorem
If $f(t)$ and $g(t)$ are functions with known Laplace Transforms, then:

$$
\mathcal{L}\{af(t) + bg(t)\} = a\mathcal{L}\{f(t)\} + b\mathcal{L}\{g(t)\}
$$

> [!math]- Proof:
> The Laplace transform of a linear combination of two functions $f(t)$ and $g(t)$:
> 
> $$
> \mathcal{L}\{af(t) + bg(t)\} = \int_0^{\infty} e^{-st} (af(t) + bg(t)) \, dt
> $$
> 
> Using the properties of integrals:
> 
> $$
> = a \int_0^{\infty} e^{-st} f(t) \, dt + b \int_0^{\infty} e^{-st} g(t) \, dt
> $$
> 
> $$
> = a\mathcal{L}\{f(t)\} + b\mathcal{L}\{g(t)\}
> $$
> 

### 2. First Shifting Theorem (Time Shifting)
If $\mathcal{L}\{f(t)\} = F(s)$, then:

$$
\mathcal{L}\{f(t - a) u(t - a)\} = e^{-as} F(s)
$$

where $u(t - a)$ is the unit step function.

> [!math]- Proof:
> By the definition of the Laplace transform:
> 
> $$
> \mathcal{L}\{f(t - a) u(t - a)\} = \int_a^{\infty} e^{-st} f(t - a) \, dt
> $$
> 
> Substitute $t' = t - a$ so that $dt = dt'$:
> 
> $$
> = \int_0^{\infty} e^{-s(t' + a)} f(t') \, dt'
> $$
> 
> $$
> = e^{-as} \int_0^{\infty} e^{-st'} f(t') \, dt'
> $$
> 
> $$
> = e^{-as} F(s)
> $$
> 

### 3. Second Shifting Theorem (Frequency Shifting)
If $\mathcal{L}\{f(t)\} = F(s)$, then:

$$
\mathcal{L}\{e^{at}f(t)\} = F(s - a)
$$

> [!math]- Proof:
> Consider the Laplace transform of $e^{at}f(t)$:
> 
> $$
> \mathcal{L}\{e^{at}f(t)\} = \int_0^{\infty} e^{-st} e^{at} f(t) \, dt
> $$
> 
> $$
> = \int_0^{\infty} e^{-(s - a)t} f(t) \, dt
> $$
> 
> $$
> = F(s - a)
> $$
> 

### 4. Differentiation Theorem
If $\mathcal{L}\{f(t)\} = F(s)$, then:

$$
\mathcal{L}\left\{ \frac{d}{dt} f(t) \right\} = sF(s) - f(0)
$$

> [!math]- Proof:
> Start with the Laplace transform definition:
> 
> $$
> \mathcal{L}\left\{ \frac{d}{dt} f(t) \right\} = \int_0^{\infty} e^{-st} \frac{d}{dt} f(t) \, dt
> $$
> 
> Using integration by parts:
> 
> $$
> = \left[ e^{-st} f(t) \right]_0^{\infty} + s \int_0^{\infty} e^{-st} f(t) \, dt
> $$
> 
> The first term vanishes because $f(t)$ and $e^{-st}$ tend to zero as $t \to \infty$, so:
> 
> $$
> = - f(0) + sF(s)
> $$
> 
> Thus:
> 
> $$
> \mathcal{L}\left\{ \frac{d}{dt} f(t) \right\} = sF(s) - f(0)
> $$
> 
> <br>

<br>

## Common Laplace Transforms

### Basic Functions
- $\mathcal{L}\{1\} = \frac{1}{s}, \, s > 0$
- $\mathcal{L}\{t^n\} = \frac{n!}{s^{n+1}}, \, s > 0$
- $\mathcal{L}\{e^{at}\} = \frac{1}{s - a}, \, s > a$

### Trigonometric Functions
- $\mathcal{L}\{\sin(at)\} = \frac{a}{s^2 + a^2}, \, s > 0$
- $\mathcal{L}\{\cos(at)\} = \frac{s}{s^2 + a^2}, \, s > 0$
- $\mathcal{L}\{\tan(at)\} = \frac{a}{s^2 - a^2}, \, s > |a|$
- $\mathcal{L}\{\sec(at)\} = \frac{s}{s^2 - a^2}, \, s > |a|$
- $\mathcal{L}\{\csc(at)\} = \frac{1}{s} - \frac{s}{s^2 + a^2}, \, s > 0$
- $\mathcal{L}\{\cot(at)\} = \frac{s}{s^2 + a^2}, \, s > 0$

### Hyperbolic Functions
- $\mathcal{L}\{\sinh(at)\} = \frac{a}{s^2 - a^2}, \, s > |a|$
- $\mathcal{L}\{\cosh(at)\} = \frac{s}{s^2 - a^2}, \, s > |a|$
- $\mathcal{L}\{\tanh(at)\} = \frac{a}{s^2 - a^2} \ln(\frac{s+a}{s-a}), \, s > |a|$
- $\mathcal{L}\{\text{sech}(at)\} = \frac{\pi}{2a} \text{sech}(\frac{\pi s}{2a}), \, s > 0$
- $\mathcal{L}\{\text{csch}(at)\} = \frac{1}{a} \ln(\frac{s+a}{s-a}), \, s > |a|$
- $\mathcal{L}\{\text{coth}(at)\} = \frac{1}{a} \ln(\frac{s+a}{s-a}), \, s > |a|$

### Inverse Trigonometric Functions
- $\mathcal{L}\{\arcsin(t)\} = \frac{\pi}{2s} - \frac{1}{s^2} \arcsin(\frac{1}{s}), \, s > 1$
- $\mathcal{L}\{\arccos(t)\} = \frac{1}{s^2} \arccos(\frac{1}{s}), \, s > 1$
- $\mathcal{L}\{\arctan(t)\} = \frac{1}{s} \arctan(\frac{1}{s}), \, s > 0$
- $\mathcal{L}\{\text{arcsec}(t)\} = \frac{1}{s} \ln(s + \sqrt{s^2 - 1}), \, s > 1$
- $\mathcal{L}\{\text{arccsc}(t)\} = \frac{1}{s} \ln(\frac{s + \sqrt{s^2 + 1}}{s}), \, s > 0$
- $\mathcal{L}\{\text{arccot}(t)\} = \frac{1}{s} \arctan(\frac{1}{s}), \, s > 0$

### Inverse Hyperbolic Functions
- $\mathcal{L}\{\text{arcsinh}(t)\} = \frac{1}{s^2} \text{arcsinh}(s), \, s > 0$
- $\mathcal{L}\{\text{arccosh}(t)\} = \frac{1}{s^2} \text{arccosh}(s), \, s > 1$
- $\mathcal{L}\{\text{arctanh}(t)\} = \frac{1}{s} \ln(\frac{s+1}{s-1}), \, s > 1$
- $\mathcal{L}\{\text{arcsech}(t)\} = \frac{1}{s} \ln(\frac{s + \sqrt{s^2 + 1}}{s}), \, s > 0$
- $\mathcal{L}\{\text{arccsch}(t)\} = \frac{1}{s} \ln(\frac{s + \sqrt{s^2 + 1}}{s}), \, s > 0$
- $\mathcal{L}\{\text{arccoth}(t)\} = \frac{1}{s} \ln(\frac{s+1}{s-1}), \, s > 1$

### Special Functions
- $\mathcal{L}\{t^n e^{at}\} = \frac{n!}{(s-a)^{n+1}}, \, s > a$
- $\mathcal{L}\{e^{at} \sin(bt)\} = \frac{b}{(s-a)^2 + b^2}, \, s > a$
- $\mathcal{L}\{e^{at} \cos(bt)\} = \frac{s-a}{(s-a)^2 + b^2}, \, s > a$
- $\mathcal{L}\{t \sin(at)\} = \frac{2as}{(s^2 + a^2)^2}, \, s > 0$
- $\mathcal{L}\{t \cos(at)\} = \frac{s^2 - a^2}{(s^2 + a^2)^2}, \, s > 0$

Remember that these transforms are valid under the specified conditions for $s$. In some cases, additional conditions may apply for the existence of the Laplace transform.

<br>

## Inverse Laplace Transform

The **Inverse Laplace Transform** is used to find $f(t)$ from $F(s)$. It is defined as:

$$
\mathcal{L}^{-1}\{F(s)\} = f(t)
$$

> [!equation]- Example:
> 
> Given $F(s) = \frac{1}{s^2 + 1}$, find $f(t)$.
> 
> Using the known inverse Laplace transform of $\sin(at)$:
> 
> $$
> \mathcal{L}^{-1}\left\{ \frac{1}{s^2 + 1} \right\} = \sin(t)
> $$
> 
> Thus, $f(t) = \sin(t)$.

Here’s a list of common **inverse Laplace transforms** related to **trigonometric functions** and their combinations, including expressions like $t \sin(at)$.

### **1. Basic Trigonometric Inverse Laplace Transforms**

- $\mathcal{L}^{-1} \left( \frac{s}{s^2 + a^2} \right) = \cos(at)$
  
- $\mathcal{L}^{-1} \left( \frac{a}{s^2 + a^2} \right) = \sin(at)$

### **2. Inverse Laplace Transforms Involving $t \sin(at)$ and $t \cos(at)$**

- $\mathcal{L}^{-1} \left( \frac{a}{(s^2 + a^2)^2} \right) = t \sin(at)$

- $\mathcal{L}^{-1} \left( \frac{s}{(s^2 + a^2)^2} \right) = t \cos(at)$

### **3. Inverse Laplace Transforms Involving Higher Powers of $t$**

- $\mathcal{L}^{-1} \left( \frac{2a}{(s^2 + a^2)^3} \right) = t^2 \sin(at)$

- $\mathcal{L}^{-1} \left( \frac{2s}{(s^2 + a^2)^3} \right) = t^2 \cos(at)$

### **4. Exponential and Trigonometric Functions**

- $\mathcal{L}^{-1} \left( \frac{s}{(s - b)^2 + a^2} \right) = e^{bt} \cos(at)$
  
- $\mathcal{L}^{-1} \left( \frac{a}{(s - b)^2 + a^2} \right) = e^{bt} \sin(at)$

### **5. Damped Sine and Cosine Functions**

- $\mathcal{L}^{-1} \left( \frac{s - b}{(s - b)^2 + a^2} \right) = e^{bt} \cos(at)$
  
- $\mathcal{L^{\text{-1}}} \left( \frac{a}{(s - b)^2 + a^2} \right) = e^{bt} \sin(at)$

### **6. Inverse Laplace Transforms of Hyperbolic Functions**

- $\mathcal{L}^{-1} \left( \frac{s}{s^2 - a^2} \right) = \cosh(at)$
  
- $\mathcal{L}^{-1} \left( \frac{a}{s^2 - a^2} \right) = \sinh(at)$

---

These transformations are widely used to solve **second-order differential equations** or analyze systems with periodic behavior, especially in **mechanics**, **electrical circuits**, and **control theory**. If you need more specific transformations or further clarification on how to apply them, feel free to ask!




## Example Questions with Answers

### Question 1:
Find the Laplace transform of $f(t) = t^2$.

#### Solution:
Using the Laplace transform of $t^n$:

$$
\mathcal{L}\{t^2\} = \frac{2!}{s^{2+1}} = \frac{2}{s^3}, \, s > 0
$$

### Question 2:
Find the Laplace transform of $f(t) = e^{3t} \cos(2t)$.

#### Solution:
Using the frequency shifting property and the known transform of $\cos(at)$:

$$
\mathcal{L}\{e^{3t} \cos(2t)\} = \frac{s - 3}{(s - 3)^2 + 2^2} = \frac{s - 3}{(s - 3)^2 + 4}, \, s > 3
$$

### Question 3:
Find the inverse Laplace transform of $F(s) = \frac{s}{s^2 + 9}$.

#### Solution:
Using the known inverse Laplace transform of $\cos(at)$:

$$
\mathcal{L}^{-1} \left\{ \frac{s}{s^2 + 9} \right\} = \cos(3t)
$$

Thus, $f(t) = \cos(3t)$.


---
Up Next : [[Fourier Series]]
