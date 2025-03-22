---
tags:
  - TheoryOfComputing
  - toc/01
Created: 2025-01-30 09:47
About: Based on CS3063-Lecture 01 Introduction to theory of computing
Reviewed: true
Completion: 100
---

## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```




> [!info] Overview
> 
> The Theory of Computing is a branch of computer science that delves into the fundamental questions about what can be computed and how efficiently computation can be performed. It encompasses three primary areas:
> 
> 1. **Automata Theory**: Studies abstract machines (automata) and the problems they can solve.
> 2. **Computability Theory**: Explores the limitations of computational machines, identifying problems that cannot be solved by any algorithm.
> 3. **Complexity Theory**: Focuses on classifying computational problems based on their inherent difficulty and the resources required to solve them.

> [!info] Mathematical Background
> 
> A solid foundation in the following mathematical concepts is essential for understanding the Theory of Computing:
> 
> - **Set Theory**: Understanding collections of distinct objects.
> - **Logic**: Propositional and predicate logic, including implications, equivalences, and quantifiers.
> - **Functions and Relations**: Mappings between sets and their properties.
> - **Proof Techniques**: Methods such as mathematical induction and recursion.

# Content

1. [[#Abstract Models of Computation|Abstract Models of Computation]]
2. [[#Decision Problems and Languages|Decision Problems and Languages]]
3. [[#The Chomsky Hierarchy|The Chomsky Hierarchy]]
	1. [[#Finite Automata]]
	2. [[#Pushdown Automata]]
	3. [[#Turing Machines]]
4. [[#Computability and Complexity|Computability and Complexity]]
5. [[#Languages|Languages]]

# Fundamental Theories of Computing



> [!NOTE] The fundamental **capabilities** and **limitations** of computers are explored through the following, 
> 
> - **Automata Theory**: Investigates different computational models and the classes of problems they can solve.
> - **Computability Theory**: Determines which problems are solvable by computational means.
> - **Complexity Theory**: Analyzes the efficiency of algorithms and classifies problems based on the resources required for their solution.

> [!faq]- What is Computation
> 
> Computation involves executing an algorithm—a step-by-step procedure that transforms inputs into outputs. The study of computation examines the nature of these procedures and the abstract machines that perform them.
> 

## Abstract Models of Computation

To theoretically analyze computation, we use simplified abstract machines rather than real-world computers, which are too complex for formal analysis. 

> [!abstract] These models include:
> 
> >[!NOTE]- **Finite Automata**:
> > Machines with a finite number of states, used to recognize regular languages.
>
> > [!NOTE]- **Pushdown Automata**: 
> > Finite automata equipped with a stack, capable of recognizing context-free languages.
> 
> 
> >[!NOTE]- **Linear-Bounded Automata**: 
> > - Turing machines with limited tape, recognizing context-sensitive languages.
> 
> 
> >[!NOTE]- **Turing Machines**: 
> > - Abstract devices with unlimited memory, representing the most powerful model of computation, capable of recognizing recursively enumerable languages.
> > 

## Decision Problems and Languages

- A significant focus is on **decision problems**—questions with a "yes" or "no" answer. 
- These problems can be framed as language recognition tasks, where the goal is to determine whether a given string belongs to a particular set (language). 
- For example, determining if a number is prime can be viewed as recognizing whether a string representing the number belongs to the language of prime numbers.

## The Chomsky Hierarchy

Noam Chomsky introduced a hierarchy that classifies languages based on their generative grammars and the computational models required to recognize them:

> [!NOTE] Chomsky Hierarchy
> 1. **Type 3**: Regular Languages —> recognized by **finite automata.**
> 2. **Type 2**: Context-Free Languages —> recognized by **pushdown automata.**
> 3. **Type 1**: Context-Sensitive Languages —> recognized by **linear-bounded automata.**
> 4. **Type 0**: Recursively Enumerable Languages —> recognized by **Turing machines.**

This hierarchy illustrates the increasing complexity and expressive power of language classes and their corresponding automata.

### Finite Automata

Finite automata are the ==simplest computational models==, consisting of a **finite set of states and transitions** between them. They are used to model systems with a limited memory and are capable of ==recognizing **regular languages**==. Applications include **text parsing, lexical analysis, and designing digital circuits**.

### Pushdown Automata

Pushdown automata ==extend finite automata by adding a stack==, providing **additional memory**. This enhancement allows them to ==**recognize context-free languages**==, which are essential for **modeling the syntax** of *programming languages* and *natural languages*.

### Turing Machines

Turing machines are the ==most powerful abstract computational models==, equipped with **unlimited memory** in the form of an **infinite tape**. They can simulate any algorithm and are used to define the limits of what can be computed. Despite their simplicity, Turing machines can perform any computation that modern computers are capable of, making them a central concept in computability theory.

## Computability and Complexity

While Turing machines can define what is computable, not all problems are solvable, and some solvable problems are computationally infeasible due to resource constraints. ==**Computability theory**== explores the existence of unsolvable problems, while ==**Complexity theory** ==examines the efficiency of algorithms, classifying problems based on the time and space resources required for their solution.



## Languages

> [!faq] What is a **Language**
> A ==**set of strings**== where the symbols are drawn from an **alphabet**


> [!faq] What is an **Alphabet**
> A *finite* ==**set of symbols**== denoted by $\Sigma$  



> [!info] **Length** of a *string* `x` over $\Sigma$
> - Number of symbols in `x`
> - Denoted by `|x|`



> [!info] **Null string**
> - A string of 0 length over $\Sigma$
> - Denoted by $\Lambda$


> [!info] ${\Sigma}^{*}$
> - The set of all strings over $\Sigma$
> - A language over $\Sigma$ is a subset of $\Sigma^*$



> [!info] **Complement** $L^\prime$ of a language $L$ over $\Sigma$
> $L\ ^\prime = \Sigma \ ^* - L$


> [!NOTE] Set Operations
> 
> 1.  If $L_{\ 1} \subseteq \Sigma_{1}^*$ and $L_{\ 2} \subseteq \Sigma_{2}^*$ then both $L_{1}$ and $L_2$ are subsets of $(\Sigma_{1} \cup \Sigma_{2})^*$ 
> 2. If $L_1 \subseteq \Sigma^*$ and $L_2 \subseteq \Sigma^*$ then $$L_{1}L_{2} = \{ xy\ | \ x \in L_{1} \cap \ y \in L_{2} \}$$

> [!tip] Kleene Star
> - Set of all strings obtained by concatenating any number of elements of L :
> $$
> L^* = \bigcup\limits_{i=0}^{\infty} L^i
> $$
> - The set of all strings obtained by concatenating one or more elements of L :
> $$
> L^+ = \bigcup\limits_{i=1}^{\infty} L^i
> $$
> - $L^+ = L^* L = L L^*$
