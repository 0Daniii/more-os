#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>


/*Goal: Create a program that filters digits from a text file, 
sums them up, and logs the operation.

The Setup:

Input File: passed as argv[1] (contains text mixed with numbers, e.g., "h3ll0 w0rld").

Two Pipes: p1 (Child 1 → Child 2) and p2 (Child 2 → Child 1).

The Process:

Child 1 (Reader):

Reads argv[1] character by character.

If the character is a digit ('0'-'9'), send it to Child 2 via pipe p1.

After the file is done, wait for a response from Child 2.

Read the final sum (integer) from pipe p2 and print it to the screen.

Child 2 (Calculator):

Reads characters from pipe p1.

Converts the character to an integer (Hint: int val = ch - '0';).

Adds it to a running total.

Writes the addition steps to a file named calculation.txt (e.g., "3+0+0+...").

Sends the final sum back to Child 1 via pipe p2.

Parent:

Closes all pipe ends and waits for children.*/


int main( int argc,char ** argv)
{

    int pipe12[2];
    int pipe21[2];
    pipe(pipe12);
    pipe(pipe21);

    pid_t pid1 = fork();
    char num[11] = "0123456789";

    if( pid1==0)
    {   
        close(pipe12[0]);
        close(pipe21[1]);
        FILE *f = fopen(argv[1], "r");
        char ch;
        while((ch = fgetc(f)) != EOF)
        {
            for( int i = 0; i<11;i++)
            {
                if(ch == num[i])
                {
                    write(pipe12[1], &ch, sizeof(ch));
                }
            }
        }
        close(pipe12[1]);
        int sum;
        read(pipe21[0],&sum, sizeof(sum));
        printf("%d", sum);

        exit(0);

    }

    pid_t pid2 = fork(); 

    if(pid2 == 0)
    {
        close(pipe12[1]);
        close(pipe21[0]);
        int sum = 0;
        char ch;
        FILE *f = fopen("write.txt", "w");
        while((read(pipe12[0], &ch, sizeof(ch))) != 0)
        {
            sum = sum+(ch - '0');
            fprintf(f, "%c+", ch);
        }
        write(pipe21[1], &sum, sizeof(sum));
        close(pipe21[1]);

        exit(0);
    }

        close(pipe12[1]);
        close(pipe21[1]);
        close(pipe21[0]);
        close(pipe12[0]);

        wait(NULL);
        wait(NULL);

        return 0;
}