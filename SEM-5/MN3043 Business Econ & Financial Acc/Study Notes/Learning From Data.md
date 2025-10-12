---
Author: Sansika Suhan Waduge
---

## 📌 What is Learning?

> [!quote]
> “A computer program is said to learn from experience **E** with respect to some class of tasks **T** and performance measure **P**, if its performance at tasks in **T**, as measured by **P**, improves with experience **E**.”
> — Tom Mitchell, 1997

* **Experience (E):** Data used for training (e.g., MNIST dataset).
* **Tasks (T):** Classification, prediction, recognition, etc.
* **Performance (P):** Accuracy, error rate, F1-score, etc.
* **Goal:** Performance improves as experience increases.

> [!example]  **Example:** Training on MNIST digit images improves recognition accuracy.
> ![[Pasted image 20250818214309.png|280]] ![[Pasted image 20250818214334.png| 230]]
> 

---

## 📊 Types of Learning from Data

> [!info]  Supervised Learning
>  - Uses **labeled data** (features + targets). 
> - Goal: learn mapping from input → output.

> [!info] Unsupervised Learning
> - No labels
> - find **patterns, clusters, structure**.

> [!info] Semi-Supervised Learning 
>  - Mix of labeled + unlabeled data.

> [!info] Self-Supervised Learning 
> - Model generates labels from raw data (e.g., Contrastive Learning, GANs, VAEs).

> [!info] Reinforcement Learning 
> - Agent learns by interacting with environment, guided by **rewards/penalties**.

> [!image]
> Supervised vs Unsupervised Learning
> ![[Pasted image 20250818215349.png|400]]

---

### Supervised Learning Example: MNIST

* **Input:** 28×28 grayscale digit images.
* **Output:** Label (0–9).
* **Model:** Learns mapping from pixels → digit class.

```python
from sklearn.datasets import fetch_openml
X, y = fetch_openml('mnist_784', version=1, return_X_y=True)
```

---

### Unsupervised Learning Example

* **Goal:** Find clusters in unlabeled data.
* **Example:** Grouping handwritten digits without knowing labels.
* **Techniques:** k-Means, PCA, t-SNE.

---

### Supervised vs Unsupervised

| Feature    | Supervised           | Unsupervised          |
| ---------- | -------------------- | --------------------- |
| Labels     | Required             | Not available         |
| Objective  | Predict outputs      | Find patterns         |
| Example    | Image classification | Customer segmentation |
| Limitation | Costly labeling      | No ground truth       |

---

## 🚧 Challenges in Learning from Data

1. **Data Quality & Quantity**

   * Missing, noisy, incomplete data.
   * Need large datasets.

2. **Data Imbalance**

   * Unequal class distribution → biased results.
   * E.g., 90% class A, 10% class B.

3. **Overfitting vs Underfitting**

   * **Overfitting:** Good on training, bad on new data.
   * **Underfitting:** Too simple to capture patterns.
   * **Generalization:** Key to success.

---

## 🛠 Data Preparation & Preprocessing

> [!NOTE] Data Cleaning: 
> Handle missing/inconsistent values.
> Approaches
> - Removing them
> - Filling with zeros/mean/median
> - Interpolation
> Data Cleaning: outlier detection and removing


> [!NOTE] Data Preprocessing
> - Feature scaling (e.g. normalization)
> - Dimensionality reduction
> 	- Principal Component Analysis (PCA)

* **Scaling:**

  * Min-Max Scaling → [0,1]
  * Standardization → mean=0, variance=1
  * Robust Scaling → resistant to outliers
  * Quantile Transformation → uniform/normal distribution

> [!example]
> California Housing Dataset
> Features: Median income, house age, average rooms, population, etc.
> Target: Median house value.

---

## 🧪 ML Training Process (Supervised)

1. **Data Splitting:** Train / Validation / Test sets.
2. **Training:** Fit model on training set.
3. **Validation:** Tune hyperparameters.
4. **Testing:** Evaluate on unseen test set.
5. **Performance Metrics:**

   * Accuracy
   * Precision / Recall / F1-score
   * MAE, MSE, RMSE

---

## 📏 Evaluation Metrics

* **Confusion Matrix:**

|        | Predicted + | Predicted - |
| ------ | ----------- | ----------- |
| True + | TP          | FN          |
| True - | FP          | TN          |

* **Formulas:**

  * Accuracy = (TP + TN) / (Total)
  * Precision = TP / (TP + FP)
  * Recall = TP / (TP + FN)
  * F1 = 2 × (Precision × Recall) / (Precision + Recall)

> [!warning]
> Accuracy is misleading with **imbalanced datasets**. Use **F1-score** instead.

---

## 🧩 Model Selection & Hyperparameter Tuning

* **Choose best model**: CNN, Decision Tree, k-NN, etc.
* **Hyperparameters:** Set before training (e.g., learning rate, depth).
* **Techniques:**

  * **k-Fold Cross Validation** → rotate training/testing splits.
  * **Grid Search** → test all hyperparameter combos.
  * **AIC / BIC / MDL** → balance complexity vs performance.

---

## ⚖️ Bias–Variance Trade-off

* **Bias:** Error from wrong assumptions (too simple model).
* **Variance:** Error from sensitivity to training data (too complex model).
* **MSE Decomposition:**

  $$
  MSE = \text{Bias}^2 + \text{Variance} + \text{Irreducible Error}
  $$

> [!tip]
>
> * High bias → underfitting
> * High variance → overfitting
> * Goal: **low bias & low variance**

![Bias Variance Tradeoff](https://miro.medium.com/v2/resize\:fit:720/format\:webp/1*vLgF0dPgboV6yJOpXoG3dA.png)

---

## 📚 Additional Reading

* [Cross-validation – scikit-learn](https://scikit-learn.org/stable/modules/cross_validation.html)
* [Hyperparameter tuning – scikit-learn](https://scikit-learn.org/stable/modules/grid_search.html)
* [Bias-Variance Trade-off – Wikipedia](https://en.wikipedia.org/wiki/Bias–variance_tradeoff)

---

Would you like me to also **insert real dataset code examples in Python (with plots)** for normalization methods (Min-Max, Standard, Robust) so you can directly run them in Jupyter?
