#include <fcntl.h>      // For open(), O_CREAT, O_RDONLY (File Control)
#include <signal.h>     // For kill(), signal(), and handling SIGCHLD/SIGPIPE
#include <sys/stat.h>   // For file permissions (used with open or shm)
#include <sys/ipc.h>    // For Inter-Process Communication keys
#include <sys/shm.h>    // For Shared Memory (shmget, shmat)
#include <sys/sem.h>    // For Semaphores (controlling access to shared data)
#include <errno.h>      // For checking specific error codes (very useful for debugging)
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

/*Advanced: Redirection and Logic (dup2 & exec)

The Hijack: Use dup2 to redirect printf (STDOUT) into a file named output.txt.

Pipe Redirection: Create a pipe, use dup2 to connect the write-end to STDOUT. Then call printf("Hello Pipe"). Have the child read it.

The Command Runner: Parent forks. Child uses execlp to run the ls command.

The Filter: Create a pipe. Parent runs ls (via execlp) and redirects output to the pipe. Child reads the output of ls from the pipe and counts how many files were listed.

The Two-Way Street: Create two pipes. Parent sends a number to Child on Pipe A. Child multiplies it by 10 and sends it back to Parent on Pipe B.

The Boss Level: Recreate the command ls | wc -l in C.

Parent forks.

Child 1 redirects STDOUT to a pipe and runs ls.

Child 2 (or Parent) redirects STDIN from that same pipe and runs wc -l.*/

/*int main()
{
    int a = open("/Users/len/Desktop/os/output.txt", O_WRONLY | O_CREAT);
    dup2(a, 1);
    printf("This is a test");
    
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);

    pid_t pid = fork();

    if(pid==0)
    {
    close(pipe12[1]);
        char ch[100];
        read(pipe12[0], &ch, sizeof(ch));
        printf("%s", ch);
    }
    else
    {
        close(pipe12[0]);
        dup2(pipe12[1], 1);
        printf("Hello Pipe");
    }
}*/

/*int main()
{
    int pipe12[2];
    pipe(pipe12);

    pid_t pid = fork();

    if(pid==0)
    {
        execlp("ls", "ls", NULL, NULL);
    }
    else
    {
        close(pipe12[0]);
    }
}*/

int main()
{
    int pipe12[2];
    pipe(pipe12);

    pid_t pid = fork();

    if(pid==0)
    {
         close(pipe12[1]);
         int count= 0, countc=0;
         char a[10000];
         read(pipe12[0], &a, sizeof(a));
         
for(unsigned long i = 0; i < strlen(a); i++) {
    if(a[i] == '\n') {
        count++;
    }
}
         printf("This is child, number of files is %d", count);
    }
    else
    {
        close(pipe12[0]);
        dup2(pipe12[1], 1);
        execlp("ls", "ls", NULL, NULL);
    }
}
