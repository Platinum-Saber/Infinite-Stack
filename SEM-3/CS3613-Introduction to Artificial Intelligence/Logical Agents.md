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

---

# Content




# Agents
> [!info] Agent types
> - **Problem solving agent** : Execute a given solution and are typically not well-suited for dynamic problems.
> - **Knowledge based/ Planning agents** 

## Knowledge Based Agents
> [!note] Characteristics
> - Given explicit goals.
> - Can achieve competence quickly by being told or learning
> - Adapts to changes in environment.


> [!summary] Functionality
> - Maintains a representation of the world.
> - Infer new representations of the world.
> - Use the representation to decide what to do.

### Knowledge Representations
- **Atomic** : The state is considered as a whole with no internal structure available to the agent.
- **Factored** : Involves the assignment of values to variables.
- **Structured** : Involves objects and relations, representing facts about these relations.

<br>

### Knowledge Base (KB)
- The place where the agent's world representation **world representation** is maintained.
- It consists of a set of *sentences* written in a *knowledge representation language*, also known as **axioms**.

KB is crucial for,
- Adding new information (TELL)
- Retrieving information (ASK)
Both involve inference. (derive new info from old)

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
