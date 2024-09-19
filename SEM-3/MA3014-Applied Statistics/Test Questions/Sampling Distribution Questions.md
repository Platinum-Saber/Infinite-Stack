
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
