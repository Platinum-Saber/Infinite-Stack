
## Dining Philosophers Problem

**Problem** 
- The Dining Philosophers Problem 

<br>

**Scenario**
- Five philosophers are seated at a round table, each with a plate of spaghetti in front of them. There is one fork between each pair of philosophers. To eat, a philosopher needs to use two forks: one from their left and one from their right.

<br>

**Implementation**:

> [!code] Solution
> ```java
> class Fork {
>     private boolean isAvailable = true;
>     
>     public synchronized void pickUp() throws InterruptedException {
>         while (!isAvailable) {
>             wait();
>         }
>         isAvailable = false;
>     }
> 
>     public synchronized void putDown() {
>         isAvailable = true;
>         notifyAll();
>     }
> }
> 
> class Philosopher extends Thread {
>     private final Fork leftFork;
>     private final Fork rightFork;
>     private final int philosopherNumber;
> 
>     public Philosopher(Fork leftFork, Fork rightFork, int philosopherNumber) {
>         this.leftFork = leftFork;
>         this.rightFork = rightFork;
>         this.philosopherNumber = philosopherNumber;
>     }
> 
>     private void think() throws InterruptedException {
>         System.out.println("Philosopher " + philosopherNumber + " is thinking.");
>         Thread.sleep((int) (Math.random() * 1000));
>     }
> 
>     private void eat() throws InterruptedException {
>         System.out.println("Philosopher " + philosopherNumber + " is eating.");
>         Thread.sleep((int) (Math.random() * 1000));
>     }
>
>     @Override
>     public void run() {
>         try {
>             while (true) {
>                 think();
> 
>                 // Pick up the forks
>                 if (philosopherNumber % 2 == 0) {
>                     leftFork.pickUp();
>                     System.out.println("Philosopher " + philosopherNumber + " picked up left fork.");
>                     rightFork.pickUp();
>                     System.out.println("Philosopher " + philosopherNumber + " picked up right fork.");
>                 } else {
>                     rightFork.pickUp();
>                     System.out.println("Philosopher " + philosopherNumber + " picked up right fork.");
>                     leftFork.pickUp();
>                     System.out.println("Philosopher " + philosopherNumber + " picked up left fork.");
>                 }
>
>                 eat();
> 
>                 // Put down the forks
>                 leftFork.putDown();
>                 System.out.println("Philosopher " + philosopherNumber + " put down left fork.");
>                 rightFork.putDown();
>                 System.out.println("Philosopher " + philosopherNumber + " put down right fork.");
>             }
>         } catch (InterruptedException e) {
>             Thread.currentThread().interrupt();
>             return;
>         }
>     }
> }
> 
> public class DiningPhilosophers {
>     public static void main(String[] args) {
>         int numberOfPhilosophers = 5;
>         Fork[] forks = new Fork[numberOfPhilosophers];
> 
>         // Initialize each fork
>         for (int i = 0; i < numberOfPhilosophers; i++) {
>             forks[i] = new Fork();
>         }
> 
>         // Initialize philosophers
>         Philosopher[] philosophers = new Philosopher[numberOfPhilosophers];
>         for (int i = 0; i < numberOfPhilosophers; i++) {
>             Fork leftFork = forks[i];
>             Fork rightFork = forks[(i + 1) % numberOfPhilosophers];
> 
>             philosophers[i] = new Philosopher(leftFork, rightFork, i);
> 
>             philosophers[i].start();
> 
>         }
> 
>     }
> 
> }
> ```


<br>

**Solution Approach and Explanation**:
- We need to manage access to shared resources, which is fork in this case, such that all philosophers gets a chance to eat(that is , to prevent starvation ) and all philosophers do not get stuck at a time (that is to prevent deadlock).
- We consider each philosopher as a single thread and each fork as a mutex.

- *Avoiding deadlock*:
	o	To avoid deadlock we have made the first four philosophers take their left fork and the fifth philosopher take the right fork.

- *Minimize Starvation*:
	 - avoid starvation, philosophers will wait, ready to take the fork once one philosopher keeps it back.
	- Has used a randomized sleeping time for each thread to be put to sleep, so that the access to forks is randomized.

<br>

**GROUP 7**
- Waduge S.S. - 220673K
- Vidyananda H.K.H - 220666R
- Kavinda L.G.L - 220316V
- Chathurangi K.L. - 220087R