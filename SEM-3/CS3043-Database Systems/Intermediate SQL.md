#DatabaseSystems #DB #DB/05 #SQL

# Content

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
- One view may be used in the expression defining another view.




