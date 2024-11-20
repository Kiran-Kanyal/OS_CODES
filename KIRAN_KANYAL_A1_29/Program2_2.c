// Write a program to show working of execlp() system call by executing ls command.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For fork() and execlp()
int main()
{
    pid_t pid;
    // Create a new process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed"); // Error handling for fork()
        exit(1);
    }
    else if (pid == 0)
    {

        // This is the child process
        printf("In child process (PID: %d), executing 'ls' command...\n", getpid());

        // Execute the 'ls' command
        if (execlp("ls", "ls", NULL) == -1)
        {
            perror("execlp failed"); // Error handling for execlp()
            exit(1);
        }
    }
    else
    {
        // This is the parent process
        printf("In parent process (PID: %d), waiting for child to finish...\n", getpid());
        wait(NULL); // Wait for the child process to finish
        printf("Child process finished, parent process continuing.\n");
    }
    return 0;
}
