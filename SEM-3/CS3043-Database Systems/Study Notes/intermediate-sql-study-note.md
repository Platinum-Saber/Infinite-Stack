# Intermediate SQL Study Notes

[Previous content on Joins remains unchanged]

## 2. Views

Views are virtual tables based on the result of an SQL statement. They don't store data themselves but provide a way to look at data in the underlying tables.

### Creating a View:

```sql
CREATE VIEW faculty AS
SELECT ID, name, dept_name
FROM instructor
WHERE dept_name = 'Computer Science';
```

This creates a view named 'faculty' that shows only Computer Science instructors.

### Using a View:

Views can be queried just like regular tables:

```sql
SELECT name
FROM faculty
WHERE name LIKE 'P%';
```

This query returns names of Computer Science faculty members whose names start with 'P'.

### View Dependencies:

Views can be based on other views:

```sql
CREATE VIEW cs_faculty_ids AS
SELECT ID
FROM faculty;
```

### View Updatability:

Not all views are updatable. For a view to be updatable:
- The FROM clause should have only one table
- The SELECT clause should only contain column names (no expressions or aggregates)
- Should not have GROUP BY or HAVING clauses

Example of an updatable view:

```sql
CREATE VIEW computerscience_instructors AS
SELECT ID, name, salary
FROM instructor
WHERE dept_name = 'Computer Science';

-- This update is allowed
UPDATE computerscience_instructors
SET salary = salary * 1.05
WHERE ID = '10101';
```

### Materialized Views:

Some databases support materialized views, which store the query results physically.

```sql
CREATE MATERIALIZED VIEW dept_total_salary AS
SELECT dept_name, SUM(salary) as total_salary
FROM instructor
GROUP BY dept_name;
```

Note: MySQL doesn't support materialized views natively.

## 3. Transactions

Transactions ensure that a series of SQL operations are executed as a single unit of work, following the ACID properties: Atomicity, Consistency, Isolation, and Durability.

Example of a transaction:

```sql
START TRANSACTION;

UPDATE account SET balance = balance - 100 WHERE account_id = 'A';
UPDATE account SET balance = balance + 100 WHERE account_id = 'B';

-- If both updates are successful
COMMIT;

-- If there's an error
-- ROLLBACK;
```

This transaction transfers $100 from account A to account B. Either both updates happen, or neither does.

## 4. Integrity Constraints

Integrity constraints maintain the accuracy and consistency of data in the database.

### Types of Constraints:

#### a. NOT NULL

Ensures a column cannot have NULL values.

```sql
CREATE TABLE student (
    ID CHAR(5) NOT NULL,
    name VARCHAR(20) NOT NULL,
    dept_name VARCHAR(20)
);
```

#### b. PRIMARY KEY

Uniquely identifies each record in a table.

```sql
CREATE TABLE course (
    course_id CHAR(5) PRIMARY KEY,
    title VARCHAR(50),
    dept_name VARCHAR(20),
    credits NUMERIC(2,0)
);
```

#### c. UNIQUE

Ensures all values in a column are different.

```sql
CREATE TABLE instructor (
    ID CHAR(5),
    name VARCHAR(20) UNIQUE,
    dept_name VARCHAR(20),
    salary NUMERIC(8,2)
);
```

#### d. CHECK

Ensures that all values in a column satisfy certain conditions.

```sql
CREATE TABLE section (
    course_id VARCHAR(8),
    sec_id VARCHAR(8),
    semester VARCHAR(6),
    year NUMERIC(4,0),
    CHECK (semester IN ('Fall', 'Winter', 'Spring', 'Summer')),
    CHECK (year > 1701 AND year < 2100)
);
```

#### e. FOREIGN KEY (Referential Integrity)

Ensures values in one table exist in another table.

```sql
CREATE TABLE course (
    course_id CHAR(5) PRIMARY KEY,
    title VARCHAR(50),
    dept_name VARCHAR(20),
    FOREIGN KEY (dept_name) REFERENCES department(dept_name)
        ON DELETE SET NULL
        ON UPDATE CASCADE
);
```

This ensures that every dept_name in the course table exists in the department table. If a department is deleted, the dept_name in course becomes NULL. If a department name is updated, it's automatically updated in the course table too.

## 5. Data Types

SQL provides various built-in data types and allows creation of user-defined types.

### Built-in Types:
- `DATE`: Stores date in 'YYYY-MM-DD' format
  Example: DATE '2023-09-15'
- `TIME`: Stores time in 'HH:MM:SS' format
  Example: TIME '14:30:00'
- `TIMESTAMP`: Combines date and time
  Example: TIMESTAMP '2023-09-15 14:30:00.00'
- `INTERVAL`: Represents a duration
  Example: INTERVAL '2' DAY

### User-Defined Types:

Create custom data types:

```sql
CREATE TYPE Dollars AS NUMERIC(12,2) FINAL;

CREATE TABLE department (
    dept_name VARCHAR(20),
    budget Dollars
);
```

### Domains:

Domains are user-defined data types with constraints:

```sql
CREATE DOMAIN age_type AS INTEGER CHECK (VALUE >= 0 AND VALUE < 150);

CREATE TABLE person (
    name VARCHAR(50),
    age age_type
);
```

### Large Object Types:
- `BLOB`: Binary Large Object, for storing binary data like images
- `CLOB`: Character Large Object, for storing large text data

Example:

```sql
CREATE TABLE documents (
    doc_id INTEGER PRIMARY KEY,
    doc_content CLOB
);
```

## 6. Indexing

Indexes are used to speed up data retrieval operations on database tables.

Creating an index:

```sql
CREATE INDEX student_name_index ON student(name);
```

This creates an index on the 'name' column of the 'student' table.

Composite index (index on multiple columns):

```sql
CREATE INDEX course_offering_index ON section(course_id, semester, year);
```

### Best Practices:
- Use indexes on frequently queried columns
- Index foreign key columns
- Don't overuse indexes, as they impact insert/update performance

Example of using an index:

```sql
-- This query can use the student_name_index
SELECT * FROM student WHERE name = 'John Doe';
```

## 7. TRUNCATE vs DELETE

### TRUNCATE:
- DDL (Data Definition Language) statement
- Faster, empties entire table
- Cannot be rolled back (in MySQL)
- Doesn't invoke ON DELETE triggers

Example:
```sql
TRUNCATE TABLE temp_logs;
```

### DELETE:
- DML (Data Manipulation Language) statement
- Can use WHERE clause to delete specific rows
- Can be rolled back
- Invokes ON DELETE triggers

Example:
```sql
DELETE FROM student
WHERE graduation_year < 2020;
```

This deletes all students who graduated before 2020.

Remember, while DELETE can be more precise, TRUNCATE is much faster for removing all data from a large table.
