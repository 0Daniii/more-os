#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//Exercise 3: "The Multi-Tool Worker"
//The Problem:
//Define a struct called WorkData that contains an id (int) and a multiplier (int).
//In main, create two "Boxes" (structs):
//Box 1: ID = 1, Multiplier = 5.
//Box 2: ID = 2, Multiplier = 10.
//Create two threads. Hand Box 1 to Thread A and Box 2 to Thread B.
//Each thread must calculate: result = ID * Multiplier and print it.
// 1. THE BOX (The Struct)

typedef struct {
    int id;
    int multiplier;
} WorkData;

// 2. THE WORKER
void* worker_func(void* arg) {
    // TASK 1: Unpack the Box.
    // First, cast 'arg' to a WorkData pointer.
    WorkData* data = (WorkData*)arg;

    // TASK 2: Use the data inside the box.
    // Access the id and multiplier to calculate a result.
    int result = data->id * data->multiplier;

    printf("Thread %d: My result is %d\n", data->id, result);
    
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // 3. PREPARE THE DATA
    // We create two instances of our struct
    WorkData w1 = {1, 5};
    WorkData w2 = {2, 10};

    // TASK 3: Create the threads.
    // Pass the ADDRESS of the structs (&w1 and &w2).
    pthread_create(&t1, NULL, worker_func, &w1);
    pthread_create(&t2, NULL, worker_func, &w2);

    // TASK 4: Join the threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: All work done.\n");
    return 0;
}