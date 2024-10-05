Related : #OS #OS/04 #ThreadsAndConcurrency 

> [!file]- Reference Note : 
> ![[L04.pdf]]
# Content 

- [[#Threads and Concurrency|Threads and Concurrency]]
	- [[#Threads and Concurrency#1. Overview|1. Overview]]
	- [[#Threads and Concurrency#2. Single vs. Multithreaded Processes|2. Single vs. Multithreaded Processes]]
	- [[#Threads and Concurrency#3. Benefits of Multithreading|3. Benefits of Multithreading]]
	- [[#Threads and Concurrency#4. Concurrency vs. Parallelism|4. Concurrency vs. Parallelism]]
	- [[#Threads and Concurrency#5. Multicore Programming Challenges|5. Multicore Programming Challenges]]
	- [[#Threads and Concurrency#6. Types of Parallelism|6. Types of Parallelism]]
	- [[#Threads and Concurrency#7. Threading Models|7. Threading Models]]
	- [[#Threads and Concurrency#8. Thread Libraries|8. Thread Libraries]]
	- [[#Threads and Concurrency#9. Fork-Join Parallelism|9. Fork-Join Parallelism]]
		- [[#9. Fork-Join Parallelism#3. Handling Data Dependency: Synchronization|3. Handling Data Dependency: Synchronization]]
- [[#Multithreading in C|Multithreading in C]]
	- [[#Multithreading in C#C Example: Multithreaded Program Using Pthreads|C Example: Multithreaded Program Using Pthreads]]
	- [[#Multithreading in C#Explanation:|Explanation:]]
- [[#Multithreading in Java|Multithreading in Java]]
	- [[#Multithreading in Java#Java Example: Creating Threads by Implementing Runnable Interface|Java Example: Creating Threads by Implementing Runnable Interface]]
	- [[#Multithreading in Java#Explanation:|Explanation:]]
	- [[#Multithreading in Java#Java Example: Creating Threads by Extending the Thread Class|Java Example: Creating Threads by Extending the Thread Class]]
	- [[#Multithreading in Java#Explanation:|Explanation:]]
	- [[#Multithreading in Java#Advantages of Multithreading|Advantages of Multithreading]]
- [[#Java Executor Framework|Java Executor Framework]]
	- [[#Java Executor Framework#Java Example: Executor Framework|Java Example: Executor Framework]]
	- [[#Java Executor Framework#Explanation:|Explanation:]]
- [[#Implicit Threading|Implicit Threading]]
	- [[#Implicit Threading#Fork-Join Parallelism in Java|Fork-Join Parallelism in Java]]
	- [[#Implicit Threading#Java Example: Fork-Join Framework|Java Example: Fork-Join Framework]]
	- [[#Implicit Threading#Explanation:|Explanation:]]
- [[#Thread Pools|Thread Pools]]
	- [[#Thread Pools#Advantages of Thread Pools:|Advantages of Thread Pools:]]
	- [[#Thread Pools#Java Example: Thread Pools with Executors|Java Example: Thread Pools with Executors]]
		- [[#Java Example: Thread Pools with Executors#Fixed Thread Pool Example|Fixed Thread Pool Example]]
	- [[#Thread Pools#Explanation:|Explanation:]]
	- [[#Thread Pools#Java Thread Pools Summary:|Java Thread Pools Summary:]]
	- [[#Thread Pools#Implicit Threading Techniques|Implicit Threading Techniques]]
- [[#Fork-Join Parallelism in Java|Fork-Join Parallelism in Java]]
	- [[#Fork-Join Parallelism in Java#Key Concepts:|Key Concepts:]]
	- [[#Fork-Join Parallelism in Java#Example: Fork-Join Framework|Example: Fork-Join Framework]]
	- [[#Fork-Join Parallelism in Java#Explanation:|Explanation:]]
- [[#OpenMP|OpenMP]]
	- [[#OpenMP#Key Features:|Key Features:]]
	- [[#OpenMP#Example: Parallel Loop Using OpenMP in C|Example: Parallel Loop Using OpenMP in C]]
	- [[#OpenMP#Explanation:|Explanation:]]
- [[#Grand Central Dispatch (GCD)|Grand Central Dispatch (GCD)]]
	- [[#Grand Central Dispatch (GCD)#Key Concepts:|Key Concepts:]]
	- [[#Grand Central Dispatch (GCD)#Example: Using GCD in Swift|Example: Using GCD in Swift]]
	- [[#Grand Central Dispatch (GCD)#Explanation:|Explanation:]]
- [[#Intel Threading Building Blocks (TBB)|Intel Threading Building Blocks (TBB)]]
	- [[#Intel Threading Building Blocks (TBB)#Example: Parallel For in TBB|Example: Parallel For in TBB]]
	- [[#Intel Threading Building Blocks (TBB)#Explanation:|Explanation:]]
- [[#Semantics of `fork()` and `exec()`|Semantics of `fork()` and `exec()`]]
	- [[#Semantics of `fork()` and `exec()`#`fork()`:|`fork()`:]]
	- [[#Semantics of `fork()` and `exec()`#`exec()`:|`exec()`:]]
	- [[#Semantics of `fork()` and `exec()`#Example of `fork()` and `exec()` in C:|Example of `fork()` and `exec()` in C:]]
	- [[#Semantics of `fork()` and `exec()`#Explanation:|Explanation:]]
- [[#Signal Handling|Signal Handling]]
	- [[#Signal Handling#Example: Handling Signals in C|Example: Handling Signals in C]]
	- [[#Signal Handling#Explanation:|Explanation:]]
- [[#Thread Cancellation|Thread Cancellation]]
	- [[#Thread Cancellation#Example of Thread Cancellation in C (Pthreads):|Example of Thread Cancellation in C (Pthreads):]]
	- [[#Thread Cancellation#Explanation:|Explanation:]]
- [[#Thread-Local Storage (TLS)|Thread-Local Storage (TLS)]]
	- [[#Thread-Local Storage (TLS)#Example of TLS in C (Pthreads):|Example of TLS in C (Pthreads):]]
	- [[#Thread-Local Storage (TLS)#Explanation:|Explanation:]]
- [[#Scheduler Activations|Scheduler Activations]]
- [[#Windows Threads|Windows Threads]]
	- [[#Windows Threads#Key Concepts:|Key Concepts:]]
	- [[#Windows Threads#Windows Example: Creating a Thread in C:|Windows Example: Creating a Thread in C:]]
	- [[#Windows Threads#Explanation:|Explanation:]]
- [[#Windows Thread Data Structures|Windows Thread Data Structures]]
- [[#Linux Threads|Linux Threads]]



## Threads and Concurrency

### 1. Overview
In modern computing, many applications are multithreaded. A **thread** is the smallest unit of a process that can be scheduled by the operating system. Multiple threads can exist within a single process, sharing its resources but running independently. This enables multitasking and helps improve the efficiency of both single-core and multicore processors.

- **Thread vs. Process**: A process is an independent program in execution, while a thread is a part of a process. Threads within the same process share memory, files, and other resources but operate independently, potentially improving the application's responsiveness and resource utilization.

---

### 2. Single vs. Multithreaded Processes

> [!info]- Single-threaded processes 
> Run one task at a time. 
> For example, in a word processor, tasks such as spell checking, updating the display, or handling user inputs are processed sequentially.

> [!info]- Multithreaded processes 
> Allow multiple tasks to run simultaneously. 
> For instance, a web browser may load web pages, handle user inputs, and display graphics simultaneously by using different threads.

---

### 3. Benefits of Multithreading

> [!tip]- Multithreading offers several advantages:
> 
> - **Responsiveness**: 
> 	- Multithreading keeps an application responsive even if a part of it is blocked. For instance, in a GUI-based application, if one thread is waiting for input from a network, the user interface can still remain responsive.
>   
> - **Resource Sharing**: 
> 	- Threads can easily share data and resources of a single process, which simplifies communication compared to inter-process communication (IPC) mechanisms.
>   
> - **Economy**: 
> 	- Thread creation is more lightweight and cheaper than creating an entire process because threads share the process’s memory and resources.
>   
> - **Scalability**: 
> 	- In multicore systems, threads can run truly in parallel, taking advantage of all available cores, thereby improving the performance of applications.

---

### 4. Concurrency vs. Parallelism

> [!info] Concurrency:
> Multiple tasks are in progress at the same time, but they may not necessarily be running simultaneously. This is achieved via scheduling in single-core systems.


> [!info] Parallelism: 
> Multiple tasks execute simultaneously on different processors or cores in multicore systems, allowing true parallel execution.

---

### 5. Multicore Programming Challenges
To fully utilize multicore systems, developers must address the following:
- **Dividing activities** across cores.
- **Balancing the workload** to ensure all cores are efficiently utilized.
- **Data dependency**: Avoid conflicts where one task needs the result of another.
- **Testing and debugging** multithreaded programs, which is more complex due to the possibility of race conditions, deadlocks, and synchronization issues.

---

### 6. Types of Parallelism
- **Data Parallelism**: Involves distributing subsets of the same data across multiple cores, where each core performs the same operation on its subset.
  
- **Task Parallelism**: Distributes different tasks (threads) across cores, where each core may perform a different operation.

---

### 7. Threading Models
Three main models define how user-level threads interact with kernel threads:
1. **Many-to-One**: Multiple user threads are mapped to a single kernel thread. This model is simple but limits parallelism because only one thread can be executed by the kernel at a time.
  
2. **One-to-One**: Each user thread maps to a unique kernel thread. This model allows true parallelism but can be costly if too many threads are created.

3. **Many-to-Many**: Multiple user-level threads are mapped to multiple kernel threads, providing a balance between the other two models. It allows the system to create an optimal number of kernel threads.

---

### 8. Thread Libraries
Popular thread libraries include:
- **POSIX Pthreads**: A standard API for creating and managing threads in UNIX systems.
- **Windows Threads**: Provides an API for thread management in Windows OS.
- **Java Threads**: Java provides high-level thread management through the `Runnable` interface and the `Thread` class, making it easy to manage multithreading in Java programs.

---

### 9. Fork-Join Parallelism
Fork-Join is a parallel execution pattern where multiple threads (tasks) are created (forked) to perform different tasks, and later the results are combined (joined). This is useful for divide-and-conquer algorithms like parallel mergesort.

In Java, **ForkJoinTask** is an abstract class used to implement this pattern. Python can achieve a similar effect using thread pools.


#### 3. Handling Data Dependency: Synchronization
When multiple threads modify shared data, **race conditions** can occur. To avoid this, Python provides a `Lock` object to synchronize thread execution.

```python
import threading

total = 0
lock = threading.Lock()

def increment():
    global total
    for _ in range(10000):
        with lock:
            total += 1

# Creating threads
t1 = threading.Thread(target=increment)
t2 = threading.Thread(target=increment)

# Starting threads
t1.start()
t2.start()

# Joining threads
t1.join()
t2.join()

print(f'Total: {total}')  # Expected total: 20000
```

**Explanation**:
- The `increment()` function adds 1 to the `total` variable 10,000 times. Since `total` is shared by both threads, a `Lock` is used to ensure that only one thread updates `total` at a time.
- The `with lock:` statement automatically acquires the lock before executing the block of code and releases it afterward, preventing race conditions.

---

Here's a detailed continuation of the study notes that includes **multithreaded C** and **Java thread** examples, with clear explanations for each.

---

## Multithreading in C

C programming offers several APIs for multithreading. A commonly used one is **Pthreads** (POSIX threads), which provides a standard interface for thread creation and management.

### C Example: Multithreaded Program Using Pthreads

Here’s an example of a multithreaded C program that creates multiple threads and performs tasks concurrently.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_message(void *thread_id) {
    long tid;
    tid = (long)thread_id;
    printf("Thread ID: %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void *)t);
        
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    // Wait for threads to finish
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
```

### Explanation:
- **Thread Function**: The `print_message` function is the task executed by each thread. It prints the thread ID passed as an argument.
  
- **Creating Threads**: In the `main()` function, we create `NUM_THREADS` (5 in this case) threads using `pthread_create()`. This function takes the following arguments:
  - A pointer to the thread (`&threads[t]`).
  - `NULL` for the thread attributes (default attributes).
  - The function the thread should execute (`print_message`).
  - The argument to be passed to the thread (the thread ID `t`).

- **Thread Join**: After creating the threads, we use `pthread_join()` to wait for all threads to finish before exiting the program. This ensures the `main()` function does not terminate before the threads complete their execution.

- **pthread_exit()**: This ensures that the thread ends safely. 

---

## Multithreading in Java

Java provides built-in support for multithreading using the `Thread` class and the `Runnable` interface.

### Java Example: Creating Threads by Implementing Runnable Interface

Here’s an example of how to create multiple threads using Java’s `Runnable` interface:

```java
public class TestThread {
    public static void main(String[] args) {
        // Creating two threads
        Thread t1 = new Thread(new MyThread("Thread 1"));
        Thread t2 = new Thread(new MyThread("Thread 2"));

        // Starting the threads
        t1.start();
        t2.start();
        
        // Ensure both threads finish before proceeding
        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("Main thread exiting.");
    }
}
class MyThread implements Runnable {
    private String threadName;

    MyThread(String name) {
        threadName = name;
    }

    // This method defines the task for each thread
    public void run() {
        try {
            for (int i = 1; i <= 5; i++) {
                System.out.println(threadName + ": " + i);
                // Sleep for 500 milliseconds
                Thread.sleep(500);
            }
        } catch (InterruptedException e) {
            System.out.println(threadName + " interrupted.");
        }
        System.out.println(threadName + " exiting.");
    }
}


```

### Explanation:
- **Runnable Interface**: The `MyThread` class implements the `Runnable` interface and overrides the `run()` method to define the task for each thread. The `run()` method prints numbers 1 to 5 with a 500-millisecond delay between each number using `Thread.sleep()`.

- **Thread Class**: In the `main()` method of the `TestThread` class, we create two threads `t1` and `t2` using the `Thread` constructor, passing in instances of the `MyThread` class.

- **Starting Threads**: We call `t1.start()` and `t2.start()` to begin the execution of both threads concurrently. The `start()` method internally calls the `run()` method defined in the `MyThread` class.

- **Thread Join**: The `join()` method ensures the main thread waits for both `t1` and `t2` to finish execution before exiting. This prevents the main thread from completing before the other threads.

---

### Java Example: Creating Threads by Extending the Thread Class

Here’s another approach in Java where the `Thread` class is extended directly:

```java
class MyThread extends Thread {
    private String threadName;

    MyThread(String name) {
        threadName = name;
    }

    // This method defines the task for each thread
    public void run() {
        try {
            for (int i = 1; i <= 5; i++) {
                System.out.println(threadName + ": " + i);
                // Sleep for 500 milliseconds
                Thread.sleep(500);
            }
        } catch (InterruptedException e) {
            System.out.println(threadName + " interrupted.");
        }
        System.out.println(threadName + " exiting.");
    }
}

public class TestThread {
    public static void main(String[] args) {
        // Creating two threads
        MyThread t1 = new MyThread("Thread 1");
        MyThread t2 = new MyThread("Thread 2");

        // Starting the threads
        t1.start();
        t2.start();

        // Ensure both threads finish before proceeding
        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("Main thread exiting.");
    }
}
```

### Explanation:
- **Extending Thread Class**: In this example, `MyThread` extends the `Thread` class. This allows us to directly override the `run()` method without needing to implement the `Runnable` interface.

- **Starting Threads**: Similar to the previous example, we use the `start()` method to begin the execution of the threads, and `join()` ensures the main thread waits for the threads to complete.

- **Advantages of Extending vs. Implementing Runnable**: 
  - **Implementing `Runnable`** allows the class to extend other classes, which is useful in cases where a class needs to inherit from a superclass.
  - **Extending `Thread`** directly is simpler, but it limits the class from extending any other class.

---

### Advantages of Multithreading
- **Concurrency**: Multithreading allows multiple tasks to be processed concurrently, improving performance and responsiveness.
- **Scalability**: Multithreading enables applications to better utilize modern multicore processors.
- **Responsiveness**: User interfaces and real-time applications benefit from multithreading because tasks like I/O or background calculations can run without freezing the main application.

Here's a detailed continuation of the study notes that includes **Java Executor Framework**, **Implicit Threading**, and **Thread Pools** with examples and explanations.

---

## Java Executor Framework

Java’s **Executor Framework** provides a higher-level API for managing and controlling thread execution compared to manually creating and managing threads using `Thread` or `Runnable`. Instead of explicitly creating threads, tasks are submitted to an **Executor** for execution, which handles the thread management behind the scenes.

### Java Example: Executor Framework

```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class Task implements Runnable {
    private String name;

    public Task(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        try {
            System.out.println("Executing task: " + name);
            Thread.sleep(1000);  // Simulate some work
            System.out.println("Task " + name + " completed.");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
	public static void main(String[] args) {
        // Create a fixed thread pool with 3 threads
        ExecutorService executor = Executors.newFixedThreadPool(3);

        // Submit tasks to executor
        for (int i = 1; i <= 5; i++) {
            executor.submit(new Task("Task " + i));
        }

        // Shutdown the executor once all tasks are submitted
        executor.shutdown();
    }
}


```

### Explanation:
- **ExecutorService**: The `ExecutorService` interface provides methods for managing a pool of threads and executing tasks. It’s part of the Java **concurrent utilities** and provides an abstraction for handling thread management.
  
- **Fixed Thread Pool**: We create a fixed thread pool using `Executors.newFixedThreadPool(3)`. This means there will be exactly 3 threads executing tasks concurrently. If more tasks are submitted, they will be queued until a thread becomes available.

- **Submitting Tasks**: The `submit()` method is used to submit instances of `Runnable` tasks to the executor for execution.

- **Shutdown**: `shutdown()` is called to terminate the executor once all tasks are submitted, preventing new tasks from being added. The executor will wait for all tasks to finish before shutting down.

---

## Implicit Threading

As the number of threads increases, explicitly managing them becomes challenging. To ease this, **implicit threading** involves allowing compilers or runtime libraries to manage thread creation, synchronization, and scheduling.

In implicit threading, several methods handle thread management without the developer explicitly controlling thread creation. The **Fork-Join Framework**, **Thread Pools**, and **OpenMP** (for C/C++) are examples of implicit threading.

---

### Fork-Join Parallelism in Java

Java’s **Fork-Join Framework** is a key part of implicit threading, primarily designed for tasks that can be recursively split into smaller tasks and then combined to produce a result (e.g., divide-and-conquer algorithms).

### Java Example: Fork-Join Framework

```java
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class ForkJoinExample {
    public static void main(String[] args) {
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        FibonacciTask fibonacciTask = new FibonacciTask(10);
        
        // Start the Fibonacci calculation
        int result = forkJoinPool.invoke(fibonacciTask);
        System.out.println("Fibonacci(10) = " + result);
    }
}
class FibonacciTask extends RecursiveTask<Integer> {
    private final int n;

    FibonacciTask(int n) {
        this.n = n;
    }

    @Override
    protected Integer compute() {
        if (n <= 1) {
            return n;
        }
        // Forking two smaller tasks
        FibonacciTask task1 = new FibonacciTask(n - 1);
        FibonacciTask task2 = new FibonacciTask(n - 2);
        task1.fork(); // Fork task1 to be executed asynchronously
        return task2.compute() + task1.join(); // Join the result of task1
    }
}

```

### Explanation:
- **ForkJoinPool**: The `ForkJoinPool` is an implementation of the **ExecutorService** designed to work with tasks that can be broken down into smaller tasks.
  
- **RecursiveTask**: This abstract class represents a task that returns a result. In this case, the task is calculating the Fibonacci number recursively.

- **fork() and join()**: The `fork()` method splits the task into smaller tasks that can be run in parallel, while the `join()` method waits for the result of the forked task.

- **Efficiency**: The **Fork-Join Framework** excels in scenarios where tasks can be recursively broken down into smaller units and then combined (e.g., parallel sorting algorithms).

---

## Thread Pools

A **Thread Pool** is a collection of pre-created threads that can be reused to execute tasks. Thread pools improve performance by reducing the overhead of creating and destroying threads for each task. They also allow developers to limit the number of threads running concurrently, avoiding overloading the system.

### Advantages of Thread Pools:
- **Efficiency**: Reusing threads saves the time and overhead involved in creating and destroying threads for each task.
- **Resource Management**: Limits the number of active threads, which is important in systems with constrained resources.
- **Simplified Task Management**: Tasks can be submitted to the pool without manually handling thread creation.

---

### Java Example: Thread Pools with Executors

Java provides three main types of thread pools via the **Executors** class:
1. **Fixed Thread Pool**: A pool with a fixed number of threads.
2. **Cached Thread Pool**: A pool that creates new threads as needed but reuses previously created threads when available.
3. **Scheduled Thread Pool**: A pool that supports scheduling of tasks to run after a delay or periodically.

#### Fixed Thread Pool Example

```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadPoolExample {
    public static void main(String[] args) {
        // Create a thread pool with 3 threads
        ExecutorService executor = Executors.newFixedThreadPool(3);

        for (int i = 1; i <= 5; i++) {
            Runnable worker = new WorkerThread("Task " + i);
            executor.execute(worker);  // Submit each task to the executor
        }

        executor.shutdown();  // Initiates an orderly shutdown
        while (!executor.isTerminated()) {
        }

        System.out.println("All tasks are finished.");
    }
}
class WorkerThread implements Runnable {
    private String message;

    public WorkerThread(String message) {
        this.message = message;
    }

    public void run() {
        System.out.println(Thread.currentThread().getName() + " (Start) message = " + message);
        processMessage();  // Simulate task processing
        System.out.println(Thread.currentThread().getName() + " (End)");
    }

    private void processMessage() {
        try {
            Thread.sleep(2000);  // Simulate processing time
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}


```

### Explanation:
- **WorkerThread Class**: Implements the `Runnable` interface and simulates processing a task by sleeping for 2 seconds.
  
- **Fixed Thread Pool**: A fixed pool with 3 threads is created using `Executors.newFixedThreadPool(3)`. Even though we submit 5 tasks, only 3 will execute simultaneously. The remaining tasks will be queued until threads are available.

- **Task Execution**: Each task is executed by calling `executor.execute(worker)`.

- **Shutdown**: After submitting all tasks, `executor.shutdown()` is called, ensuring no new tasks are accepted. The program waits until all threads complete their work.

---

### Java Thread Pools Summary:
- **Fixed Thread Pool**: Limits the number of concurrent threads. Useful when the number of threads can be determined beforehand.
- **Cached Thread Pool**: Dynamically adjusts the number of threads depending on the number of tasks. Good for tasks that execute for short durations.
- **Scheduled Thread Pool**: Used for scheduling tasks to execute after a delay or periodically.

---

### Implicit Threading Techniques
1. **Thread Pools**: Automatically manage and reuse threads.
2. **Fork-Join Framework**: Splits tasks into smaller, independent tasks that can be executed in parallel.
3. **Grand Central Dispatch (GCD)**: An Apple technology that handles the creation and management of threads for parallel computing.

---

## Fork-Join Parallelism in Java

Fork-Join is a powerful parallel programming model introduced in Java 7 as part of the `java.util.concurrent` package. It is particularly well-suited for divide-and-conquer tasks, where problems can be recursively split into smaller, independent tasks that are processed in parallel and later joined to produce the final result.

### Key Concepts:
- **Fork**: A task is split into smaller subtasks, which can be processed concurrently.
- **Join**: Once the subtasks complete, their results are combined (joined) to produce the final result.

### Example: Fork-Join Framework

```java
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class ForkJoinExample {
    public static void main(String[] args) {
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        FibonacciTask fibonacciTask = new FibonacciTask(10);
        
        // Start the Fibonacci calculation
        int result = forkJoinPool.invoke(fibonacciTask);
        System.out.println("Fibonacci(10) = " + result);
    }
}
class FibonacciTask extends RecursiveTask<Integer> {
    private final int n;

    FibonacciTask(int n) {
        this.n = n;
    }

    @Override
    protected Integer compute() {
        if (n <= 1) {
            return n;
        }
        // Forking two smaller tasks
        FibonacciTask task1 = new FibonacciTask(n - 1);
        FibonacciTask task2 = new FibonacciTask(n - 2);
        task1.fork(); // Fork task1 to be executed asynchronously
        return task2.compute() + task1.join(); // Join the result of task1
    }
}


```

### Explanation:
- **RecursiveTask**: An abstract class representing a task that returns a result.
- **Fork**: We split the problem into smaller tasks (recursive calls to compute Fibonacci numbers).
- **Join**: After computing the smaller tasks, the results are combined.

---

## OpenMP

**OpenMP** is an API that supports multi-platform shared memory multiprocessing programming in C, C++, and Fortran. It provides compiler directives to specify parallel regions in code.

### Key Features:
- **Parallel Regions**: Sections of code can be marked to run in parallel.
- **Work-sharing Constructs**: Loop iterations can be divided among threads.
- **Synchronization Primitives**: Ensures safe access to shared resources.

### Example: Parallel Loop Using OpenMP in C

```c
#include <omp.h>
#include <stdio.h>

int main() {
    int n = 10;
    int arr[10];

    // Parallel for loop
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
        printf("Thread %d computed arr[%d] = %d\n", omp_get_thread_num(), i, arr[i]);
    }

    return 0;
}
```

### Explanation:
- The `#pragma omp parallel for` directive tells the compiler to parallelize the following loop.
- `omp_get_thread_num()` returns the thread ID to show which thread is executing each iteration.

---

## Grand Central Dispatch (GCD)

**Grand Central Dispatch (GCD)** is an Apple-developed technology for managing concurrency in macOS and iOS. GCD abstracts thread management and provides a simple API for performing tasks in parallel, using **dispatch queues**.

### Key Concepts:
- **Dispatch Queues**: Tasks are placed in queues and executed by available threads. Two types of queues are:
  - **Serial Queues**: Tasks are executed in FIFO order.
  - **Concurrent Queues**: Multiple tasks may be executed simultaneously.
- **Blocks/Closures**: Code chunks that are added to dispatch queues.

### Example: Using GCD in Swift

```swift
import Foundation

let queue = DispatchQueue(label: "com.example.myQueue")

queue.async {
    print("This is running asynchronously on a background queue.")
}

DispatchQueue.main.async {
    print("This is running on the main queue.")
}
```

### Explanation:
- **DispatchQueue**: Represents a queue on which tasks can be dispatched asynchronously.
- The `async` method allows tasks to be added to the queue and executed without blocking the main thread.

---

## Intel Threading Building Blocks (TBB)

**Intel Threading Building Blocks (TBB)** is a C++ library that abstracts low-level thread management. It provides high-level algorithms for parallelism, such as `parallel_for` and `parallel_reduce`.

### Example: Parallel For in TBB

```cpp
#include <iostream>
#include <tbb/tbb.h>

int main() {
    tbb::parallel_for(0, 10, [](int i) {
        std::cout << "Processing index " << i << " in parallel." << std::endl;
    });
    
    return 0;
}
```

### Explanation:
- **parallel_for**: TBB divides the iteration space into chunks and assigns them to available threads, optimizing parallel execution.

---

## Semantics of `fork()` and `exec()`

### `fork()`:
The `fork()` system call creates a new process by duplicating the calling process. The new process is referred to as the **child process**.

### `exec()`:
The `exec()` family of functions replaces the current process image with a new program image. It doesn’t create a new process but changes the memory space of the calling process.

### Example of `fork()` and `exec()` in C:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        execlp("/bin/ls", "ls", NULL);
    } else {
        // Parent process
        wait(NULL);
        printf("Child complete\n");
    }
    
    return 0;
}
```

### Explanation:
- The `fork()` call creates a child process. The `execlp()` function replaces the child process with the `ls` command.

---

## Signal Handling

In UNIX-like systems, signals are used to notify a process that a particular event has occurred (e.g., termination request, illegal memory access).

### Example: Handling Signals in C

```c
#include <signal.h>
#include <stdio.h>

void signalHandler(int signal_num) {
    printf("Received signal %d\n", signal_num);
}

int main() {
    signal(SIGINT, signalHandler);  // Catch interrupt signal (Ctrl+C)

    while (1) {
        printf("Waiting for signal...\n");
        sleep(1);
    }
    
    return 0;
}
```

### Explanation:
- The `signal()` function sets a signal handler for `SIGINT` (interrupt signal). When the user presses Ctrl+C, the `signalHandler` function is executed.

---

## Thread Cancellation

Thread cancellation allows one thread to terminate another. In POSIX threads, this can be either **asynchronous** (terminating immediately) or **deferred** (checking cancellation points).

### Example of Thread Cancellation in C (Pthreads):

```c
#include <pthread.h>
#include <stdio.h>

void *threadFunction(void *arg) {
    while (1) {
        printf("Thread is running...\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);
    
    sleep(3);  // Let the thread run for a few seconds
    pthread_cancel(thread);  // Cancel the thread

    pthread_join(thread, NULL);
    printf("Thread was cancelled.\n");
    
    return 0;
}
```

### Explanation:
- `pthread_cancel()` sends a cancellation request to the thread, which will be processed at the next cancellation point.

---

## Thread-Local Storage (TLS)

**Thread-Local Storage** allows each thread to maintain its own separate copy of a variable, preventing interference between threads.

### Example of TLS in C (Pthreads):

```c
#include <pthread.h>
#include <stdio.h>

pthread_key_t key;

void *threadFunction(void *arg) {
    int *threadData = (int *)pthread_getspecific(key);
    printf("Thread-specific data: %d\n", *threadData);
    return NULL;
}

int main() {
    pthread_key_create(&key, NULL);

    int mainThreadData = 5;
    pthread_setspecific(key, &mainThreadData);
    
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);

    pthread_join(thread, NULL);
    pthread_key_delete(key);
    
    return 0;
}
```

### Explanation:
- `pthread_key_t` creates a key for TLS. Each thread can set its own value for this key using `pthread_setspecific()` and retrieve it using `pthread_getspecific()`.

---

## Scheduler Activations

Scheduler Activations provide a mechanism for coordinating user-level thread libraries and the kernel. **Upcalls** notify the user-level thread library when certain events occur, such as a thread blocking or unblocking, enabling efficient management of thread scheduling.

---

## Windows Threads

Windows provides native support for multithreading using the **Windows API

**. Threads are created using the `CreateThread()` function.

### Key Concepts:
- **Thread Context**: Contains the thread’s execution state, including the register set and stacks.
- **Thread ID**: Unique identifier for a thread.
  
### Windows Example: Creating a Thread in C:

```c
#include <windows.h>
#include <stdio.h>

DWORD WINAPI threadFunction(LPVOID param) {
    printf("Thread is running\n");
    return 0;
}

int main() {
    HANDLE thread = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
    
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    return 0;
}
```

### Explanation:
- **CreateThread()**: Creates a new thread that starts execution in `threadFunction`.
- **WaitForSingleObject()**: Waits for the thread to finish execution.

---

## Windows Thread Data Structures

- **ETHREAD**: Represents a thread in the Windows kernel.
- **KTHREAD**: Kernel thread block containing scheduling information.
- **TEB (Thread Environment Block)**: Contains user-mode information about the thread.

---

## Linux Threads

Linux refers to threads as **tasks**, and thread creation is handled using the `clone()` system call. The `pthread` library is used for POSIX-compliant thread management.

---
Up Next : [[Synchronization Tools]]
