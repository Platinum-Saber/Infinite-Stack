---
tags:
  - DatabaseSystems
  - DB
Reviewed: true
Created: 2024-09-11T18:45:00
About: Based on CS3043-Lecture 04 Overview of Normalization
---
Related : #Normalization #DB/04
Reference Note  : [Lecture 4 - Ch7_Normalization](file:///E:%5CAcademics%5CSEM%203%5CCS3043-Database%20Systems%5CNew%20Lecture%20notes%5CLec%204%20-%20Ch7_NormalizationP1of2.pdf), [Lecture 06](file:///E:%5CAcademics%5CSEM%203%5CCS3043-Database%20Systems%5CLecture%20slide%5CL06%20RelDBDesign.pdf)
Reference Video : [Part 1 - Lecture 4](file:///E:%5CAcademics%5CSEM%203%5CCS3043-Database%20Systems%5CLecture%20Video%5CLecture%204_P1.mp4), 

---
# Content
- [[#Introduction to Normalization]]
	1. [[#Key Concepts]]
	2. [[#Types of Normal Forms with Examples]]
		- [[#1. First Normal Form (1NF)]]
		- [[#2. Second Normal Form (2NF)]]
		- [[#3. Third Normal Form (3NF)]]
		- [[#4. Boyce-Codd Normal Form (BCNF)]]
		- [[#5. Fourth Normal Form (4NF)]]
	3. [[#Benefits of Normalization]]
	4. [[#Decomposition]]
		- [[#1. Lossless Join Decomposition]]
		- [[#2. Dependency Preservation]]
	5. [[#Closure of Functional Dependencies]]
	6. [[#Attribute Closure]]
	7. [[#Normalization Process]]

---
<br>
<br>

# Introduction to Normalization

>[!error]- Qualities of a bad relational design
>- Repetition of information
>- Need to use null values

<br>

- Database normalization is a technique used in relational database design to organize data efficiently, reduce data redundancy, and improve data integrity. The process involves breaking down a database into smaller, more manageable tables and establishing relationships between them.

<br>


## Key Concepts



> [!info]- Functional Dependencies:
>  A constraint between two sets of attributes in a relation. If A functionally determines B, then knowing the value of A allows us to uniquely determine the value of B.
>  > [!note]- 
>  > A functional dependency is a **constraint** between two sets of attributes in a relation. If A and B are attributes of relation R, B is functionally dependent on A (denoted as `A → B`) if each value of A is associated with exactly one value of B.
>  
>  
>> [!Example]- Example:
>> In a relation Student(StudentID, Name, DateOfBirth), we can say that:
>>`StudentID → Name, DateOfBirth`
>> 
>> This means that knowing the StudentID determines both the Name and DateOfBirth.
> 
> Learn more about functional dependencies: [Functional Dependency in DBMS](https://www.geeksforgeeks.org/functional-dependency-in-dbms/)

> [!info]- Keys:
> - **Superkey**: A set of attributes that can uniquely identify a tuple in a relation.
> 
> - **Candidate Key**: A minimal superkey (no subset of it can be a superkey).
> 
> - **Primary Key**: The chosen candidate key used to identify tuples in a relation.

> [!info]- Normal Forms: 
> Different levels of normalization, each with specific rules to eliminate various types of anomalies and redundancies.

<br>

## Types of Normal Forms with Examples

<br>

### 1. First Normal Form (1NF):

- Each column contains atomic (indivisible) values
- No repeating groups of columns

> [!table]- Example
> >[!example]- Before 1NF:
> > 
> > | StudentID | Name     | Courses                 |
> > | :-------- | :------- | :---------------------- |
> > | 1         | John     | Math, Physics, English  |
> > | 2         | Emma     | Biology, Chemistry      |
> 
> >[!example]- After 1NF:
> > | StudentID | Name     | Course     |
> > | --------- | -------- | ---------- |
> > | 1         | John     | Math       |
> > | 1         | John     | Physics    |
> > | 1         | John     | English    |
> > | 2         | Emma     | Biology    |
> > | 2         | Emma     | Chemistry  |

<br>

### 2. Second Normal Form (2NF):
- Must be in 1NF
- All non-key attributes are fully functionally dependent on the primary key


> [!table]- Example
> >[!example]- Before 2NF:
> > | OrderID | ProductID | ProductName | Quantity | CustomerID | CustomerName |
> > |---------|-----------|-------------|----------|------------|--------------|
> > | 1       | P1        | Laptop      | 2        | C1         | John Doe     |
> > | 1       | P2        | Mouse       | 1        | C1         | John Doe     |
> > | 2       | P1        | Laptop      | 1        | C2         | Jane Smith   |
> 
> >[!example]- After 2NF:
> > - Orders:
> > 
> > | OrderID | CustomerID | CustomerName |
> > |---------|------------|--------------|
> > | 1       | C1         | John Doe     |
> > | 2       | C2         | Jane Smith   |
> > 
> > - OrderDetails:
> >  
> > | OrderID | ProductID | ProductName | Quantity |
> > |---------|-----------|-------------|----------|
> > | 1       | P1        | Laptop      | 2        |
> > | 1       | P2        | Mouse       | 1        |
> > | 2       | P1        | Laptop      | 1        |

<br>

### 3. Third Normal Form (3NF):
- Must be in 2NF
- No transitive dependencies (non-key attributes depending on other non-key attributes)

> [!Table]- Example
> >[!example]- Before 3NF:
> > 
> > | EmployeeID | EmployeeName | DepartmentID | DepartmentName | ManagerID |
> > |------------|--------------|--------------|----------------|-----------|
> > | 1          | Alice        | D1           | Sales          | 3         |
> > | 2          | Bob          | D2           | Marketing      | 4         |
> > | 3          | Charlie      | D1           | Sales          | 3         |
> 
> 
> >[!example]- After 3NF:
> > - Employees:
> > 
> > | EmployeeID | EmployeeName | DepartmentID | ManagerID |
> > |------------|--------------|--------------|-----------|
> > | 1          | Alice        | D1           | 3         |
> > | 2          | Bob          | D2           | 4         |
> > | 3          | Charlie      | D1           | 3         |
> > 
> > - Departments:
> > 
> > | DepartmentID | DepartmentName |
> > |--------------|----------------|
> > | D1           | Sales          |
> > | D2           | Marketing      |

<br>

### 4. Boyce-Codd Normal Form (BCNF):

- A stricter version of 3NF
- For any dependency `A → B`, `A` should be a **superkey**

> [!table]- Example
> > [!example]- Before BCNF:
> > 
> > | StudentID | Course | Professor |
> > |-----------|--------|-----------|
> > | 1         | Math   | Smith     |
> > | 1         | Physics| Brown     |
> > | 2         | Math   | Smith     |
> > | 3         | Physics| Johnson   |
> > 
> >- Functional dependencies:
> > `{StudentID, Course} → Professor`
> > `Professor → Course`
> 
> > [!example]- After BCNF:
> > 
> > StudentCourse:
> > - 
> > | StudentID | Course |
> > |-----------|--------|
> > | 1         | Math   |
> > | 1         | Physics|
> > | 2         | Math   |
> > | 3         | Physics|
> > 
> > CourseProfessor:
> > - 
> > | Course  | Professor |
> > |---------|-----------|
> > | Math    | Smith     |
> > | Physics | Brown     |
> > | Physics | Johnson   |

Learn more about BCNF: [Boyce-Codd Normal Form (BCNF)](https://www.geeksforgeeks.org/boyce-codd-normal-form-bcnf/)

<br>

### 5. Fourth Normal Form (4NF):
- Addresses multi-valued dependencies
- Must be in BCNF

> [!table]- Example
>
> > [!example]- Before 4NF:
> > 
> > | StudentID | Sport   | Musical Instrument |
> > |-----------|---------|---------------------|
> > | 1         | Football| Piano               |
> > | 1         | Football| Guitar              |
> > | 1         | Tennis  | Piano               |
> > | 1         | Tennis  | Guitar              |
> > | 2         | Swimming| Violin              
> 
> > [!example]- After 4NF:
> > 
> > StudentSports:
> > 
> > | StudentID | Sport    |
> > |-----------|----------|
> > | 1         | Football |
> > | 1         | Tennis   |
> > | 2         | Swimming |
> > 
> > StudentInstruments:
> > 
> > | StudentID | Musical Instrument |
> > |-----------|---------------------|
> > | 1         | Piano               |
> > | 1         | Guitar              |
> > | 2         | Violin              |

<br>
<br>

## Benefits of Normalization

1. Minimizes data redundancy
2. Reduces data anomalies (update, insert, and delete anomalies)
3. Improves data integrity
4. Simplifies data maintenance
5. Facilitates future database extensions

<br>

## Decomposition

<br>

Decomposition is the process of breaking down a table into smaller tables to achieve normalization. There are two important properties of decomposition:

> [!info]- Lossless Decomposition: 
> Ensures that no information is lost when a relation is decomposed into smaller relations. The original relation can be reconstructed by joining the decomposed relations.

> [!info]- Dependency Preservation: 
> Ensures that all functional dependencies in the original relation are maintained in the decomposed relations.

<br>

### 1. Lossless Join Decomposition

- A lossless join decomposition ensures that when we decompose a relation into smaller relations, we can reconstruct the original relation by joining the smaller relations without losing or gaining any tuples.

> [!example]- Example:
> Consider the relation `R(A, B, C)` with functional dependency `A → B`.
> A lossless decomposition would be:
> `R1(A, B)`
> `R2(A, C)`
> 
> This decomposition is lossless because we can always reconstruct `R` by joining `R1` and `R2` on `A`.

Learn more about lossless join decomposition: [Lossless Join Decomposition](https://www.geeksforgeeks.org/lossless-join-decomposition-in-dbms/)

<br>

### 2. Dependency Preservation

A decomposition is dependency preserving **if** each functional dependency in the original relation can be **inferred** from the functional dependencies in the decomposed relations.

> [!example]- Example:
> Consider `R(A, B, C)` with functional dependencies `A → B` and `B → C`.
> A dependency-preserving decomposition would be:
> `R1(A, B)`
> `R2(B, C)`
> 
> This preserves both original functional dependencies.

Learn more about dependency preservation: [Dependency Preservation](https://www.geeksforgeeks.org/dependency-preservation-in-dbms/)

<br>
<br>

## Closure of Functional Dependencies
  
- The closure of a set of functional dependencies F, denoted as F+, is the set of all functional dependencies that can be logically derived from F using **Armstrong's Axioms**:

	- **Reflexivity**: If `Y ⊆ X`, then `X → Y`
	- **Augmentation**: If `X → Y`, then `XZ → YZ` for any `Z`
	- **Transitivity**: If `X → Y` and `Y → Z`, then `X → Z`

> [!example]- Example:
> Given `F = {A → B, B → C}`
> `F+` includes: `A → B`, `B → C`, `A → C`, `AB → C`, and more.

Learn more about closure of functional dependencies: [Closure of Functional Dependencies](https://www.geeksforgeeks.org/closure-of-functional-dependencies-in-dbms/)

<br>
<br>

## Attribute Closure

- The attribute closure of a set of attributes X under a set of functional dependencies F, denoted as X+, is the set of all attributes that are functionally determined by X under F.

> [!example]- Example:
> Given `R(A, B, C, D)` and `F = {A → B, B → C}`
> `A+ = {A, B, C}`

Learn more about attribute closure: [Attribute Closure](https://www.geeksforgeeks.org/attribute-closure-and-its-application-in-dbms/)


## Normalization Process

1. Identify all functional dependencies in the relation
2. Determine the highest normal form the relation satisfies
3. If necessary, decompose the relation into smaller relations that satisfy higher normal forms
4. Ensure the decomposition is lossless and dependency-preserving
5. Repeat the process for each new relation until all relations are in the desired normal form

  
>[!warning] While normalization is important for data integrity and reducing redundancy, it's sometimes necessary to denormalize for performance reasons in certain scenarios.

---

Up Next : [[Intermediate SQL]]
