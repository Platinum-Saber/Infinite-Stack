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
	- [[#OUTER JOIN]]
		- [[#LEFT OUTER JOIN]]
		- [[#RIGHT OUTER JOIN]]
		- [[#FULL OUTER JOIN]]
	- [[#INNER JOIN]]
2. [[#Views]]
	- [[#VIEW Definition]]
	- [[#View Dependencies]]
	- [[#View Expansion]]
	- [[#Updating a View]]

---
# Joined Relations
- **Join operations** take 2 relations and **return another relation** as a result.
- A join operation is a **Cartesian product** which requires that tuples in the 2 **relations match**.
- *Specifies the* **attributes** that are present in the *result of the join*.
- The join operations are *typically used* as **subquery** expressions in the `FROM` clause.

<br>

## OUTER JOIN
- **Avoids** *loss of information*.
- *Computes the* **join** and *then* **adds tuples** *from one relation that* **doesn't** *match tuples in the other relation* to the result of the join using **null values**. 

#### LEFT OUTER JOIN
- Returns **all the rows from the left table** with matching rows from the right table.
- If there is **no match** *in the right table* those values will be **null**.
- ![[Pasted image 20240820105725.png]]

> [!example] 
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

#### RIGHT OUTER JOIN
- Returns **all the rows from the right table** with matching rows from the left table.
- If there is **no match** *in the left table* those values will be **null**.
- ![[Pasted image 20240820111728.png|600x300]]

> [!example] 
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

#### FULL OUTER JOIN
- Returns **all the rows from the right table** and **all the rows from the left table**.
- *Missing values* will be **null**.
- ![[Pasted image 20240820112332.png]]
> [!warning] Not supported in **MySQL**

> [!example] 
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

## INNER JOIN
- Returns the rows when there is a **match in both tables.**
- ![[Pasted image 20240820113127.png]]


> [!example] 
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
> 

# Views
- Provides a mechanism to **hide** *certain data* from the *view of certain users*.
- Abstract / conceptual model created on top of the actual database.

## VIEW Definition
- Once a view is defined the **view** can be used to *refer to the virtual relation* that the view generates.
-  View definition is **not the same** *as creating a new relation* by evaluating the query expression.
- The view definition causes the **saving of an expression**. The **expression** *is substituted into queries* **using the view**.

> [!note] Definition
> - Defined using the `CREATE VIEW` statement which has the form below,
> ```SQL
> CREATE VIEW v AS  {query expression}
> // v - name of the view
> ```

> [!example] 
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

<br>

## View Dependencies
- One **view** may be *used in the expression defining* **another view**.
- A view is said to be **recursive** if it *depends on* **itself**. 
- A view relation $V_2$ is said to **depend directly** on a view relation $V_1$ , if  $V_1$  is *used in the expression defining* $V_2$ . ($V_1$ :luc_arrow_left: $V_2$) 

> [!example] 
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

## View Expansion
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

## Updating a View
- For a view to be updatable, there must be a one-to-one relationship between the rows in the view and the rows in the underlying table

