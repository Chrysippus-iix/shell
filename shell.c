#include <stdio.h>      // printf, fgets, perror
#include <stdlib.h>     // exit
#include <string.h>     // strtok, strcmp, strcspn
#include <unistd.h>     // fork, execvp
#include <sys/wait.h>   // waitpid

int main(void) {

    // this is our input box, holds whatever the user types, up to 256 characters
    char buffer[256];

    // the shell never stops on its own, it keeps looping until the user types "exit"
    while(1) {

        // print the prompt so the user knows the shell is listening
        printf("greyfox> ");

        // force the prompt to appear on screen before waiting for input
        // without this the terminal might buffer it and show nothing
        // man 3 printf, man 3 fflush
        fflush(stdout);

        // read a line of input from the keyboard into buffer
        // if the user hits Ctrl+D the fgets returns NULL and we exit cleanly
        // man 3 fgets
        if (fgets(buffer, 256, stdin) == NULL)
            break;

        // fgets keeps the newline at the end of what you typed
        // this replaces that newline with a null terminator so it doesnt cause issues later
        // man 3 strcspn
        buffer[strcspn(buffer, "\n")] = 0;

        // if the user typed "exit" break out of the loop and close the shell
        // man 3 strcmp
        if (strcmp(buffer, "exit") == 0)
            break;

        // args is a list of words from whatever the user typed
        // "ls -la /home" becomes args[0]="ls" args[1]="-la" args[2]="/home"
        char *args[64];

        // i is just a position tracker, think of it like a mailbox number
        // args is a row of 64 mailboxes, i tells you which mailbox you are currently at
        // starts at 0 because arrays in C start at index 0
        // when you write args[i] you are saying put this in mailbox number i
        // after storing something you do i++ to move to the next mailbox
        // i doesnt know anything about args, you are the one connecting them by writing args[i]
        int i = 0;

        // strtok cuts our input string at every space and hands back one word at a time
        // first call gets the very first word
        // man 3 strtok
        char *token = strtok(buffer, " ");

        // keep grabbing words until strtok runs out and returns NULL
        // NULL here means there are no more words left to find
        while(token != NULL) {

            // store the current word into args at mailbox i
            // then move i forward to the next mailbox
            args[i++] = token;

            // passing NULL tells strtok to continue where it left off in the same string
            // first call takes the buffer, every call after takes NULL, thats just how strtok works
            // the dual meaning of NULL here confused me too, NULL as input means "continue",
            // NULL as return value means "done", same word two completely different jobs
            // man 3 strtok
            token = strtok(NULL, " ");
        }

        // execvp needs to know where the argument list ends
        // NULL in the last mailbox slot is the signal that says nothing comes after this
        args[i] = NULL;

        // fork is the shell making a copy of itself, a ghost of the current process
        // for a moment there are two identical processes running the same code
        // the parent gets the childs PID back, the child gets 0
        // thats how each one knows which role it plays
        // man 2 fork
        pid_t pid = fork();

        if (pid == 0) {

            // we are the child, the ghost copy of the shell
            // execvp completely replaces this ghost with the actual command like ls or grep
            // the ghost stops being the shell and becomes ls, it possesses the binary
            // args[0] is the command name, args is the full list of arguments
            // man 3 execvp
            execvp(args[0], args);

            // if execvp returns at all something went wrong, the command wasnt found
            // man 3 perror
            perror("execvp");
            exit(1);

        } else if (pid > 0) {

            // we are the parent, the original shell
            // the parent waits here doing nothing until the child finishes
            // this is why your terminal appears to freeze while a command runs
            // man 2 waitpid
            waitpid(pid, NULL, 0);

        } else {

            // fork returning -1 means something went wrong and no child was created
            perror("fork");
        }
    }

    return 0;
}
