Related : #DatabaseSystems #DB #DB/01

<br>

# Database Management Systems

<br>

>[!note]- Database Management System
>DBMS contains information about a particular enterprise
>>[!info] DBMS facilitates,
>>- Collection of interrelated data
>>- Set of programs to access data
>>- An environment that is both convenient and efficient to use

>[!example]- Examples for Database Applications
>- Banking transactions
>- Airlines  : reservations, schedules
>- Universities  : registration, grades
>- Sales  : customers, products
>- Manufacturing  : inventory, supply chain
>- Online retailers  : order tracking
>- Human resources  : employee records, salaries

>[!warning]- Drawbacks of using file systems to store data
>- **Data redundancy and inconsistency** (multiple file formats, duplication of information)
>- **Difficulty in increasing data** (Need to write a new program to carry out each new task)
>- **Data isolation** (multiple file formats)
>- **Integrity problems**
>	- Integrity constraints become buried in program code rather than being stated explicitly 
>	- Hard to add new constraints or change existing ones
>- **Atomicity of updates**
>	- Failures may leave database in an inconsistent state with partial updates carried out
>- **Concurrent access by multiple users**
>	- Concurrent access needed for performance
>	- uncontrolled concurrent access can lead to inconsistencies
>- **Security problems** (Hard to provide user access to some, but not all data)

<br>
<br>

### Levels of Abstraction of a DBMS
>[!abstract]- Levels of Abstraction
>>[!info]- Physical level
>>Describes data stored in database, and the relationships among the data.
>
>>[!info]- Logical level
>>Describes data stored in database, and the relationships among data.
>
>>[!info]- View level
>>Application programs hide details of data types. Views can also hide information for security purposes.

>[!info]- Architecture for a database system
>![[Pasted image 20240718082934.png]]

<br>

****

<br>

Up Next : [[Database Design Using the E-R Model]]

