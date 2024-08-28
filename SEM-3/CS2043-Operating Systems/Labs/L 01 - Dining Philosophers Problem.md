
## Dining Philosophers Problem

> [!code]- Solution
> ```java
> class Fork {
> 
>     private boolean isAvailable = true;
> 
>   
> 
>     public synchronized void pickUp() throws InterruptedException {
> 
>         while (!isAvailable) {
> 
>             wait();
> 
>         }
> 
>         isAvailable = false;
> 
>     }
> 
>   
> 
>     public synchronized void putDown() {
> 
>         isAvailable = true;
> 
>         notifyAll();
> 
>     }
> 
> }
> 
>   
> 
> class Philosopher extends Thread {
> 
>     private final Fork leftFork;
> 
>     private final Fork rightFork;
> 
>     private final int philosopherNumber;
> 
>   
> 
>     public Philosopher(Fork leftFork, Fork rightFork, int philosopherNumber) {
> 
>         this.leftFork = leftFork;
> 
>         this.rightFork = rightFork;
> 
>         this.philosopherNumber = philosopherNumber;
> 
>     }
> 
>   
> 
>     private void think() throws InterruptedException {
> 
>         System.out.println("Philosopher " + philosopherNumber + " is thinking.");
> 
>         Thread.sleep((int) (Math.random() * 1000));
> 
>     }
> 
>   
> 
>     private void eat() throws InterruptedException {
> 
>         System.out.println("Philosopher " + philosopherNumber + " is eating.");
> 
>         Thread.sleep((int) (Math.random() * 1000));
> 
>     }
> 
>   
> 
>     @Override
> 
>     public void run() {
> 
>         try {
> 
>             while (true) {
> 
>                 think();
> 
>   
> 
>                 // Pick up the forks
> 
>                 if (philosopherNumber % 2 == 0) {
> 
>                     leftFork.pickUp();
> 
>                     System.out.println("Philosopher " + philosopherNumber + " picked up left fork.");
> 
>                     rightFork.pickUp();
> 
>                     System.out.println("Philosopher " + philosopherNumber + " picked up right fork.");
> 
>                 } else {
> 
>                     rightFork.pickUp();
> 
>                     System.out.println("Philosopher " + philosopherNumber + " picked up right fork.");
> 
>                     leftFork.pickUp();
> 
>                     System.out.println("Philosopher " + philosopherNumber + " picked up left fork.");
> 
>                 }
> 
>   
> 
>                 eat();
> 
>   
> 
>                 // Put down the forks
> 
>                 leftFork.putDown();
> 
>                 System.out.println("Philosopher " + philosopherNumber + " put down left fork.");
> 
>                 rightFork.putDown();
> 
>                 System.out.println("Philosopher " + philosopherNumber + " put down right fork.");
> 
>             }
> 
>         } catch (InterruptedException e) {
> 
>             Thread.currentThread().interrupt();
> 
>             return;
> 
>         }
> 
>     }
> 
> }
> 
>   
> 
> public class DiningPhilosophers {
> 
>     public static void main(String[] args) {
> 
>         int numberOfPhilosophers = 5;
> 
>         Fork[] forks = new Fork[numberOfPhilosophers];
> 
>   
> 
>         // Initialize each fork
> 
>         for (int i = 0; i < numberOfPhilosophers; i++) {
> 
>             forks[i] = new Fork();
> 
>         }
> 
>   
> 
>         // Initialize philosophers
> 
>         Philosopher[] philosophers = new Philosopher[numberOfPhilosophers];
> 
>         for (int i = 0; i < numberOfPhilosophers; i++) {
> 
>             Fork leftFork = forks[i];
> 
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