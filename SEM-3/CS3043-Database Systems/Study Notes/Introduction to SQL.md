---
tags:
  - "#DatabaseSystems"
  - DB
  - "#DB/03"
  - SQL
Reviewed: false
Created: 2024-08-21T10:19:00
About: Based on CS3043-Lecture 03 Introduction to SQL
---
Related : #DatabaseSystems #DB #DB/03 #SQL 

---
Reference Video : [Online video](https://www.youtube.com/watch?v=7S_tz1z_5bA)
Reference Notes : [Online notes](https://www.w3schools.com/MySQL/mysql_join.asp)

<br>

---
# Content

1. [[#History]]
2. [[#SQL]]
	- [[#CREATE TABLE Construct]]
	- [[#DROP and ALTER TABLE Constructs]]
	- [[#Basic Query Structure]]
	- [[#SELECT Clause]]
	- [[#WHERE Clause]]
	- [[#FROM Clause]]
	- [[#JOINS]]
	- [[#Rename Operation]]
	- [[#Ordering The Results]]
	- [[#String Operations]]
	- [[#Aggregate functions]]
	- [[#GROUP BY Clause]]
	- [[#HAVING Clause]]
	- [[#NULL Values]]
	- [[#Nested Subqueries]]

<br>

****
# History
>[!note] Brief History of SQL
>- IBM Sequel Language was developed as a  part of System R project at IBM San Jose Research Lab.
>- It was renamed into **Structured Query Language** (`SQL`)

<br>
<br>

****
# SQL
>[!FAQ]- What is **SQL**
>It's a **very high level** language used for **Data Definition** and **Data Manipulation**

>[!abstract]- Data Types in SQL
>- `char(n)` : Fixed length character string with user specified length '*n*'
>- `varchar(n)` : Variable length character strings with user specified maximum length '*n*'
>- `int` : Integer
>- `smallint` : Small integer.
>- `numeric(p,d)` : Fixed point number with user specified precision of '*p*' digits, with '*d*' digits to the right of the decimal point.
>- `real, double precision` : Floating point and double precision floating point numbers
>- `float(n)` : Floating point number with user specified precision of at least '*n*' digits.

<br>

## CREATE TABLE Construct
>[!note]- An `sql` relation is defined using **CREATE TABLE** construct

> [!tip] How to create a table 
> ```sql
> CREATE TABLE r(A_1 D_1, A_2, D_2,...., A_n D_n
> 				(integrity constraint_1),
> 				...,
> 				(integrity constrain_n)
> )
> ```
>`r` - name of the relation
>`A_1` - Attribute name in the schema of the relation
> `D_1` - Data type of values in the domain of attribute A_1
> 
> > [!example]- Example
> > ```sql
> > CREATE TABLE instructor (
> >	ID char(5),
> > 	name varchar(20) not null,
> >	dept_name varchar(20),
> > 	salary numeric(8,2)
> >)
>> ```

<br>

### Integrity constraints
>[!abstract] Available integrity constraints in CREATE TABLE
>- `not null`
>- `primary key(A_1, A_2, ...)`
>- `foreign key (A_k, A_j, ...)`
>
>>[!warning] `primary key` declaration on an attribute automatically ensures `not null`
>
>
 >>[!example]- Example
 >>```sql
 >>	CREATE TABLE instructor (
 >>		ID char(5),
 >>		name varcahr(20) not null,
 >>		dept_name varcahr(20),			
 >>		salary numeric(8,2),
 >>		primary key (ID),
 >>		foreign key (dept_name)
 >>			references department(dept_name)
 >>	)
 >>```

<br>
<br>

## DROP and ALTER TABLE Constructs

<br>

**DROP TABLE (table_name)** ::  Deletes the table and its content

**DELETE FROM (table_name)** ::  Deletes all the content of the table but retains the table.

>[!note]- **ALTER TABLE**
>>[!info] **ALTER TABLE** r **ADD** A D
>>- where `A` is the name of the attribute to be added to relation `r`and `D` is the domain/data type of `A`.
>>- All tuples in the relation are assigned `null` as the value of the new attribute.
>
>>[!info] **ALTER TABLE** r **DROP** A
>>- where A is the name of an attribute in relation r.
>>> [!warning] Many databases do not support this functionality

<br>
<br>

## Basic Query Structure

>[!note] SQL Query
>
>- SQL is also a data manipulation language
>>[!info] Typical SQL structure
>>```SQL
>>SELECT A1, A2, A3
>>FROM r1, r2, r3
>>WHERE P
>>```
>>A => attribute
>>r => relation
>>P => Predicate
>
>**Result of a query is another relation**

<br>
<br>

## SELECT Clause
- The `SELECT` clause *list the attributes* desired in the result of a query. (corresponds to the projection operation of the relational algebra)

>[!info] SQL Query
>```SQL
>SELECT dept_name
>FROM instructor
>```
>
>>[!warning] SQL names are case **insensitive**.

<br>

- To force the *elimination of duplicates*, insert the **keyword** `DISTINCT` after `SELECT`

>[!info] SQL Query
>```SQL
>SELECT DISTINCT dept_name
>FROM instructor
>```

<br>

- An  *asterisk* ✳ in the `SELECT` clause denotes **All Attributes**

>[!info] SQL Query
>```SQL
>SELECT * FROM instructor
>```

<br>

- The `SELECT` clause can contain *arithmetic expressions* involving the operators **+, -,  /,** and operating on **constants or attributes of tuples.**

>[!info] SQL Query
>```SQL
>SELECT ID, name, salary/12
>FROM instructor
>```

<br>
<br>

## WHERE Clause
- `WHERE` clause specifies the **condition** that the *results must satisfy*.
	- corresponds to the **selection predicate** of the relational algebra.
- Comparison *results can be combined* using the logical connectives **and, or, not**.
- **Comparisons** can be applied to *results of arithmetic expressions.*

>[!info] SQL Query
>```SQL
>SELECT name
>FROM instructor
>WHERE dept_name = 'Comp. Sci.' AND salary > 80000
>```

<br>

#### WHERE Clause Predicates
- `BETWEEN` comparison operator

> [!info] SQL Query
> ```SQL
> SELECT name
> FROM instructor
> WHERE salary BETWEEN 90000 AND 100000
> ```

- Tuple comparison

> [!info] SQL Query
> ```SQL
> SELECT name
> FROM instructor
> WHERE (instructor.ID, dept_name) = (teaches.ID, 'Biology')
> ```

<br>
<br>

## FROM Clause
- `FROM` clause **lists the relations** involved in the query.
	- Corresponds to the *cartesian product operation* of the relational algebra.

> [!info] SQL Query
> ```SQL
> SELECT *
> FROM instructor, teaches
> ```
> Generates every possible **instructor - teaches pair**, *with all attributes from both relations*.

<br>
<br>

## JOINS 
#### NATURAL JOIN

> [!example] 
> > [!info] Without `NATURAL JOIN`
> > ```SQL
> > SELECT name, course_id
> > FROM instructor, teaches
> > WHERE instructor.id = teaches.id
> > ```
> 
> > [!info] With `NATURAL JOIN`
> > ```SQL
> > SELECT name, course_id
> > FROM instructor NATURAL JOIN teaches
> > ```

<br>

> [!warning] Dangers in **NATURAL JOIN**
> *Unrelated attributes* with the **same name** can get *equated incorrectly*.
> 
> > [!info] Incorrect version (`makes course.dept_name = instructor.dept_name`)
> > ```SQL
> > SELECT name, title
> > FROM instructor NATURAL JOIN teaches NATURAL JOIN course
> > ```
>  
> > [!info] Correct version 1,2
> > ```SQL
> > SELECT name, title
> > FROM instructor NATURAL JOIN teaches, course
> > WHERE teaches.course_id = course.course_id
> > 
> > SELECT name, title
> > FROM (instructor NATURAL JOIN teaches) JOIN course USING (course_id)
> > ```

<br>
<br>

## Rename Operation
- SQL allows **renaming relations and attributes** using the `AS` clause.

> [!info] SQL Query
> ```SQL
>SELECT ID, name, salary/12 AS monthly_salary
>FROM instructor 
>```

- Keyword `AS` is **optional** & *can be omitted*.

> [!info] SQL Query
> ```SQL
>SELECT ID, name, salary/12 monthly_salary
>FROM instructor 
>```

<br>
<br>

## Ordering The Results
- List in alphabetic order.
- **Ascending** order is the *default*.
- Can *specify descending* order using `DESC` and *ascending* order using `ASC` for each attribute.
- Can sort multiple attributes.

> [!info] SQL Query
> ```SQL
> SELECT DISTINCT name
> FROM instructor
> ORDER BY name ASC
>```

<br>
<br>

## String Operations

- `LIKE` operator can be used for *string matching*.
- *Patterns* are **case sensitive**.
- SQL supports a variety of string operations such as,
	- concatenation using `||`
	- match any substring using `%`
	- match any character using `_`
	- escape character for `%` or `_`using `\`

> [!info] SQL Query
> ```SQL
> SELECT name 
> FROM instructor
> WHERE name LIKE "%dar%"
> ```

<br>
<br>

## Aggregate functions
- Operates on the *multiset of values* of a **column** of a **relation**, and *return a value*.
	- `AVG` : average value
	- `MIN` : minimum value 
	- `MAX` : maximum value
	- `SUM` : sum of values
	- `COUNT` : number of values

> [!info] SQL Query
> ```SQL
> SELECT AVG(salary)
> FROM instructor
> WHERE dept_name = 'Comp. Sci.'
> 
> SELECT COUNT(DISTINCT ID)
> FROM teaches 
> WHERE semester = 'Spring' AND year = 2010
> 
> SELECT COUNT (*)
> FROM course
> ```

<br>

#### GROUP BY Clause
- Attributes in `SELECT` clause *outside* of the **aggregate functions** *must appear in* `GROUP BY` list.

> [!info] SQL Query
> ```SQL
> SELECT dept_name, AVG(salary)
> FROM instruntor`
> GROUP BY dept_name
> ```

<br>

#### HAVING Clause
- Predicates in the `HAVING` clause are *applied* **after** *the formation of groups* where as predicates in the `WHERE` clause are *applied* **before** *forming groups*.

> [!info] SQL Query
> ```SQL
> SELECT dept_name, AVG(salary)
> FROM instructor
> GROUP BY dept_name
> HAVING AVG(salary) > 42000
> ```

<br>

#### NULL Values
- *All aggregate operations* **except** `COUNT(*)` *ignore tuples with* **null values** on the aggregated attributes.
	- If all collections have null values then 
		- `COUNT` returns `0`
		- All other aggregates return `null`

> [!info] SQL Query
> ```SQL
> SELECT SUM(salary)
> FROM instructor
> 
> // statement ignores all the null values but the result becomes null if there are only null values in the salary column
> ```

<br>
<br>

## Nested Subqueries
- `subquery` is a **select-from-where** expression nested within another query.
- common uses of **subqueries** is to perform tests for *set membership*, *set comparison*, and *set cardinality*.

> [!info] SQL Query
> ```SQL
> // Find courses offered in Fall 2009 and in Spring 2010
> 
> SELECT DISTINCT course_id
> FROM section
> WHERE semester = 'Fall' AND year = 2009 AND
> 		course_id IN (SELECT course_id
> 						FROM section
> 						WHERE semester = 'Spring' AND year = 2010)
> 						
> 						
>// Find courses offered in Fall 2009 but not in Spring 2010
>
> SELECT DISTINCT course_id
> FROM section
> WHERE semester = 'Fall' AND year = 2009 AND
> 		course_id NOT IN (SELECT course_id
> 						FROM section
> 						WHERE semester = 'Spring' AND year = 2010)
> ```

<br>

---
Up Next : [[Intermediate SQL]]


