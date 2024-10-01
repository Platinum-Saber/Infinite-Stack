---
tags:
  - AI
  - Agents
Reviewed: 
Created: 2024-10-01T13:30:00
About: Based on CS3613-Lecture 08 First Order Logic
---
Here is a comprehensive study note in markdown format based on the **First Order Logic (FOL)** concepts from the uploaded PDF:

---

# First Order Logic (FOL)

### Outline:
- [[#1. Objects, Relations, and Functions]]
- [[#2. Ontological Commitment]]
- Epistemological Commitments
- Models of FOL
- Symbols and Interpretations
- Syntax: Terms, Sentences, and Quantifiers
- Equality and Logical Connectives
- Axioms and Theorems
- Example: The Royal Kinship Domain

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
- **Universal Quantifier** (`∀`): Expresses that something is true for all objects.
  - Syntax: `∀x <sentence>`.
  - Example: "Everyone at UoM is smart":
    ``` 
    ∀x At(x, UoM) ⇒ Smart(x)
    ```
  
- **Existential Quantifier** (`∃`): Expresses that there exists an object for which the sentence is true.
  - Syntax: `∃x <sentence>`.
  - Example: "Someone at UoM is smart":
    ```
    ∃x At(x, UoM) ∧ Smart(x)
    ```

---

## 7. Equality and Logical Connectives

- **Equality**: `term1 = term2` is true if `term1` and `term2` refer to the same object.
  - Example: Defining sibling relation:
    ```
    ∃x, y Brother(x, Richard) ∧ Brother(y, Richard) ∧ ¬(x = y)
    ```

- **De Morgan’s Rules**:
  - **Universal Quantifier** (`∀`) is equivalent to a conjunction.
  - **Existential Quantifier** (`∃`) is equivalent to a disjunction.

---

## 8. Axioms and Theorems

- **Axioms**: Basic factual information from which conclusions are derived.
  - Example: "One’s mother is one’s female parent":
    ```
    ∀m, c Mother(c) = m ⇔ (Female(m) ∧ Parent(m, c))
    ```
  
- **Theorems**: Statements entailed by axioms.
  - Example: Sibling relation is commutative:
    ```
    ∀x, y Sibling(x, y) ⇔ Sibling(y, x)
    ```

---

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

### Summary:
- **First Order Logic** is more expressive than propositional logic, allowing objects, relations, and quantifiers to describe facts about the world.

---

