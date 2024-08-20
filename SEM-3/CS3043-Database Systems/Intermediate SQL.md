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
> > ![[Pasted image 20240820110759.png]]

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

