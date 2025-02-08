Here's a step-by-step solution and explanation for each question in the exam paper:

---

### Question 1

#### Part A
1. **Sampling Distribution of Sample Proportions**  
   - For men ($ p_1 = 0.40, n_1 = 500 $):
     - The sample proportion follows an approximate normal distribution:  
       $\hat{p}_1 \sim N\left(0.40, \sqrt{\frac{0.40 \times (1 - 0.40)}{500}}\right)$.
   - For women ($p_2 = 0.25, n_2 = 400$):
     - The sample proportion follows an approximate normal distribution:  
       $\hat{p}_2 \sim N\left(0.25, \sqrt{\frac{0.25 \times (1 - 0.25)}{400}}\right)$.

2. **95% Confidence Interval for Difference in Population Proportions**  
   - The confidence interval formula for $ p_1 - p_2 $ is:
     $$
     (\hat{p}_1 - \hat{p}_2) \pm z \cdot \sqrt{\frac{\hat{p}_1 (1 - \hat{p}_1)}{n_1} + \frac{\hat{p}_2 (1 - \hat{p}_2)}{n_2}}
     $$
   - Substitute values to get the interval.

3. **Interpretation**  
   - The confidence interval represents the range in which the difference in proportions is likely to lie, with 95% confidence.

#### Part B
- **Hypothesis Testing for Difference in Proportions**  
  - Null hypothesis: $ H_0: p_1 - p_2 = 0.15 $.
  - Alternative hypothesis: $ H_1: p_1 - p_2 \neq 0.15 $.
  - Calculate the test statistic and compare with the critical value at 5% significance level.

---

### Question 2

#### Part A
1. **Percentage of Marketable Disk Packs**  
   - Use Poisson distribution to find the probability of having 0 or 1 defect in an 800 cm² area.
   
2. **Average and Variance of Time Between Interrupts**  
   - Given 150 interrupts per 10 ms, calculate the average and variance for time between interrupts as the reciprocal of the rate.

#### Part B
1. **90% Confidence Interval for Population Variance**  
   - Use the Chi-square distribution to construct the confidence interval for variance based on sample data.
   
2. **Regression Model Fit Test**  
   - Hypothesis: The model fits well if the variance due to regression is significant compared to the error variance.
   - Use an F-test with the provided Mean Square values.

---

### Question 3

#### Part A
1. **Sampling Plan**  
   - Suggest a stratified random sampling plan, taking into account representation from all 3 intakes and 5 disciplines.

2. **Association Test**  
   - Perform a chi-square test of independence to check if the preference for mode of delivery is associated with the field of study.

#### Part B
- **SGPA Comparison Between Groups**  
  - Use a t-test or non-parametric test to compare mean SGPA between groups, assuming independence and normality or similar assumptions based on sample data.

---

### Question 4

#### Part A
1. **Treatments and Replicates**  
   - Identify treatments (types of stress relief activities) and calculate replicates.

2. **Statistical Model**  
   - Define a suitable model for the performance score, including factors for stress relief type, project type, and time interval.

3. **Hypothesis Test**  
   - Use ANOVA to test if there's a significant difference in performance scores across different activities.

#### Part B
- **Regression Model Assumptions and Interpretation**  
  - List two assumptions (e.g., linearity, independence of errors).
  - Interpret the coefficient for $X_3$ as the change in the outcome per unit increase in $X_3$.
  - Discuss $R^2$ as a measure of model fit.

---

Here's a detailed solution and explanation for each question based on the typical methods used to solve these types of problems. I'll go through the questions and provide explanations, calculations, and reasoning.

---

### Question 1

#### Part A: Sampling Distribution and Confidence Interval for Difference in Population Proportions

1. **Sampling Distribution of Sample Proportions**

   For men:
   - Given: $p_1 = 0.40$ and $n_1 = 500$.
   - The sample proportion $ \hat{p}_1 $ follows an approximate normal distribution:
     $$
     \hat{p}_1 \sim N\left(0.40, \sqrt{\frac{0.40 \times (1 - 0.40)}{500}}\right)
     $$
   - Calculate the standard error:
     $$
     \text{SE}_1 = \sqrt{\frac{0.40 \times 0.60}{500}} = \sqrt{\frac{0.24}{500}} = \sqrt{0.00048} \approx 0.0219
     $$

   For women:
   - Given: $p_2 = 0.25$ and $n_2 = 400$.
   - The sample proportion $\hat{p}_2$ follows an approximate normal distribution:
     $$
     \hat{p}_2 \sim N\left(0.25, \sqrt{\frac{0.25 \times (1 - 0.25)}{400}}\right)
     $$
   - Calculate the standard error:
     $$
     \text{SE}_2 = \sqrt{\frac{0.25 \times 0.75}{400}} = \sqrt{\frac{0.1875}{400}} = \sqrt{0.00046875} \approx 0.0216
     $$

2. **95% Confidence Interval for the Difference in Population Proportions**

   - The difference in sample proportions $\hat{p}_1 - \hat{p}_2$ follows an approximate normal distribution with mean $p_1 - p_2$ and standard error $\sqrt{\text{SE}_1^2 + \text{SE}_2^2}$.
   - Calculate the difference in sample proportions:
     $$
     \hat{p}_1 - \hat{p}_2 = 0.40 - 0.25 = 0.15
     $$
   - Calculate the combined standard error:
     $$
     \text{SE}_{\text{combined}} = \sqrt{0.0219^2 + 0.0216^2} \approx \sqrt{0.00047961 + 0.00046656} \approx \sqrt{0.00094617} \approx 0.0308
     $$
   - For a 95% confidence interval, the z-value is approximately 1.96.
   - The confidence interval is:
     $$
     (0.15) \pm 1.96 \times 0.0308 = 0.15 \pm 0.0604 = (0.0896, 0.2104)
     $$

   **Interpretation**: We are 95% confident that the difference in proportions of men and women in the population is between 0.0896 and 0.2104.

#### Part B: Hypothesis Testing for Difference in Proportions

- Null hypothesis $H_0: p_1 - p_2 = 0.15$.
- Alternative hypothesis $H_1: p_1 - p_2 \neq 0.15$.
- Test statistic:
  $$
  z = \frac{(\hat{p}_1 - \hat{p}_2) - 0.15}{\text{SE}_{\text{combined}}} = \frac{0.15 - 0.15}{0.0308} = 0
  $$
- Since $z = 0$ is less than the critical value of 1.96, we do not reject $H_0$. There is no significant evidence to suggest a difference from 0.15.

---

### Question 2

#### Part A: Poisson Distribution and Expected Values

1. **Percentage of Marketable Disk Packs**

   - Let the number of defects in an 800 cm² area follow a Poisson distribution with mean $\lambda = 1.2$.
   - A disk pack is marketable if it has 0 or 1 defect. We calculate:
     $$
     P(X = 0) = e^{-\lambda} \frac{\lambda^0}{0!} = e^{-1.2}
     $$
     $$
     P(X = 1) = e^{-\lambda} \frac{\lambda^1}{1!} = e^{-1.2} \cdot 1.2
     $$
   - The total probability of a marketable pack is $P(X = 0) + P(X = 1)$.

2. **Average and Variance of Time Between Interrupts**

   - Given 150 interrupts per 10 ms, the rate $\lambda = 150$ per 10 ms.
   - The average time between interrupts is $\frac{1}{\lambda}$.
   - The variance is also $\frac{1}{\lambda^2}$.

---

#### Part B: Confidence Interval and Regression Analysis

1. **90% Confidence Interval for Population Variance**

   - Use the Chi-square distribution to find the interval:
     $$
     \chi^2_{\alpha/2, n-1} \text{ and } \chi^2_{1-\alpha/2, n-1}
     $$

2. **Regression Model Fit Test**

   - Use an F-test to compare the variance due to regression and error variance.

---

### Question 3

#### Part A: Sampling and Chi-Square Test

1. **Sampling Plan**

   - Use stratified sampling based on intake and discipline.

2. **Association Test**

   - Use a chi-square test for independence.

---

#### Part B: Comparing Means

- Use a t-test for independent samples.

---

### Question 4

#### Part A: ANOVA for Performance Scores

1. **Treatments and Replicates**

2. **Model**

3. **ANOVA Test**

---

This outline provides a complete framework for answering all the questions on this test paper, but exact numerical answers require more specific values. Let me know if you need full calculations or further explanations.