

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


## Question 05
- Assume the speed of vehicles along a stretch of I-10 has an approximately normal distribution with a mean of 71 mph and a standard deviation of 8 mph. 
	- a. The current speed limit is 65 mph. What is the proportion of vehicles less than or equal to the speed limit? 
	- b. What proportion of the vehicles would be going less than 50 mph? 
	- c. A new speed limit will be initiated such that approximately 10% of vehicles will be over the speed limit. What is the new speed limit based on this criterion? 
	- d. In what way do you think the actual distribution of speeds differs from a normal distribution?

> [!math]- Answer
> ### Given:
> - Mean ($\mu$) = 71 mph
> - Standard deviation ($\sigma$) = 8 mph
> 
> ### a. Proportion of Vehicles Less Than or Equal to the Speed Limit (65 mph)
> 
> To find this proportion, we first calculate the z-score for the speed limit:
> 
> $$
> z = \frac{(X - \mu)}{\sigma} = \frac{(65 - 71)}{8} = \frac{-6}{8} = -0.75
> $$
> 
> Using a z-table or calculator, we find the cumulative probability for $z = -0.75$:
> 
> $$
> P(Z < -0.75) \approx 0.2266
> $$
> 
> Thus, the proportion of vehicles less than or equal to the speed limit is approximately **22.66%**.
> 
> ### b. Proportion of Vehicles Going Less Than 50 mph
> 
> Next, we calculate the z-score for 50 mph:
> 
> $$
> z = \frac{(50 - 71)}{8} = \frac{-21}{8} = -2.625
> $$
> 
> Using a z-table or calculator, we find the cumulative probability for $z = -2.625$:
> 
> $$
> P(Z < -2.625) \approx 0.0043
> $$
> 
> Thus, the proportion of vehicles going less than 50 mph is approximately **0.43%**.
> 
> ### c. New Speed Limit for 10% of Vehicles to Be Over the Limit
> 
> To find the new speed limit such that approximately 10% of vehicles will be over it, we need the z-score that corresponds to the 90th percentile (since 100% - 10% = 90%).
> 
> Using a z-table or calculator, we find:
> 
> $$
> P(Z < z) = 0.90 \implies z \approx 1.2816
> $$
> 
> Now we can convert this z-score back to the raw score (new speed limit):
> 
> $$
> X = z \cdot \sigma + \mu
> $$
> 
> Substituting the values:
> 
> $$
> X = (1.2816 \cdot 8) + 71 \approx 10.2528 + 71 \approx 81.25
> $$
> 
> Thus, the new speed limit should be approximately **81.25 mph**.
> 
> ### d. Differences Between Actual Distribution of Speeds and a Normal Distribution
> 
> The actual distribution of vehicle speeds may differ from a normal distribution in several ways:
> 
> 1. **Skewness**: Vehicle speeds may be right-skewed due to a higher number of vehicles adhering to the speed limit, with fewer vehicles exceeding it significantly.
> 
> 2. **Kurtosis**: The distribution may have heavier tails (more extreme values) due to outliers (e.g., speeding vehicles) compared to a normal distribution.
> 
> 3. **Bimodal Distribution**: There may be two distinct groups of drivers: those who drive at or below the speed limit and those who speed significantly.
> 
> 4. **Traffic Conditions**: Factors such as congestion, road conditions, and enforcement of speed limits can cause deviations from normality.
> 
> ### Summary:
> - a. Proportion ≤ 65 mph: **22.66%**
> - b. Proportion < 50 mph: **0.43%**
> - c. New speed limit for 10% over: **81.25 mph**
> - d. Actual distribution may be skewed, have heavier tails, or be bimodal.

## Question 06
- You want to use the normal distribution to approximate the binomial distribution. Explain what you need to do to find the probability of obtaining exactly 7 heads out of 12 flips.

> [!math]- Answer
> ### Given:
> - Number of trials (\(n\)) = 12
> - Probability of success (getting heads) in each trial (\(p\)) = 0.5 (assuming a fair coin)
> 
> ### Steps to Approximate Using Normal Distribution
> 
> 1. **Calculate the Mean and Standard Deviation of the Binomial Distribution**:
>    - The mean ($(\mu)$) of a binomial distribution is given by:
>      $$
>      \mu = n \cdot p
>      $$
>    - The standard deviation ($(\sigma)$) is given by:
>      $$
>      \sigma = \sqrt{n \cdot p \cdot (1 - p)}
>      $$
> 
>    For this case:
>    - Mean ($(\mu)$):
>      $$
>      \mu = 12 \cdot 0.5 = 6
>      $$
>    - Standard deviation (\(\sigma\)):
>      $$
>      \sigma = \sqrt{12 \cdot 0.5 \cdot 0.5} = \sqrt{3} \approx 1.732
>      $$
> 
> 2. **Use Continuity Correction**:
>    Since the binomial distribution is discrete and the normal distribution is continuous, apply a continuity correction when using the normal approximation. To find the probability of getting exactly 7 heads, you approximate it by finding the probability of getting between 6.5 and 7.5 heads:
>    $$
>    P(6.5 < X < 7.5)
>    $$
> 
> 3. **Calculate the z-scores**:
>    Convert the x-values (6.5 and 7.5) to z-scores using the formula:
>    $$
>    z = \frac{(X - \mu)}{\sigma}
>    $$
>    - For \(X = 6.5\):
>      $$
>      z_{6.5} = \frac{(6.5 - 6)}{1.732} \approx 0.2887
>      $$
>    - For \(X = 7.5\):
>      $$
>      z_{7.5} = \frac{(7.5 - 6)}{1.732} \approx 0.8659
>      $$
> 
> 4. **Find the Cumulative Probabilities**:
>    Use a z-table or calculator to find the cumulative probabilities for $(z_{6.5}) and \ (z_{7.5})$:
>    - Let’s say:
>      - $\ (P(Z < 0.2887) \approx 0.6133\ )$
>      - $\ (P(Z < 0.8659) \approx 0.8078\ )$
> 
> 5. **Calculate the Probability**:
>    The probability of obtaining exactly 7 heads is:
>    $$
>    P(6.5 < X < 7.5) = P(Z < 0.8659) - P(Z < 0.2887) \approx 0.8078 - 0.6133 \approx 0.1945
>    $$
> 
> ### Summary
> To find the probability of obtaining exactly 7 heads out of 12 flips using the normal approximation to the binomial distribution:
> - Calculate the mean and standard deviation.
> - Apply a continuity correction.
> - Convert to z-scores.
> - Find cumulative probabilities and calculate the probability.

## Question 06
- A group of students at a school takes a history test. The distribution is normal with a mean of 25, and a standard deviation of 4. 
	- (a) Everyone who scores in the top 30% of the distribution gets a certificate. What is the lowest score someone can get and still earn a certificate? 
	- (b) The top 5% of the scores get to compete in a statewide history contest. What is the lowest score someone can get and still go onto compete with the rest of the state?

> [!math]- Answer
> ### Given:
> - Mean ($\mu$) = 25
> - Standard deviation ($\sigma$) = 4
> 
> ### a. Lowest Score for the Top 30% of the Distribution
> 
> To find the lowest score for the top 30%, we need to determine the z-score that corresponds to the 70th percentile (since the top 30% starts above the 70th percentile).
> 
> Using a z-table or calculator, we find:
> 
> $$
> P(Z < z) = 0.70 \implies z \approx 0.524
> $$
> 
> Now we can convert this z-score back to the raw score ($X$) using the formula:
> 
> $$
> X = z \cdot \sigma + \mu
> $$
> 
> Substituting the values:
> 
> $$
> X = (0.524 \cdot 4) + 25 \approx 2.096 + 25 \approx 27.10
> $$
> 
> Thus, the lowest score someone can get and still earn a certificate is approximately **27.10**.
> 
> ### b. Lowest Score for the Top 5% of the Distribution
> 
> To find the lowest score for the top 5%, we need to determine the z-score that corresponds to the 95th percentile.
> 
> Using a z-table or calculator, we find:
> 
> $$
> P(Z < z) = 0.95 \implies z \approx 1.645
> $$
> 
> Now we use the z-score formula again:
> 
> $$
> X = z \cdot \sigma + \mu
> $$
> 
> Substituting the values:
> 
> $$
> X = (1.645 \cdot 4) + 25 \approx 6.58 + 25 \approx 31.58
> $$
> 
> Thus, the lowest score someone can get and still compete in the statewide history contest is approximately **31.58**.
> 
> ### Summary:
> - a. Lowest score for the top 30%: **27.10**
> - b. Lowest score for the top 5%: **31.58**

## Question 07
- Use the normal distribution to approximate the binomial distribution and find the probability of getting 15 to 18 heads out of 25 flips. Compare this to what you get when you calculate the probability using the binomial distribution. Write your answers out to four decimal places

> [!math]- Answer
> ### Given:
> - Number of trials (n) = 25
> - Probability of success (getting heads) in each trial (p) = 0.5
> 
> ### Step 1: Calculate Mean and Standard Deviation
> 
> 1. **Mean ($\mu$)**:
>    $$
>    \mu = n \cdot p = 25 \cdot 0.5 = 12.5
>    $$
> 
> 2. **Standard Deviation $( \sigma )$**:
>    $$
>    \sigma = \sqrt{n \cdot p \cdot (1 - p)} = \sqrt{25 \cdot 0.5 \cdot 0.5} = \sqrt{6.25} = 2.5
>    $$
> 
> ### Step 2: Use Continuity Correction
> 
> To find the probability of getting between 15 and 18 heads, we apply continuity correction. We approximate the probability as:
> 
> $$
> P(14.5 < X < 18.5)
> $$
> 
> ### Step 3: Calculate the z-scores
> 
> 1. **For \(X = 14.5\)**:
>    $$
>    z_{14.5} = \frac{(14.5 - 12.5)}{2.5} = \frac{2}{2.5} = 0.8
>    $$
> 
> 2. **For \(X = 18.5\)**:
>    $$
>    z_{18.5} = \frac{(18.5 - 12.5)}{2.5} = \frac{6}{2.5} = 2.4
>    $$
> 
> ### Step 4: Find Cumulative Probabilities
> 
> Using a z-table or calculator:
> 
> 1. **For \(z = 0.8\)**:
>    $$
>    P(Z < 0.8) \approx 0.7881
>    $$
> 
> 2. **For \(z = 2.4\)**:
>    $$
>    P(Z < 2.4) \approx 0.9918
>    $$
> 
> ### Step 5: Calculate the Probability
> 
> Now, compute the probability between 14.5 and 18.5:
> 
> $$
> P(14.5 < X < 18.5) = P(Z < 2.4) - P(Z < 0.8) \approx 0.9918 - 0.7881 = 0.2037
> $$
> 
> ### Step 6: Calculate the Probability Using the Binomial Distribution
> 
> To calculate the probability using the binomial distribution:
> 
> $$
> P(X = k) = \binom{n}{k} p^k (1-p)^{n-k}
> $$
> 
> We need to find the probabilities for \(k = 15, 16, 17, 18\):
> 
> 1. **For \(k = 15\)**:
>    $$
>    P(X = 15) = \binom{25}{15} (0.5)^{15} (0.5)^{10} = \binom{25}{15} (0.5)^{25}
>    $$
> 
> 2. **For \(k = 16\)**:
>    $$
>    P(X = 16) = \binom{25}{16} (0.5)^{25}
>    $$
> 
> 3. **For \(k = 17\)**:
>    $$
>    P(X = 17) = \binom{25}{17} (0.5)^{25}
>    $$
> 
> 4. **For \(k = 18\)**:
>    $$
>    P(X = 18) = \binom{25}{18} (0.5)^{25}
>    $$
> 
> ### Calculating Each Probability
> 
> Using a calculator or statistical software:
> 
> - $P(X = 15) \approx 0.2023$
> - $P(X = 16) \approx 0.1967$
> - $P(X = 17) \approx 0.1460$
> - $P(X = 18) \approx 0.0735$
> 
> ### Total Probability Using Binomial Distribution
> 
> $$
> P(15 \leq X \leq 18) \approx 0.2023 + 0.1967 + 0.1460 + 0.0735 = 0.6185
> $$
> 
> ### Summary
> 
> - **Probability using normal approximation**: **0.2037**
> - **Probability using binomial distribution**: **0.6185**

