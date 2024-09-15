---
tags:
  - "#DB"
  - DatabaseSystems
  - "#backend"
Reviewed: 
Created: 2024-09-15T20:03:00
About: Based on CS3043-Lecture 06 Application design and development
---
Related : #web #javaScript #backend #App #html
Reference Note : [Lecture 07](file:///E:%5CAcademics%5CSEM%203%5CCS3043-Database%20Systems%5CLecture%20slide%5CL07%20Application%20Design%20and%20development.pdf)

---
# Content
- [[#1. Web Fundamentals]]
	- [[#1.1 HTML Basics]]
	- [[#1.2 URLs (Uniform Resource Locators)]]
- [[#2. Server-Side Programming]]
	- [[#2.1 Servlets (Java)]]
	- [[#2.2 JSP (Java Server Pages)]]
	- [[#2.3 PHP]]
- [[#3. Client-Side Programming]]
	- [[#JavaScript]]
- [[#4. Application Architectures]]
	- [[#Three-Tier Architecture]]
- [[#5. Object-Relational Mapping (ORM)]]
	- [[#Hibernate Example (Java)]]
- [[#6. Security Considerations]]
	- [[#SQL Injection Prevention]]
	- [[#Cross-Site Scripting (XSS) Prevention]]
- [[#7. Encryption]]
	- [[#Symmetric Encryption (AES)]]
	- [[#Public Key Encryption (RSA)]]

---
<br>

# Database Application Design and Development 

## 1. Web Fundamentals

### 1.1 HTML Basics
- HTML (Hyper Text Markup Language) is the standard markup language for creating web pages.

Example:
```html
<!DOCTYPE html>
<html>
<head>
    <title>My First Web Page</title>
</head>
<body>
    <h1>Welcome to My Website</h1>
    <p>This is a paragraph of text.</p>
    <a href="https://www.example.com">Click here to visit Example.com</a>
</body>
</html>
```


<br>

### 1.2 URLs (Uniform Resource Locators)
- URLs are used to specify the location of resources on the web.

Example:
```
http://www.example.com/path/to/page.html?param1=value1&param2=value2
```

- `http://`: Protocol
- `www.example.com`: Domain name
- `/path/to/page.html`: Path to the resource
- `?param1=value1&param2=value2`: Query parameters

<br>
<br>

## 2. Server-Side Programming

### 2.1 Servlets (Java)
- Servlets are Java classes that handle requests and generate dynamic responses.

Example:
```java
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Hello, World!</h1>");
        out.println("</body></html>");
    }
}
```

<br>

### 2.2 JSP (Java Server Pages)
- JSP allows embedding Java code within HTML.

Example:
```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>JSP Example</title>
</head>
<body>
    <h1>Current Time</h1>
    <p>The current time is: <%= new java.util.Date() %></p>
</body>
</html>
```

<br>

### 2.3 PHP
- PHP is a popular server-side scripting language.

Example:
```php
<!DOCTYPE html>
<html>
<head>
    <title>PHP Example</title>
</head>
<body>
    <h1>Welcome</h1>
    <?php
    $name = "John";
    echo "<p>Hello, $name!</p>";
    ?>
</body>
</html>
```

<br>
<br>

## 3. Client-Side Programming

### JavaScript
- JavaScript is used for client-side interactivity and dynamic content.

Example:
```html
<!DOCTYPE html>
<html>
<head>
    <title>JavaScript Example</title>
</head>
<body>
    <h1>Click Counter</h1>
    <button onclick="incrementCounter()">Click me</button>
    <p id="counter">0</p>

    <script>
    let count = 0;
    function incrementCounter() {
        count++;
        document.getElementById("counter").innerText = count;
    }
    </script>
</body>
</html>
```

<br>

## 4. Application Architectures

### Three-Tier Architecture
1. Presentation Layer (UI)
2. Business Logic Layer
3. Data Access Layer

> [!code] Example (Pseudocode):
> ```
> // Presentation Layer
> class UserInterface {
>     displayStudentInfo(student) {
>         // Code to render student info on the page
>     }
> }
> 
> // Business Logic Layer
> class StudentManager {
>     getStudentById(id) {
>         // Fetch student from data access layer
>         // Apply business rules
>         return student;
>     }
> }
> 
> // Data Access Layer
> class StudentDAO {
>     fetchStudentFromDatabase(id) {
>         // SQL query to fetch student data
>         return studentData;
>     }
> }
> ```
> 

<br>

## 5. Object-Relational Mapping (ORM)

### Hibernate Example (Java)
```java
@Entity
@Table(name = "students")
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "first_name")
    private String firstName;

    @Column(name = "last_name")
    private String lastName;

    // Getters and setters
}

// Using Hibernate to save a student
Session session = sessionFactory.openSession();
Transaction tx = session.beginTransaction();

Student student = new Student();
student.setFirstName("Alice");
student.setLastName("Smith");

session.save(student);

tx.commit();
session.close();
```

<br>

## 6. Security Considerations

### SQL Injection Prevention
- Use prepared statements to prevent SQL injection attacks.

> [!code] Example :
> ```java
> String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
> PreparedStatement pstmt = connection.prepareStatement(sql);
> pstmt.setString(1, username);
> pstmt.setString(2, password);
> ResultSet rs = pstmt.executeQuery();
> ```
> 

### Cross-Site Scripting (XSS) Prevention
- Sanitize user input to prevent XSS attacks.

> [!code] Example :
> ```php
> $userInput = $_POST['comment'];
> $sanitizedInput = htmlspecialchars($userInput, ENT_QUOTES, 'UTF-8');
> echo "Your comment: " . $sanitizedInput;
> ```
> 

<br>

## 7. Encryption

### Symmetric Encryption (AES)
Example (Java):
```java
import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;

// Generate a secret key
KeyGenerator keyGen = KeyGenerator.getInstance("AES");
keyGen.init(256);
SecretKey secretKey = keyGen.generateKey();

// Encrypt
Cipher cipher = Cipher.getInstance("AES");
cipher.init(Cipher.ENCRYPT_MODE, secretKey);
byte[] encryptedData = cipher.doFinal(originalData);

// Decrypt
cipher.init(Cipher.DECRYPT_MODE, secretKey);
byte[] decryptedData = cipher.doFinal(encryptedData);
```

### Public Key Encryption (RSA)
Example (Java):
```java
import java.security.*;

// Generate key pair
KeyPairGenerator keyGen = KeyPairGenerator.getInstance("RSA");
keyGen.initialize(2048);
KeyPair pair = keyGen.generateKeyPair();
PublicKey publicKey = pair.getPublic();
PrivateKey privateKey = pair.getPrivate();

// Encrypt with public key
Cipher cipher = Cipher.getInstance("RSA");
cipher.init(Cipher.ENCRYPT_MODE, publicKey);
byte[] encryptedData = cipher.doFinal(originalData);

// Decrypt with private key
cipher.init(Cipher.DECRYPT_MODE, privateKey);
byte[] decryptedData = cipher.doFinal(encryptedData);
```

