---
tags: 
Created: 2025-06-01 21:37
About: 
Reviewed: false
Completion: 0
---



```python
import numpy as np
from sympy import Matrix

# Define the matrix A
A = np.array([
    [2, 1, 0, 0, 0, 0],
    [0, 2, 1, 0, 0, 0],
    [0, 0, 2, 0, 0, 0],
    [0, 0, 0, 2, 1, 0],
    [0, 0, 0, 0, 2, 1],
    [1, 0, 0, 0, 0, 2]
])

# Convert to sympy Matrix for Jordan form computation
A_sympy = Matrix(A)

# Compute the Jordan form and the transformation matrix P
J, P = A_sympy.jordan_form()

# Print the matrices
print("Matrix A:")
print(A)
print("\nJordan Form J:")
print(np.array(J, dtype=float))
print("\nTransformation Matrix P:")
print(np.array(P, dtype=float))

# Verify A = P J P^{-1}
P_np = np.array(P, dtype=float)
J_np = np.array(J, dtype=float)
P_inv = np.linalg.inv(P_np)
A_computed = P_np @ J_np @ P_inv

print("\nVerification: P J P^{-1} (should equal A):")
print(np.round(A_computed, decimals=10))  # Round to handle numerical precision

# Verify eigenvalues
eigenvals = np.linalg.eigvals(A)
print("\nEigenvalues of A:")
print(eigenvals)

# Check if A differs from J in at least one position where J is zero
J_np = np.array(J, dtype=float)
diff_positions = (A != J_np) & (J_np == 0)
if np.any(diff_positions):
    print("\nCondition satisfied: A has non-zero entries where J has zeros at positions:")
    print(np.where(diff_positions))
else:
    print("\nCondition not satisfied: A does not differ from J where J has zeros.")
```



