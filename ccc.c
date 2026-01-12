#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

/*Dear students,
The attached files contain examples on how to use dup2 in conjunction with 
various file descriptors/pipes. You can use them to implement the following 
requirements:
1. Implement a C application that creates N different child processes which 
can communicate with each other, full duplex (both ways). The parent process 
will send information from file F to the children. Both N and the path to 
file F will be sent as command-line arguments at execution.
The information sent by the parent process to the child processes through pipes
 can be:
a) All the characters found at odd positions in the file.
b) All the even-value characters.
c) Each third word found in the file.
The subprocesses will process the information and send it back to the parent, 
attaching their own PID to the information, through pipes.
 The information will be further processed by the parent and then printed to
  STDOUT, based on the above subpoints:
a) The number of vowels.
b) The characters resulted from doubling the value received 
(the parent will print the values as hexadecimal numbers).
c) The number of characters in each word.
Each subprocess will validate the information received by the parent 
with the other child processes by communicating it through pipes.*/

int main(int argc, char **argv)
{
    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);

    pid_t pid=fork();

    if(pid==0)
    {
        
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        int n = atoi(argv[2]);

        for(int i=0; i<n;i++){
            
        }
    }
}