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
	[[#1.1 JDBC (Java Database Connectivity)]]
	[[#1.2 Prepared Statements]]
	[[#1.3 ODBC (Open Database Connectivity)]]
	[[#1.4 Embedded SQL]]
[[#2. Procedural Extensions in SQL]]
	[[#2.1 SQL Functions]]
	[[#2.2 SQL Procedures]]
	[[#2.3 Control Structures]]
[[#3. Triggers]]
[[#4. Advanced Aggregation Features]]
	[[#4.1 Ranking]]
	[[#4.2 Windowing]]
	[[#4.3 CUBE and ROLLUP]]
[[#5. Authorization]]
	[[#5.1 Roles]]
[[#6. OLAP (Online Analytical Processing)]]
	[[#6.1 Data Cubes]]
	[[#6.2 OLAP Implementation Types]]
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

## 1.3 ODBC (Open Database Connectivity)

- Standard API for communicating with database servers.
- Works with `C`, `C++`, `C#`, and `Visual Basic`.
- Requires a **driver library** for each database system.

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

# 2. Procedural Extensions in SQL

## 2.1 SQL Functions

- Can be written in `SQL` or external programming languages.
- Useful for specialized data types (e.g., images, geometric objects).
- Some databases support **table-valued functions**.

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
> ```

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
> ```
> 

## 2.3 Control Structures

- Compound statements: BEGIN ... END
- Loops: WHILE, REPEAT, FOR
- Conditional statements: IF-THEN-ELSE

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
> ```

# 4. Advanced Aggregation Features

## 4.1 Ranking

- Used in conjunction with `ORDER BY`.
- Functions: RANK(), DENSE_RANK()

Example:
```sql
SELECT ID, RANK() OVER (ORDER BY GPA DESC) AS s_rank
FROM student_grades
ORDER BY s_rank;
```

## 4.2 Windowing

- Performs calculations across a set of rows related to the current row.
- Useful for moving averages, running totals, etc.

Example:
```sql
SELECT date, SUM(value) OVER (
    ORDER BY date
    ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING
) AS moving_average
FROM sales;
```

## 4.3 CUBE and ROLLUP

- CUBE: Generates all possible combinations of GROUP BY clauses.
- ROLLUP: Generates a hierarchy of GROUP BY clauses.

Example:
```sql
SELECT item_name, color, size, SUM(quantity)
FROM sales
GROUP BY CUBE(item_name, color, size);
```

# 5. Authorization

- Controls access to database objects and operations.
- Main commands: GRANT and REVOKE.
- Privileges: SELECT, INSERT, UPDATE, DELETE, etc.

Example:
```sql
GRANT SELECT, INSERT ON employees TO hr_staff;
REVOKE DELETE ON customer_data FROM intern_user;
```

## 5.1 Roles

- Named sets of privileges that can be assigned to users.
- Simplifies management of complex permission systems.

Example:
```sql
CREATE ROLE manager;
GRANT SELECT, INSERT, UPDATE ON all_tables TO manager;
GRANT manager TO user1, user2;
```

# 6. OLAP (Online Analytical Processing)

- Interactive analysis of multidimensional data.
- Key concepts: dimensions, measures, hierarchies.
- Operations: drill-down, roll-up, slice, dice, pivot.

## 6.1 Data Cubes

- Multidimensional representation of data.
- Allows quick computation of aggregated data along various dimensions.

## 6.2 OLAP Implementation Types

- MOLAP (Multidimensional OLAP): Uses in-memory multidimensional arrays.
- ROLAP (Relational OLAP): Uses only relational database features.
- HOLAP (Hybrid OLAP): Combines MOLAP and ROLAP approaches.

# 7. Best Practices and Considerations

1. Always use prepared statements when dealing with user inputs to prevent SQL injection.
2. Be cautious with triggers, as they can lead to unintended consequences and performance issues.
3. Use appropriate indexing strategies to optimize query performance.
4. Regularly analyze and optimize your database schema and queries.
5. Implement proper authorization and access control to ensure data security.
6. Consider using stored procedures for complex operations that need to be reused.
7. When working with large datasets, consider using partitioning and materialized views.
8. Use transactions to ensure data consistency, especially for multi-step operations.
9. Regularly backup your database and test recovery procedures.
10. Stay updated with the latest features and best practices of your specific database management system.



