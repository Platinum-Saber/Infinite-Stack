---
tags:
  - DatabaseSystems
  - DB
Reviewed: 
Created: 2024-08-07T16:00:00
About: Based on CS3043-Lecture 01 Introduction to Database Systems
---
Related : #DatabaseSystems #DB #DB/01

---

# Content




---

<br>


# 1. Introduction to Database Management Systems

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

# 2. Database Architecture and Abstraction Levels
>[!abstract]- Levels of Abstraction
>>[!info]- Physical level
>>Describes how a record is stored.
>
>>[!info]- Logical level
>>Describes data stored in database, and the relationships among data.
>
>>[!info]- View level
>>Application programs hide details of data types. Views can also hide information for security purposes.

>[!image]- Architecture for a database system
>![[Pasted image 20240718082934.png]]

### Instances and Schemas
- `Schema`: The logical structure of the database
- `Instance`: The actual content of the database at a particular point in time

### Data Independence
- Physical Data Independence: Ability to modify physical schema without changing logical schema
- Logical Data Independence: Ability to modify logical schema without changing application programs

<br>

# 3. Data Models

 > [!abstract]- Types of Data Models
> - Relational Model (most common)
> - Entity-Relationship Model (for database design)
> - Object-based Models (Object-oriented and Object-relational)
> - Semistructured Data Model (XML)

### The Relational Model
- Data organized in tables (relations)
- Each table consists of rows (tuples) and columns (attributes)
- Each attribute has a domain (set of allowed values)

<br>

# 4. Database Languages

### Data Definition Language (DDL)
****
- Used to define database schemas
- Example: `CREATE TABLE`, `ALTER TABLE`, `DROP TABLE`
- DDL compiler generates a set of table templates stored in a `data dictionary`.
- **Data dictionary** contains meta data. (data about data like integrity constraints)

### Data Manipulation Language (DML)

- Used for accessing and manipulating data
- SQL is the most widely used query language (both DDL and DML)

> [!info]- Two types of DML:
>   1. **Procedural**: Specifies what data is required and how to get it
>   2. **Declarative**: Specifies what data is required without specifying how to get it

<br>

# 5. Database Design

### Logical Design
- Deciding on the database schema
- Involves both business and computer science decisions

### Physical Design
- Deciding on the physical layout of the database

### Design Approaches

> [!NOTE]- Normalization Theory
>    - Formalizes what designs are bad and tests for them

> [!NOTE]- Entity-Relationship Model
>    - Models an enterprise as a collection of entities and relationships

# 6. Key Database Concepts

### Keys
- Superkey: Set of attributes that can uniquely identify a tuple
- Candidate Key: Minimal superkey
- Primary Key: The chosen candidate key
- Foreign Key: Attribute(s) referring to a primary key in another relation

### Relational Algebra
Basic operators:
- Select (σ): Selects tuples based on a condition
- Project (Π): Selects attributes from a relation
- Union (∪): Combines tuples from two relations
- Set Difference (−): Returns tuples in one relation but not in another
- Cartesian Product (×): Combines each tuple from one relation with every tuple from another
- Rename (ρ): Renames attributes or relations

Additional operators:
- Intersection (∩): Returns tuples common to both relations
- Natural Join (⋈): Combines related tuples from two relations based on common attributes

# 7. Database Engine Components

### Storage Manager
- Provides interface between low-level data stored in the database and application programs
- Responsible for data storage, retrieval, and updating

### Query Processor
- Translates queries into low-level instructions
- Optimizes queries for efficient execution

### Transaction Manager
- Ensures database consistency despite system failures
- Controls concurrent access to data

# 8. Database Users and Administrators

### Types of Users
- Naive users: Interact with the system through application programs
- Application Programmers: Develop programs using database access
- Sophisticated Users: Interact directly with the DBMS using query languages

### Database Administrator (DBA)
- Responsible for overall management of the database system
- Duties include schema definition, storage structure and access method definition, and schema and physical organization modification

# 9. Database System Evolution

### Historical Overview
- 1950s-1960s: Magnetic tapes and punched cards
- Late 1960s-1970s: Hard disks, network and hierarchical models, relational model introduced
- 1980s: Commercial relational systems, SQL standardization
- 1990s: Large-scale decision support, data mining, web databases
- 2000s: XML, automated administration, big data systems

### Current Trends
- Big Data and NoSQL databases
- Cloud databases
- In-memory databases
- Machine learning and AI integration

****

<br>

Up Next : [[Database Design Using the E-R Model]]

