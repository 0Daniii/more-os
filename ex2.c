
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// --- GLOBAL KITCHEN ---
int shared_result = 0;
sem_t sem1; // Between Multiplier and Adder
sem_t sem2; // Between Adder and Printer

// --- STAGE 1: THE MULTIPLIER ---
void* multiplier_func(void* arg) {
    // TASK 1: "Unpack" the suitcase. 
    // Convert the 'arg' back into an integer.
    int start_val = *(int*)arg; 
    
    shared_result = start_val * 2;
    printf("Multiplier: Result is %d. Signaling Adder...\n", shared_result);

    // TASK 2: Turn the light green for the Adder
    sem_post(&sem1);
    return NULL;
}

// --- STAGE 2: THE ADDER ---
void* adder_func(void* arg) {
    sem_wait(&sem1)
    
    shared_result = shared_result + 10;
    printf("Adder: Result is %d. Signaling Printer...\n", shared_result);

    sem_post(&sem1);
    sem_post(&sem2);
    
    return NULL;
}

// --- STAGE 3: THE PRINTER ---
void* printer_func(void* arg) {

    sem_wait(&sem2);
    
    printf("Printer: The final factory result is: %d\n", shared_result);

    sem_post(&sem2);
        return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int initial_input = 5;

    // TASK 6: Initialize both semaphores to 0
    sem_init(&sem1, 0 ,0 );
    sem_init(&sem, 0, 0 );

    // TASK 7: Create threads. 
    // Pass the ADDRESS of initial_input to t1.
    // Pass NULL to t2 and t3 (they don't need suitcases).
    pthread_create(&t1, NULL, multiplier_func, &initial_input);
    pthread_create(&t2, NULL, adder_func, NULL);
    pthread_create(&t3, NULL, printer_func, NULL);

    // TASK 8: Join all 3 threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Cleanup
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}


int main() {
    pthread_t t1, t2, t3;
    int initial_input = 5;

    // TASK 6: Initialize both semaphores to 0
    sem_init(&sem1, 0 ,0 );
    sem_init(&sem, 0, 0 );

    // TASK 7: Create threads. 
    // Pass the ADDRESS of initial_input to t1.
    // Pass NULL to t2 and t3 (they don't need suitcases).
    pthread_create(&t1, NULL, multiplier_func, &initial_input);
    pthread_create(&t2, NULL, adder_func, NULL);
    pthread_create(&t3, NULL, printer_func, NULL);

    // TASK 8: Join all 3 threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Cleanup
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}