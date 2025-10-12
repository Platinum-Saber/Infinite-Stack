# 📌 1. Object-Oriented Programming (OOP)

**Q1. Explain the four main concepts of OOP.**
**A:**

* **Encapsulation** – Wrapping fields and methods into a class, restricting direct access.
* **Abstraction** – Hiding implementation details, exposing only interfaces.
* **Inheritance** – Acquiring properties/behaviors from a parent class.
* **Polymorphism** – Same method behaving differently depending on context.

---

**Q2. What is encapsulation? Why is it important?**
**A:** Encapsulation protects data by restricting direct access and only allowing controlled modification through getters/setters.

```java
class Student {
    private String name;
    private int marks;

    public void setMarks(int m) {
        if (m >= 0) marks = m;
    }
    public int getMarks() { return marks; }
}
```

---

**Q3. Difference between encapsulation and abstraction?**

* Encapsulation → focuses on **hiding data**.
* Abstraction → focuses on **hiding implementation logic**.

---

**Q4. Real-world example?**

* A **bank account app**: you can call `deposit()` or `withdraw()`, but you can’t directly modify the balance field.

---

---

# 📌 2. Java-Specific

**Q1. Familiar concepts in Java?**
OOP, Collections, Generics, Exception Handling, JDBC, Threads, and using frameworks like Spring Boot.

---

**Q2. Most complex implementation in Java?**
*(Adapt this for your project, e.g., if you used Java in backend)* Example:

* Writing REST APIs in Java Spring Boot to connect with MySQL.
* Implementing Firebase Auth with Java backend for user identity.

---

**Q3. Checked vs Unchecked exceptions?**

* **Checked** → must be handled (IOException, SQLException).
* **Unchecked** → runtime errors (NullPointerException).

---

**Q4. HashMap vs Hashtable?**

* **HashMap:** not synchronized, allows null keys/values, faster.
* **Hashtable:** synchronized, no null keys/values, slower.

---

**Q5. Garbage collection in Java?**

* GC automatically removes unreferenced objects from heap memory.
* Example: `System.gc()` requests garbage collection.

---

---

# 📌 3. Project Questions (Semester 5)

**Q1. Describe your semester 5 project.**
*(Example, adjust for your actual project)*

* Built a **mobile healthcare app** with Flutter frontend, **Firebase Auth** for authentication, and **MySQL backend** for structured storage.
* Features: Appointment booking, medicine reminders, and doctor ratings.

---

**Q2. Role in project?**

* Implemented MySQL schema & queries.
* Integrated Firebase Authentication for secure login.
* Developed backend APIs in Node.js / Java to link Firebase with MySQL.

---

**Q3. Why Firebase + MySQL?**

* **Firebase** → simple and secure authentication, real-time database for notifications.
* **MySQL** → reliable relational database, ACID-compliant, well-suited for structured healthcare data.

---

**Q4. Example of functionality implementation?**

* **User authentication with Firebase**:

  * Sign up/sign in handled by Firebase Auth.
  * Token verification on backend to ensure secure access.
* **Data stored in MySQL**:

  * Doctors, patients, appointments in relational schema.
  * Queries used for scheduling & conflict checking.

---

**Q5. What would you improve?**

* Add **caching** with Redis for faster queries.
* Set up **Firebase Cloud Messaging (FCM)** for better push notifications.

---

---

# 📌 4. Database (Firebase + MySQL)

**Q1. How does Firebase differ from MySQL?**

* **Firebase:**

  * Cloud-hosted, NoSQL JSON-like structure.
  * Built-in authentication & real-time sync.
  * Good for notifications and mobile apps.
* **MySQL:**

  * Relational DB with structured schema.
  * Strong consistency & transaction support.
  * Suitable for structured queries (joins, aggregations).

---

**Q2. How does Firebase Authentication work?**

* Provides SDKs for email/password, Google, Facebook logins.
* Generates an ID token for authenticated users.
* Backend verifies token → ensures secure access.

---

**Q3. What are MySQL transactions? Why important?**

* A transaction is a sequence of queries executed as a **single unit**.
* Follows **ACID properties** → Atomicity, Consistency, Isolation, Durability.

```sql
START TRANSACTION;
UPDATE Accounts SET balance = balance - 100 WHERE id = 1;
UPDATE Accounts SET balance = balance + 100 WHERE id = 2;
COMMIT;
```

If any query fails → `ROLLBACK`.

---

**Q4. Advantages & disadvantages of Firebase in your project?**

* ✅ Easy integration, authentication, real-time updates.
* ❌ Vendor lock-in, limited relational querying.

**Advantages & disadvantages of MySQL?**

* ✅ Reliable, structured schema, transactions, joins.
* ❌ Less flexible schema changes, not real-time like Firebase.

---

---

# 📌 5. Multithreading

**Q1. What is a thread?**

* A thread is a lightweight unit of execution within a process.

---

**Q2. Thread vs Process?**

* Process = Independent execution with separate memory.
* Thread = Smaller execution unit inside a process, shares memory.

---

**Q3. Ways to create threads in Java?**

1. Extend `Thread` class.
2. Implement `Runnable`.
3. Use ExecutorService / ThreadPool.

---

**Q4. Example of multithreading improving performance?**

* Chat app → each client handled by a separate thread.
* File downloader → multiple files downloaded concurrently.

---

---

# 📌 6. SQL Practice (MySQL)

Given `Employees(id, name, department, salary)`

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

✅ Now you have a **Firebase + MySQL version** of the prep guide.

Do you want me to also **make a condensed quick-revision sheet** (bullet-point + examples only, no long explanations) so you can glance at it right before the interview?
