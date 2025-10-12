
## 📌 Object-Oriented Programming (OOP)

1. Explain the four main concepts of OOP: Encapsulation, Abstraction, Inheritance, and Polymorphism.
2. What is encapsulation? Why is it important? Can you give an example in Java?
3. How does encapsulation differ from abstraction?
4. Can you describe a real-world example of encapsulation in software?
5. What could happen if encapsulation is not used properly in a system?

---

## 📌 Java-Specific Questions

1. What Java concepts are you most familiar with?
2. What is the most complex project or functionality you’ve implemented in Java so far?
3. Explain the difference between **checked** and **unchecked exceptions** in Java.
4. What is the difference between `HashMap` and `Hashtable`?
5. How does Java handle multithreading?
6. What is the difference between `synchronized` methods and `synchronized` blocks?
7. How does garbage collection work in Java?

---

## 📌 Project-Based Questions (Semester 5 Project)

1. Can you describe your semester 5 project in detail?
2. What was your role and main contributions in the project?
3. Which technologies did you use and why?
4. Can you explain a specific implementation in your project (e.g., authentication, data storage, business logic)?
5. If you were to improve one part of your project, what would it be and why?

---

## 📌 Database & MongoDB

1. What database did you use in your project and why?
2. Can you explain how MongoDB stores data compared to relational databases?
3. What is a MongoDB transaction? Can you explain with an example use case?
4. How does MongoDB ensure data consistency in multi-document transactions?
5. What are the advantages and disadvantages of using MongoDB in your project?

---

## 📌 Multithreading

1. What is a thread?
2. How is a thread different from a process?
3. What are the ways to create a thread in Java?
4. What is the difference between extending `Thread` and implementing `Runnable`?
5. Can you explain a scenario where multithreading improved performance in an application?

---

## 📌 SQL / Query Writing

Given a sample table (e.g., **Employees** with columns: `id`, `name`, `department`, `salary`):

1. Write a query to select employees with a salary greater than 50,000.
2. Write a query to find the highest salary in each department.
3. Write a query to update an employee’s salary by 10%.
4. Write a query to delete all employees in the “HR” department.
5. Write a query to join two tables: Employees and Departments.

---

✅ This set mirrors the interview focus: **OOP → Java → Project → MongoDB → Threads → SQL.**
Would you like me to also **add model answers with explanations** for these so you can practice both questions and ideal responses?

# 📌 1. Object-Oriented Programming (OOP)

**Q1. Explain the four main concepts of OOP.**
**A:**

* **Encapsulation** – Wrapping data (fields) and methods (functions) into a single unit (class). Example: private fields with getters/setters.
* **Abstraction** – Hiding implementation details and exposing only the necessary functionality. Example: interfaces and abstract classes.
* **Inheritance** – Acquiring properties and behavior from a parent class. Example: `class Dog extends Animal`.
* **Polymorphism** – Ability to take many forms; same method behaves differently based on context. Example: method overriding (`toString()`) and method overloading.

---

**Q2. What is encapsulation? Why is it important? Give example.**
**A:** Encapsulation is about restricting direct access to fields and providing controlled access via methods. It improves data security and maintainability.

```java
class BankAccount {
    private double balance; // hidden from outside

    public void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    public double getBalance() {
        return balance;
    }
}
```

Here, the balance cannot be accessed directly, only through controlled methods.

---

**Q3. Difference between encapsulation and abstraction?**

* **Encapsulation** = Implementation detail is hidden by restricting direct access to fields.
* **Abstraction** = Implementation is hidden but functionality is exposed via abstract classes/interfaces.
  Example:
* Encapsulation → making fields private.
* Abstraction → defining `interface Vehicle { void start(); }`.

---

**Q4. Real-world example of encapsulation?**
ATM machine → Users can **deposit** or **withdraw**, but they cannot directly manipulate the account’s internal variables.

---

**Q5. What if encapsulation isn’t used?**
Anyone could modify data fields directly → leads to inconsistent, insecure, and buggy systems.

---

# 📌 2. Java-Specific

**Q1. What Java concepts are you most familiar with?**
OOP principles, Collections framework, Exception handling, Threads, Generics, JDBC, and basics of Spring Boot.

---

**Q2. Most complex project/feature in Java so far?**
*(Personalize based on your semester 5 project)* Example:

* Implementing role-based authentication with JWT in Java Spring Boot.
* Handling real-time data with multithreading for concurrent requests.

---

**Q3. Checked vs Unchecked exceptions?**

* **Checked:** Must be handled at compile-time. Example: `IOException`, `SQLException`.
* **Unchecked:** Runtime exceptions. Example: `NullPointerException`, `ArrayIndexOutOfBoundsException`.

---

**Q4. HashMap vs Hashtable?**

* **HashMap:** Non-synchronized, allows one null key & multiple null values, faster.
* **Hashtable:** Synchronized, no null key/value, slower.

---

**Q5. Java Multithreading?**

* Allows multiple tasks to run concurrently.
* Achieved via extending `Thread` or implementing `Runnable`.
* Used for responsive UIs, servers handling multiple clients, parallel processing.

---

**Q6. Difference between synchronized methods and blocks?**

* **Synchronized method:** Entire method locked for a thread.
* **Synchronized block:** Only a specific block of code locked, improving performance.

---

**Q7. How does garbage collection work?**

* Automatic memory management.
* GC frees memory of objects no longer referenced.
* Algorithms: Mark-and-sweep, generational collection.
* Example: `System.gc()` requests garbage collection.

---

# 📌 3. Project Questions (Semester 5)

**Q1. Describe your semester 5 project.**
*(Customize this for your project, Cryo)* Example:

* Built a **healthcare management platform** with Java Spring Boot backend, React frontend, and MongoDB database.
* Features: doctor-patient booking system, real-time notifications, and role-based access control.

---

**Q2. What was your role?**

* Designed database schema in MongoDB.
* Implemented backend APIs in Java Spring Boot.
* Worked on authentication and booking flow.

---

**Q3. Why those technologies?**

* **Java Spring Boot** → scalable backend.
* **MongoDB** → schema flexibility for evolving requirements.
* **React** → responsive UI.

---

**Q4. Explain specific implementation.**
Example: Role-based authentication

* Implemented using **JWT tokens**.
* Token contains encoded role data.
* Backend validates token on each request → ensures correct access rights.

---

**Q5. What would you improve?**

* Add automated test coverage with JUnit.
* Implement database sharding in MongoDB for scalability.

---

# 📌 4. Database & MongoDB

**Q1. How MongoDB stores data vs RDBMS?**

* MongoDB → JSON-like documents (BSON). Flexible schema.
* RDBMS → tables with fixed schema.

---

**Q2. What is a MongoDB transaction?**

* Transactions allow **multiple operations across documents/collections** to be executed atomically.
* Either **all succeed or none succeed**.

Example:

```js
const session = client.startSession();
session.startTransaction();
try {
    await orders.insertOne({ orderId: 1, product: "Laptop" }, { session });
    await inventory.updateOne({ product: "Laptop" }, { $inc: { stock: -1 } }, { session });
    await session.commitTransaction();
} catch {
    await session.abortTransaction();
}
session.endSession();
```

---

**Q3. How MongoDB ensures consistency?**

* Uses **write concern** and **multi-document transactions** to maintain ACID properties.

---

**Q4. Advantages & disadvantages of MongoDB in project?**

* ✅ Flexible schema, good for fast prototyping, horizontal scaling.
* ❌ No JOINs, larger memory usage, transaction handling weaker compared to SQL.

---

# 📌 5. Multithreading

**Q1. What is a thread?**
A lightweight unit of execution inside a process.

---

**Q2. Thread vs Process?**

* **Process:** Independent execution with own memory.
* **Thread:** Shares memory of the process but runs independently.

---

**Q3. Ways to create threads in Java?**

1. Extend `Thread` class → override `run()`.
2. Implement `Runnable` interface.
3. Use `ExecutorService` / ThreadPool.

---

**Q4. Difference between extending `Thread` and implementing `Runnable`?**

* **Extending Thread:** Class can’t extend any other class (single inheritance limitation).
* **Implementing Runnable:** Preferred, allows class to extend others.

---

**Q5. Example where multithreading improves performance?**

* Web server handling multiple client requests simultaneously.
* Real-time stock trading application.

---

# 📌 6. SQL Practice

Given table `Employees(id, name, department, salary)`

**Q1. Select employees with salary > 50,000**

```sql
SELECT * FROM Employees WHERE salary > 50000;
```

**Q2. Find highest salary in each department**

```sql
SELECT department, MAX(salary) AS highest_salary 
FROM Employees 
GROUP BY department;
```

**Q3. Update an employee’s salary by 10%**

```sql
UPDATE Employees 
SET salary = salary * 1.1 
WHERE id = 101;
```

**Q4. Delete all employees in HR**

```sql
DELETE FROM Employees WHERE department = 'HR';
```

**Q5. Join Employees with Departments**

```sql
SELECT e.name, d.department_name 
FROM Employees e
JOIN Departments d ON e.department = d.id;
```

---

✅ That’s the full prep set: **Questions + Answers**.

Do you want me to also create a **mock interview script** (interviewer vs you) so you can practice real dialogue flow?
