#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

/*Create a C application that spawns two child processes communicating via pipes.
The first subprocess reads all command-line arguments, concatenates them into a single
 string separated by spaces, and sends the result to the second subprocess through a pipe.
The second subprocess reverses each word individually (without changing word order), prints 
the result to standard output, and sends the reversed string back to the first subprocess.
The first subprocess compares the received string with its own locally reversed version and 
prints "OK" if they match, otherwise "ERROR"
If no argument is used at execution, the program will print to STDOUT:
 "Error: no argument found" and exit with an exit code 0.
e.g: executing the program with the following arguments:
./a.out abcd AbCd abtd3 q-t3
will generate the following output:
dcba dCA 3dtba 3t-q
OK*/

int main(int argc, char **argv)
{
    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);
    pid_t pid1 = fork();
    if(pid1 == 0 )
    {
        close(pipe12[0]);
        close(pipe21[1]);
        char c[1000];
        for(int i=1; i<argc;i++)
        {
            strcat(c, argv[i]);
            if(i< argc-1)
            {
                strcat(c, " ");
            }
        }
       // printf("%s\n", c);
        write(pipe12[1], &c, sizeof(c));
        char crevloc[1000]= "";
         for(int i=0; c[i]!= '\0';i=i+2)
            {   char aug[100] = "";
                int count = 0;
                while(c[i] != ' ' && c[i]!= '\0')
                {
                    i++;
                    count++;
                }
                i--;
                count--;
                for(int j = 0; j<=count; j++)
                {
                    aug[j]= c[i-j];

                }
                strcat(crevloc, aug);
                if(c[i+1]!= '\0')
                {
                    strcat(crevloc, " ");
                }
            }
        char crev[1000] = "";
        read(pipe21[0], &crev, sizeof(crev));
    
        for(int i = 0; crevloc[i]!= '\0';i++)
        {
            if( !(crevloc[i]== crev[i]))
            {
                printf("\nCom unsucs");
                exit(0);
            }
        }

        printf("\nCom sucs");

        exit(0);
    }

    pid_t pid2 = fork();

    if(pid2 == 0)
    {
        close(pipe12[1]);
        close(pipe21[0]);
        char c[1000] = "";
        char crev[1000]= "";
        read(pipe12[0], &c, sizeof(c));
        printf("%s this is c from parent, got from pipe\n", c);
            /*for(int i=0; c[i]!= '\0';i=i+2)
            {   char aug[100] = "";
                int count = 0;
                while(c[i] != ' ' && c[i]!= '\0')
                {
                    i++;
                    count++;
                }
                i--;
                count--;
                for(int j = 0; j<=count; j++)
                {
                    aug[j]= c[i-j];

                }
                strcat(crev, aug);
                if(c[i+1]!= '\0')
                {
                    strcat(crev, " ");
                }
            }*/
           int k = 0, ws=0;
           for(int i = 0; i<= strlen(c); i++)
           {
            if(c[i]== ' ' || c[i]== '\0')
            {
                for(int j = i-1; j>=ws; j--)
                {
                    crev[k]=c[j];
                    k++;
                }

                if(c[i]== ' ')
                {
                    crev[k]= ' ';
                    k++;
                }
                ws= i+1;
            }
           }
            printf("%s\n", crev);
            write(pipe21[1], &crev, sizeof(crev));

            exit(0);
    }
}