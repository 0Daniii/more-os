#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#define BUF_SIZE 128


/*2. Implement a C application able to mimic the pipe mechanism from BASH, 
where the entire process chain is sent as command-line arguments. 
The chain can be made of an unknown number of processes linked by pipes.
 You can use "|" to mark the pipe when specifying the arguments.
For example, running ./a.out cat file "|" head -n 4 "|" wc -c
Will have the same behaviour as running the commands cat file 
| head -n 4 | wc -c directly in BASH*/

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s cmd1 arg1 ... | cmd2 arg2 ... | ...\n", argv[0]);
        return 1;
    }

    #define MAX_CMDS 10
    #define MAX_ARGS 10
    char *cmds[MAX_CMDS][MAX_ARGS];
    int cmd_count = 0;
    int arg_count = 0;

    // Parse arguments into commands
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            cmds[cmd_count][arg_count] = NULL;
            cmd_count++;
            arg_count = 0;
            if (cmd_count >= MAX_CMDS) {
                fprintf(stderr, "Too many commands\n");
                return 1;
            }
        } else {
            cmds[cmd_count][arg_count] = argv[i];
            arg_count++;
            if (arg_count >= MAX_ARGS) {
                fprintf(stderr, "Too many args in command\n");
                return 1;
            }
        }
    }
    cmds[cmd_count][arg_count] = NULL;
    int num_cmds = cmd_count + 1;

    // Create pipes
    int pipes[num_cmds - 1][2];
    for (int i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            return 1;
        }
    }

    // Fork and execute
    for (int i = 0; i < num_cmds; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }
        if (pid == 0) {
            // Child: redirect stdin/stdout
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < num_cmds - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            // Close all pipes
            for (int j = 0; j < num_cmds - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            // Execute
            execvp(cmds[i][0], cmds[i]);
            perror("execvp");
            exit(1);
        }
    }

    // Parent: close pipes and wait
    for (int i = 0; i < num_cmds - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    for (int i = 0; i < num_cmds; i++) {
        wait(NULL);
    }

    return 0;
}