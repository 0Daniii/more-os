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


//1. Create a C application that spawns two child processes able to communicate with
//each other by using pipes. The first subprocess will take the command-line execution
//arguments and will apply Caesar's cypher on each runtime argument character, sending
//the encrypted message through a pipe to the second subprocess. The second subprocess
//will read from the pipe and decrypt the message, sending the result back to the first 
// subprocess through another pipe, while also printing the received message on the screen. 
//  If both the original message and the one received from the second subprocess are the same, 
//  the first subprocess will print "Communication successful", otherwise "Communication failed".
//   The Caesar cypher/ROT13 is computed by shifting each character by 13 positions within the 7-bit 
//    ASCII code (the character a becomes the character n). 
//Executing the program with the following arguments:  
//./a.out abcd AbCd abtd3 q-t3

 //will generate the following output:
//nopq-NoPq-no\x01q@-~:\x01@
 //Communication successful

void caesar(char *buf, int shift)
{
    for(int i = 0; buf[i] != '\0'; i++)
    {
        unsigned char c = buf[i];
        buf[i] = (c + shift + 128) % 128;
    }
}

void print(char *buf)
{
    for(int i = 0; buf[i] != '\0'; i++)
    {
        if(isprint(buf[i]))
            printf("%c",buf[i]);
        else
            printf("\\x%02x",(unsigned char)buf[i]);
    }
}

int main (int argc, char **argv)
{

    int pipe12[2];
    int pipe21[2];
    char original[BUF_SIZE] = "";
    char encrypted[BUF_SIZE] = "";
    char decrypted[BUF_SIZE] = "";

    if (pipe(pipe12) < 0)
    {
        fprintf(stderr, "Error opening pipe12\n");
        exit(1);
    }

    if (pipe(pipe21) < 0)
    {
        fprintf(stderr, "Error opening pipe21\n");
        exit(2);
    }

    int pid1=fork();

    if (pid1<0)
    {
        printf("error 1");
        return 1;
    }
    if (pid1 == 0)
    {
        close(pipe12[0]);
        close(pipe21[1]);
        for ( int i = 1; i< argc; i++)
        {
            strcat(original, argv[i]);
            if(i<argc-1)
            {
                strcat(original, " ");
            }
        }
        strcpy(encrypted, original );
        caesar(encrypted, 13);

        write(pipe12[1], encrypted, strlen(encrypted)+1);

        read(pipe21[0], decrypted, BUF_SIZE);

        if(strcmp(original, decrypted) == 0) 
        {
            printf("Communication successful");
        }
        else
        {
            printf("Communication unsuccessful");
        }
        close(pipe12[1]);
        close(pipe21[0]);
        exit(0);
    }
    
    int pid2=fork();

    if (pid2<0)
    {
        printf("error 2");
        return 2;
    }
    if (pid2 == 0)
    {
        close(pipe12[1]);
        close(pipe21[0]);

        read(pipe12[0], encrypted, BUF_SIZE);
        encrypted[strlen(encrypted)] = '\0';  // Ensure null termination
           print(encrypted);
        printf("\n");
        strcpy(decrypted, encrypted);

        caesar(decrypted, -13);

        write(pipe21[1], decrypted, strlen(decrypted)+1);
        close(pipe12[0]);
        close(pipe21[1]);
        exit(0);

        exit(0);
    }

    close(pipe12[0]);
    close(pipe12[1]);
    close(pipe21[0]);
    close(pipe21[1]);

    wait(NULL);
    wait(NULL);


}