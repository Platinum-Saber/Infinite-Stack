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
- [[#Inverse Laplace Transform]]


# Laplace Transformations Study Note

## Introduction

The **Laplace Transform** is a powerful integral transform used to convert a function of time, $f(t)$, into a function of a complex variable, $s$, simplifying the analysis of linear time-invariant systems.

The **Laplace Transform** of a function $f(t)$ is defined as:

$$
\mathcal{L}\{f(t)\} = F(s) = \int_0^{\infty} e^{-st} f(t) \, dt
$$

where $s$ is a complex variable, $s = \sigma + j\omega$.

<br>

## Theorems and Properties of Laplace Transform

### 1. Linearity Theorem
If $f(t)$ and $g(t)$ are functions with known Laplace Transforms, then:

$$
\mathcal{L}\{af(t) + bg(t)\} = a\mathcal{L}\{f(t)\} + b\mathcal{L}\{g(t)\}
$$

#### Proof:
The Laplace transform of a linear combination of two functions $f(t)$ and $g(t)$:

$$
\mathcal{L}\{af(t) + bg(t)\} = \int_0^{\infty} e^{-st} (af(t) + bg(t)) \, dt
$$

Using the properties of integrals:

$$
= a \int_0^{\infty} e^{-st} f(t) \, dt + b \int_0^{\infty} e^{-st} g(t) \, dt
$$

$$
= a\mathcal{L}\{f(t)\} + b\mathcal{L}\{g(t)\}
$$

### 2. First Shifting Theorem (Time Shifting)
If $\mathcal{L}\{f(t)\} = F(s)$, then:

$$
\mathcal{L}\{f(t - a) u(t - a)\} = e^{-as} F(s)
$$

where $u(t - a)$ is the unit step function.

#### Proof:
By the definition of the Laplace transform:

$$
\mathcal{L}\{f(t - a) u(t - a)\} = \int_a^{\infty} e^{-st} f(t - a) \, dt
$$

Substitute $t' = t - a$ so that $dt = dt'$:

$$
= \int_0^{\infty} e^{-s(t' + a)} f(t') \, dt'
$$

$$
= e^{-as} \int_0^{\infty} e^{-st'} f(t') \, dt'
$$

$$
= e^{-as} F(s)
$$

### 3. Second Shifting Theorem (Frequency Shifting)
If $\mathcal{L}\{f(t)\} = F(s)$, then:

$$
\mathcal{L}\{e^{at}f(t)\} = F(s - a)
$$

#### Proof:
Consider the Laplace transform of $e^{at}f(t)$:

$$
\mathcal{L}\{e^{at}f(t)\} = \int_0^{\infty} e^{-st} e^{at} f(t) \, dt
$$

$$
= \int_0^{\infty} e^{-(s - a)t} f(t) \, dt
$$

$$
= F(s - a)
$$

### 4. Differentiation Theorem
If $\mathcal{L}\{f(t)\} = F(s)$, then:

$$
\mathcal{L}\left\{ \frac{d}{dt} f(t) \right\} = sF(s) - f(0)
$$

#### Proof:
Start with the Laplace transform definition:

$$
\mathcal{L}\left\{ \frac{d}{dt} f(t) \right\} = \int_0^{\infty} e^{-st} \frac{d}{dt} f(t) \, dt
$$

Using integration by parts:

$$
= \left[ e^{-st} f(t) \right]_0^{\infty} + s \int_0^{\infty} e^{-st} f(t) \, dt
$$

The first term vanishes because $f(t)$ and $e^{-st}$ tend to zero as $t \to \infty$, so:

$$
= - f(0) + sF(s)
$$

Thus:

$$
\mathcal{L}\left\{ \frac{d}{dt} f(t) \right\} = sF(s) - f(0)
$$

<br>

## Common Laplace Transforms

- $\mathcal{L}\{1\} = \frac{1}{s}, \, s > 0$
- $\mathcal{L}\{t^n\} = \frac{n!}{s^{n+1}}, \, s > 0$
- $\mathcal{L}\{e^{at}\} = \frac{1}{s - a}, \, s > a$
- $\mathcal{L}\{\sin(at)\} = \frac{a}{s^2 + a^2}, \, s > 0$
- $\mathcal{L}\{\cos(at)\} = \frac{s}{s^2 + a^2}, \, s > 0$

<br>

## Inverse Laplace Transform

The **Inverse Laplace Transform** is used to find $f(t)$ from $F(s)$. It is defined as:

$$
\mathcal{L}^{-1}\{F(s)\} = f(t)
$$

### Example:

Given $F(s) = \frac{1}{s^2 + 1}$, find $f(t)$.

Using the known inverse Laplace transform of $\sin(at)$:

$$
\mathcal{L}^{-1}\left\{ \frac{1}{s^2 + 1} \right\} = \sin(t)
$$

Thus, $f(t) = \sin(t)$.

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
