#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//This is the best way to learn: building the muscle memory. Here is your first exercise. We will call it "The Hand-Off." It’s the simplest possible version of a pipeline.

//The Problem: "The Secret Number"
//Thread A (The Creator): Will pick a secret number (like 42) and save it in a global variable.
//Thread B (The Messenger): Must wait for Thread A to finish, then read that number and print: "The secret number is: [X]".
//Constraint: You must use a Semaphore to make sure Thread B doesn't try to print the number before Thread A has actually set it.

//Your Logic Tasks:
//Inside creator_func: Set the variable and "ring the bell" (Signal/Post).
//Inside messenger_func: "Listen for the bell" (Wait) and then print.
//Inside main: Use the "Start Buttons" (create) and "Wait Buttons" (join).
//Critical Thinking Question for you:
//If you forgot to use the Semaphore, and the OS decided to run Thread B before Thread A, what would the output be?

//Try to fill in those tasks. If you get stuck on a specific line of code, ask me and I'll explain just that line!
// --- GLOBAL KITCHEN (Shared Memory) ---


int secret_number = 0;
sem_t data_ready; // The traffic light

// --- THREAD A: THE CREATOR ---
void* creator_func(void* arg) {
    printf("Creator: I am thinking of a number...\n");
    sleep(2); // Simulating work
    
    secret_number = 42; // TASK 1: Set the secret number
    
    // TASK 2: "Post" to the semaphore to say the data is ready
    sem_post(&data_ready);
    printf("Creator: I've set the number and signaled Thread B.\n");
    return NULL;
}

// --- THREAD B: THE MESSENGER ---
void* messenger_func(void* arg) {
    // TASK 3: "Wait" on the semaphore (Wait for the light to turn green)
    sem_wait(&data_ready);
    printf("Messenger: Received the signal from Thread A.\n");
    // TASK 4: Print the secret_number
    printf("Messenger: The secret number is: %d\n", secret_number);
    
    return NULL;
}

int main() {
    pthread_t threadA, threadB;

    // --- INITIALIZATION ---
    // TASK 5: Initialize the semaphore. 
    // Logic: Should it start at 0 (locked) or 1 (open)? 
    // Hint: We want Thread B to wait at the start.

    sem_init(&data_ready, 0, 0);

    // --- CREATION ---
    // TASK 6: Create both threads
    // Hint: pthread_create(&id, NULL, func, NULL);
    pthread_create(&threadA, NULL, creator_func, NULL);
    pthread_create(&threadB, NULL, messenger_func, NULL);

    // --- SYNCHRONIZATION ---
    // TASK 7: Join both threads so main doesn't exit early
    // Hint: pthread_join(id, NULL);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Cleanup
    sem_destroy(&data_ready);
    printf("Main: Work finished. Program exiting.\n");

    return 0;
}