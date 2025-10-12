# Z Notation -- Structure

## 🏗 Tuples & Records

Combine heterogeneous elements.

``` z
DAY == 1..31; MONTH == 1..12; YEAR == Z
DATE == DAY × MONTH × YEAR
```

------------------------------------------------------------------------

## 📊 Relations & Tables

-   Set of tuples = relation.
-   Example: employee database as relation.

------------------------------------------------------------------------

## 🔀 Pairs & Binary Relations

-   Pair: `(alice, 1234)` or `alice 7→ 1234`
-   Binary relation: `NAME ↔ PHONE`

Operators:\
- `dom R`, `ran R`\
- Restriction: `S ◁ R`, `R ▷ T`\
- Override: `⊕`\
- Inverse: `R∼`

------------------------------------------------------------------------

## 🔧 Functions

-   Special binary relations (one input → one output).
-   **Partial** `↛` vs. **Total** `→`.
-   **Injection**: one-to-one `↣/`.

------------------------------------------------------------------------

## 📜 Sequences

Ordered collections (arrays, lists).

``` z
workweek = <mon, tue, wed, thu, fri>
workweek 3 = wed
```

-   Sequences are functions from `1..n`.

------------------------------------------------------------------------

## ⚙ Operators

-   Infix viewed as functions:\
    `2 + 3 = 5 ⇔ (+)(2,3) = 5`【11†Z09-Structure.pdf】
