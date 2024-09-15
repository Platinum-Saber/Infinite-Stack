# Relational Database Design Study Note

## 1. Introduction to Relational Database Design

Relational database design is crucial for creating efficient, consistent, and maintainable databases. This study note covers key concepts in relational database design, including normal forms, functional dependencies, and decomposition techniques.

## 2. Features of Good Relational Design

A good relational design should:
- Minimize redundancy
- Ensure data consistency
- Facilitate easy maintenance and updates
- Support data integrity

## 3. Atomic Domains and First Normal Form (1NF)

First Normal Form (1NF) is the most basic level of database normalization. It requires that:

a) Each column in a table should contain atomic (indivisible) values.
b) There should be no repeating groups of columns.

Example:
Consider a table that violates 1NF:

| StudentID | Name  | Courses                |
|-----------|-------|------------------------|
| 1         | Alice | Math, Physics, Biology |
| 2         | Bob   | Chemistry, English     |

To convert this to 1NF, we can create a separate table for courses:

Students:

| StudentID | Name  |
|-----------|-------|
| 1         | Alice |
| 2         | Bob   |

StudentCourses:

| StudentID | Course    |
|-----------|-----------|
| 1         | Math      |
| 1         | Physics   |
| 1         | Biology   |
| 2         | Chemistry |
| 2         | English   |

Learn more about 1NF: [First Normal Form](https://www.geeksforgeeks.org/first-normal-form-1nf/)

## 4. Functional Dependencies

A functional dependency is a constraint between two sets of attributes in a relation. If A and B are attributes of relation R, B is functionally dependent on A (denoted as A → B) if each value of A is associated with exactly one value of B.

Example:
In a relation Student(StudentID, Name, DateOfBirth), we can say that:
StudentID → Name, DateOfBirth

This means that knowing the StudentID determines both the Name and DateOfBirth.

Learn more about functional dependencies: [Functional Dependency in DBMS](https://www.geeksforgeeks.org/functional-dependency-in-dbms/)

## 5. Boyce-Codd Normal Form (BCNF)

BCNF is a stricter version of the Third Normal Form (3NF). A relation is in BCNF if, for every non-trivial functional dependency X → Y, X is a superkey of the relation.

Example:
Consider the relation:
Course_Offering(CourseID, Professor, Room)

With functional dependencies:
CourseID, Professor → Room
Room → Professor

This relation is not in BCNF because Room → Professor is a non-trivial functional dependency, but Room is not a superkey.

To decompose into BCNF:
Course_Professor(CourseID, Professor)
Room_Professor(Room, Professor)

Learn more about BCNF: [Boyce-Codd Normal Form (BCNF)](https://www.geeksforgeeks.org/boyce-codd-normal-form-bcnf/)

## 6. Third Normal Form (3NF)

3NF is a slightly relaxed form of BCNF. A relation is in 3NF if, for every non-trivial functional dependency X → Y, at least one of the following holds:
- X is a superkey
- Y is a prime attribute (part of some candidate key)

3NF allows some functional dependencies that BCNF would not, which can be useful for preserving dependencies.

Learn more about 3NF: [Third Normal Form (3NF)](https://www.geeksforgeeks.org/third-normal-form-3nf/)

## 7. Lossless Join Decomposition

A lossless join decomposition ensures that when we decompose a relation into smaller relations, we can reconstruct the original relation by joining the smaller relations without losing or gaining any tuples.

Example:
Consider the relation R(A, B, C) with functional dependency A → B.
A lossless decomposition would be:
R1(A, B)
R2(A, C)

This decomposition is lossless because we can always reconstruct R by joining R1 and R2 on A.

Learn more about lossless join decomposition: [Lossless Join Decomposition](https://www.geeksforgeeks.org/lossless-join-decomposition-in-dbms/)

## 8. Dependency Preservation

A decomposition is dependency preserving if each functional dependency in the original relation can be inferred from the functional dependencies in the decomposed relations.

Example:
Consider R(A, B, C) with functional dependencies A → B and B → C.
A dependency-preserving decomposition would be:
R1(A, B)
R2(B, C)

This preserves both original functional dependencies.

Learn more about dependency preservation: [Dependency Preservation](https://www.geeksforgeeks.org/dependency-preservation-in-dbms/)

## 9. Closure of Functional Dependencies

The closure of a set of functional dependencies F, denoted as F+, is the set of all functional dependencies that can be logically derived from F using Armstrong's Axioms:

- Reflexivity: If Y ⊆ X, then X → Y
- Augmentation: If X → Y, then XZ → YZ for any Z
- Transitivity: If X → Y and Y → Z, then X → Z

Example:
Given F = {A → B, B → C}
F+ includes: A → B, B → C, A → C, AB → C, and more.

Learn more about closure of functional dependencies: [Closure of Functional Dependencies](https://www.geeksforgeeks.org/closure-of-functional-dependencies-in-dbms/)

## 10. Attribute Closure

The attribute closure of a set of attributes X under a set of functional dependencies F, denoted as X+, is the set of all attributes that are functionally determined by X under F.

Example:
Given R(A, B, C, D) and F = {A → B, B → C}
A+ = {A, B, C}

Learn more about attribute closure: [Attribute Closure](https://www.geeksforgeeks.org/attribute-closure-and-its-application-in-dbms/)

## 11. Fourth Normal Form (4NF)

4NF deals with multi-valued dependencies. A relation is in 4NF if it is in BCNF and has no non-trivial multi-valued dependencies.

Example:
Consider a relation Student_Sport_Music(Student, Sport, Instrument)
This relation might have multi-valued dependencies:
Student →→ Sport (a student can play multiple sports)
Student →→ Instrument (a student can play multiple instruments)

To achieve 4NF, we would decompose this into:
Student_Sport(Student, Sport)
Student_Instrument(Student, Instrument)

Learn more about 4NF: [Fourth Normal Form (4NF)](https://www.geeksforgeeks.org/fourth-normal-form-4nf/)

This study note covers the main concepts from the PDF. For a deeper understanding, refer to the linked resources and practice with various examples and exercises.