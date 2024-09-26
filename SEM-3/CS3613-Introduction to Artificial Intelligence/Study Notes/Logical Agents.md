---
tags:
  - AI
  - AI/06
  - Agents
Reviewed: 
Created: 2024-09-02T10:27:00
About: Based on CS3613-Lecture 06 Logical Agents
---
Related : #AI #AI/06 #Agents 

---
Reference Note : [Logical Agents I](file:///E:%5CAcademics%5CSEM%203%5CCS3613-Introduction%20to%20Artificial%20Intelligence%5CLecture%20note%5C06%20Logical%20Agents%20I.pdf)
Reference Video : 
Reference Links : [Worlds web app](https://adam.math.hhu.de/#/g/trequetrum/lean4game-logic/world/AndIntro/level/1) , [Logical Agents by Harvard](https://cs50.harvard.edu/ai/2024/notes/1/)



---

# Content
1. [[#Agents]]
	- [[#Knowledge Based Agents]]
		- [[#Knowledge Representations]]
		- [[#Knowledge Base (KB)]]
2. [[#Logic]]
	- [[#Logical Languages]]
	- [[#Logical Reasoning]]

<br>
<br>

# Agents
> [!info] Agent types
> - **Problem solving agent** : Execute a given solution and are typically not well-suited for dynamic problems.
> - **Knowledge based/ Planning agents** 

<br>

## Knowledge Based Agents
> [!note] Characteristics
> - Given explicit goals.
> - Can achieve competence quickly by being told or learning
> - Adapts to changes in environment.


> [!summary] Functionality
> - Maintains a representation of the world.
> - Infer new representations of the world.
> - Use the representation to decide what to do.

<br>

### Knowledge Representations
- **Atomic** : The state is considered as a whole with no internal structure available to the agent.
- **Factored** : Involves the assignment of values to variables.
- **Structured** : Involves objects and relations, representing facts about these relations.

<br>

### Knowledge Base (KB)
- The place where the agent's world representation **world representation** is maintained.
- It consists of a set of *sentences* written in a *knowledge representation language*, also known as **axioms**.
- KB is crucial for,
	- Adding new information (TELL)
	- Retrieving information (ASK)
- Both involve inference. (derive new info from old)

<br>
<br>

# Logic
- Fundamental concepts of logical representation & reasoning.

### Logical Languages
- A knowledge base contains **sentences** that must be **syntactically** *correct*. The **semantics** of these sentences define their truth in possible worlds (models).

> [!info]- Semantics
> - Defines the truth of sentences with respect to each possible world.
> - Possible world = model; An abstraction where each sentence is either true or false.
> - If a sentence `S` is true in model `m`. This implies that `m` satisfies `s` or `m` is a model of `s`.
> - Set of `m` which are models of `s` is defined as : `M(s)`

<br>

### Logical Reasoning
- Involves **logical entailment**, where one **sentence** *implies* another if it is true in every **model** where the first sentence is true. **Logical inference** allows the agent to derive conclusions from its knowledge base.

> [!info]- Logical Inference
> - Derive conclusions using **entailments**.
> - **Model checking** : enumerates all possible models to check that a sentence is true in all models where the `KB` is true.
> - `i` - Inference algorithm, should be *sound*, *truth preserving*, and *complete*.
> - Model checking works if space for models is finite.

<br>

### Grounding
- if `KB` is true in the real world, then any sentence derived from `KB` by a **sound inference** procedure is also true in the real world.

> [!image]- Grounding diagram
> ![[Pasted image 20240909112910.png]]

<br>
<br>

# The Wumpus World

- The Wumpus World is a classic example used to illustrate logical agents in AI. It is characterized by properties such as partial observability, determinism, sequential nature, and a single agent environment. The agent must navigate the world based on its percepts (e.g., stench, breeze, glitter) and use logical reasoning to make decisions.

> [!image]- Wumpus world diagram
> ![[Pasted image 20240909113247.png]]

<br>

### Properties of the Wumpus World 
- **Partially observable**: The Wumpus world in AI is partially observable because the agent can only sense the immediate surroundings, such as an adjacent room. 
- **Deterministic**: It is deterministic because the result and end of the world are already known. 
- **Sequential**: It is sequential because the order is essential. 
- **Static**: It is motionless because Wumpus and Pits are not moving. 
- **Discrete**: The surroundings are distinct. 
- **One agent**: The environment is a single agent because we only have one agent, and Wumpus is not regarded as an agent.


# Propositional Logic 

## 1. Propositional Logic - Syntax
Propositional logic deals with **propositional symbols** that represent statements, which can either be **true** or **false**. A sentence in propositional logic is formed by combining these symbols using **logical connectives**.

### Logical Connectives:
- **Negation (¬)**: Negates the truth value of a proposition.
- **Conjunction (∧)**: True if both propositions are true.
- **Disjunction (∨)**: True if at least one proposition is true.
- **Implication (⇒)**: True unless the first proposition is true and the second is false.
- **Biconditional (⇔)**: True if both propositions have the same truth value.

### Atomic Sentences:
An atomic sentence is a single propositional symbol:
- Example: $P$, $Q$, $R$ are atomic sentences.

### Complex Sentences:
Complex sentences are formed using atomic sentences and logical connectives.
- Example: $P \land Q$, $\neg P$, $P \Rightarrow Q$

## 2. Propositional Logic - Semantics
Semantics define the **truth** of sentences relative to possible models (interpretations).

### Models in Propositional Logic:
A model is an assignment of **truth values** (True or False) to propositional symbols. For example, if a model assigns:
- $P = \text{True}$, $Q = \text{True}$, and $R = \text{False}$, then:
  - $P \land Q = \text{True}$
  - $P \lor R = \text{True}$

### Truth Table:
A truth table helps in determining the truth value of complex sentences for all possible combinations of truth values of the atomic sentences.

| $P$ | $Q$ | $\neg P$ | $P \land Q$ | $P \lor Q$ | $P \Rightarrow Q$ | $P \Leftrightarrow Q$ |
| --- | --- | -------- | ----------- | ---------- | ----------------- | --------------------- |
| T   | T   | F        | T           | T          | T                 | T                     |
| T   | F   | F        | F           | T          | F                 | F                     |
| F   | T   | T        | F           | T          | T                 | F                     |
| F   | F   | T        | F           | F          | T                 | T                     |

## 3. Computing the Truth Value of Sentences
To compute the truth value of a sentence in propositional logic, apply the truth values from the model to the propositional symbols and then use the truth table to determine the truth of the overall sentence.

Example: For the sentence $P \Rightarrow Q$ and a model where $P = \text{True}$, $Q = \text{False}$:
- Using the truth table, $P \Rightarrow Q = \text{False}$.

## 4. Inferencing
Inference in propositional logic involves deriving a new sentence from a set of known sentences (the **knowledge base, KB**) using logical entailment or other inference algorithms.

### Logical Entailment (⊨):
A sentence $\alpha$ is **entailed** by the KB ($KB \models \alpha$) if and only if $\alpha$ is true in every model where the KB is true.

### Model Checking:
Model checking is an inference technique where all possible models are checked to determine whether a sentence is true given a knowledge base.

### Theorem Proving:
Another approach to inference is to use rules of inference to construct a **proof** of the desired sentence directly from the knowledge base.

## 5. Logical Equivalence
Two sentences $\alpha$ and $\beta$ are **logically equivalent** if they are true in the same set of models. This is denoted by:
- $\alpha \equiv \beta \iff (\alpha \models \beta \text{ and } \beta \models \alpha)$.

Example:
- $P \Rightarrow Q \equiv \neg P \lor Q$

## 6. Inference and Proofs
In propositional logic, inference rules can be used to derive new sentences from existing ones.

### Common Inference Rules:
1. **Modus Ponens**:
   If $P \Rightarrow Q$ and $P$ are true, then $Q$ must be true.
   - $(P \Rightarrow Q), P \models Q$
   
2. **And Elimination**:
   From $P \land Q$, we can infer $P$ or $Q$ individually.
   - $P \land Q \models P$
   - $P \land Q \models Q$

3. **Biconditional Elimination**:
   From $P \Leftrightarrow Q$, we can infer both $P \Rightarrow Q$ and $Q \Rightarrow P$.
   - $P \Leftrightarrow Q \models (P \Rightarrow Q) \land (Q \Rightarrow P)$

## 7. Proof by Resolution
**Resolution** is a powerful inference rule used in conjunction with **Conjunctive Normal Form (CNF)**. It allows us to prove statements by refutation, i.e., showing that the negation of the goal leads to a contradiction.

### Conjunctive Normal Form (CNF):
CNF is a standard form of a sentence in propositional logic where the sentence is expressed as a conjunction of disjunctions of literals (e.g., $(P \lor Q) \land (\neg Q \lor R)$).

### Resolution Rule:
If two clauses contain complementary literals (e.g., $P$ and $\neg P$), we can infer a new clause by eliminating the complementary literals and combining the remaining parts.
   - Example: $(P \lor Q)$ and $(\neg P \lor R)$ resolve to $(Q \lor R)$.

### Application:
Proof by resolution involves converting all sentences into CNF, then iteratively applying the resolution rule until the desired conclusion is reached or a contradiction is found.

### 1. Conjunctive Normal Form (CNF)

**Conjunctive Normal Form (CNF)** is a standardized way of expressing logical formulas in propositional logic. It is a conjunction of one or more disjunctions of literals. A **literal** is either a propositional symbol or its negation. A **disjunction** is a logical "OR" ($\lor$) operation, while a **conjunction** is a logical "AND" ($\land$) operation.

#### CNF Structure:

**A formula in CNF looks like this:** 
- $(P1∨P2∨⋯∨Pn)∧(Q1∨Q2∨⋯∨Qm)∧…(P_1 \lor P_2 \lor \dots \lor P_n) \land (Q_1 \lor Q_2 \lor \dots \lor Q_m) \land \dots(P1​∨P2​∨⋯∨Pn​)∧(Q1​∨Q2​∨⋯∨Qm​)∧…$
-  Each disjunction $(P_1 \lor P_2 \lor \dots)$ is called a **clause**.

#### Conversion to CNF:

To convert a propositional logic formula into CNF, you follow these steps:

1. **Eliminate biconditionals ($\Leftrightarrow$) and implications ($\Rightarrow$)**:
    - Replace $P \Rightarrow Q$ with $\neg P \lor Q$.
    - Replace $P \Leftrightarrow Q$ with $(P \Rightarrow Q) \land (Q \Rightarrow P)$.
2. **Move negations inwards** using De Morgan's laws:
    - $\neg(P \land Q) \equiv \neg P \lor \neg Q$
    - $\neg(P \lor Q) \equiv \neg P \land \neg Q$
3. **Distribute $\lor$ over $\land$** to create a conjunction of disjunctions:
    - Apply distributive law: $(P \land Q) \lor R \equiv (P \lor R) \land (Q \lor R)$

#### Example:

Consider the formula $(P \Rightarrow Q) \land \neg R$:

- First, convert the implication: $(\neg P \lor Q) \land \neg R$.
- This is already in CNF: one clause is $(\neg P \lor Q)$, and the other is $(\neg R)$.

---

### 2. Resolution in Propositional Logic

**Resolution** is an inference rule used in propositional logic for proving statements by **refutation** (i.e., showing that the negation of the desired goal leads to a contradiction).

#### Resolution Rule:

If we have two clauses:

1. $(A \lor B)$
2. $(\neg A \lor C)$

We can infer a new clause $(B \lor C)$ by eliminating the complementary literals $A$ and $\neg A$. This is called **resolving** the two clauses.

#### Steps in Resolution:

1. **Convert all formulas into CNF**.
2. **Negate** the conclusion you want to prove and add it to the knowledge base.
3. **Resolve** pairs of clauses repeatedly to derive new clauses.
4. If you derive an empty clause (denoted by $\square$), it indicates a contradiction, and the original conclusion is valid.

#### Example:

Let’s say we want to prove $P$ from the following knowledge base:

- $P \lor Q$
- $\neg P \lor R$
- $\neg Q$
- $\neg R$

We start by negating $P$ (i.e., adding $\neg P$) and proceed with resolution:

- Resolve $(P \lor Q)$ with $(\neg P)$ to get $Q$.
- Resolve $Q$ with $\neg Q$ to get the empty clause ($\square$).

Thus, we have derived a contradiction, meaning $P$ is true.