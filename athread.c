
#include <stdio.h>      // For printf and input/output
#include <stdlib.h>     // For exit(), malloc(), and rand()
#include <pthread.h>    // The core Threading library (create, join, exit)
#include <semaphore.h>  // The Semaphore library (init, wait, post, destroy)
#include <unistd.h>     // For sleep() and usleep()
#include <sys/types.h>  // For specialized type definitions like pthread_t
#include <string.h>

/*Phase 1: Thread Basics (The "Roommates")

These exercises focus on creating and joining threads using pthread_create and pthread_join.

The Hello Thread: Create a single thread that prints
 "Hello from the thread!" and its thread ID.

The Argument Passer: Create a thread and pass it an integer (e.g., 42) 
through the void *arg parameter. Have the thread print that number.

The Multi-Threader: Use a loop to create 5 threads. Each should print 
"I am thread number X" (where X is the loop index).

The Return Value: Have a thread calculate the square of a number and 
"return" it to the main thread using pthread_exit or by returning from the function. 
Catch it with pthread_join.*/

//cheat
//sem_t s;
//sem_init(&s, 0, 1); // 0 means shared between threads, 1 is initial value
//sem_wait(&s);       // The "P" operation (Wait/Decrement)
//sem_post(&s);       // The "V" operation (Signal/Increment)
//sem_destroy(&s);    // Cleanup


/*sem_t sem1;

void* thread01()
{

    printf("Hello from the thread!");

}

int main()
{
    pthread_t t1;
    sem_init(&sem1, 0, 0);

    pthread_create(&t1, NULL, thread01, NULL);

    pthread_join(t1, NULL);


}*/


/*The Argument Passer: Create a thread and pass it an integer (e.g., 42) 
through the void *arg parameter. Have the thread print that number.*/


/*void* vt(void* arg)
{
    int d = *(int*)arg;
    printf("Hello, this is thread and i got the number %d", d);
}

int main()
{
    int i = 69;
    pthread_t t1;


    pthread_create(&t1, NULL, vt, &i);
    pthread_join(t1, NULL);

}*/



//The Multi-Threader: Use a loop to create 5 threads. Each should print 
//"I am thread number X" (where X is the loop index).
/*sem_t sem1;

void* vt(void* arg)
{
    sem_wait(&sem1);
    int d = *(int*)arg;
    printf("I am thread number %d\n", d+1);
    sem_post(&sem1);
}

int main()
{
    sem_init(&sem1, 0, 1);
    pthread_t t[5];

    for(int i = 0; i<5; i++)
    {
        pthread_create(&t[i], NULL, vt, &i);
        pthread_join(t[i], NULL);
    }
 

    return 0;
}*/


//The Return Value: Have a thread calculate the square of a number and 
//return" it to the main thread using pthread_exit or by returning from the function. 
//Catch it with pthread_join.*/

/*void* vd(void* arg)
{
    int a = *(int*)arg;
    a = a*a;
    int *s = malloc(sizeof(int));
    *s = a;
    pthread_exit(s);
}

int main()
{
    pthread_t t1;
    int var = 10;
    void* s;
    pthread_create(&t1, NULL, vd, &var);
    pthread_join(t1, &s);

    int fin = *(int*)s;

    printf("%d", fin);
}*/

/*Phase 2: Semaphore Basics (The "Traffic Lights")

Focus on sem_init, sem_wait, and sem_post.

The Red Light: Initialize a semaphore to 0. Create a thread that prints "Waiting...". 
In main, sleep for 2 seconds, then call sem_post. Watch the child wait.

The Mutex Lock: Create a global variable int counter = 0. Create two threads that both 
increment it 10,000 times. Observe the "Race Condition" (the total won't be 20,000). Now, 
use a semaphore (initialized to 1) to lock the incrementing line and fix it.

The Alternator (Ping-Pong): Create two semaphores: sem1 (init to 1) and sem2 (init to 0).
 Thread A prints "Ping" and posts sem2. Thread B waits for sem2, prints "Pong", and posts sem1.
  Loop this to see them alternate perfectly.*/

/*sem_t sem1;

void* vd(void* arg)
{
    printf("Waiting..\n");
    sem_wait(&sem1);

    sleep(2);

    sem_post(&sem1);
}

int main()
{
    pthread_t t1;
    sem_init(&sem1, 0, 1);

    pthread_create(&t1, NULL, vd, NULL);

    pthread_join(t1, NULL);

    return 0;
}*/

//The Mutex Lock: Create a global variable int counter = 0. Create two threads that both 
//increment it 10,000 times. Observe the "Race Condition" (the total won't be 20,000). Now, 
//use a semaphore (initialized to 1) to lock the incrementing line and fix it.

/*int counter = 0; 
 sem_t sem1; 

 void* inc()
 {
    sem_wait(&sem1);
    for(int i=0; i<10000; i++)
    counter++;
    sem_post(&sem1);
    return NULL;
 }
int main()
{
    pthread_t t1,t2;
    sem_init(&sem1, 0,1);
    pthread_create(&t1, NULL, inc, NULL);
    pthread_create(&t2, NULL, inc, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%d", counter);
    return 0; 

}*/

/*The Alternator (Ping-Pong): Create two semaphores: sem1 (init to 1) and sem2 (init to 0).
 Thread A prints "Ping" and posts sem2. Thread B waits for sem2, prints "Pong", and posts sem1.
  Loop this to see them alternate perfectly.*/


/*sem_t sem1, sem2;

void* vd1(void* arg)
{
    int s = *(int)arg;
 
    for(int i= 0; i<s;i++)
    {
           sem_wait(sem1);
        printf("Ping\n");
           sem_post(sem2);
    }
 
}


void* vd2(void* arg)
{
    int s = *(int*)arg;

    for(int i= 0; i<s;i++)
    {
            sem_wait(sem2);
        printf("Pong\n");
           sem_post(sem1);
    }
 
}

int main()
{
    pthread_t p1, p2;
    int alt = 5;
    sem_init(&sem1, 0,1);
    sem_init(&sem2, 0,0);
    pthread_create(&p1, NULL, vd1, &alt);
    pthread_create(&p2, NULL, vd2, &alt);
    pthread_join(t1,NULL);
    pthread_join(t2, NULL);

    return 0;
}*/

/*Phase 3: Resource Management (The "Buffet")

These are closer to actual exam problems.

The Shared Array: Create a global array of size 10. Thread A fills
 the array with random numbers. Thread B must wait until the array
  is completely full before it calculates the sum. Use a semaphore 
  to signal when "Data is Ready."

The Limited Capacity: Initialize a semaphore to 3. Create 10 threads
 that all try to "enter a room" (print "I'm in!"), sleep for 1 second,
  then leave. Observe how only 3 threads are "inside" at any given time.

The Barrier: Create 3 threads. Make them all wait at a "starting line" 
using semaphores. None should print "Running!" until all 3 have reached the line.*/
 /*char wowels[6] = "aeiou";
    int count = 0;
sem_t sem1;

void* vd(void* arg)
{
    char* ch = (char*)arg;
    for(int j =0; ch[j]!='\0'; j++)
    for( int i = 0; i<5;i++)
    {
        if(ch[j]==wowels[i])
        {
            sem_wait(&sem1);
            count++;
            sem_post(&sem1);
        }
    }
}

int main(int argc, char **argv)
{
    pthread_t t[argc-1];

    sem_init(&sem1, 0 ,1);

    for(int i = 0; i<argc-1;i++)
    {
   
        pthread_create(&t[i], NULL, vd, argv[i+1]);
    }
    for(int i = 0; i<argc-1;i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("Total numb of wowels is: %d", count);

    return 0;
}*/




/*int main (int argc, char**argv)
{
    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);
    pid_t pid1 = fork();

        if (pid1 ==0 )
        {
            close(pipe21[1]);
            close(pipe12[0]);
            char ch[1000] = "";
            for(int i=1; i<=argc; i++)
            {
                strcat(ch, argv[i]);
                if(i<argc)
                {
                    strcat(ch, " ");
                }
            }
            write(pipe12[1], &ch, sizeof(ch));
            close(pipe12[1]);
            char chver[1000]= "";
            char chverlocal[1000] = "";
            strcpy(chverlocal, ch);
            int count = 0;
              for( int i = 0; i <= strlen(ch);i++)
            {
                if(ch[i]== ' ' || ch[i]=='\0')
                {
                    for(int j = 0; j<i-count; j++)
                    {
                        chverlocal[j] = ch[i-j];
                    }
                    
                    if(ch[i] == ' ')
                    count = i+1;
                }
            }
            read(pipe21[0], &chver, sizeof(chver));
           
          //  we will also run the same algoritm from pid 2 to create a local version 

          if (strcmp(chverlocal,chver) == 0)
          {
            printf("OK");
          }

          exit(0);


        }
        pid_t pid2 = fork();
        if(pid2==0)
        {
                close(pipe21[0]);
            close(pipe12[1]);
            char ch[1000] = "", chrev[1000] = "";
            read(pipe12[0], &ch, sizeof(ch));
            int k=0,count=0;
             // logic for mirroring the arguments but not the order of them
            for( int i = 0; i<strlen(ch);i++)
            {
                if(ch[i]== ' ' || ch[i]=='\0')
                {
                    for(int j = 0; j<i-count; j++)
                    {
                        chrev[j] = ch[i-j];
                    }
                    
                    if(ch[i] == ' ')
                    count = i+1;
                }
            }
            exit(0);
          
           //we print them back 

           //this is orientative since i m too lazy to do it rn, in princple i ll go trough the string with a for, another for then, have a k to 0, have a count, we itterate till we find the read to be different to " " or \0, and when we hit space or eoc, we have an aug char where we write from 
           // from i - j , j rises while i-j is bigger or equal than count, and then count is going to be count +i to start at the next character that is a letter.
        }
       
          
            close(pipe21[1]);
            close(pipe12[0]);
            close(pipe21[1]);
            close(pipe12[0]);

            wait(NULL);
            wait(NULL);
}



Problem 1: The Threaded Character Filter

Focus: Thread management, Mutexes, and Case-sensitivity logic.

Requirement: Write a C program that receives multiple strings as command-line arguments. 
The program spawns one thread per string. Each thread identifies all uppercase consonants 
(B, C, D, F, G, etc.) in its string and adds the count to a shared global counter.

Access to the shared counter must be synchronized using a mutex.

After all threads finish, the main thread prints the total number of uppercase consonants 
found.

If no argument is used at execution, the program will print to STDOUT:
"Error: no argument found" and exit with an exit code 0.

Example Execution: ./a.out Apple Banana Orange Output: 
3 (Explanation: A is a vowel, B is uppercase, P is lowercase, etc. Only 'B', 'P', 'N'
     counts if they were uppercase... wait,
 let's re-count: 'A' (vowel), 'B' (consonant), 'O' (vowel). The only uppercase consonants are 'B'. 
 If it were "APPLE BANANA", it would count B, N, N.)' */

/*sem_t sem1;
char cons[22] = "BCDFGHJKLMNPQRSTVWXYZ";
int count = 0;

void* vd(void* arg)
{
    char* ch = (char*)arg;
    for(int i = 0; ch[i] != '\0';i++)
    {
        for(int j = 0; j<22;j++)
        {
            
            if(ch[i]==cons[j])
            {
            sem_wait(&sem1);
            count++;
            sem_post(&sem1);
            }
        }
    }
    pthread_exit(0);
}

 int main (int argc, char **argv)
 {
    pthread_t t[argc-1];
    sem_init(&sem1, 0 ,1);

    for(int i = 1; i<argc-1; i++)
    {
        pthread_create(&t[i-1], NULL, vd, argv[i]);
    }

    for(int i = 1; i<argc-1; i++)
    {
        pthread_join(t[i], NULL);
    }

    return 0;

 }*/



 /*Problem 2: The Two-Way Math Pipe

Focus: Two child processes, bidirectional pipes, and string parsing.

Requirement: Create a C application that spawns two child processes communicating 
via two pipes.

The first subprocess reads all command-line arguments, converts each argument into 
its string length (e.g., "apple" becomes "5"), concatenates these lengths into a single 
string separated by commas (e.g., "5,6,3"), and sends this string to the second subprocess.

The second subprocess receives the string, calculates the sum of all the numbers
 in that string, prints the sum to STDOUT, and sends the sum (as an integer) back
  to the first subprocess.

The first subprocess receives the sum, checks if the sum is an even number, 
and prints "EVEN" or "ODD" accordingly.

If no argument is used at execution, the program will print to STDOUT:
 "Error: no argument found" and exit with an exit code 0.

Example Execution: ./a.out cat dog Output: 6 EVEN*/

/*int main(int argc, char** argv)
{
    if( argc<1)
    {
        printf("Error: no argument found");
        return 0;
    }
    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);

    pid_t pid1 = fork();

    if (pid1 == 0)
    {
        close(pipe12[0]);
        close(pipe21[1]);
        char ch[1000] = "";
        for(int i = 0; i<argc-1;i++)
        {
            int a = strlen(argv[i+1]);
            char b[2];   
            b[0] = a + '0'; 
            b[1] = '\0';
            strcat(ch,&b);
            if(i<argc-2)
            strcat(ch, ",");
        }
        write(pipe12[1], &ch, sizeof(ch));
        close(pipe12[1]);
        int sum;
        read(pipe21[0],&sum,sizeof(sum));
        close(pipe21[0]);

        if(sum%2 ==0 )
        {
            printf("\nEven");
        }
        else
        {
            printf("\nODD");
        }

        exit(0);


    }
    pid_t pid2 = fork();

    if(pid2 == 0 )
    {
         close(pipe12[1]);
        close(pipe21[0]);

        char ch[1000] = "";
        int sum = 0;
        read(pipe12[0], &ch, sizeof(ch));
        for(int i= 0; i<strlen(ch); i= i+2)
        {
            sum = sum + atoi(&ch[i]);
        }
        printf("Sum is: %d", sum);
        write(pipe21[1],&sum, sizeof(sum));
        close(pipe21[1]);
        exit(0);
    }
     close(pipe12[1]);
        close(pipe21[0]);
           close(pipe12[0]);
        close(pipe21[1]);

        wait(NULL);
        wait(NULL);

        return 0;
}*/

/*Create a C application that spawns two child processes which communicate with 
each other using pipes.

The first subprocess will read all command-line execution arguments, which are strings 
representing words. It will concatenate them into a single message separated by spaces 
and then apply a character substitution transformation defined as follows:

Each lowercase letter (a–z) is replaced by the next letter in the alphabet (z becomes a)
Each uppercase letter (A–Z) is replaced by the previous letter in the alphabet (A becomes Z)

All other characters remain unchanged
The transformed message is sent through a pipe to the second subprocess.

The second subprocess will read the message from the pipe, apply the inverse transformation
to recover the original message, print the recovered message to standard output, and then
 send it back to the first subprocess through a second pipe.

After receiving the message from the second subprocess, the first subprocess compares it
 with its original concatenated message. If they are identical, it prints:
  "Communication successful", otherwise "Communication failed". If no argument 
  is used at execution, the program will print to STDOUT: "Error: no argument found" 
  and exit with an exit code 0.

Executing the program with the following arguments:  
./a.out abcd AbCd abtd3 q-t3

 will generate the following output:
 bcde ZcBe bcue3 r-u3
 Communication successful  */

 int main( int argc,char **argv)
 {
    if(argc<1)
    {
        printf("Error: no argument found");
        exit(0);
    }
    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);

    pid_t pid1= fork();

    if(pid1 == 0)
    {
        char a[1000] = "";
        char b[1000] = "";
        close(pipe12[0]);
        close(pipe21[1]);
        
        for(int i = 1; i<argc;i++)
        {
            strcat(a, argv[i]);
            if(i<argc-1){
                strcat(a, " ");
            }
        }
        for( int i = 0; i<strlen(a);i++)
        {
            if(a[i]< 'a' && a[i] > 'z')
            {
                b[i] = (a[i] + 1)%27;
            }
             if(a[i]< 'A' && a[i] > 'Z')
            {
                b[i] = (a[i] - 1)%27;
            }
        }
        write(pipe12[1],&b, sizeof(b));
        close(pipe12[1]);
        char chc2[1000] = "";
        read(pipe21[0],&chc2, sizeof(chc2));
        if((strcmp(chc2, a))== 0)
        {
            printf("Communication successful");
        }
        else
        {
            printf("Communication unsuccessful");
        }
        exit(0);

    }
    pid_t pid2 = fork();
    
    if(pid2==0)
    {
        char b[1000] = "";
        char a[1000] = "";
        close(pipe12[1]);
        close(pipe21[0]);
        read(pipe12[0], &a, sizeof(a));
        close(pipe12[0]);
          for( int i = 0; i<strlen(a);i++)
        {
            if(a[i]< 'a' && a[i] > 'z')
            {
                b[i] = (a[i] - 1)%27;
            }
             if(a[i]< 'A' && a[i] > 'Z')
            {
                b[i] = (a[i] + 1)%27;
            }
        }
        write(pipe21[1], &b, sizeof(b));
        close(pipe21[1]);
    
        exit(0);

    }
        close(pipe12[0]);
        close(pipe21[1]);
        close(pipe12[1]);
        close(pipe21[0]);

        wait(NULL);
        wait(NULL);
 }