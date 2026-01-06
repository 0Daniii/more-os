//2. Implement a C-based application that reads data from a file given as a command-line argument. 
//The program will split the file into a number of thread parts, then compute the average value of 
//each part in each thread. The main thread will compute the average of the values received from 
//the threads. You can use:
        //a) the exit values from the threads to send the information to the main thread.
        //b) use a shared variable to compute all the final average.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int v[1000]; //we assume the file has less than 1000 numbers 

int main(int argc, char *argv[])
{

    char *name = argv[1];
    int a = atoi(argv[2]);
    FILE *filee = fopen(name, "r");
    char ch;  
    int i=0;
     while(fscanf(filee, "%d", &v[i]) == 1)
        {
            i++;
        }
    int chunk = total_numbers / num_threads;

for (int k = 0; k < num_threads; k++) {
    int start = k * chunk;
    int end = (k + 1) * chunk - 1;

    // Special case: The last thread takes everything until the very end
    if (k == num_threads - 1) {
        end = total_numbers - 1;
    }
    
    // Now you put 'start' and 'end' into the suitcase and call pthread_create
}


}