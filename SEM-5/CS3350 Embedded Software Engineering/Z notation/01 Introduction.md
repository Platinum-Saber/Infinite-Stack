## Z ("zed") Notation


> [!NOTE] **Definition** : Z notation
> -   A **mathematical language** of logic, sets, and relations
> -   A **schema language** of patterns and objects
> -   A **theory of refinement** between abstract data types

> [!tip] Uses
> 
> -   **Create Descriptions**
> 	- Describe data structures
> 	- Model system state
> 	- Formalize properties
> -   **Reasoning** 
> 	- Explain design intentions
> 	- Verify development steps
> 	- Compare descriptions at different levels of abstraction

> [!info] Difference between Code and Model 
> - **Code**: internal structure of computation (without describing behaviour)
> - **Model**: behaviour specification without code


> [!example] Formal Description Techniques 
> - SDL, LOTOS, ESTELLE
> - More concrete than Z or CSP.
> - More useful for description than for reasoning 

---

## 02 Code vs Model



### Example: Integer Square Root

C Code implementation vs. Z specification.
#### In C

``` c
int iroot(int a) {
  int i, term, sum;
  term = 1; sum = 1;
  for (i = 0; sum <= a; i++) {
    term = term + 2;
    sum = sum + term;
  }
  return i;
}
```

#### In Z


$$
 \begin{array}{l}
 iroot : \mathbb{N} \to \mathbb{N}  \\ \hline
 \forall a \in \mathbb{N} \;\bullet\; \; \; \; \; \; \; \; \; \;  \\ 
 iroot(a) \times iroot(a) \leq a < (iroot(a) + 1) \times (iroot(a) + 1) 
 \end{array}
 $$


- Specification in **Z** is stronger as it clearly specifies that the input must be a natural number. (uses a bound variable)
- The **Predicate** $iroot(a) \times iroot(a) \leq a < (iroot(a) + 1) \times (iroot(a) + 1)$ is much stronger than the mathematical definition $\sqrt a * \sqrt a = a$
------------------------------------------------------------------------

