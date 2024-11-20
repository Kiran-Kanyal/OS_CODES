// 3. Write a program to create child process which will list all the files present in your system. Make sure that parent process waits until child has not completed its execution. (use wait(), exit())
// What will happen if parent process dies before child process? Illustrate it by creating one more child of parent process.
// we are using exit(0);
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0)
    {
        printf("Fork failed.\n");
        return 1;
    }
    else if (pid1 == 0)
    {
        printf("Child Process 1 (PID: %d): Listing files...\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        exit(0);

    }
    else
    {
        wait(NULL);
        printf("Parent Process (PID: %d): First Child Completed.\n", getpid());

        pid2 = fork();
        if (pid2 < 0)
        {
            printf("Fork failed.\n");
            return 1;
        }
        else if (pid2 == 0)
        {
            printf("Child Process 2 (PID: %d): I am the second child.\n", getpid());
            sleep(5);
            printf("Child Process 2 (PID: %d): Work done.\n", getpid());
            exit(0);
        }
        else
        {
            printf("Parent Process (PID: %d): Exiting now.\n", getpid());
            exit(0);
        }
    }
    return 0;
}

// Outcome of Parent Exiting Early
// If you let the parent exit before the second child finishes, the second child will become an orphan process. The system's init process (PID 1) will adopt it, and it will continue executing independently.

// execlp("ls", "ls", "-l", (char *)NULL); is called in the first child process to run the ls -l command, which lists files in the current directory in long format.
// The parameters:
// "ls": Th
e name of the program to execute.
    // "ls": The first argument to pass to the program (typically the name of the program itself).
    // "-l": The second argument, specifying the long format for the listing.
    // (char *)NULL: A null terminator to indicate the end of the arguments list.
    // Once execlp() i
    s called,
    the current child process is replaced by the ls command, and the process no longer returns to the original program code.That 's why it' s essential to call exit() after execlp(), as it would not return unless execlp() fails.

                                                                                                                                                                                       // Summary:
                                                                                                                                                                                       // exit(0) ensures the child and parent processes exit cleanly after their task is done.
                                                                                                                                                                                       // execlp() replaces the current child process with a new process (in this case, executing the ls -l command).