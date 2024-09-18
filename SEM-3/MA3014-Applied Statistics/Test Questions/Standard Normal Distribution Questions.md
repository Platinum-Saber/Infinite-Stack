

## Question 01
- If scores are normally distributed with a mean of 35 and a standard deviation of 10, what percent of the scores is: 
	- a. greater than 34? 
	- b. smaller than 42? 
	- c. between 28 and 34?

> [!math]- Answer
> ### Given:
> - Mean ($\mu$) = 35
> - Standard deviation ($\sigma$) = 10
> 
> ### Z-score formula:
> $$
> z = \frac{(X - \mu)}{\sigma}
> $$
> 
> ### a. Percent of scores greater than 34
> 
> 1. **Calculate the z-score** for $X = 34$:
>    $$
>    z = \frac{(34 - 35)}{10} = \frac{-1}{10} = -0.1
>    $$
> 
> 2. **Find the cumulative probability** for $z = -0.1$ (approximately):
>    $$
>    P(Z < -0.1) \approx 0.4602
>    $$
> 
> 3. **Calculate the percentage greater than 34**:
>    $$
>    P(X > 34) = 1 - P(Z < -0.1) = 1 - 0.4602 = 0.5398
>    $$
>    - Thus, approximately **53.98%** of the scores are greater than 34.
> 
> ### b. Percent of scores smaller than 42
> 
> 1. **Calculate the z-score** for $X = 42$:
>    $$
>    z = \frac{(42 - 35)}{10} = \frac{7}{10} = 0.7
>    $$
> 
> 2. **Find the cumulative probability** for $z = 0.7$ (approximately):
>    $$
>    P(Z < 0.7) \approx 0.7580
>    $$
> 
> 3. **Calculate the percentage smaller than 42**:
>    $$
>    P(X < 42) \approx 0.7580
>    $$
>    - Thus, approximately **75.80%** of the scores are smaller than 42.
> 
> ### c. Percent of scores between 28 and 34
> 
> 1. **Calculate the z-scores**:
>    - For $X = 28$:
>    $$
>    z = \frac{(28 - 35)}{10} = \frac{-7}{10} = -0.7
>    $$
>    - For $X = 34$ (already calculated):
>    $$
>    z = -0.1
>    $$
> 
> 2. **Find the cumulative probabilities**:
>    - For $z = -0.7$:
>    $$
>    P(Z < -0.7) \approx 0.2420
>    $$
>    - For $z = -0.1$:
>    $$
>    P(Z < -0.1) \approx 0.4602
>    $$
> 
> 3. **Calculate the percentage between 28 and 34**:
>    $$
>    P(28 < X < 34) = P(Z < -0.1) - P(Z < -0.7) = 0.4602 - 0.2420 = 0.2182
>    $$
>    - Thus, approximately **21.82%** of the scores are between 28 and 34.
> 
> ### Summary:
> - a. Greater than 34: **53.98%**
> - b. Smaller than 42: **75.80%**
> - c. Between 28 and 34: **21.82%**


## Question 02
- What are the mean and standard deviation of the standard normal distribution? 
	- (b) What would be the mean and standard deviation of a distribution created by multiplying the standard normal distribution by 8 and then adding 75?

> [!math]- Answer
> ### a. Mean and Standard Deviation of the Standard Normal Distribution
> 
> The standard normal distribution has:
> 
> - **Mean** ($\mu$):
>   $$
>   \mu = 0
>   $$
> - **Standard Deviation** ($\sigma$):
>   $$
>   \sigma = 1
>   $$
> 
> ### b. Mean and Standard Deviation of the Transformed Distribution
> 
> When transforming a standard normal distribution using the formula:
> 
> $$
> Y = aX + b
> $$
> 
> where:
> - \( a = 8 \) (scaling factor),
> - \( b = 75 \) (shifting factor),
> 
> the mean and standard deviation are given by:
> 
> 1. **Mean of the transformed distribution**:
>    $$
>    \mu_Y = a \mu_X + b
>    $$
> 
> 2. **Standard deviation of the transformed distribution**:
>    $$
>    \sigma_Y = |a| \sigma_X
>    $$
> 
> #### Applying this to your transformation:
> 
> - For the standard normal distribution:
>   - $\ ( \mu_X = 0 \ )$
>   - $\ ( \sigma_X = 1 \ )$
> 
> **Calculating the mean**:
> $$
> \mu_Y = 8 \cdot 0 + 75 = 75
> $$
> 
> **Calculating the standard deviation**:
> $$
> \sigma_Y = |8| \cdot 1 = 8
> $$
> 
> ### Summary:
> - The mean of the transformed distribution is $\mu_Y = 75$.
> - The standard deviation of the transformed distribution is $\sigma_Y = 8$.


## Question 03
- What proportion of a normal distribution is within one standard deviation of the mean? 
	- (b) What proportion is more than 2.0 standard deviations from the mean? 
	- (c) What proportion is between 1.25 and 2.1 standard deviations above the mean?

> [!math]- Answer
> ### a. Proportion of a Normal Distribution Within One Standard Deviation of the Mean
> 
> For a normal distribution, approximately **68%** of the data falls within one standard deviation of the mean. This can be expressed as:
> 
> $$
> P(\mu - \sigma < X < \mu + \sigma) \approx 0.68
> $$
> 
> ### b. Proportion More Than 2.0 Standard Deviations from the Mean
> 
> To find the proportion of the distribution that is more than 2.0 standard deviations from the mean, we look at both tails of the distribution:
> 
> - Approximately **95%** of the data falls within 2 standard deviations:
> 
> $$
> P(\mu - 2\sigma < X < \mu + 2\sigma) \approx 0.95
> $$
> 
> Thus, the proportion more than 2 standard deviations from the mean is:
> 
> $$
> P(X < \mu - 2\sigma) + P(X > \mu + 2\sigma) \approx 1 - 0.95 = 0.05
> $$
> 
> So, approximately **5%** of the data is more than 2.0 standard deviations from the mean.
> 
> ### c. Proportion Between 1.25 and 2.1 Standard Deviations Above the Mean
> 
> To find this proportion, we need to calculate the cumulative probabilities for \(z = 1.25\) and \(z = 2.1\):
> 
> 1. **Cumulative probability for \(z = 1.25\)**:
>    $$
>    P(Z < 1.25) \approx 0.8944
>    $$
> 
> 2. **Cumulative probability for \(z = 2.1\)**:
>    $$
>    P(Z < 2.1) \approx 0.9821
>    $$
> 
> Now, the proportion between \(z = 1.25\) and \(z = 2.1\) is:
> 
> $$
> P(1.25 < Z < 2.1) = P(Z < 2.1) - P(Z < 1.25) \approx 0.9821 - 0.8944 = 0.0877
> $$
> 
> ### Summary:
> - a. Proportion within one standard deviation: **68%**
> - b. Proportion more than 2.0 standard deviations from the mean: **5%**
> - c. Proportion between 1.25 and 2.1 standard deviations above the mean: **8.77%**


## Question 04
- A test is normally distributed with a mean of 70 and a standard deviation of 8. 
	- (a) What score would be needed to be in the 85th percentile? 
	- (b) What score would be needed to be in the 22nd percentile?

> [!math]- Answer
> 
> ### Given:
> - Mean ($\mu$) = 70
> - Standard deviation ($\sigma$) = 8
> 
> ### a. Score Needed to be in the 85th Percentile
> 
> To find the score corresponding to the 85th percentile, we first need to find the z-score that corresponds to the 85th percentile.
> 
> Using a z-table or calculator, we find:
> 
> $$
> P(Z < z) = 0.85 \implies z \approx 1.036
> $$
> 
> Now we can use the z-score formula to find the raw score ($X$):
> 
> $$
> z = \frac{(X - \mu)}{\sigma}
> $$
> 
> Rearranging gives:
> 
> $$
> X = z \cdot \sigma + \mu
> $$
> 
> Substituting the values:
> 
> $$
> X = (1.036 \cdot 8) + 70 \approx 8.288 + 70 \approx 78.29
> $$
> 
> Thus, the score needed to be in the **85th percentile** is approximately **78.29**.
> 
> ### b. Score Needed to be in the 22nd Percentile
> 
> Similarly, for the 22nd percentile, we find the z-score:
> 
> $$
> P(Z < z) = 0.22 \implies z \approx -0.774
> $$
> 
> Now we can use the z-score formula again:
> 
> $$
> X = z \cdot \sigma + \mu
> $$
> 
> Substituting the values:
> 
> $$
> X = (-0.774 \cdot 8) + 70 \approx -6.192 + 70 \approx 63.81
> $$
> 
> Thus, the score needed to be in the **22nd percentile** is approximately **63.81**.
> 
> ### Summary:
> - a. Score for the 85th percentile: **78.29**
> - b. Score for the 22nd percentile: **63.81**
> 

## Question 05
- Assume a normal distribution with a mean of 70 and a standard deviation of 12. What limits would include the middle 65% of the cases?

> [!math]- Answer
> ### Given:
> - Mean ($\mu$) = 70
> - Standard deviation ($\sigma$) = 12
> 
> ### Finding Limits for the Middle 65% of the Cases
> 
> To find the limits that include the middle 65% of the cases in a normal distribution, we need to determine the z-scores that correspond to the lower and upper bounds of the middle 65%.
> 
> 1. **Calculate the area in each tail**:
>    Since we want the middle 65%, the total area in the tails is:
>    $$
>    1 - 0.65 = 0.35
>    $$
>    This area is split between the two tails, so each tail has:
>    $$
>    \frac{0.35}{2} = 0.175
>    $$
> 
> 2. **Find the z-scores corresponding to the cumulative probabilities**:
>    - For the lower limit:
>      $$
>      P(Z < z) = 0.175 \implies z \approx -0.93
>      $$
> 
>    - For the upper limit:
>      $$
>      P(Z < z) = 0.825 \implies z \approx 0.93
>      $$
> 
> 3. **Convert the z-scores back to raw scores** using the formula:
>    $$
>    X = z \cdot \sigma + \mu
>    $$
> 
>    - For the lower limit ($z \approx -0.954$):
>      $$
>      X_{lower} = -0.93 \cdot 12 + 70 \approx -11.16 + 70 \approx 58.8
>      $$
> 
>    - For the upper limit ($z \approx 0.954$):
>      $$
>      X_{upper} = 0.93 \cdot 12 + 70 \approx 11.448 + 70 \approx 81.2
>      $$
> 
> ### Summary:
> The limits that include the middle 65% of the cases are approximately:
> 
> - **Lower Limit**: **58.8**
> - **Upper Limit**: **81.2**



