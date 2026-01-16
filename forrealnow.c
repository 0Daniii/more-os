#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

/*1. Create a C application that spawns two child processes able to 
communicate with each other by using pipes. The first subprocess
 will take the command-line execution arguments and will apply 
 Caesar's cypher on each runtime argument character, sending the 
 encrypted message through a pipe to the second subprocess. 
 The second subprocess will read from the pipe and decrypt the message,
  sending the result back to the first subprocess through another pipe,
   while also printing the received message on the screen. 
   If both the original message and the one received from 
   the second subprocess are the same, the first subprocess will print 
   "Communication successful", otherwise "Communication failed".
    The Caesar cypher/ROT13 is computed by shifting each character
     by 13 positions within the 7-bit ASCII code (the character a becomes 
     the character n). 
Executing the program with the following arguments:  
./a.out abcd AbCd abtd3 q-t3

 will generate the following output:
 nopq-NoPq-no\x01q@-~:\x01@
 Communication successful*/

 int main(int argc, char **argv)
 {
    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);
    char a[1000] = "";
    char c[1000] = "";
    char d[1000] = "";
    pid_t pid1 = fork();

    if (pid1 == 0)
    {
        close(pipe12[0]);
        close(pipe21[1]);
        for( int i=1; i<argc; i++)
        {
            strcat(a, argv[i]);
            if(i < argc-1)
            {
                strcat(a, " ");
            }
        }
       // printf("%s", a);
        for(int i = 0; i < strlen(a); i++){

            c[i] = (a[i] + 13 + 128)%128;
        }
          // printf("\n%s", c);
          // printf("\n%s", c);
          write(pipe12[1], &c, sizeof(c));
        char check[1000];
            read(pipe21[0], &check, sizeof(check));
        printf("\n%s\n%s", a, check);
            for(int i = 0; i< strlen(a); i++)
            
            {
                if(!(check[i] == a[i])){
                printf("Communication unsucessfull\n");
                return 1;}
            
            }

            printf("\nCommunication sucessfull\n");
           
           exit (0);

    }
    pid_t pid2 = fork();

    if(pid2 == 0 )
    {
        close(pipe12[1]);
        close(pipe21[0]);
        char x[1000] = "";
        read(pipe12[0], &x, sizeof(d));
        
        for(int i = 0; i < strlen(a); i++){

            x[i] = (x[i] - 12 + 128)%128;
        }
        printf("\n%s", d);
        write(pipe21[1], &d, sizeof(d));


        exit (0);

    }
    wait(NULL);
    wait(NULL);
    return 0; 
 }