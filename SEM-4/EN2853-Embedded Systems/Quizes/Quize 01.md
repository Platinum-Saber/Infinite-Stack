---
tags: 
Created: 2025-02-19 09:50
About: 
Reviewed: false
Completion: 0
---

## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```










# Questions

1. **What is the communication protocol where asynchronous?**
    
    - Options:  
        - [ ] UART 
        - [ ] SPI  
        - [ ] I2C  
        - [ ] USART
    - **Correct Answer:** UART
2. **What is not a C++ built-in datatype?**
    
    - Options:  
        - [ ] Character  
        - [ ] Short  
        - [ ] String  
        - [ ] Void
    - **Correct Answer:** String
3. **What is NOT a keyword used in defining conditional statements in C++?**
    
    - Options:  
        - [ ] for  
        - [ ] `#define`
        - [ ] break  
        - [ ] switch
    - **Correct Answer:** `#define`
4. **What is not a common logic gate?**  
    _(Options were not fully extracted, but likely included incorrect choices)_
    

Let me know if you need any modifications or additional explanations! 🚀

# Quiz 1 Study Notes

## 1. Asynchronous Communication Protocol

- **Correct Answer:** UART
- **Explanation:**
    - **UART (Universal Asynchronous Receiver-Transmitter)** is an asynchronous communication protocol.
    - It does **not use a clock signal** for synchronization.
    - Uses **start and stop bits** to frame data.
    - **USART** can operate in both synchronous and asynchronous modes.
    - **SPI** and **I2C** are synchronous protocols.
    - **Example:** UART is commonly used in **serial communication** between microcontrollers and computers.
    - **More Info:** [UART Communication](https://www.techtarget.com/whatis/definition/UART-Universal-Asynchronous-Receiver-Transmitter)

## 2. C++ Built-in Data Types

- **Correct Answer:** String
- **Explanation:**
    - **Built-in types:** `char`, `short`, `void`
    - **String (`std::string`) is not built-in** but comes from the **C++ Standard Library**.
    - **Example:**
        
        ```cpp
        #include <iostream>
        #include <string>
        using namespace std;
        int main() {
            string name = "Cryo";
            cout << "Hello, " << name << "!";
            return 0;
        }
        ```
        
    - **More Info:** [C++ Data Types](https://www.geeksforgeeks.org/cpp-data-types/)

## 3. Keywords for Conditional Statements in C++

- **Correct Answer:** `#define`
- **Explanation:**
    - **Conditional statements:** `if`, `else`, `switch`, `for`, `while`, `break`
    - `#define` is **not** a conditional statement but a **preprocessor directive** used for defining macros.
    - **Example:**
        
        ```cpp
        #define PI 3.14159
        #include <iostream>
        using namespace std;
        int main() {
            cout << "The value of PI is: " << PI;
            return 0;
        }
        ```
        
    - **More Info:** [C++ Preprocessor Directives](https://www.tutorialspoint.com/cplusplus/cpp_preprocessor.htm)

## 4. Common Logic Gates

- **Explanation:**
    - Common gates: **AND, OR, NOT, XOR, NAND, NOR, XNOR**
    - If an option is not one of these, it is **not** a logic gate.
    - **Example:**
        
        ```
        A | B | AND | OR  | XOR
        ------------------------
        0 | 0 |  0  |  0  |  0
        0 | 1 |  0  |  1  |  1
        1 | 0 |  0  |  1  |  1
        1 | 1 |  1  |  1  |  0
        ```
        
    - **More Info:** [Logic Gates Basics](https://www.electronics-tutorials.ws/logic/logic_1.html)

## 5. Handling Push Button Input in Embedded Systems

- **Correct Answer:** Using interrupts is advantageous when real-time responsiveness to button events is a critical requirement.
- **Explanation:**
    - **Interrupts allow immediate response** to button presses, making them ideal for real-time applications.
    - **Polling (reading in the main loop)** is simpler but can introduce delays and is less power-efficient.
    - **Example:**
        
        ```c
        void buttonISR() {
            // Interrupt Service Routine for button press
        }
        attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
        ```
        
    - **More Info:** [Interrupts in Embedded Systems](https://www.electronics-tutorials.ws/system/interrupts.html)

---
