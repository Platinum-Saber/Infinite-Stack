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
>[!info] **DROP TABLE (table_name)** ::  Deletes the table and its content

>[!info] **DELETE FROM (table_name)** ::  Deletes all the content of the table but retains the table.

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

[?]
<br>

## SELECT Clause
