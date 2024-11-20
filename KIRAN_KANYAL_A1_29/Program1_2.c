// 2. Write a program to print process Id's of parent and child process i.e. parent should
// print its own and its child process id while child process should print its own and its
// parent process id. (use getpid(), getppid())
#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Fork failed.\n");
        return -1;
    }
    else if (pid == 0)
    {
        printf("Child Process is running.\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent Process is running.\n");
        printf("PID: %d, Child PID: %d\n", getpid(), pid);
    }
    return 0;
}