#include <stdio.h>      // For printf and perror
#include <stdlib.h>     // For exit()
#include <unistd.h>     // THE MOST IMPORTANT: contains pipe(), fork(), read(), write(), and close()
#include <sys/wait.h>   // For wait() and waitpid()
#include <string.h>     // Useful for strlen() when sending text through pipes

/*Intermediate: The Basics of pipe()

The Basic Tube: Create a pipe, write the integer 100 into it, and read it back in the same process.

One-Way Talk: Create a pipe, fork(), and have the parent send the character 'A' to the child.

The Secret Message: Parent sends a string "OS is fun" to the child. Child prints it.

Close the Mouth: Write a program where the child tries to read from a pipe, but the parent closes the write-end without sending anything. Observe what happens to read().

The Broken Pipe: Have the child close the read-end, and then have the parent try to write to it. (Research what SIGPIPE is).

Array Transfer: Parent creates an array of 5 integers {1, 2, 3, 4, 5} and sends the whole array through a pipe to the child.

Simple Math: Parent sends two integers to the child. Child adds them and prints the result.*/

/*int main()
{
    int pipe12[2];
    int n = 100;
    char readd[100];
    pipe(pipe12);
    write(pipe12[1], &n, sizeof(readd));
    read(pipe12[0], readd, sizeof(readd));
    printf("%d", *readd);
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);
    pid_t pid = fork();
    if(pid==0)
    {
        close(pipe12[1]);
        char a[100];
        read(pipe12[0], &a, sizeof(a));
        printf("%s", a);
    }
    else
    {

        close(pipe12[0]);
        char a = 'A';
        write(pipe12[1], &a, sizeof(a));

        wait(NULL);


    }
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);
    pid_t pid = fork();
    if(pid==0)
    {
        close(pipe12[1]);
        char a[100];
        read(pipe12[0], &a, sizeof(a));
        printf("%s", a);
    }
    else
    {

        close(pipe12[0]);
        char a[100] = "OS is fun";
        write(pipe12[1], &a, sizeof(a));

        wait(NULL);


    }
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);
    pid_t pid = fork();
    if(pid==0)
    {
        close(pipe12[1]);
        char a[100];
        read(pipe12[0], &a, sizeof(a));
        printf("%s", a);
    }
    else
    {

        close(pipe12[0]);
        close(pipe12[1]);

        wait(NULL);


    }
}*/

/*int main() 
{
    int pipe12[2];
    pipe(pipe12);
    pid_t pid =fork();

    if (pid == 0 ){
        close(pipe12[0]);
        close(pipe12[1]);
    }
    else 
    {   close(pipe12[0]);
        char a = 'A';
        write(pipe12[1], &a, sizeof(a));

    }
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);
    pid_t pid = fork();
    if ( pid== 0 )
    {
        close(pipe12[1]);
        int v[5];
        read(pipe12[0], &v, sizeof(v));

        for( int i=0; i<5; i++)
        {
            printf("%d ", v[i]);
        }

    }
    else
    {
        close(pipe12[0]);
        int v[5];

        for( int i=0; i<5; i++)
        {
            v[i]= i+1;
        }

        write(pipe12[1], &v, sizeof(v));

    }
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);
    pid_t pid = fork();
    if ( pid== 0 )
    {
        close(pipe12[1]);
        int a, count = 0;
        while(read(pipe12[0], &a, sizeof(int)) != 0) 
        {
            count += a;
        }
        printf("%d ", a);
        

    }
    else
    {
        close(pipe12[0]);
        int a=5, b=12;
        write(pipe12[1], &a, sizeof(int));
  write(pipe12[1], &b, sizeof(int));
    }
}*/


