#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//The Problem: The Controlled Warehouse
//You need to simulate a factory line with two specific roles that must work in a perfect, repeating sequence.
//The Producer (Thread A):
//Must "manufacture" 5 items, one by one.
//For each item, it increments a global variable warehouse_stock.
//Crucial: It cannot start making the next item until the Quality Control thread has finished checking the current one.
//The Quality Control (Thread B):
//Must wait for the Producer to put an item in the warehouse.
//Once an item arrives, it prints: "QC: Item #[N] has been verified."
//Crucial: It must signal the Producer that the warehouse is now empty and ready for the next item.
//Requirements:
//Use two semaphores to create a "ping-pong" effect (Thread A signals B, then Thread B signals A).
//Create a struct to pass a "Worker ID" (int) and a "Work Delay" (int) to the Producer thread.
//The Producer must use sleep() based on the delay passed in the struct.
//Ensure the program finishes cleanly only after all 5 items are produced and checked.

// 1. Define your Struct here

// 2. Define your Global Variables and Semaphores here
typedef struct {
    int id;
    int delay;
    int total_to_make; // You can put the '5' in here too!
} WorkData;

sem_t sem1;
sem_t sem1;

void* producer(void* arg) {
    WorkData* data = (WorkData*)arg; // Unpacking the suitcase
    
    for(int i = 0; i < data->total_to_make; i++) {
        // 1. Wait for permission to produce (sem_wait)
        sem_wait(sem2);
        // 2. Do work (increment stock, maybe sleep(data->delay))
        
        // 3. Signal that item is ready (sem_post)
    }
    return NULL;
}

void* quality(void* arg) {
    int limit = *(int*)arg; // If you only pass stock
    
    for(int i = 0; i < limit; i++) {
        // 1. Wait for item to be ready
        // 2. Print verification
        // 3. Signal that warehouse is empty (sem_post)
    }
    return NULL;
}

int main() {
    // 5. Initialize IDs, Threads, and Semaphores
    pthread_t A,B;
    sem_init(&sem1, 1, 0);
    sem_init(&sem2, 0, 0)
    pthread_create(&A, NULL, producer, &stock);
    pthread_create(&B, NULL, quality, &stock);
    // 7. Wait for completion
    thread_join(A, NULL);
    thread_join(B,NULL);
    // 8. Cleanup and Exit

    return 0;
}