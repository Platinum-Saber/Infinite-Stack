
Related : #DatabaseSystems #DB #DB/02

<br>

# Design Process

<br>
<br>

### Design Phases

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

# ER Model
>[!FAQ]- Why was the ER data model developed
>To facilitate database design by allowing specification of an `enterprise schema` that represents the overall logical structure of the database

>[!abstract]- Basic concepts used in ER-data model
>- entity sets
>- relationship sets
>- attributes

>[!tip] The ER model also has an associated diagrammatic representation, the `ER diagram` which can express the overall logical structure of a database graphically

<br>
<br>

### Entity Sets
>[!FAQ]- What is an `entity`
>An object that exists and is distinguishable from other objects

>[!FAQ]- what is an `Entity Set`
>A set of entities of the same type that share the same properties

>[!note]- Attributes
>An entity is represented by a set of **attributes** (descriptive properties possessed by all members of an entity set).
>A subset of the attributes form a **`primary key`** 🔑 of the entity set. (uniquely identifying each member of the set)

<br>

>[!tip]- How to represent **entity sets** graphically
>- Rectangles represents entity sets
>- Attributes are listed inside the entity rectangle
>- Underline indicates **primary key 🗝 ** attribute
>
>![[Pasted image 20240704100409.png]]

<br>
<br>

### Relationship Sets
>[!info] A **relationship** is an association among several entities.

>[!info]- A **relationship set** is a mathematical relation among 2 or more entities each taken from entity sets
> { $(\ e_1 ,\ e_2,\ ... \ e_n\ ) |\ e_1 \ \in \ E_1,\ e_2 \ \in \ E_2,\ ...\ e_n\  \in \ E_n$ }

<br>

****

<br>

Up Next : [[Introduction to SQL]]
