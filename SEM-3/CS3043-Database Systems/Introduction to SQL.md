# History
>[!note] Brief History of SQL
>- IBM Sequel Language was developed as a  part of System R project at IBM San Jose Research Lab.
>- It was renamed into **Structured Query Language** (`SQL`)

<br>
<br>

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

> [!example] Example
> ```sql
> CREATE TABLE instructor (
> 	ID char(5),
> 	name varchar(20) not null,
> 	dept_name varchar(20),
> 	salary numeric(8.2)
> )
> ```
