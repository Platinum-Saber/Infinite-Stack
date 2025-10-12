Got it 👍 — let’s make the Flutter/Dart note **more descriptive** with a stronger focus on **functions** (their syntax, parameters, return values, async, arrow functions, higher-order functions). I’ll then rebuild the entire note so it reads like a proper Obsidian knowledge sheet.

Here’s the expanded note:


# Flutter & Dart — Complete Basics

> [!abstract] Overview
> Flutter is Google’s **UI toolkit** for building cross-platform apps from a single codebase.  
> Dart is the **programming language** that powers Flutter. It is object-oriented, strongly typed, null-safe, and designed for building scalable apps with fast performance.

---

## 📌 Table of Contents
1. Dart Basics
   - Variables & Types
   - Functions (detailed)
   - Control Flow
   - Classes & Objects
   - Null Safety
   - Asynchronous Programming
2. Flutter Basics
   - Widgets
   - Stateless vs Stateful Widgets
   - Layout System
   - State Management
   - Navigation
3. Use Cases
4. Wrap-Up

---

## 1. Dart Basics

### Variables & Types
```dart
void main() {
  var name = "Suhan";     // inferred as String
  String city = "Colombo";
  int age = 22;
  double pi = 3.14159;
  bool isActive = true;
}


> [!tip] Dart is **strongly typed with inference**:
> Use explicit types (`int`, `String`) or `var`/`final`/`const`.

---

### Functions (Core Concept)

Functions in Dart are **first-class citizens**: they can be stored in variables, passed as arguments, or returned from other functions.

#### Basic Function

```dart
int add(int a, int b) {
  return a + b;
}

void main() {
  print(add(3,4)); // 7
}
```

#### Arrow Function (shorthand for one-liners)

```dart
int multiply(int a, int b) => a * b;
```

#### Named Parameters

```dart
void greet(String name, {String prefix = "Hello"}) {
  print("$prefix, $name!");
}

void main() {
  greet("Suhan");                 // Hello, Suhan!
  greet("Suhan", prefix: "Hi");   // Hi, Suhan!
}
```

#### Optional Positional Parameters

```dart
String join(String a, [String b = "World"]) {
  return "$a $b";
}

void main() {
  print(join("Hello"));       // Hello World
  print(join("Hello", "Dart")); // Hello Dart
}
```

#### Higher-Order Functions

```dart
void apply(int x, int y, int Function(int, int) operation) {
  print("Result: ${operation(x, y)}");
}

void main() {
  apply(3, 4, (a, b) => a + b); // Result: 7
}
```

#### Anonymous Functions (Lambdas)

```dart
var list = [1,2,3];
list.forEach((n) => print(n * n));
```

#### Asynchronous Functions

```dart
Future<String> fetchData() async {
  await Future.delayed(Duration(seconds: 2));
  return "Data loaded";
}

void main() async {
  print(await fetchData());
}
```

> [!info] Dart supports **sync** and **async** functions with `Future`, `await`, and `async`.

---

### Control Flow

```dart
for (var i = 0; i < 5; i++) {
  print(i);
}

if (age > 18) {
  print("Adult");
} else {
  print("Minor");
}
```

---

### Classes & Objects

```dart
class Person {
  String name;
  int age;

  Person(this.name, this.age);

  void greet() => print("Hi, I'm $name, $age years old.");
}

void main() {
  var p = Person("Suhan", 22);
  p.greet(); // Hi, I'm Suhan, 22 years old.
}
```

---

### Null Safety

```dart
String? nullableName;  // Can be null
String nonNullName = "Dart"; // Must not be null
```

> [!warning] Null safety prevents runtime null errors by enforcing checks at compile-time.

---

### Asynchronous Programming (Futures & Streams)

* `Future` → represents a single async computation.
* `Stream` → represents a sequence of async events.

```dart
Stream<int> numbers() async* {
  for (int i = 0; i < 3; i++) {
    yield i;
    await Future.delayed(Duration(seconds: 1));
  }
}
```

---

## 2. Flutter Basics

### Widgets

> [!note] In Flutter **everything is a widget**:
>
> * UI elements (Text, Button, Image)
> * Layouts (Row, Column, Stack)
> * Entire screens

```dart
import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(title: Text("Hello Flutter")),
        body: Center(child: Text("Welcome!")),
      ),
    );
  }
}
```

---

### Stateless vs Stateful Widgets

**StatelessWidget** (UI does not change):

```dart
class Hello extends StatelessWidget {
  @override
  Widget build(BuildContext ctx) {
    return Text("Hello World");
  }
}
```

**StatefulWidget** (UI can change using `setState`):

```dart
class Counter extends StatefulWidget {
  @override
  _CounterState createState() => _CounterState();
}

class _CounterState extends State<Counter> {
  int count = 0;

  @override
  Widget build(BuildContext ctx) {
    return Column(
      children: [
        Text("Count: $count"),
        ElevatedButton(
          onPressed: () => setState(() => count++),
          child: Text("Increment"),
        ),
      ],
    );
  }
}
```

---

### Layout System

* **Row** → horizontal layout
* **Column** → vertical layout
* **Container** → styling box
* **Expanded/Flexible** → proportional sizing

```dart
Row(
  mainAxisAlignment: MainAxisAlignment.spaceEvenly,
  children: [Text("A"), Text("B"), Text("C")],
)
```

---

### State Management

> [!info] Options for managing state:
>
> * `setState()` → small apps
> * **InheritedWidget** → basic sharing
> * **Provider** → popular package
> * **Riverpod / BLoC / Redux** → large scale apps

---

### Navigation

```dart
Navigator.push(
  context,
  MaterialPageRoute(builder: (ctx) => SecondScreen()),
);

// Back
Navigator.pop(context);
```

---

## 3. Use Cases

> [!example] Where Flutter shines
>
> * Cross-platform apps (iOS, Android, Web, Desktop)
> * Prototyping with hot reload
> * Custom UIs & widgets
> * Business apps with one codebase

---

