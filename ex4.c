#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* rank_worker(void* arg) {
    // TASK 1: Unpack the rank from the suitcase
    // (Hint: It was passed as an int pointer)
    int my_rank = *(int*)arg;

    printf("I am thread #%d reporting for duty!\n", my_rank);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // This array provides a unique "suitcase" for each thread
    int thread_ranks[NUM_THREADS];

    // TASK 2: Use a loop to create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Prepare the data for this specific thread
        thread_ranks[i] = i;

        // Start the thread
        // Hint: Pass the address of the specific slot in thread_ranks
        pthread_create(&threads[i], NULL, rank_worker, &thread_ranks[i]);
    }

    // TASK 3: Use another loop to join all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: All threads have reported back.\n");
    return 0;
}
