#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

/*2. Write a C program which receives strings that each contain
space‐separated integers (e.g. "10 20 -30"). 
The program spawns one thread per input string; each thread parses 
its numbers, computes their partial sum, and adds it to a shared long accumulator.

 When all threads complete, the main thread prints the overall sum. 
 Solutions that do not employ threads and proper synchronisation
 will not receive credit.
Executing the program with the following arguments:  
./a.out "1 2 4 5" "1 2 5 1 4" "1 5 1 2 5" "1 2 4 1 5" "1 15 12 22"
 
will generate the following output:
 102*/
sem_t sem1;
int total = 0;
void thread(*arg)
{
    char* ch = (char*)arg;

    while( *ch != '\0')
    {
        if(!( ch >- '0' && ch <= '9' || ch == '-'))
        {
            ch++;
            continue;
        }

        int curvar = 0, neg = 0;
        if( ch == '-')
        {
            neg = 1; 
        }
        else 
        {
            curvar = curvar + atoi(ch);
        }
    }

}

int main(int argc, char *argv[])
{
 int n = argc-1; 
 pthread_t threads[n];
 for( i = 1; i<argc;i++)
 {
    pthread_create(&threads[i], NULL, thread, argv[i]);
 }
  for( i = 1; i<argc;i++)
 {
    pthread_join(threads[i], NULL);
 }

 

}