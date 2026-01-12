#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#define BUF_SIZE 128

void caesar(char *buf, int shift)
{
    for(int i = 0; buf[i] != '\0'; i++)
    {
        unsigned char c = buf[i];
        buf[i] = (c + shift + 128)%256; //116 -> -12
    }
}

void print(char *buf)
{
    for(int i = 0; buf[i] != '\0'; i++)
    {
        if(isprint(buf[i]))
            printf("%c",buf[i]);
        else
            printf("\\x%02x",buf[i]);
    }
}
int main(int argc, char **argv)
{
    int pipe12[2];
    int pipe21[2];
    int i;
    char original[BUF_SIZE] = "";
    char encrypted[BUF_SIZE] = "";
    char decrypted[BUF_SIZE] = "";

    if (pipe(pipe12) < 0)
    {
        fprintf(stderr, "Error opening pipe1\n");
        exit(1);
    }

    if (pipe(pipe21) < 0)
    {
        fprintf(stderr, "Error opening pipe1\n");
        exit(2);
    }

    int pid1 = fork();

    if (pid1 < 0)
    {
        fprintf(stderr, "Error creating the first subprocess\n");
        exit(3);
    }

    if (pid1 == 0)
    {
        close(pipe12[0]);
        close(pipe21[1]);

        for(i = 1; i < argc; i++)
        {
            strcat(original, argv[i]);
            if(i < argc - 1)
                strcat(original, " ");
        }

        strcpy(encrypted, original);

        caesar(encrypted, 13);
        write(pipe12[1], encrypted, strlen(encrypted) + 1);

        read(pipe21[0], decrypted, BUF_SIZE);

        /*printf("check: \n");
        print(original);
        printf("\n");
        print(decrypted);*/
        if (strcmp(original, decrypted) == 0)
            printf("Communication successful\n");
        else
            printf("Communication failed\n");

        close(pipe12[1]);
        close(pipe21[0]);

        exit(0);
    }

    int pid2 = fork();

    if (pid2 < 0)
    {
        fprintf(stderr, "Error creating the second subprocess\n");
        exit(4);
    }

    if (pid2 == 0)
    {
        close(pipe12[1]);
        close(pipe21[0]);

        read(pipe12[0], encrypted, BUF_SIZE);
        //printf("%s\n", encrypted);
        print(encrypted);
        printf("\n");
        strcpy(decrypted, encrypted);
        caesar(decrypted, -13);

        write(pipe21[1], decrypted, strlen(decrypted) + 1);

        close(pipe12[0]);
        close(pipe21[1]);

        exit(0);
    }

    close(pipe12[0]);
    close(pipe12[1]);
    close(pipe21[0]);
    close(pipe21[1]);

    wait(NULL);
    wait(NULL);
}
