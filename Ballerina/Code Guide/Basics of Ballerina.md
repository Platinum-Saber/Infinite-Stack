---
tags:
  - Ballerina
Reviewed: true
Created: 2024-09-17T19:03:00
About: "Ballerina basics for dummies: step by step guide."
---
---
### 1. Run "Hello World"
1. **Hello World Program**: Let's start with a simple program.
```ballerina
import ballerina/io;  public function main() {     io:println("Hello, World!"); }
```
    
- Save this as `hello_world.bal` and run it using the command `bal run hello_world.bal.

2. **Run the Program**: Use `bal run` followed by the filename to run your program.
    
<br>

### 2. Ballerina Syntax

1. **Variables**:
   - Variables are declared with the type followed by the variable name.

     ```ballerina
     int x = 10;
     string name = "Ballerina";
     ```

2. **Functions**:
   - Define functions with the `function` keyword.

     ```ballerina
     public function add(int a, int b) returns int {
         return a + b;
     }
     ```

3. **Conditionals and Loops**:
   - Ballerina supports common control structures like `if`, `else`, `while`, and `foreach`.

     ```ballerina
     if (x > 5) {
         io:println("x is greater than 5");
     }
     ```

<br>


### 3. Understand Ballerina's Unique Features

1. **Network Programming**: Ballerina is known for its ability to easily handle network interactions. For example, creating HTTP services:

   ```ballerina
   import ballerina/http;

   service /hello on new http:Listener(8080) {
       resource function get sayHello() returns string {
           return "Hello, Ballerina!";
       }
   }
   ```

   - This creates an HTTP service that listens on port 8080.

2. **Data Handling (JSON, XML)**: Ballerina makes it easy to handle data formats such as JSON and XML:

   ```ballerina
   json j = { "name": "Ballerina", "age": 5 };
   io:println(j.toString());
   ```

<br>

### 4. Explore Concurrency with Ballerina

Ballerina offers native concurrency through `workers` and `strands`. Workers allow you to execute multiple tasks concurrently.

Example of a concurrent function with workers:

```ballerina
public function processConcurrently() {
    worker w1 {
        io:println("Worker 1");
    }
    worker w2 {
        io:println("Worker 2");
    }
}
```

<br>

### 5. Dive into Microservices and Integrations

Ballerina is heavily designed for modern microservices and integrations:

1. **Build REST APIs**: You can easily create RESTful services.
2. **Integrate with Databases**: Use connectors to interact with databases.
3. **Containerization**: Ballerina integrates well with Docker and Kubernetes, which is great for deploying microservices.

<br>

### 6. Use Ballerina’s Package System

Ballerina supports a package system for modular development. You can organize your code in modules and import them.

- Create a module:
  
  ```bash
  bal new my_package
  cd my_package
  bal add utils
  ```

- This creates a new project structure where you can start organizing your code into modules.

<br>

### 7. Explore the Ballerina Standard Library

The Ballerina Standard Library contains pre-built packages for:
- HTTP
- gRPC
- Database (SQL, NoSQL)
- File I/O
- JSON/XML handling
- Testing

You can explore these in the [Ballerina API Documentation](https://ballerina.io/learn/api-docs/).

<br>

### 8. Practice and Build Projects

Now that you have a basic understanding of Ballerina, start practicing by building small projects:
- Build REST APIs.
- Create microservices.
- Work with database connections.
- Experiment with cloud-native features.

<br>

---

You can always refer to [Ballerina by Example](https://ballerina.io/learn/by-example/) for more code samples and use cases.