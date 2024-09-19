
## Question 01
- A population has a mean of 50 and a standard deviation of 6. 
	- (a) What are the mean and standard deviation of the sampling distribution of the mean for N = 16?
	-  (b) What are the mean and standard deviation of the sampling distribution of the mean for N = 20?

> [!math]- Answer
> ### Given:
> - Population Mean ($\mu$) = 50
> - Population Standard Deviation ($\sigma$) = 6
> 
> ### a. Mean and Standard Deviation of the Sampling Distribution of the Mean for \(N = 16\)
> 
> 1. **Mean of the Sampling Distribution**:
>    The mean of the sampling distribution of the mean is the same as the population mean:
>    $$
>    \mu_{\bar{X}} = \mu = 50
>    $$
> 
> 2. **Standard Deviation of the Sampling Distribution (Standard Error)**:
>    The standard deviation of the sampling distribution (also called the standard error) is given by:
>    $$
>    \sigma_{\bar{X}} = \frac{\sigma}{\sqrt{N}} = \frac{6}{\sqrt{16}} = \frac{6}{4} = 1.5
>    $$
> 
> ### Summary for \(N = 16\):
> - Mean: **50**
> - Standard Deviation: **1.5**
> 
> ---
> 
> ### b. Mean and Standard Deviation of the Sampling Distribution of the Mean for \(N = 20\)
> 
> 1. **Mean of the Sampling Distribution**:
>    The mean remains the same:
>    $$
>    \mu_{\bar{X}} = \mu = 50
>    $$
> 
> 2. **Standard Deviation of the Sampling Distribution (Standard Error)**:
>    For \(N = 20\):
>    $$
>    \sigma_{\bar{X}} = \frac{\sigma}{\sqrt{N}} = \frac{6}{\sqrt{20}} \approx \frac{6}{4.472} \approx 1.342
>    $$
> 
> ### Summary for \(N = 20\):
> - Mean: **50**
> - Standard Deviation: **1.342**

## Question 02
- A questionnaire is developed to assess women’s and men’s attitudes toward using animals in research. One question asks whether animal research is wrong and is answered on a 7-point scale. Assume that in the population, the mean for women is 5, the mean for men is 4, and the standard deviation for both groups is 1.5. Assume the scores are normally distributed. If 12 women and 12 men are selected randomly, what is the probability that the mean of the women will be more than 2 points higher than the mean of the men?

> [!math]- Answer
> ### Given:
> - Mean for women ($\mu_W$) = 5
> - Mean for men ($\mu_M$) = 4
> - Standard deviation for both groups ($\sigma$) = 1.5
> - Sample size for women ($N_W$) = 12
> - Sample size for men ($N_M$) = 12
> 
> ### Step 1: Define the Difference in Means
> 
> We are interested in the probability that:
> 
> $$
> \bar{X}_W - \bar{X}_M > 2
> $$
> 
> Where:
> - $\bar{X}_W$ = mean score of women
> - $\bar{X}_M$ = mean score of men
> 
> ### Step 2: Calculate the Mean and Standard Deviation of the Difference of Means
> 
> 1. **Mean of the Difference**:
>    The mean of the difference in means is:
> 
>    $$
>    \mu_{\bar{X}_W - \bar{X}_M} = \mu_W - \mu_M = 5 - 4 = 1
>    $$
> 
> 2. **Standard Deviation of the Difference**:
>    The standard deviation of the difference in means (assuming independence) is:
> 
>    $$
>    \sigma_{\bar{X}_W - \bar{X}_M} = \sqrt{\frac{\sigma^2}{N_W} + \frac{\sigma^2}{N_M}} = \sqrt{\frac{1.5^2}{12} + \frac{1.5^2}{12}} = \sqrt{2 \cdot \frac{2.25}{12}} = \sqrt{\frac{4.5}{12}} = \sqrt{0.375} \approx 0.6124
>    $$
> 
> ### Step 3: Standardize the Difference
> 
> We want to find the probability that:
> 
> $$
> \bar{X}_W - \bar{X}_M > 2
> $$
> 
> This can be rewritten in terms of the z-score:
> 
> $$
> P(\bar{X}_W - \bar{X}_M > 2) = P\left(Z > \frac{2 - 1}{0.6124}\right) = P(Z > \frac{1}{0.6124}) \approx P(Z > 1.632)
> $$
> 
> ### Step 4: Find the Probability from the Z-Table
> 
> Using a z-table or calculator, we find the cumulative probability for \(Z = 1.632\):
> 
> $$
> P(Z < 1.632) \approx 0.9484
> $$
> 
> Thus,
> 
> $$
> P(Z > 1.632) = 1 - P(Z < 1.632) \approx 1 - 0.9484 = 0.0516
> $$
> 
> ### Summary
> 
> The probability that the mean score of the women will be more than 2 points higher than the mean score of the men is approximately **0.0516** or **5.16%**.
> 

## Question 03
-  A normal distribution has a mean of 20 and a standard deviation of 10. Two scores are sampled randomly from the distribution and the second score is subtracted from the first. What is the probability that the difference score will be greater than 5?

> [!math]- Answer
> ### Given:
> - Mean $\mu$ = 20
> - Standard deviation (\(\sigma\)) = 10
> 
> ### Step 1: Define the Difference of Two Scores
> 
> Let $X_1$ and $X_2$ be the two scores sampled from the distribution. We are interested in the difference:
> 
> $$
> D = X_1 - X_2
> $$
> 
> ### Step 2: Calculate the Mean and Standard Deviation of the Difference
> 
> 1. **Mean of the Difference**:
>    The mean of the difference \(D\) is given by:
> 
>    $$
>    \mu_D = \mu_{X_1} - \mu_{X_2} = \mu - \mu = 20 - 20 = 0
>    $$
> 
> 2. **Standard Deviation of the Difference**:
>    The standard deviation of the difference is calculated using the formula for the standard deviation of the difference of two independent random variables:
> 
>    $$
>    \sigma_D = \sqrt{\sigma_{X_1}^2 + \sigma_{X_2}^2} = \sqrt{10^2 + 10^2} = \sqrt{100 + 100} = \sqrt{200} = 10\sqrt{2} \approx 14.14
>    $$
> 
> ### Step 3: Standardize the Difference
> 
> We want to find the probability that:
> 
> $$
> D > 5
> $$
> 
> We can standardize this using the z-score formula:
> 
> $$
> P(D > 5) = P\left(Z > \frac{5 - \mu_D}{\sigma_D}\right) = P\left(Z > \frac{5 - 0}{10\sqrt{2}}\right) = P\left(Z > \frac{5}{14.14}\right) \approx P(Z > 0.3536)
> $$
> 
> ### Step 4: Find the Probability from the Z-Table
> 
> Using a z-table or calculator, we find the cumulative probability for \(Z = 0.3536\):
> 
> $$
> P(Z < 0.3536) \approx 0.6384
> $$
> 
> Thus,
> 
> $$
> P(Z > 0.3536) = 1 - P(Z < 0.3536) \approx 1 - 0.6384 = 0.3616
> $$
> 
> ### Summary
> 
> The probability that the difference score $D = X_1 - X_2$ will be greater than 5 is approximately **0.3616** or **36.16%**.
