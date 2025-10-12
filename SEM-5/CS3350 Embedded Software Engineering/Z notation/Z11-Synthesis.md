# Z Notation -- Synthesis

## 📦 Set Comprehensions

Form:

``` z
{ declaration | predicate • expression }
```

Example:

``` z
ODD == {i : Z • 2*i + 1}
```

------------------------------------------------------------------------

## 🔣 Lambda Expressions

Functions via comprehensions:

``` z
isqr == (λ i : Z • i * i)
```

------------------------------------------------------------------------

## 🧮 Formal Specs

Prime numbers:

``` z
PRIME == {n : N | n > 1 ∧ ¬(∃m : 2..n−1 • n mod m = 0)}
```

------------------------------------------------------------------------

## ✂ Simplifications

-   `let` for local defs
-   Conditional `if ... then ... else`

Absolute value:

``` z
∀x : Z • |x| = if x ≥ 0 then x else −x
```

------------------------------------------------------------------------

## 📅 Example: Appointment Calendar

``` z
DAY == 1..31; MONTH == 1..12; YEAR == Z
DATE == DAY × MONTH × YEAR
days == {1 7→ 31, 2 7→ 28, ..., 12 7→ 31}
```

Function:

``` z
next : DATE ↛ DATE
∀d:DAY; m:MONTH; y:YEAR •
(d < days m ∧ next(d,m,y) = (d+1,m,y)) ∨
(d = days m ∧ m < 12 ∧ next(d,m,y) = (1,m+1,y)) ∨
(d = days m ∧ m = 12 ∧ next(d,m,y) = (1,1,y+1))
```

【13†Z11-Synthesis.pdf】
