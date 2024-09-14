---
tags:
  - DatabaseSystems
  - DB
  - ERD
Reviewed: 
Created: 2024-08-14T22:51:00
About: Based on CS3043-Lecture 02 Database design using E-R models
---
Related : #DatabaseSystems #DB/02 #ERD

---
# Content
[[#1. Design Process]]
- [[#Design Phases]]
[[#2. ER Model]]
- [[#Entity Sets]]
- [[#Attributes]]
- [[#Relationship Sets]]
- [[#Cardinality]]
	- [[#One-to-One (1 1) Relationship]]
	- [[#One-to-Many (1 N) Relationship]]
	- [[#Many-to-Many (M N) Relationship]]
[[#3. ER Diagram Notation]]
- [[#Keys and Identifiers]]
- [[#Primary Key]]
- [[#Weak Entities]]
[[#4. Participation Constraints]]
[[#5. Specialization and Generalization]]
[[#6. Aggregation]]
[[#7. Reduction to Relational Schemas]]
[[#8. Design Issues and Best Practices]]
[[#9. Alternative Notations]]

---

<br>

# 1. Design Process

## Design Phases

```mermaid
flowchart LR
Requirements --> Conceptual_design --> Logical_design --> Physical_design

```

<br>

>[!abstract]- Design phases
>>[!info]- Initial phase
>>Characterize fully the data needs of the prospective database users.
>
>>[!info]- Second phase
>>Choosing a data model
>>- Applying the concepts of the chosen data model
>>- Translating these requirements into a conceptual schema of the database
>>- A fully developed conceptual schema indicates the functional requirements of the enterprise (kinds of operations that will be performed on the data)
>
>>[!info]- Final phase
>>Moving from abstract data model to the implementation of the database
>>- Logical design (Deciding the database schema)
>>- Physical design (Deciding the physical layout of the database)

>[!warning]- Major pitfalls to avoid in designing a database schema
>>[!error]- Redundancy
>
>>[!error]- Incompleteness

>[!abstract]- Design Approaches
>>[!info]- Entity relationship Model
>>- Models that enterprise as a collection of `entities` and `relationships`
>>- Represented diagrammatically by an *entity-relationship diagram*
>
>>[!info]- Normalization
>>Formalize what designs are bad and test for them

<br>

# 2. ER Model
>[!FAQ]- Why was the ER data model developed
>To facilitate database design by allowing specification of an `enterprise schema` that represents the overall logical structure of the database

>[!abstract]- Basic concepts used in ER-data model
>- entity sets
>- relationship sets
>- attributes

>[!tip] The ER model also has an associated diagrammatic representation, the `ER diagram` which can express the overall logical structure of a database graphically

<br>

## Entity Sets
>[!FAQ]- What is an `entity`
>An object that exists and is distinguishable from other objects

>[!FAQ]- what is an `Entity Set`
>A set of entities of the same type that share the same properties

>[!note]- Attributes
>An entity is represented by a set of **attributes** (descriptive properties possessed by all members of an entity set).
>A subset of the attributes form a **`primary key`** 🔑 of the entity set. (uniquely identifying each member of the set)

>[!tip]- How to represent **entity sets** graphically
>- Rectangles represents entity sets
>- Attributes are listed inside the entity rectangle
>- Underline indicates **primary key 🗝 ** attribute
>
>![[Pasted image 20240704100409.png]]

<br>

## Attributes

Attributes describe the properties of an entity:
- **Simple Attribute**: Cannot be divided further (e.g., Name).
- **Composite Attribute**: Composed of multiple subparts (e.g., Address can be split into Street, City, Zip).
- **Derived Attribute**: Can be computed from other attributes (e.g., Age derived from Date of Birth).

**Composite Attribute Example (Address)**:
```plaintext
   Address
   +------------------------+
   | Street, City, Zip Code  |
   +------------------------+
```

**Student Entity with Composite and Simple Attributes**:
```plaintext
+------------+
|  Student   |
+------------+
|  ID        |
|  Name      |
|  Address   |
|   -Street  |
|   -City    |
|   -Zip     |
+------------+
```

<br>

## Relationship Sets
>[!info] A **relationship** is an association among several entities.

>[!info]- A **relationship set** is a mathematical relation among 2 or more entities each taken from entity sets
> { $(\ e_1 ,\ e_2,\ ... \ e_n\ ) |\ e_1 \ \in \ E_1,\ e_2 \ \in \ E_2,\ ...\ e_n\  \in \ E_n$ }

<br>

## Cardinality

- **Cardinality** defines how many instances of one entity relate to another entity in a relationship.

### One-to-One (1:1) Relationship:
- Each entity in one entity set corresponds to one and only one entity in another entity set.

> [!image]- Example diagram:  
> A **Student** has one **Advisor**, and each **Advisor** is assigned to one **Student**.
> ![[Pasted image 20240914235425.png]]

### One-to-Many (1:N) Relationship:
- One entity in an entity set can be associated with multiple entities in the other set.

> [!image]- Example diagram   
> An **Instructor** can advise many **Students**, but each **Student** has only one **Advisor**.
> ![[Pasted image 20240914235533.png]]

### Many-to-Many (M:N) Relationship:
- Multiple entities from one entity set are associated with multiple entities from another set.

> [!image]- Example diagram  
> A **Student** can take multiple **Courses**, and each **Course** can have multiple **Students**.
> ![[Pasted image 20240915000914.png]]
> 

<br>

# 3. ER Diagram Notation

ER diagrams use specific symbols to represent different elements:

| Element | Symbol |
|---------|--------|
| Entity Set | Rectangle |
| Relationship Set | Diamond |
| Attribute | Oval |
| Primary Key | Underlined Attribute |
| Weak Entity Set | Double Rectangle |
| Identifying Relationship | Double Diamond |

> [!image]- ER notations
> ![[Pasted image 20240915003223.png]]
> ![[Pasted image 20240915003236.png]]
> ![[Pasted image 20240915003303.png]]

## Keys and Identifiers

### Primary Key
- A **Primary Key** is an attribute or a set of attributes that uniquely identifies each entity in an entity set. No two entities can share the same primary key value.

**Example**:
- The `student_id` is the primary key in the **Student** entity set.
```plaintext
+------------+
|  Student   |
+------------+
| *ID        |  ← Primary Key
|  Name      |
|  Age       |
+------------+
```

### Weak Entities
- A **Weak Entity** is an entity that cannot be uniquely identified by its own attributes and depends on a **Strong Entity**.
- A **Discriminator** is used to uniquely identify weak entities in combination with the primary key of the strong entity.

**Example**:  
A **Section** entity depends on the **Course** entity, and its unique identifier is a combination of `course_id`, `section_id`, and `year`.
> [!image]- ER Diagram of Weak Entity:
>  ![[Pasted image 20240915001406.png]]
> The **Section** is a weak entity depending on the **Course**.

<br>

# 4. Participation Constraints

- **Total Participation**: Every entity in the entity set participates in at least one relationship in the relationship set. (indicated using double lines)
- **Partial Participation**: Some entities may not participate in any relationship in the relationship set.

> [!image]- Participant constraints diagram
> ![[Pasted image 20240915001627.png]]
> Here participation of student in advisor relation is total
> participation of instructor in advisor is partial


<br>

# 5. Specialization and Generalization

- **Specialization**: Top-down design process; designating subgroupings within an entity set.
- **Generalization**: Bottom-up design process; combining entity sets with shared features into a higher-level entity set.

Example:
```
Person
  |
  |-- Employee
  |     |-- Instructor
  |     |-- Secretary
  |
  |-- Student
        |-- Graduate
        |-- Undergraduate
```


- **Specialization**: Represented by a triangle and an “ISA” relationship.
```plaintext
+-------------+
|   Employee  |
+-------------+
      |
      ISA
     /   \
+-----------+ +------------+
| Faculty   | |   Staff    |
+-----------+ +------------+
```


<br>

# 6. Aggregation

Aggregation allows treating a relationship set as an entity set for purposes of participating in other relationship sets.

Example:
```
(proj_guide(student, project, instructor)) --- eval_for --- evaluation
```

> [!image]- Aggregation diagram
> >[!fail]- Before
> > ![[Pasted image 20240915002626.png]]
> 
> 
> >[!success]- After
> > ![[Pasted image 20240915002604.png]]

<br>
<br>

# 7. Reduction to Relational Schemas

The ER model can be converted to relational schemas:
- Each entity set and relationship set becomes a relation schema
- Attributes become attributes of the relation schemas

Example:
```sql
CREATE TABLE instructor (
    ID INT PRIMARY KEY,
    name VARCHAR(50),
    salary DECIMAL(10, 2)
);

CREATE TABLE advisor (
    student_id INT,
    instructor_id INT,
    PRIMARY KEY (student_id, instructor_id),
    FOREIGN KEY (student_id) REFERENCES student(ID),
    FOREIGN KEY (instructor_id) REFERENCES instructor(ID)
);
```

<br>
<br>

# 8. Design Issues and Best Practices

- Choose between entities and attributes based on the complexity and importance of the concept.
- Decide whether a concept should be an entity set or a relationship set.
- Use ternary relationships judiciously; sometimes binary relationships are more appropriate.
- Consider using weak entity sets for dependent entities.
- Utilize specialization/generalization for better modularity.
- Apply aggregation to represent complex relationships.

<br>
<br>

# 9. Alternative Notations

While this note focuses on the classic ER notation, other notations exist:
- Chen notation
- IE Crow's Foot notation
- UML Class Diagrams

> [!image]- Alternative notations diagram
> ![[Pasted image 20240915003120.png]]

Each notation has its strengths and is used in different contexts or by different tools.

****

<br>

Up Next : [[Introduction to SQL]]
