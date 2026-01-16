#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

/*Goal: Write a C program that mimics the behavior of this shell command:
 grep "error" <logfile> | wc -l

(In plain English: "Search for the word 'error' in a file, and count how many 
lines were found.")

The Setup:

Input: The filename is passed as argv[1].

The Pipe: Connects the output of grep to the input of wc.

The Process:

Child 1 (The Searcher):

Connects its Standard Output (stdout) to the write-end of the pipe using dup2.

Closes the unused read-end.

Replaces its code using execlp to run grep.

Command: grep "error" argv[1]

Child 2 (The Counter):

Connects its Standard Input (stdin) to the read-end of the pipe using dup2.

Closes the unused write-end.

Replaces its code using execlp to run wc.

Command: wc -l (counts lines).

Parent:

Crucial: Closes both ends of the pipe (so Child 2 sees EOF).

Waits for both children.*/



int main( int argc, char **argv)
{
    int pipe12[2];
    pipe(pipe12);

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
       
        dup2(pipe12[1], 1);
         close(pipe12[0]);
        close(pipe12[1]);
        execlp("grep", "grep", "error", argv[1], NULL);

    }

    pid_t pid2 = fork();
    if(pid2 == 0 )
    {
        close(pipe12[1]);
        dup2(pipe12[0], 0);
        close(pipe12[0]);
        execlp("wc", "wc", "-l", NULL);
    
    }
    close(pipe12[0]);
    close(pipe12[1]);

    wait(NULL);
    wait(NULL);

    return 0; 
}