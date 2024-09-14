---
tags:
  - DatabaseSystems
Reviewed: 
Created: 2024-09-14T19:41:00
About: Note generated using Claude 3.5 Sonnet
---
Related : #RelationalAlgebra

---
# Content
- [[#Relational Algebra]]
	- [[#Sample Relations]]
	- [[#1. Selection (`σ`)]]
	- [[#2. Projection (`π`)]]
	- [[#3. Union (∪)]]
	- [[#4. Set Difference (-)]]
	- [[#5. Cartesian Product (×)]]
	- [[#6. Natural Join (⋈)]]

# Relational Algebra

Relational algebra provides a set of operations that can be performed on relations (tables) to query and manipulate data. 



## Sample Relations


> [!Table]- Example Tables
> #### Employee Table:
> | EmpID | Name   | Department | Salary |
> |-------|--------|------------|--------|
> | 1     | Alice  | IT         | 75000  |
> | 2     | Bob    | HR         | 65000  |
> | 3     | Carol  | Finance    | 80000  |
> | 4     | David  | IT         | 72000  |
> | 5     | Eve    | HR         | 68000  |
> 
> #### Project Table:
> 
> | ProjID | ProjectName | Department |
> |--------|-------------|------------|
> | 101    | Website     | IT         |
> | 102    | Recruiting  | HR         |
> | 103    | Budgeting   | Finance    |
> | 104    | App Dev     | IT         |
> 



## 1. Selection (`σ`)

- The selection operation selects tuples (rows) that satisfy a given predicate.
- `Syntax`: σ<sub>predicate</sub>(R)

> [!example]- **Example**: Find all employees in the IT department.
> 
> #### σ<sub>Department = 'IT'</sub>(Employee)
> 
> >[!table]- Result:
> > 
> > | EmpID | Name   | Department | Salary |
> > |-------|--------|------------|--------|
> > | 1     | Alice  | IT         | 75000  |
> > | 4     | David  | IT         | 72000  |

<br>

## 2. Projection (`π`)

- The projection operation selects certain attributes (columns) from a relation.
- `Syntax`: π<sub>attribute list</sub>(R)

> [!example]- **Example**: List only the names and salaries of all employees.
> 
>#### π<sub>Name, Salary</sub>(Employee)
> 
> >[!table]- Result:
> > 
> > | Name   | Salary |
> > |--------|--------|
> > | Alice  | 75000  |
> > | Bob    | 65000  |
> > | Carol  | 80000  |
> > | David  | 72000  |
> > | Eve    | 68000  |

<br>

## 3. Union (`∪`)

- The union operation combines tuples from two relations, removing duplicates.
- `Syntax`: R ∪ S

> [!example]- **Example**: List all departments from both Employee and Project tables.
> 
>#### π<sub>Department</sub>(Employee) ∪ π<sub>Department</sub>(Project)
> 
> >[!table]- Result:
> > 
> > | Department |
> > |------------|
> > | IT         |
> > | HR         |
> > | Finance    |

<br>

## 4. Set Difference (`-`)

- The set difference operation returns tuples that are in one relation but not in another.
- `Syntax`: R - S

> [!example]- **Example**: Find departments that have employees but no projects.
> 
> #### π<sub>Department</sub>(Employee) - π<sub>Department</sub>(Project)
> 
> **Result**: (Empty set, as all departments with employees also have projects)

<br>

## 5. Cartesian Product (`×`)

- The Cartesian product combines each tuple from one relation with every tuple from another relation.
- `Syntax`: R × S

> [!example]- **Example**: Combine all employees with all projects (note: this can produce a large result set).
> 
> #### Employee × Project
> 
> >[!table]- Partial Result (first few rows):
> > 
> > | EmpID | Name   | Department | Salary | ProjID | ProjectName | ProjDepartment |
> > |-------|--------|------------|--------|--------|-------------|----------------|
> > | 1     | Alice  | IT         | 75000  | 101    | Website     | IT             |
> > | 1     | Alice  | IT         | 75000  | 102    | Recruiting  | HR             |
> > | 1     | Alice  | IT         | 75000  | 103    | Budgeting   | Finance        |
> > | 1     | Alice  | IT         | 75000  | 104    | App Dev     | IT             |
> > | 2     | Bob    | HR         | 65000  | 101    | Website     | IT             |
> > | ...   | ...    | ...        | ...    | ...    | ...         | ...            |

<br>

## 6. Natural Join (`⋈`)

- The natural join combines tuples from two relations based on common attributes.
- `Syntax`: R ⋈ S

> [!example]- **Example**: Join employees with their respective projects based on the department.
> 
> #### Employee ⋈ Project
> 
> >[!table]- Result:
> > 
> > | EmpID | Name   | Department | Salary | ProjID | ProjectName |
> > |-------|--------|------------|--------|--------|-------------|
> > | 1     | Alice  | IT         | 75000  | 101    | Website     |
> > | 1     | Alice  | IT         | 75000  | 104    | App Dev     |
> > | 2     | Bob    | HR         | 65000  | 102    | Recruiting  |
> > | 3     | Carol  | Finance    | 80000  | 103    | Budgeting   |
> > | 4     | David  | IT         | 72000  | 101    | Website     |
> > | 4     | David  | IT         | 72000  | 104    | App Dev     |
> > | 5     | Eve    | HR         | 68000  | 102    | Recruiting  |


> [!example]- **Example**: Find names of employees in the IT department with a salary greater than 73000:
> 
> #### π<sub>Name</sub>(σ<sub>Department = 'IT' AND Salary > 73000</sub>(Employee))
> 
> >[!table]- Result:
> > 
> > | Name  |
> > |-------|
> > | Alice |
> 
> This combination first selects the rows that meet the criteria (IT department and salary > 73000) and then projects only the Name column.

