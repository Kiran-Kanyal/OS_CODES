// Problem Statement 1:
// Demonstration of FORK() System Call

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed.\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Hello from the child process! PID %d\n", getpid());
    }
    else
    {
        printf("Hello from the parent process! PID %d, Child PID: %d\n", getpid(), pid);
    }
    return 0;
}

// LEARNINGS:
//   pid
//  Type: It is a variable (of type pid_t) that holds the process ID of a child process returned by the fork() system call.
//  Usage: After a successful call to fork(), the pid variable can have one of the following values:
//  0: This indicates that the code is running in the child process.
//  Positive integer: This is the process ID of the child process and indicates that the code is running in the parent process.
//  Negative value: This indicates an error in creating the child process (the fork() call failed).

// 2. getpid()
// Type: It is a function that returns the process ID of the calling process.
// Usage: Regardless of whether the calling code is executed in the parent or child process, getpid() will return the PID of that specific process. This is useful for logging or debugging, as it allows you to know which process is executing a particular piece of code.