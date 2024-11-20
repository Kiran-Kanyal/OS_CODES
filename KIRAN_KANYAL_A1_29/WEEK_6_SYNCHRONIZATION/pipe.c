#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int pipefds[2];
    pid_t pid;
    char writeMsg[] = "Message from Child";
    char readMsg[100];
    // Create a pipe
    if (pipe(pipefds) == -1)
    {
        perror("Pipe failed");
        return 1;
    }
    // Fork to create a child process
    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0)
    {
        // Child process
        close(pipefds[0]); // Close reading end
        write(pipefds[1], writeMsg, strlen(writeMsg) + 1);
        close(pipefds[1]); // Close writing end
    }
    else
    {
        // Parent process
        close(pipefds[1]); // Close writing end
        read(pipefds[0], readMsg, sizeof(readMsg));
        printf("Parent read: %s\n", readMsg);
        close(pipefds[0]); // Close reading end
    }
    return 0;
}