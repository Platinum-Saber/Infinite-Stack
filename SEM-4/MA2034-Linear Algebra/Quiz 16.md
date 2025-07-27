---
tags: 
Created: 2025-06-01 22:02
About: 
Reviewed: false
Completion: 0
---
```python
import numpy as np

# Define the matrix A
A = np.array([
    [1, 0, 0],
    [1, 2, 1],
    [1, 1, 2]
])

# Manually computed Q and R from Gram-Schmidt
Q0 = np.array([
    [1/np.sqrt(3), -1/np.sqrt(2), -1/np.sqrt(6)],
    [1/np.sqrt(3), 1/np.sqrt(2), -1/np.sqrt(6)],
    [1/np.sqrt(3), 0, 2/np.sqrt(6)]
])

# Correct R to be upper triangular
R0 = np.array([
    [np.sqrt(3), np.sqrt(3), np.sqrt(3)],
    [0, np.sqrt(2), np.sqrt(2)/2],
    [0, 0, np.sqrt(6)/2]
])

# Verify A = Q0 R0
print("Verification: Q0 R0 =")
print(np.dot(Q0, R0))

# QR Iteration
A_k = A.copy()
n_iterations = 20  # Sufficient for convergence
for k in range(n_iterations):
    print(f"\nIteration {k}: A_{k} =")
    print(np.round(A_k, decimals=8))
    
    # Perform QR factorization
    Q_k, R_k = np.linalg.qr(A_k)
    A_k = np.dot(R_k, Q_k)

# Final A_k
print(f"\nFinal A_{n_iterations} (after {n_iterations} iterations):")
print(np.round(A_k, decimals=8))

# Read diagonal elements
diagonal = np.diag(A_k)
print("\nDiagonal elements of final A_k:")
print(np.round(diagonal, decimals=8))

# Compute eigenvalues of A
eigenvalues = np.linalg.eigvals(A)
print("\nEigenvalues of A:")
print(np.round(eigenvalues, decimals=8))

# Compare
print("\nComparison:")
for i, (d, e) in enumerate(zip(diagonal, np.sort(eigenvalues))):
    print(f"Diagonal {i+1}: {d:.8f}, Eigenvalue: {e:.8f}")
```


```shell
Verification: Q0 R0 =
[[ 1.00000000e+00  2.02930727e-17 -2.47782643e-17]
 [ 1.00000000e+00  2.00000000e+00  1.00000000e+00]
 [ 1.00000000e+00  1.00000000e+00  2.00000000e+00]]

Iteration 0: A_0 =
[[1 0 0]
 [1 2 1]
 [1 1 2]]

Iteration 1: A_1 =
[[ 3.          0.         -0.        ]
 [ 1.22474487  1.          0.        ]
 [-0.70710678  0.          1.        ]]

Iteration 2: A_2 =
[[ 3.18181818 -0.86696663 -0.55337157]
 [ 0.32511249  0.8708134  -0.08245784]
 [ 0.20751434 -0.08245784  0.94736842]]

Iteration 3: A_3 =
[[ 3.07079646 -1.07534552  0.73330411]
 [ 0.09305875  0.95167545  0.03295368]
 [-0.06345901  0.03295368  0.97752809]]

Iteration 4: A_4 =
[[ 3.02436739 -1.13005488 -0.78932772]
 [ 0.02933796  0.98362278 -0.01143926]
 [ 0.02049216 -0.01143926  0.99200983]]

Iteration 5: A_5 =
[[ 3.00819588 -1.14668276  0.80750421]
 [ 0.00959518  0.99452114  0.00385826]
 [-0.00675701  0.00385826  0.99728298]]

Iteration 6: A_6 =
[[ 3.00273970e+00 -1.15204975e+00 -8.13506270e-01]
 [ 3.17805000e-03  9.98171870e-01 -1.29091000e-03]
 [ 2.24414000e-03 -1.29091000e-03  9.99088440e-01]]

Iteration 7: A_7 =
[[ 3.00091408e+00 -1.15381936e+00  8.15500610e-01]
 [ 1.05709000e-03  9.99390430e-01  4.30830000e-04]
 [-7.47140000e-04  4.30830000e-04  9.99695490e-01]]

Iteration 8: A_8 =
[[ 3.00030479e+00 -1.15440708e+00 -8.16164680e-01]
 [ 3.52110000e-04  9.99796790e-01 -1.43670000e-04]
 [ 2.48940000e-04 -1.43670000e-04  9.99898430e-01]]

Final A_20 (after 20 iterations):
[[ 3.         -1.15470054 -0.81649658]
 [ 0.          1.         -0.        ]
 [ 0.         -0.          1.        ]]

Diagonal elements of final A_k:
[3. 1. 1.]

Eigenvalues of A:
[3. 1. 1.]
```




