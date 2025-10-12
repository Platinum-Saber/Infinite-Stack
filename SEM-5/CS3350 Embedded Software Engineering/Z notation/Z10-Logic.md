# Z Notation -- Logic

## 🧩 Basic Predicates

-   `true`, `false`
-   Equality: `x = y`
-   Membership: `x ∈ S`

------------------------------------------------------------------------

## 🔗 Logical Connectives

-   Conjunction: `p ∧ q`
-   Disjunction: `p ∨ q`
-   Negation: `¬p`
-   Equivalence: `p ⇔ q`
-   Implication: `p ⇒ q`

Example:

``` z
beam = on ⇒ door = closed
```

------------------------------------------------------------------------

## ∀ Quantifiers

-   Universal: `∀x : S • P(x)`
-   Existential: `∃x : S • P(x)`

Example: integer square root

``` z
∀a : N • iroot(a)^2 ≤ a < (iroot(a)+1)^2
```

------------------------------------------------------------------------

## ⚖ Z & Boolean Types

-   Z does not have a Boolean type.
-   Predicates (`true`, `false`) not values but truth assertions.
-   Avoids undefined expressions like `12 div 0`.【12†Z10-Logic.pdf】
