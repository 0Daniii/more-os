#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

/*Warm-up: The Basics of fork()

Identity Crisis: Write a program where the child prints "I am the child, PID: [ID]" and the parent prints "I am the parent, PID: [ID]".

The Relative: Write a program where the child prints its own PID and its parent's PID.

The Orphan: Create a child process, make the parent exit() immediately, and have the child print its parent's PID after a 2-second sleep(). (Observe how the parent PID changes to 1).

The Double Fork: Call fork() twice in a row. How many processes are created? Have each one print "Hello".

The Loop Fork: Write a loop that calls fork() 3 times. How many "Hello" messages do you get? (Hint: It’s not 3).

The Conditional Fork: Create a child only if the parent's PID is an even number.

Exit Status: Have a child exit with the code 42. Have the parent catch it and print: "Child finished with status: 42".*/

//problem 1 

/*int main ()
{
    pid_t pid = fork();

    if(pid==0)
    {
        printf("I am the child, PID:%d\n", getpid());
        exit(0); 
    }
    if(pid>0)
    {
        printf("I am the parent, PID:%d\n", getpid());
        wait(NULL);
    }
    return 0;
}*/

/*int main ()
{
    pid_t pid = fork();

    if(pid==0)
    {
        printf("I am the child, PID:%d\n", getpid());
        printf("I am the parent, PID:%d\n", getppid());
        exit(0); 
        
    }
    if(pid>0)
    {
        wait(NULL);
    }
    return 0;
}*/

/*int main ()
{
    pid_t pid = fork();

    if(pid==0)
    {
        sleep(2);
        printf("I am the parent, PID:%d\n", getppid());
        exit(0); 
        
    }
    if(pid>0)
    {
        exit(0);
    }
    return 0;
}*/

/*int main ()
{
    fork();
    fork();

    printf("hello\n");
   
    return 0;
}*/

/*int main ()
{
    for(int i= 0; i<=2;i++)
    fork();


    printf("hello\n");
   
    return 0;
}*/

/*int main ()
{
 
   pid_t pid = fork();

    if(pid==0 && (getppid() %2) == 0)
    printf("hello\n");
   
    return 0;
}*/

/*int main ()
{
    int status;
   pid_t pid = fork();

    if(pid==0)
    {
        exit(42);
    }
    else
    {
        wait(&status);
        int result = WEXITSTATUS(status);
        printf("Child exited with code %d", result);
    }
   
    return 0;
}*/
