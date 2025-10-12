
## 🧮 Basic Constructs

-   **Declarations**: introduce variables
-   **Expressions**: describe possible values
-   **Predicates**: constrain values


## 📦 Sets

-   Unordered, no duplicates
-   `{}` = ∅
-   Named sets: $\mathbb{Z, N, N_1}$
> [!info] SET
> Basic composite object that allows representation of a collection as a single object
> Can be described by listing or enumerating all of its members
> ==Every **type** is a **set**== but not all sets are types. 

------------------------------------------------------------------------

## 📝 Variables & Constraints

-   Declarations constrain variables by set membership.
-   **Axiomatic definitions** allow constraints.
-   Constants defined via `==`.

### Example

``` z
length == 1024
```

------------------------------------------------------------------------

## 🎨 Defining New Types

-   **Free type** (enumerated):

``` z
COLOR ::= red | green | blue
```

-   **Basic type** (unspecified set):

``` z
[NAME]
```

------------------------------------------------------------------------

## ➕ Operators & Predicates

-   Arithmetic: `+ − * div mod`
-   Set: `∪ ∩ \`
-   Predicate examples:
    -   `size = 1024`\
    -   `e ∈ EVEN`\
    -   Laws: `(c*n) ÷ (c*d) = n ÷ d`【10†Z08-Elements.pdf】
