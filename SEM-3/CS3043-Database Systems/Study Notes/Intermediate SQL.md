---
tags:
  - SQL
  - DatabaseSystems
  - DB
Reviewed: 
Created: 2024-08-28T00:56:00
About: Based on CS3043-Lecture 05 Intermediate SQL
---
Related : #DatabaseSystems #DB #DB/05 #SQL
Reference Note : [Lecture 05](file:///E:%5CAcademics%5CSEM%203%5CCS3043-Database%20Systems%5CLecture%20slide%5CL05%20%20Intermediate%20SQL.pdf)

---
# Content
1. [[#Joined Relations]]
	- [[#1. OUTER JOIN]]
		- [[#1.1 LEFT OUTER JOIN]]
		- [[#1.2 RIGHT OUTER JOIN]]
		- [[#1.3 FULL OUTER JOIN]]
	- [[#2. INNER JOIN]]
2. [[#Views]]
	- [[#1. VIEW Definition]]
	- [[#2. View Dependencies]]
	- [[#3. View Expansion]]
	- [[#4. Updating a View]]
	- [[#5. Materialized Views]]
3. [[#Transactions]]
4. [[#Integrity Constraints]]
	1. [[#Types of Constraints]]
		- [[#1. NOT NULL]]
		- [[#2. PRIMARY KEY]]
		- [[#3. UNIQUE]]
		- [[#4. CHECK]]
		- [[#5. FOREIGN KEY (Referential Integrity)]]
5. [[#Data Types]]
	- [[#1. Built-in Types]]
	- [[#2. User-Defined Types]]
	- [[#3. Domains]]
	- [[#4. Large Object Types]]
6. [[#Indexing]]
	1. [[#Best Practices]]
7. [[#TRUNCATE vs DELETE]]
	1. [[#TRUNCATE]]
	2. [[#DELETE]]

---
# Joined Relations
- **Join operations** take 2 relations and **return another relation** as a result.
- A join operation is a **Cartesian product** which requires that tuples in the 2 **relations match**.
- *Specifies the* **attributes** that are present in the *result of the join*.
- The join operations are *typically used* as **subquery** expressions in the `FROM` clause.

<br>

## 1. OUTER JOIN
- **Avoids** *loss of information*.
- *Computes the* **join** and *then* **adds tuples** *from one relation that* **doesn't** *match tuples in the other relation* to the result of the join using **null values**. 

#### 1.1 LEFT OUTER JOIN
- Returns **all the rows from the left table** with matching rows from the right table.
- If there is **no match** *in the right table* those values will be **null**.

> [!image]- Left outer join diagram
>  ![[Pasted image 20240820105725.png]]

> [!example]- Example 
> > [!info]- INPUT
> > ![[Pasted image 20240820110725.png]]
> 
> 
> > [!info] SQL Query
> > ```SQL
> > SELECT *
> > FROM course LEFT OUTER JOIN prereq
> > ON course.course_id = prereq.course_id
> > 
> > //Different method
> > SELECT *
> > FROM course LEFT OUTER JOIN prereq
> > USING (course_id)
> > ```
> 
> 
> > [!info]- OUTPUT
> > ![[Pasted image 20240820112041.png]]

<br>

#### 1.2 RIGHT OUTER JOIN
- Returns **all the rows from the right table** with matching rows from the left table.
- If there is **no match** *in the left table* those values will be **null**.

> [!image]- Right outer join diagram
>  ![[Pasted image 20240820111728.png|600x300]]

> [!example]- 
> > [!info]- INPUT
> > ![[Pasted image 20240820110725.png]]
> 
> 
> > [!info] SQL Query
> > ```SQL
> > SELECT *
> > FROM course RIGHT OUTER JOIN prereq
> > ON course.course_id = prereq.course_id
> > 
> > //Different method
> > SELECT *
> > FROM course RIGHT OUTER JOIN prereq
> > USING (course_id)
> > ```
> 
> 
> > [!info]- OUTPUT
> > ![[Pasted image 20240820111951.png]]

<br>

#### 1.3 FULL OUTER JOIN
- Returns **all the rows from the right table** and **all the rows from the left table**.
- *Missing values* will be **null**.

> [!image]- Full outer join diagram
> ![[Pasted image 20240820112332.png]]

> [!warning] Not supported in **MySQL**

> [!example]- 
> > [!info]- INPUT
> > ![[Pasted image 20240820110725.png]]
> 
> 
> > [!info] SQL Query
> > ```SQL
> > SELECT *
> > FROM course FULL OUTER JOIN prereq
> > ON course.course_id = prereq.course_id
> > 
> > ```
> 
> 

<br>

## 2. INNER JOIN
- Returns the rows when there is a **match in both tables.**

> [!image]- Inner join diagram
> ![[Pasted image 20240820113127.png]]


> [!example]- 
> > [!info]- INPUT
> > ![[Pasted image 20240820110725.png]]
> 
> 
> > [!info] SQL Query
> > ```SQL
> > SELECT *
> > FROM course INNER JOIN prereq
> > ON course.course_id = prereq.course_id
> > 
> > //method 2
> > SELECT *
> > FROM course INNER JOIN prereq
> > USING (course_id)
> > ```


---
<br>
<br>

# Views
- Provides a mechanism to **hide** *certain data* from the *view of certain users*.
- Abstract / conceptual model created on top of the actual database.

## 1. VIEW Definition
- Once a view is defined the **view** can be used to *refer to the virtual relation* that the view generates.
-  View definition is **not the same** *as creating a new relation* by evaluating the query expression.
- The view definition causes the **saving of an expression**. The **expression** *is substituted into queries* **using the view**.

> [!note]- Definition
> - Defined using the `CREATE VIEW` statement which has the form below,
> ```SQL
> CREATE VIEW v AS  {query expression}
> // v - name of the view
> ```

> [!example]- View Creation examples
> > [!info] View of instructors without their salary
> > ```SQL
> > CREATE VIEW faculty AS
> > SELECT ID, name, dept_name
> > FROM instructor 
> > ```
> 
> > [!info] Create a view of department salary totals
> > ```SQL
> > CREATE VIEW department_total_salary (dept_name, total_salary) AS
> > SELECT dept_name, SUM(salary)
> > FROM instructor
> > GROUP BY dept_name
> > ```

> [!info]- Using a View:
> - Views can be queried just like regular tables:
> 
> ```sql
> SELECT name
> FROM faculty
> WHERE name LIKE 'P%';
> ```
> This query returns names of Computer Science faculty members whose names start with 'P'.

<br>

## 2. View Dependencies
- One **view** may be *used in the expression defining* **another view**.
- A view is said to be **recursive** if it *depends on* **itself**. 
- A view relation $V_2$ is said to **depend directly** on a view relation $V_1$ , if  $V_1$  is *used in the expression defining* $V_2$ . ($V_1$ :luc_arrow_left: $V_2$) 

> [!example]- 
> > [!info] SQL Query
> > ```SQL
> > CREATE VIEW physics_fall_2009 AS
> > SELECT course.course_id, sec_id, building, room_number
> > FROM course, section
> > WHERE course.course_id = section.course_id
> > 	AND course.dept_name = 'Physics'
> > 	AND section.semester = 'Fall'
> > 	AND section.year = '2009'
> > 
> > //dependent view
> > CREATE VIEW physics_fall_2009_watson AS
> > SELECT course_id, room_number
> > FROM physics_fall_2009
> > WHERE building = 'Watson'
> > ```

<br>

## 3. View Expansion
- A way to define the meaning of views defined in terms of other views.
- Let the view $v_1$ be defined by an expression $e_1$ that may itself contain uses of view relations.

> [!note] Replacement step of view expansion 
> ```pascal
> repeat
> 	Find any view relation v_i in e_1
> 	Replace the view relation v_i by the expression defining v_i
> until no more view relations are present in e_1
> ```

- As long as the *view definitions* **aren't recursive**, this *loop will terminate*.

<br>

## 4. Updating a View
- For a view to be updatable, there must be a one-to-one relationship between the rows in the view and the rows in the underlying table.

- Not all views are updatable. For a view to be updatable:
	- The `FROM` clause should have only one table
	- The `SELECT` clause should only contain column names (**no expressions or aggregates**)
	- Should not have `GROUP BY` or `HAVING` clauses

> [!info]- SQL example code 
> Updatable view:
> 
> ```sql
> CREATE VIEW computerscience_instructors AS
> SELECT ID, name, salary
> FROM instructor
> WHERE dept_name = 'Computer Science';
> 
> -- This update is allowed
> UPDATE computerscience_instructors
> SET salary = salary * 1.05
> WHERE ID = '10101';
> ```

<br>

## 5. Materialized Views:
- Some databases support materialized views, which store the query results physically.

> [!info] SQL code
> ```sql
> CREATE MATERIALIZED VIEW dept_total_salary AS
> SELECT dept_name, SUM(salary) as total_salary
> FROM instructor
> GROUP BY dept_name;
> ```

>[!warning] MySQL doesn't support materialized views natively.

---
<br>
<br>

# Transactions
- Transactions ensure that a series of SQL operations are executed as a single unit of work, following the `ACID` properties: **Atomicity**, **Consistency**, **Isolation**, and **Durability**.

> [!info] SQL example of a transaction:
> 
> ```sql
> START TRANSACTION;
> 
> UPDATE account SET balance = balance - 100 WHERE account_id = 'A';
> UPDATE account SET balance = balance + 100 WHERE account_id = 'B';
> 
> -- If both updates are successful
> COMMIT;
> 
> -- If there's an error
> -- ROLLBACK;
> ```
> 

This transaction transfers $100 from account A to account B. Either both updates happen, or neither does.

---
<br>
<br>

# Integrity Constraints
- Integrity constraints maintain the accuracy and consistency of data in the database.

## Types of Constraints:

#### 1. NOT NULL
- Ensures a column **cannot** have `NULL` values.

> [!info] SQL code
> ```sql
> CREATE TABLE student (
>     ID CHAR(5) NOT NULL,
>     name VARCHAR(20) NOT NULL,
>     dept_name VARCHAR(20)
> );
> ```

#### 2. PRIMARY KEY
- **Uniquely** identifies each record in a table.

> [!info] SQL code
> ```sql
> CREATE TABLE course (
>     course_id CHAR(5) PRIMARY KEY,
>     title VARCHAR(50),
>     dept_name VARCHAR(20),
>     credits NUMERIC(2,0)
> );
> ```
> 

#### 3. UNIQUE
- Ensures all values in a column are different.

> [!info] SQL code
> ```sql
> CREATE TABLE instructor (
>     ID CHAR(5),
>     name VARCHAR(20) UNIQUE,
>     dept_name VARCHAR(20),
>     salary NUMERIC(8,2)
> );
> ```

#### 4. CHECK
- Ensures that all values in a column satisfy certain conditions.

> [!info] SQL code
> ```sql
> CREATE TABLE section (
>     course_id VARCHAR(8),
>     sec_id VARCHAR(8),
>     semester VARCHAR(6),
>     year NUMERIC(4,0),
>     CHECK (semester IN ('Fall', 'Winter', 'Spring', 'Summer')),
>     CHECK (year > 1701 AND year < 2100)
> );
> ```

#### 5. FOREIGN KEY (Referential Integrity)
- Ensures values in one table exist in another table.

> [!info] SQL code
> ```sql
> CREATE TABLE course (
>     course_id CHAR(5) PRIMARY KEY,
>     title VARCHAR(50),
>     dept_name VARCHAR(20),
>     FOREIGN KEY (dept_name) REFERENCES department(dept_name)
>         ON DELETE SET NULL
>         ON UPDATE CASCADE
> );
> ```
>This ensures that every dept_name in the course table exists in the department table. If a department is deleted, the dept_name in course becomes NULL. If a department name is updated, it's automatically updated in the course table too.

---
<br>

# Data Types

SQL provides various built-in data types and allows creation of user-defined types.

## 1. Built-in Types:
#### `DATE`: Stores date in 'YYYY-MM-DD' format
  - Example: DATE '2023-09-15'
#### `TIME`: Stores time in 'HH:MM:SS' format
 -  Example: TIME '14:30:00'
#### `TIMESTAMP`: Combines date and time
-  Example: TIMESTAMP '2023-09-15 14:30:00.00'
#### `INTERVAL`: Represents a duration
-  Example: INTERVAL '2' DAY

<br>

## 2. User-Defined Types:

> [!info] Create custom data types:
> 
> ```sql
> CREATE TYPE Dollars AS NUMERIC(12,2) FINAL;
> 
> CREATE TABLE department (
>     dept_name VARCHAR(20),
>     budget Dollars
> );
> ```
> 

<br>

## 3. Domains:
- Domains are user-defined data types with constraints:

> [!info] SQL code
> ```sql
> CREATE DOMAIN age_type AS INTEGER CHECK (VALUE >= 0 AND VALUE < 150);
> 
> CREATE TABLE person (
>     name VARCHAR(50),
>     age age_type
> );
> ```
> 

<br>

## 4. Large Object Types:
- `BLOB`: Binary Large Object, for storing binary data like images
- `CLOB`: Character Large Object, for storing large text data

> [!info] SQL example:
> 
> ```sql
> CREATE TABLE documents (
>     doc_id INTEGER PRIMARY KEY,
>     doc_content CLOB
> );
> ```
> 

---
<br>
<br>

# Indexing
- Indexes are used to speed up data retrieval operations on database tables.

> [!info] Creating an index:
> 
> ```sql
> CREATE INDEX student_name_index ON student(name);
> ```
> This creates an index on the 'name' column of the 'student' table.

> [!info] Composite index (index on multiple columns):
> 
> ```sql
> CREATE INDEX course_offering_index ON section(course_id, semester, year);
> ```
> 

## Best Practices:
- Use indexes on frequently queried columns
- Index foreign key columns
- Don't overuse indexes, as they impact insert/update performance

> [!info] Example of using an index:
> 
> ```sql
> -- This query can use the student_name_index
> SELECT * FROM student WHERE name = 'John Doe';
> ```
> 

---
<br>
<br>

# TRUNCATE vs DELETE

### TRUNCATE:
- DDL (Data Definition Language) statement
- Faster, empties entire table
- Cannot be rolled back (in MySQL)
- Doesn't invoke ON DELETE triggers

> [!info] Truncate example:
> ```sql
> TRUNCATE TABLE temp_logs;
> ```


### DELETE:
- DML (Data Manipulation Language) statement
- Can use WHERE clause to delete specific rows
- Can be rolled back
- Invokes ON DELETE triggers

> [!info] Delete example:
> ```sql
> DELETE FROM student
> WHERE graduation_year < 2020;
> ```
> This deletes all students who graduated before 2020.

> [!warning] while `DELETE` can be more precise, `TRUNCATE` is much faster for removing all data from a large table.
