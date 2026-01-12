#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char **argv)
{

    int pipe_fd[2];
    pipe(pipe_fd);
    int n = open(argv[1], O_RDONLY);
    pid_t pid=fork();

    if(pid<0)
        {
        perror("Issue with fork");
        exit(EXIT_FAILURE);
        }
    if(pid==0)
    {
        close(pipe_fd[1]);
        char buffer[100]; int count = 0;
        n = read(pipe_fd[0],buffer,sizeof(buffer)>0);
        for (int i = 0; i < n; i++)
        {
        if (isalpha(buffer[i])){ count++;}}
            printf("Total alpha-numerical characters read: %d",n);
        close(pipe_fd[0]);
    }
    else
    {
        close(pipe_fd[0]);
        char buffer[100];
        if ((dup2(pipe_fd[1], STDOUT_FILENO)) < 0)
        {
            fprintf(stderr, "Error duplicating the writing file descriptor\n");
            exit(4);
        }
         close(pipe_fd[1]);
        wait(NULL);
        execlp("cat", "cat", argv[1], NULL);
       
    }
}