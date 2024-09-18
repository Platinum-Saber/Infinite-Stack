---
tags: 
Reviewed: 
Created: 
About:
---
Related : #math #statistics #CLT #t-distribution #chi-square #f-distribution
# Content



## 1. Introduction to Sampling Distributions

A sampling distribution is the probability distribution of a statistic (such as the mean, proportion, or standard deviation) calculated from all possible samples of a given size drawn from a population.

### Factors Affecting Variability of a Sampling Distribution:
- $N$: Number of observations in the population
- $n$: Number of observations in the sample
- Method used to select samples at random

> [!NOTE]- If $N$ is much larger than $n$, the sampling distribution has roughly the same sampling error, regardless of whether sampling is done with or without replacement.

<br>

## 2. The Central Limit Theorem (CLT)

The CLT states that the probability distribution of any statistic will be normal or nearly normal if the sample size is "large enough."

**Rule of thumb**: A sample size of 30 is often considered "large enough."

> [!summary]- Other considerations for "large enough" sample size:
> - Population distribution is normal
> - Sampling distribution is symmetric, unimodal, without outliers, and sample size ≤ 15
> - Sampling distribution is moderately skewed, unimodal, without outliers, and 16 ≤ sample size ≤ 40
> - Sample size > 40, without outliers

<br>

## 3. Sampling Distribution of the Mean

For a sample mean $\bar{x}$ from a population with mean $\mu$ and standard deviation $\sigma$ :
### $$\bar{x} \sim N(\mu_{\bar{x}}, \sigma^2_{\bar{x}})$$
Where:
- $\mu_{\bar{x}} = \mu$
- $\sigma_{\bar{x}} = \frac{\sigma}{\sqrt{n}}$

Therefore:
- $\bar{x} \sim N(\mu, \frac{\sigma^2}{n})$

> [!summary]- Apply conditions:
> 1. The population is normally distributed, or the sample size is sufficiently large
> 2. The population standard deviation $\sigma$ is known

> [!equation]- Example:
> Let's say we have a population with $\mu = 50$ and $\sigma = 10$. If we take samples of size $n = 25$, the sampling distribution of the mean would be:
> 
> $\bar{x} \sim N(50, \frac{10^2}{25}) = N(50, 4)$
> 
> This means the sampling distribution of the mean has a mean of 50 and a standard deviation of 2.

<br>

## 4. Sampling Distribution of the Proportion

For a sample proportion $p$ from a population with proportion $P$ of successes and $Q = 1-P$ of failures:
### $$p \sim N(\mu_p, \sigma^2_p)$$
Where:
- $\mu_p = P$
- $\sigma_p = \sqrt{\frac{PQ}{n}}$

Therefore:
- $p \sim N(P, \frac{PQ}{n})$

> [!NOTE] This applies when the sample size is sufficiently large and the population probability of success $(P)$ is known.

> [!equation]- Example:
> A biased coin has a probability $P = 0.4$ of heads. In 1000 tosses, what is the probability that the number of heads exceeds 410?
> 
> **Solution**:
> Let $X$ be the number of heads in 1000 tosses.
> $X \sim B(1000, 0.4)$, which can be approximated by $N(400, 240)$
> 
> We want $P(X > 410)$:
> 
> $P(X > 410) = P(Z > \frac{410.5 - 400}{\sqrt{240}}) = P(Z > 0.68)$
> 
> Using a standard normal table, we find:
> $P(Z > 0.68) \approx 0.2483$ or about 24.83%

<br>

## 5. Student's t-Distribution

The t-distribution is used when the `population standard deviation` is **unknown** and must be estimated from the sample. It is determined by its degrees of freedom (df).

For a sample of size $n$ from a normal population with **unknown mean** $\mu$ and **unknown standard deviation** $\sigma$ :
### $$t = \frac{\bar{x} - \mu}{s/\sqrt{n}}$$
This statistic follows a `t-distribution` with $n-1$ `degrees of freedom`.

> [!summary]- Properties of the t-Distribution:
> - Mean = 0
> - Variance = $\frac{v}{v-2}$, where $v$ is the degrees of freedom and $v > 2$
> - As df increases, the t-distribution approaches the standard normal distribution

> [!equation]- Example:
> A sample of 12 observations from a normal population with mean 48 produced $\bar{x} = 47.1$ and $s^2 = 4.7$. Find the probability of getting a sample of the same size with its mean less than or equal to the population mean.
> 
> Solution:
> We need to find $P(\bar{x} \leq 48)$
> 
> $t = \frac{47.1 - 48}{\sqrt{4.7}/\sqrt{12}} = -1.44$
> 
> With 11 df, using a t-table, we find:
> $P(t \leq -1.44) \approx 0.0885$ or about 8.85%

<br>

## 6. Chi-square Distribution

The chi-square statistic for a sample of size $n$ from a normal population with known variance $\sigma^2$ is:
### $$\chi^2 = \frac{(n-1)s^2}{\sigma^2}$$
This statistic follows a `chi-square distribution` with $n-1$ `degrees of freedom`.

> [!summary]- Properties of the Chi-square Distribution:
> - Mean = $v$ (degrees of freedom)
> - Variance = $2v$
> - As df increases, the distribution approaches a normal distribution

> [!equation]- Example:
> A cell phone battery lasts 60 minutes on average with a standard deviation of 5 minutes. A quality control test selects 10 batteries randomly, finding a sample standard deviation of 6 minutes. What is the probability that the standard deviation of any sample of size 10 would be greater than 6 minutes?
> 
> Solution:
> $\chi^2 = \frac{(10-1)(6^2)}{5^2} = 12.96$
> 
> Using a chi-square table with 9 df, we find:
> $P(\chi^2 > 12.96) \approx 0.1643$ or about 16.43%

<br>

## 7. F-Distribution

The F-distribution is the ratio of two chi-square distributions divided by their respective degrees of freedom:
#### $$f(v_1, v_2) = \frac{\chi^2_1/v_1}{\chi^2_2/v_2}$$

Where $v_1 = n_1 - 1$ and $v_2 = n_2 - 1$ are the degrees of freedom.

> [!summary]- Properties of the F-distribution:
> - Mean = $\frac{v_2}{v_2 - 2}$ for $v_2 > 2$
> - Variance = $\frac{2v_2^2(v_1 + v_2 - 2)}{v_1(v_2 - 2)^2(v_2 - 4)}$ for $v_2 > 4$

> [!equation]- Example:
> A sample of 11 cows has a population standard deviation of 5 kg and a sample standard deviation of 4.5 kg. Another sample of 7 bulls has a population standard deviation of 3.5 kg and a sample standard deviation of 4 kg. Compute the F-statistic.
> 
> Solution:
> $f = \frac{(4.5^2/5^2)}{(4^2/3.5^2)} = 0.6125$
> 
> Using an F-table with $v_1 = 10$ and $v_2 = 6$ degrees of freedom, we can find the associated cumulative probability.

