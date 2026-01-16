#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
/*Requirement: Create a C program that takes a filename as a command-line argument 
(e.g., ./a.out input.txt). The program must spawn two child 
processes that communicate via two pipes.

Child 1 (The Reader):

Opens the file specified in the command line argument.

Reads the file character by character.

Checks if the character is a Vowel (a, e, i, o, u — case insensitive).

If it is a vowel, it sends it through Pipe 1 to Child 2.

If it is not a vowel, it ignores it.

After the file is done, it waits to receive a "Total Count" from Child 2 via Pipe 2, 
prints it to the screen, and exits.

Child 2 (The Writer):

Reads the vowels from Pipe 1.

Converts every vowel to UPPERCASE.

Writes these uppercase vowels into a new file called vowels.txt.

Counts how many vowels it received.

Sends the total count (as an integer or string) back to Child 1 via Pipe 2.

Example Execution

Create a file input.txt:

Plaintext
Hello World! This is a test.
Run the program:

Bash
./a.out input.txt
Expected Console Output:

Plaintext
Extraction complete.
Total vowels processed: 8*/

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
        char wowels[6] = "aeiou";
        char ch; 
        FILE *f = fopen(argv[1], "r");
        while((ch = fgetc(f))!= EOF)
        {
            for(int i = 0; i<strlen(wowels);i++)
            {
                if(ch == wowels[i])
                {
                    write(pipe12[1], &ch, sizeof(ch));
                }
            }
        }
        close(pipe12[1]);
        int count;
        read(pipe21[0],&count, sizeof(count));

                printf("%d", count);

                exit(0);


    }

    pid_t pid2 = fork();

    if( pid2 == 0 )
    {
        close(pipe12[1]);
        close(pipe21[0]);
        char ch;
        int a = ('a' - 'A');
        FILE *f = fopen("write.txt", "w");
        int count = 0;
        while((read(pipe12[0], &ch, sizeof(ch))) != 0)
        {
            ch = ch - a;
            fputc(ch, f);
            count++;
           
        }

         write(pipe21[1], &count, sizeof(count));


    }
    close(pipe12[0]);
    close(pipe12[1]);
    close(pipe21[0]);
    close(pipe21[1]);

    // Optional: Wait for children to finish (good practice)
    wait(NULL); 
    wait(NULL);

    return 0;

}