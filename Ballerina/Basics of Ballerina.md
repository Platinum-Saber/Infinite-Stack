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
