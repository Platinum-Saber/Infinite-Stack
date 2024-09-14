# Database Design Using the Entity-Relationship (ER) Model

## 1. Overview of the Design Process

The database design process consists of several phases:

1. **Initial Phase**: Characterize the data needs of prospective database users.
2. **Second Phase**: 
   - Choose a data model
   - Apply concepts of the chosen model
   - Translate requirements into a conceptual schema
3. **Final Phase**: Move from abstract model to database implementation
   - Logical Design: Decide on database schema
   - Physical Design: Decide on physical layout of the database

### Design Objectives
- Avoid redundancies
- Prevent inconsistencies
- Ensure completeness

## 2. The Entity-Relationship Model

The ER model is a high-level conceptual data model that describes:
- Entity sets
- Relationships
- Attributes

### 2.1 Entity Sets

- An **entity** is an object that exists and is distinguishable from other objects.
- An **entity set** is a set of entities of the same type that share the same properties.

Example:
```
instructor = (ID, name, salary)
course = (course_id, title, credits)
```

### 2.2 Relationship Sets

- A **relationship** is an association among several entities.
- A **relationship set** is a mathematical relation among n ≥ 2 entities, each taken from entity sets.

Example:
```
advisor(student_id, instructor_id)
```

### 2.3 Attributes

Attributes are properties of entities or relationships. They can be:
- Simple or composite
- Single-valued or multi-valued
- Derived

## 3. ER Diagram Notation

ER diagrams use specific symbols to represent different elements:

| Element | Symbol |
|---------|--------|
| Entity Set | Rectangle |
| Relationship Set | Diamond |
| Attribute | Oval |
| Primary Key | Underlined Attribute |
| Weak Entity Set | Double Rectangle |
| Identifying Relationship | Double Diamond |

## 4. Mapping Cardinalities

Mapping cardinalities express the number of entities to which another entity can be associated via a relationship set.

Types:
- One-to-one (1:1)
- One-to-many (1:N)
- Many-to-one (N:1)
- Many-to-many (M:N)

Example:
```
instructor ---(1)---- advisor ----(N)--- student
```

## 5. Participation Constraints

- **Total Participation**: Every entity in the entity set participates in at least one relationship in the relationship set.
- **Partial Participation**: Some entities may not participate in any relationship in the relationship set.

## 6. Weak Entity Sets

A weak entity set is one whose existence depends on another entity, called its identifying entity.

Example:
```
section (weak entity) depends on course (identifying entity)
```

## 7. Specialization and Generalization

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

## 8. Aggregation

Aggregation allows treating a relationship set as an entity set for purposes of participating in other relationship sets.

Example:
```
(proj_guide(student, project, instructor)) --- eval_for --- evaluation
```

## 9. Reduction to Relational Schemas

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

## 10. Design Issues and Best Practices

- Choose between entities and attributes based on the complexity and importance of the concept.
- Decide whether a concept should be an entity set or a relationship set.
- Use ternary relationships judiciously; sometimes binary relationships are more appropriate.
- Consider using weak entity sets for dependent entities.
- Utilize specialization/generalization for better modularity.
- Apply aggregation to represent complex relationships.

## 11. Alternative Notations

While this note focuses on the classic ER notation, other notations exist:
- Chen notation
- IE Crow's Foot notation
- UML Class Diagrams

Each notation has its strengths and is used in different contexts or by different tools.

