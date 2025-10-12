# Java 
> [!abstract] Overview  
> Java is a **class-based, object-oriented language** designed for modular, reusable, and secure software development.  
> This note covers **all major OOP concepts in Java** with explanations, examples, pros/cons, and comparisons.

---

## 📌 Table of Contents
1. Classes & Objects  
2. Constructors (`default`, `parameterized`, `copy`)  
3. Encapsulation  
4. Inheritance  
5. Polymorphism  
   - Method Overloading  
   - Method Overriding  
   - Static vs Dynamic Binding  
6. Abstraction  
7. Interfaces & Multiple Inheritance  
8. `this`, `super`, `final`, `static` keywords  
9. Access Modifiers  
10. Association, Aggregation, Composition  
11. Generics (Intro)  
12. Comparison Tables  
13. Wrap-Up  

---

## 1. Classes & Objects
```java
class Car {
    String brand;
    int speed;

    void drive() { System.out.println(brand + " at " + speed + " km/h"); }
}

public class Main {
    public static void main(String[] args) {
        Car c = new Car(); // object
        c.brand = "Honda";
        c.speed = 120;
        c.drive();
    }


```


## 2. Constructors

Special methods for initializing objects.

```java
class Student {
    String name;
    int age;

    // Default constructor
    Student() { name = "Unknown"; age = 0; }

    // Parameterized constructor
    Student(String n, int a) { name = n; age = a; }

    // Copy constructor
    Student(Student s) { name = s.name; age = s.age; }
}
```

✔ Eliminates boilerplate.
⚠ Java does **not support multiple constructors with the same parameters.**

---

## 3. Encapsulation

```java
class Account {
    private double balance;
    public void deposit(double amt) { if (amt > 0) balance += amt; }
    public double getBalance() { return balance; }
}
```

✔ Secure, hides complexity.
⚠ More code with getters/setters.

---

## 4. Inheritance

```java
class Animal { void eat() { System.out.println("Eating..."); } }
class Dog extends Animal { void bark() { System.out.println("Barking"); } }
```

✔ Reusability.
⚠ Tight coupling, avoid deep hierarchies.

---

## 5. Polymorphism

### Method Overloading (Compile-time)

```java
class Math {
    int add(int a, int b) { return a+b; }
    double add(double a, double b) { return a+b; }
}
```

### Method Overriding (Runtime)

```java
class Animal { void sound() { System.out.println("Generic"); } }
class Dog extends Animal {
    @Override void sound() { System.out.println("Bark"); }
}
```

### Static vs Dynamic Binding

* **Static (early)**: Resolved at compile-time (`overloading`, `private`, `final`, `static` methods).
* **Dynamic (late)**: Resolved at runtime (`overriding`).

---

## 6. Abstraction

```java
abstract class Shape { abstract void draw(); }
class Circle extends Shape { void draw() { System.out.println("Circle"); } }
```

✔ Hides complexity.
⚠ Cannot instantiate directly.

---

## 7. Interfaces & Multiple Inheritance

```java
interface A { void show(); }
interface B { void display(); }

class Demo implements A, B {
    public void show() { System.out.println("Show A"); }
    public void display() { System.out.println("Display B"); }
}
```

✔ Java avoids **diamond problem** by using interfaces.

---

## 8. Important Keywords

* **`this`**: refers to current object.
* **`super`**: refers to parent class object/methods.
* **`final`**: prevents inheritance/overriding.
* **`static`**: shared among all objects, class-level.

```java
class Parent { void greet() { System.out.println("Hello from parent"); } }
class Child extends Parent {
    @Override void greet() {
        super.greet(); // call parent
        System.out.println("Hello from child");
    }
}
```

---

## 9. Access Modifiers

| Modifier    | Same Class | Same Package | Subclass | Other Packages |
| ----------- | ---------- | ------------ | -------- | -------------- |
| `public`    | ✅          | ✅            | ✅        | ✅              |
| `protected` | ✅          | ✅            | ✅        | ❌              |
| `default`   | ✅          | ✅            | ❌        | ❌              |
| `private`   | ✅          | ❌            | ❌        | ❌              |

---

## 10. Association, Aggregation, Composition

* **Association**: General “uses-a” relationship.
* **Aggregation**: Weak ownership (`has-a`, objects independent).
* **Composition**: Strong ownership (lifecycle tied).

```java
class Engine {}
class Car { private Engine e; } // Composition
```

---

## 11. Generics (Intro)

```java
class Box<T> {
    private T value;
    void set(T v) { value = v; }
    T get() { return value; }
}

Box<Integer> b = new Box<>();
b.set(10);
System.out.println(b.get());
```

✔ Provides **type safety**.

---

## 12. Comparison Tables

### Overloading vs Overriding

| Feature     | Overloading           | Overriding                 |
| ----------- | --------------------- | -------------------------- |
| Binding     | Compile-time          | Runtime                    |
| Params      | Must differ           | Must be same               |
| Return type | Can differ            | Must be same/covariant     |
| Inheritance | Not required          | Required                   |
| Use Case    | Multiple ways to call | Specific subclass behavior |

---

## 13. Wrap-Up

> [!done] Key Takeaways
>
> * **Encapsulation**: Secure data access.
> * **Inheritance**: Reuse, but don’t overuse.
> * **Polymorphism**: Flexibility via overloading/overriding.
> * **Abstraction**: Blueprint for design.
> * **Interfaces**: Multiple inheritance & loose coupling.
> * **Keywords**: `this`, `super`, `final`, `static` refine OOP behavior.
> * **Generics**: Add type safety to collections and classes.

---

