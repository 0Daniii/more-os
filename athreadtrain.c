#include <stdio.h>
#include <pthread.h>  // For creating and managing threads
#include <semaphore.h> // For sem_init, sem_wait, sem_post
#include <unistd.h>    // For sleep()

/*The Thread & Semaphore Training Plan 🚦

Since we are only focusing on Semaphores for synchronization, here are your exercises. 
Note that in threads, we use global variables to "pass" data instead of pipes.

1. The Green Light

Create one semaphore and initialize it to 0. Create a thread that prints "Child waiting...". 
In your main, sleep for 2 seconds, then "post" (increment) the semaphore. Observe how the 
thread waits for the main process to give it the signal.

2. The Shared Variable

Create a global integer x = 0. Create two threads. Both threads should try to increment 
x 10,000 times. Run it without semaphores first to see it fail (the result won't be 20,000).
 Then, use a semaphore as a "Lock" to make the result exactly 20,000.

3. The Ping-Pong (Two Semaphores)

Create two semaphores: sem_ping (init to 1) and sem_pong (init to 0).

Thread A waits for sem_ping, prints "Ping", then posts sem_pong.

Thread B waits for sem_pong, prints "Pong", then posts sem_ping. Loop this 5 times to 
see them perfectly alternate.

4. The Array Protector

Create a global array of 5 integers. Thread A fills the array with numbers (1 to 5). 
Thread B should not start reading/printing the array until Thread A is completely finished. 
Use a semaphore to signal "Work Done."

5. The Producer-Consumer (Mini Version)

Create a "mailbox" (a single global integer).

Producer thread generates a random number, puts it in the mailbox, and signals the consumer.

Consumer thread waits for the signal, "eats" the number (prints it), and signals the producer 
that the mailbox is empty and ready for a new number.*/

