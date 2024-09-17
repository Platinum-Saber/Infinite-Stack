---
tags:
  - SQL
  - DatabaseSystems
  - DB
Reviewed: 
Created: 2024-09-12T08:34:00
About: Based on CS3043-Lecture 07 Advanced SQL
---
Related : #AdvancedSQL
Reference Note : [L08 Advanced SQL](file:///E:%5CAcademics%5CSEM%203%5CCS3043-Database%20Systems%5CLecture%20slide%5CL08%20Advanced%20SQL.pdf), [[nodejs-sql-resources]]
Reference Video :


---

# Content
[[#1. Database Connectivity]]
- [[#1.1 JDBC (Java Database Connectivity)]]
- [[#1.2 Prepared Statements]]
- [[#1.3 ODBC (Open Database Connectivity)]]
- [[#1.4 Embedded SQL]]

[[#2. Procedural Extensions in SQL]]
- [[#2.1 SQL Functions]]
- [[#2.2 SQL Procedures]]
- [[#2.3 Control Structures]]
- [[#3. Triggers]]

[[#4. Advanced Aggregation Features]]
- [[#4.1 Ranking]]
- [[#4.2 Windowing]]
- [[#4.3 CUBE and ROLLUP]]

[[#5. Authorization]]
- [[#5.1 Roles]]

[[#6. OLAP (Online Analytical Processing)]]
- [[#6.1 Data Cubes]]
- [[#6.2 OLAP Implementation Types]]

[[#7. Best Practices and Considerations]]

---

# 1. Database Connectivity

## 1.1 JDBC (Java Database Connectivity)

- JDBC is a Java API for communicating with database systems supporting SQL.

> [!abstract]- Features:
>   - Querying and updating data
>   - Retrieving query results
>   - Metadata retrieval (e.g., querying about relations and attribute names/types)

> [!NOTE]- Communication model:
>   1. Open a connection
>   2. Create a "statement" object
>   3. Execute queries using the Statement object
>   4. Fetch results
>   5. Close the connection
>   6. Handle errors using exception mechanism

> [!code]- JDBC Example:
> 
> ```java
> try {
>     // Update database
>     statement.executeUpdate("INSERT INTO instructor VALUES ('77987','Kim','Physics',98000)");
>     
>     // Execute query and fetch results
>     ResultSet resultSet = statement.executeQuery(
>         "SELECT dept_name, AVG(salary) FROM instructor GROUP BY dept_name"
>     );
>     while (resultSet.next()) {
>         System.out.println(resultSet.getString("dept_name") + " : " + resultSet.getFloat(2));
>     }
> } catch (SQLException e) {
>     log.error("Unable to access the database server: ", e);
> }
> ```
> 

<br>

## 1.2 Prepared Statements

- Used for **precompiling** SQL statements with **placeholders** for parameters.

> [!tip]- Benefits:
>   - Improved performance for repeated executions
>   - Protection against SQL injection attacks

> [!code]- Example code
> ```java
> PreparedStatement preparedStatement = connection.prepareStatement(
>     "INSERT INTO instructor VALUES(?,?,?,?)"
> );
> preparedStatement.setString(1, "88877");
> preparedStatement.setString(2, "Perry");
> preparedStatement.setString(3, "Finance");
> preparedStatement.setInt(4, 125000);
> preparedStatement.executeUpdate();
> ```
> 

<br>

## 1.3 ODBC (Open Database Connectivity)

- Standard API for communicating with database servers.
- Works with `C`, `C++`, `C#`, and `Visual Basic`.
- Requires a **driver library** for each database system.

<br>

## 1.4 Embedded SQL

- Allows SQL queries to be embedded directly in host programming languages.
- Requires **preprocessing before compilation**.

> [!code]- Example (`SQLJ - embedded SQL in Java`):
> 
> ```java
> #sql iterator deptInfoIter (String dept_name, int avgSal);
> deptInfoIter iter = null;
> #sql iter = { select dept_name, avg(salary) from instructor group by dept_name };
> while (iter.next()) {
>     String deptName = iter.dept_name();
>     int avgSal = iter.avgSal();
>     System.out.println(deptName + " " + avgSal);
> }
> iter.close();
> ```

<br>
<br>

# 2. Procedural Extensions in SQL

## 2.1 SQL Functions

- Can be written in `SQL` or external programming languages.
- Useful for specialized data types (e.g., images, geometric objects).
- Some databases support **table-valued functions**.

> [!summary]- Built-in Functions:
>    - String functions (e.g., `CONCAT`, `SUBSTRING`)
>    - Numeric functions (e.g., `ABS`, `ROUND`)
>    - Date functions (e.g., `NOW`, `DATEDIFF`)
>    - Aggregate functions (e.g., `SUM`, `AVG`, `COUNT`)

> [!summary]- User-Defined Functions (UDFs):
>    These are custom functions created by users. In MySQL, there are three types:
>    - **Scalar functions** (return a single value)
>    - **Table functions** (return a table)
>    - **Stored functions** (similar to stored procedures but return a value)

> [!code]- Example code:
> ```sql
> CREATE FUNCTION dept_count (dept_name VARCHAR(20))
> RETURNS INTEGER
> BEGIN
>     DECLARE d_count INTEGER;
>     SELECT COUNT(*) INTO d_count
>     FROM instructor
>     WHERE instructor.dept_name = dept_name;
>     RETURN d_count;
> END;
> 
> DELIMITER //
> CREATE FUNCTION calculate_age(birthdate DATE) 
> RETURNS INT
> DETERMINISTIC
> BEGIN
>     RETURN FLOOR(DATEDIFF(CURDATE(), birthdate) / 365);
> END //
> DELIMITER ;
> ```

<br>

## 2.2 SQL Procedures

- Similar to functions but *can have* **output parameters**.
- Invoked using the `CALL` statement.

> [!code]- Example code
> ```sql
> CREATE PROCEDURE dept_count_proc (IN dept_name VARCHAR(20), OUT d_count INTEGER)
> BEGIN
>     SELECT COUNT(*) INTO d_count
>     FROM instructor
>     WHERE instructor.dept_name = dept_count_proc.dept_name;
> END;
> 
> ```


<br>

## 2.3 Control Structures

- Compound statements: BEGIN ... END
- Loops: WHILE, REPEAT, FOR
- Conditional statements: IF-THEN-ELSE

<br>
<br>

# 3. Triggers

- **Automatically** executed statements in *response* to specified database events.
- Events can be `INSERT`, `DELETE`, or `UPDATE` operations.
- Can be executed `BEFORE` or `AFTER` the triggering event.
- Types: row-level triggers and statement-level triggers.

> [!code]- Example:
> ```sql
> CREATE TRIGGER update_credit_score
> AFTER UPDATE OF balance ON account
> FOR EACH ROW
> WHEN (NEW.balance < 0)
> BEGIN
>     UPDATE customer
>     SET credit_score = credit_score - 20
>     WHERE customer.cust_id = NEW.cust_id;
> END;
> 
> 
> DELIMITER //
> CREATE TRIGGER before_employee_update 
> BEFORE UPDATE ON employees
> FOR EACH ROW 
> BEGIN
>     IF NEW.salary < OLD.salary THEN
>         SIGNAL SQLSTATE '45000' 
>         SET MESSAGE_TEXT = 'Salary cannot be decreased';
>     END IF;
> END //
> DELIMITER ;
> 
> ```

<br>
<br>

# 4. Advanced Aggregation Features

## 4.1 Ranking

- Used in **conjunction** with `ORDER BY`.
- **Functions**: `RANK()`, `DENSE_RANK()`

> [!code]- Example code
> ```sql
> SELECT ID, RANK() OVER (ORDER BY GPA DESC) AS s_rank
> FROM student_grades
> ORDER BY s_rank;
> ```
> 

<br>

## 4.2 Windowing

- Performs calculations across a set of rows related to the current row.
- Useful for moving averages, running totals, etc.

> [!code]- Example code:
> ```sql
> SELECT date, SUM(value) OVER (
>     ORDER BY date
>     ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING
> ) AS moving_average
> FROM sales;
> ```

<br>

## 4.3 CUBE and ROLLUP

- **CUBE**: Generates all possible combinations of GROUP BY clauses.
- **ROLLUP**: Generates a hierarchy of GROUP BY clauses.

> [!code]- Example code:
> ```sql
> SELECT item_name, color, size, SUM(quantity)
> FROM sales
> GROUP BY CUBE(item_name, color, size);
> ```

<br>
<br>

# 5. Authorization

- Controls access to database objects and operations.
- **Main commands**: `GRANT` and `REVOKE`.
- **Privileges**: `SELECT`, `INSERT`, `UPDATE`, `DELETE`, etc.

> [!code]- Example code:
> ```sql
> GRANT SELECT, INSERT ON employees TO hr_staff;
> REVOKE DELETE ON customer_data FROM intern_user;
> ```
> 

#### 1. Creating Users:

- To create a new user in MySQL, you use the `CREATE USER` statement. 
> [!note]- How !!!
> 
> ```sql
> CREATE USER 'username'@'hostname' IDENTIFIED BY 'password';
> ```
> 
> - '`username`': The name of the user you want to create.
> - '`hostname`': The host from which this user will connect. Use `'%'` for any host.
> - '`password`': The user's password.
>> [!code] Example:
>>```sql
>> CREATE USER 'john'@'localhost' IDENTIFIED BY 'securepass123';
>> ```

#### 2. Granting Privileges:

After creating a user, you need to grant them privileges. The `GRANT` statement is used for this purpose.

> [!note]- How !!!
> ```sql
> GRANT privilege_type [(column_list)] 
>     ON [object_type] privilege_level
>     TO 'username'@'hostname'
>     [WITH GRANT OPTION];
> ```
> 
> - **privilege_type**: The type of operation allowed (e.g., SELECT, INSERT, UPDATE, DELETE, ALL PRIVILEGES)
> - **column_list**: Optional. Specific columns the privilege applies to.
> - **object_type**: Optional. Can be TABLE, FUNCTION, or PROCEDURE.
> - **privilege_level**: The level at which the privilege applies (e.g., *.* for global, database_name.* for database-level, database_name.table_name for table-level)
> - WITH GRANT OPTION: Optional. Allows the user to grant their privileges to other users.

> [!code]- Examples:
> 
> 1. Grant all privileges on all databases:
> ```sql
> GRANT ALL PRIVILEGES ON *.* TO 'john'@'localhost';
> ```
> 
> 2. Grant specific privileges on a database:
> ```sql
> GRANT SELECT, INSERT, UPDATE ON mydb.* TO 'john'@'localhost';
> ```
> 
> 3. Grant privileges on a specific table:
> ```sql
> GRANT SELECT, UPDATE (name, email) ON mydb.users TO 'john'@'localhost';
> ```
> 

#### 3. View user's privileges:
```sql
SHOW GRANTS FOR 'john'@'localhost';
```

#### 4. Revoke privileges:
```sql
REVOKE privilege_type ON privilege_level FROM 'username'@'hostname';
```

#### 5. Drop a user:
```sql
DROP USER 'username'@'hostname';
```
#### 4. Reload the privileges from the grant tables:
```sql
FLUSH PRIVILEGES;
```

<br>

## 5.1 Roles

- Named sets of privileges that can be assigned to users.
- Simplifies management of complex permission systems.

> [!code]- Example code
> ```sql
> CREATE ROLE manager;
> GRANT SELECT, INSERT, UPDATE ON all_tables TO manager;
> GRANT manager TO user1, user2;
> ```

<br>
<br>

# 6. OLAP (Online Analytical Processing)

- Interactive analysis of multidimensional data.
- Key concepts: dimensions, measures, hierarchies.
- Operations: drill-down, roll-up, slice, dice, pivot.

<br>

## 6.1 Data Cubes

- Multidimensional representation of data.
- Allows quick computation of aggregated data along various dimensions.

<br>

## 6.2 OLAP Implementation Types

- MOLAP (Multidimensional OLAP): Uses in-memory multidimensional arrays.
- ROLAP (Relational OLAP): Uses only relational database features.
- HOLAP (Hybrid OLAP): Combines MOLAP and ROLAP approaches.

<br>
<br>

# 7. Best Practices and Considerations

1. **Always** use **prepared statements** when dealing with user inputs to prevent SQL injection.
2. Be **cautious** with **triggers**, as they can lead to unintended consequences and performance issues.
3. Use appropriate indexing strategies to optimize query performance.
4. Regularly analyze and optimize your database schema and queries.
5. Implement proper **authorization** and access control to ensure data security.
6. Consider using stored procedures for complex operations that need to be reused.
7. When working with large datasets, consider using **partitioning** and materialized views.
8. Use **transactions** to ensure data consistency, especially for multi-step operations.
9. Regularly backup your database and test recovery procedures.
10. Stay updated with the latest features and best practices of your specific database management system.

---
Up Next : [[]]
