

> [!abstract] Overview
> Java is a **fully object-oriented programming language** (except for primitive types).  
> Its design follows the **OOP paradigm**, making it modular, reusable, and maintainable.  
> The four core pillars of OOP in Java are:
> - Encapsulation  
> - Inheritance  
> - Polymorphism  
> - Abstraction  

---

## 📌 Table of Contents
1. Classes & Objects
2. Encapsulation
3. Inheritance
4. Polymorphism
5. Abstraction
6. Interfaces
7. Wrap-Up

---

## 1. Classes & Objects

A **class** is a blueprint, and an **object** is an instance of that class.

```java
class Car {
    String brand;
    int speed;

    void drive() {
        System.out.println(brand + " is driving at " + speed + " km/h");
    }
}

public class Main {
    public static void main(String[] args) {
        Car car = new Car();
        car.brand = "Toyota";
        car.speed = 100;
        car.drive(); // Toyota is driving at 100 km/h
    }
}


```



## 2. Encapsulation

> [!info] Definition
> Wrapping **data (variables)** and **methods** into a single unit (class), with controlled access using **getters/setters**.

```java
class Account {
    private double balance;

    public void deposit(double amount) {
        balance += amount;
    }

    public double getBalance() {
        return balance;
    }
}

public class Main {
    public static void main(String[] args) {
        Account acc = new Account();
        acc.deposit(500);
        System.out.println(acc.getBalance()); // 500.0
    }
}
```

✔ **Advantages**: Improves security, hides internal details.
⚠ **Disadvantage**: Slightly more boilerplate (getters/setters).

---

## 3. Inheritance

> [!info] Definition
> One class (child) inherits fields & methods from another class (parent).

```java
class Vehicle {
    void start() {
        System.out.println("Vehicle started");
    }
}

class Bike extends Vehicle {
    void ride() {
        System.out.println("Riding the bike");
    }
}

public class Main {
    public static void main(String[] args) {
        Bike b = new Bike();
        b.start(); // Vehicle started
        b.ride();  // Riding the bike
    }
}
```

✔ Promotes **code reuse**.
⚠ Can lead to **tight coupling** if misused.

---

## 4. Polymorphism

> [!info] Definition
> The ability of an object to take many forms. Two types:
>
> * **Compile-time (method overloading)**
> * **Runtime (method overriding)**

### Method Overloading (Compile-time)

```java
class MathUtils {
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
}
```

### Method Overriding (Runtime)

```java
class Animal {
    void sound() {
        System.out.println("Animal makes a sound");
    }
}

class Dog extends Animal {
    @Override
    void sound() {
        System.out.println("Dog barks");
    }
}

public class Main {
    public static void main(String[] args) {
        Animal a = new Dog();
        a.sound(); // Dog barks
    }
}
```

---

## 5. Abstraction

> [!info] Definition
> Hiding implementation details and showing only essential features using **abstract classes** or **interfaces**.

```java
abstract class Shape {
    abstract void draw();
}

class Circle extends Shape {
    void draw() {
        System.out.println("Drawing a circle");
    }
}

public class Main {
    public static void main(String[] args) {
        Shape s = new Circle();
        s.draw(); // Drawing a circle
    }
}
```

✔ Helps in designing **blueprints**.
⚠ Cannot instantiate abstract classes directly.

---

## 6. Interfaces

An **interface** defines a contract — classes must implement its methods.

```java
interface Animal {
    void sound();
}

class Cat implements Animal {
    public void sound() {
        System.out.println("Meow");
    }
}

public class Main {
    public static void main(String[] args) {
        Animal a = new Cat();
        a.sound(); // Meow
    }
}
```

✔ Supports **multiple inheritance** of type.
✔ Used for **loose coupling**.

---

## 7. Wrap-Up

> [!done] Key Takeaways
>
> * **Encapsulation** → data hiding
> * **Inheritance** → code reuse
> * **Polymorphism** → flexibility
> * **Abstraction** → blueprint design
> * **Interfaces** → contracts and loose coupling

---
