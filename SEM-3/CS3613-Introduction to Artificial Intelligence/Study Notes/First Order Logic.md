---
tags:
  - AI
  - Agents
Reviewed: 
Created: 2024-10-01T13:30:00
About: Based on CS3613-Lecture 08 First Order Logic
---
Related : #Logic #Logic/firstorder
Reference Note : [Lecture 08 First Order Logic](file:///E:%5CAcademics%5CSEM%203%5CCS3613-Introduction%20to%20Artificial%20Intelligence%5CLecture%20note%5C08%20First%20Order%20Logic.pdf)

---

# Content

- [[#1. Objects, Relations, and Functions]]
- [[#2. Ontological Commitment]]
- [[#3. Epistemological Commitments]]
- [[#]]

---

## 1. Objects, Relations, and Functions

- **Objects**: Entities in the world (e.g., people, places, numbers).
  - Example: `John`, `Red`, `Ball`.
  
- **Relations**: Describe interactions between objects.
  - **Unary Relations** (Properties): Applied to a single object.
    - Example: `Round(Ball)`.
  - **n-ary Relations**: Applied to multiple objects.
    - Example: `Married(John, Mary)`, `LargerThan(3, 2)`.

- **Functions**: Return objects based on given input.
  - Example: `Plus(2, 3)`, `Father(Mike)`.

---

## 2. Ontological Commitment

- **Propositional Logic**: Assumes facts either hold or do not hold.
- **First Order Logic (FOL)**: Assumes the existence of objects and relationships between objects.
- **Temporal Logic**: Facts hold at specific times.
- **Higher-order Logic**: Relations and functions are also considered objects (more expressive than FOL).

---

## 3. Epistemological Commitments

- Represents the possible states of knowledge a logic allows for each fact.
> [!image]- Diagram
> ![[Pasted image 20241001133920.png]]

---

## 4. Models of FOL

- **Domain**: Set of objects a model contains, referred to as **domain elements**.
- **Relations**: Set of tuples representing relations between objects.
- **Functions**: Must be total functions, providing output for all possible inputs.

> [!image]- Diagram 
> ![[Pasted image 20241001134425.png]]


---

## 5. Symbols and Interpretations

- **Symbols**:
  - **Constant symbols**: Represent objects (e.g., `Richard`, `John`).
  - **Predicate symbols**: Represent relations (e.g., `Brother`, `OnHead`).
  - **Function symbols**: Represent functions (e.g., `LeftLeg`).

- **Interpretation**: Specifies how symbols are mapped to objects, relations, or functions.
  - Example: 
    - `Richard` refers to Richard the Lionheart.
    - `Brother` refers to a brotherhood relation.

---

## 6. Syntax of FOL

- **Basic Elements**:
  - **Constants**: `Dan`, `UoM`, `5`, etc.
  - **Predicates**: `Brother`, `>`, `Before`.
  - **Functions**: `Sqrt`, `Length`.
  - **Variables**: `x`, `y`, `a`, `b`.
  - **Connectives**: `⇒`, `∧`, `∨`, `⇔`.
  - **Equality**: `=`.
  - **Quantifiers**: Universal (`∀`), Existential (`∃`).

- **Terms**: Logical expressions that refer to objects.
  - Example: `John`, `LeftLeg(John)`, `LeftLeg(x)`.

---

### 6.1 Sentences
- **Atomic Sentences**: 
  - Consist of a predicate symbol followed by a parenthesized list of terms.
  - Example: `Brother(Richard, John)`.

- **Complex Sentences**: 
  - Constructed using logical connectives (similar to propositional logic).
  - Example: `¬Brother(LeftLeg(Richard), John)`.

---

### 6.2 Quantifiers

Quantifiers in **First Order Logic (FOL)** allow for generalization over objects. There are two primary types of quantifiers:

1. **Universal Quantifier (`∀`)**: Denotes "for all."
   - Syntax: `∀x P(x)` means that the statement `P(x)` is true for every possible value of `x`.
   - Example: `∀x At(x, UoM) ⇒ Smart(x)` asserts that everyone at UoM is smart.

2. **Existential Quantifier (`∃`)**: Denotes "there exists."
   - Syntax: `∃x P(x)` means that there is at least one value of `x` for which the statement `P(x)` is true.
   - Example: `∃x At(x, UoM) ∧ Smart(x)` asserts that there exists someone at UoM who is smart.

#### Key Properties:

- **Order of Universal Quantifiers**: The order of universal quantifiers does not affect the meaning of the expression.
  - Example: `∀x ∀y P(x, y)` is equivalent to `∀y ∀x P(x, y)`.

- **Order of Existential Quantifiers**: Similarly, existential quantifiers are also commutative.
  - Example: `∃x ∃y P(x, y)` is equivalent to `∃y ∃x P(x, y)`.

- **Mixing Universal and Existential Quantifiers**: The order of different types of quantifiers matters.
  - Example:
    - `∃x ∀y Loves(x, y)` means "There is a person who loves everyone."
    - `∀y ∃x Loves(x, y)` means "Everyone is loved by at least one person."

- **Quantifier Duality**: 
  - Universal and existential quantifiers can be expressed in terms of each other:
    - `∀x P(x)` is equivalent to `¬∃x ¬P(x)`: "For all x, P(x) is true" is equivalent to saying "There is no x such that P(x) is false."
    - `∃x P(x)` is equivalent to `¬∀x ¬P(x)`: "There exists an x such that P(x) is true" is equivalent to saying "It is not the case that P(x) is false for all x."

---

## 7. Equality and De Morgan's Rules

- **Equality**: `term1 = term2` is true if `term1` and `term2` refer to the same object.
  - Example: Defining sibling relation:
    ```
    ∃x, y Brother(x, Richard) ∧ Brother(y, Richard) ∧ ¬(x = y)
    ```

### De Morgan’s Rules

**De Morgan’s Laws** are essential for negating logical expressions involving quantifiers, ensuring that quantifiers are correctly transformed during negation.

#### De Morgan’s Laws for Quantifiers:
1. **Negating a Universal Quantifier**:
   - Negating `∀x P(x)` gives: 
     ```
     ¬∀x P(x) ≡ ∃x ¬P(x)
     ```
     Meaning: "It is not true that `P(x)` holds for all `x`" is equivalent to "There exists an `x` such that `P(x)` is false."

   - Example:
     - Original: `∀x At(x, UoM) ⇒ Smart(x)` means "Everyone at UoM is smart."
     - Negated: `∃x At(x, UoM) ∧ ¬Smart(x)` means "There is someone at UoM who is not smart."

2. **Negating an Existential Quantifier**:
   - Negating `∃x P(x)` gives:
     ```
     ¬∃x P(x) ≡ ∀x ¬P(x)
     ```
     Meaning: "It is not true that there exists an `x` such that `P(x)` holds" is equivalent to "For all `x`, `P(x)` is false."

   - Example:
     - Original: `∃x At(x, UoM) ∧ Smart(x)` means "There is someone at UoM who is smart."
     - Negated: `∀x At(x, UoM) ⇒ ¬Smart(x)` means "Everyone at UoM is not smart."

#### Key Points:
- **Universal Quantifier as Conjunction**: Universal quantification (`∀`) can be understood as a large conjunction of statements, one for each object.
- **Existential Quantifier as Disjunction**: Existential quantification (`∃`) can be understood as a large disjunction of statements, one for each object.


---

## 8. Axioms and Theorems

### 1. Axioms

**Axioms** are fundamental assumptions or statements taken to be true without proof. They form the foundation of a knowledge base and allow for further logical reasoning.

- **Definition**: An axiom is a statement that describes basic truths about a domain. These truths are accepted and used to deduce other statements (theorems).

#### Example of Axioms in FOL:
In the **Royal Kinship Domain**:
- **Axiom 1**: "One's mother is one's female parent":
  ```
  ∀m, c Mother(c) = m ⇔ (Female(m) ∧ Parent(m, c))
  ```
- **Axiom 2**: "One's husband is one's male spouse":
  ```
  ∀w, h Husband(h, w) ⇔ Male(h) ∧ Spouse(h, w)
  ```

#### Types of Axioms:
1. **Logical Axioms**: These are general truths of logic.
   - Example: `P ∨ ¬P` (A statement is either true or false).
   
2. **Non-logical Axioms**: These describe specific properties about a particular domain.
   - Example: In the kinship domain, `Male(Harry)` is a non-logical axiom stating that Harry is male.

---

### 2. Theorems

**Theorems** are statements that can be proven to be true based on a set of axioms and rules of inference.

- **Definition**: A theorem is a logical consequence of a set of axioms. Once proven, a theorem can be used like an axiom for further reasoning.

#### Example of a Theorem:
From the kinship domain:
- **Axiom**: "Sibling is another child of one’s parent":
  ```
  ∀x, y Sibling(x, y) ⇔ ∃p Parent(p, x) ∧ Parent(p, y)
  ```
  
- **Theorem**: "Sibling is a symmetric relation" (If x is a sibling of y, then y is a sibling of x):
  ```
  ∀x, y Sibling(x, y) ⇔ Sibling(y, x)
  ```
  This theorem logically follows from the axioms defining the sibling relationship.

---

#### Differences Between Axioms and Theorems:
- **Axioms** are assumed to be true without proof, forming the basis of the logical system.
- **Theorems** are derived from axioms and require proof.

#### Theorems in Mathematics:
For example, in geometry, the **Pythagorean Theorem** is a well-known theorem derived from the axioms of Euclidean geometry:
```
a² + b² = c²
```
This theorem, although universally accepted, requires proof based on prior axioms and the rules of geometry.

## 9. Example: The Royal Kinship Domain

- **Facts**:
  - Elizabeth is the mother of Charles.
  - Charles is the father of William.
  - William is the husband of Kate.

- **Predicates**:
  - **Unary Predicates**: `Male`, `Female`.
  - **Binary Predicates**: `Parent`, `Brother`, `Husband`, etc.

- **Functions**:
  - Example: `Mother`, `Father`.

- **Axioms**:
  - Example: "One’s husband is one’s male spouse":
    ```
    ∀w, h Husband(h, w) ⇔ Male(h) ∧ Spouse(h, w)
    ```

---
