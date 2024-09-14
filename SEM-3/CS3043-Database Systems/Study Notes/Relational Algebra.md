# Relational Algebra

Relational algebra provides a set of operations that can be performed on relations (tables) to query and manipulate data. 

Let's consider two sample relations (tables) for our examples:

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



## 1. Selection (σ)

The selection operation selects tuples (rows) that satisfy a given predicate.

Syntax: σ<sub>predicate</sub>(R)

Example: Find all employees in the IT department.

σ<sub>Department = 'IT'</sub>(Employee)

Result:

| EmpID | Name   | Department | Salary |
|-------|--------|------------|--------|
| 1     | Alice  | IT         | 75000  |
| 4     | David  | IT         | 72000  |

## 2. Projection (π)

The projection operation selects certain attributes (columns) from a relation.

Syntax: π<sub>attribute list</sub>(R)

Example: List only the names and salaries of all employees.

π<sub>Name, Salary</sub>(Employee)

Result:

| Name   | Salary |
|--------|--------|
| Alice  | 75000  |
| Bob    | 65000  |
| Carol  | 80000  |
| David  | 72000  |
| Eve    | 68000  |

## 3. Union (∪)

The union operation combines tuples from two relations, removing duplicates.

Syntax: R ∪ S

Example: List all departments from both Employee and Project tables.

π<sub>Department</sub>(Employee) ∪ π<sub>Department</sub>(Project)

Result:

| Department |
|------------|
| IT         |
| HR         |
| Finance    |

## 4. Set Difference (-)

The set difference operation returns tuples that are in one relation but not in another.

Syntax: R - S

Example: Find departments that have employees but no projects.

π<sub>Department</sub>(Employee) - π<sub>Department</sub>(Project)

Result: (Empty set, as all departments with employees also have projects)

## 5. Cartesian Product (×)

The Cartesian product combines each tuple from one relation with every tuple from another relation.

Syntax: R × S

Example: Combine all employees with all projects (note: this can produce a large result set).

Employee × Project

Partial Result (first few rows):

| EmpID | Name   | Department | Salary | ProjID | ProjectName | ProjDepartment |
|-------|--------|------------|--------|--------|-------------|----------------|
| 1     | Alice  | IT         | 75000  | 101    | Website     | IT             |
| 1     | Alice  | IT         | 75000  | 102    | Recruiting  | HR             |
| 1     | Alice  | IT         | 75000  | 103    | Budgeting   | Finance        |
| 1     | Alice  | IT         | 75000  | 104    | App Dev     | IT             |
| 2     | Bob    | HR         | 65000  | 101    | Website     | IT             |
| ...   | ...    | ...        | ...    | ...    | ...         | ...            |

## 6. Natural Join (⋈)

The natural join combines tuples from two relations based on common attributes.

Syntax: R ⋈ S

Example: Join employees with their respective projects based on the department.

Employee ⋈ Project

Result:

| EmpID | Name   | Department | Salary | ProjID | ProjectName |
|-------|--------|------------|--------|--------|-------------|
| 1     | Alice  | IT         | 75000  | 101    | Website     |
| 1     | Alice  | IT         | 75000  | 104    | App Dev     |
| 2     | Bob    | HR         | 65000  | 102    | Recruiting  |
| 3     | Carol  | Finance    | 80000  | 103    | Budgeting   |
| 4     | David  | IT         | 72000  | 101    | Website     |
| 4     | David  | IT         | 72000  | 104    | App Dev     |
| 5     | Eve    | HR         | 68000  | 102    | Recruiting  |

These operations can be combined to form more complex queries. For example:

Find names of employees in the IT department with a salary greater than 73000:

π<sub>Name</sub>(σ<sub>Department = 'IT' AND Salary > 73000</sub>(Employee))

Result:

| Name  |
|-------|
| Alice |

This combination first selects the rows that meet the criteria (IT department and salary > 73000) and then projects only the Name column.
