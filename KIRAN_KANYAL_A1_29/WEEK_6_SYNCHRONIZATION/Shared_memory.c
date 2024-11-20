#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Generate a unique key
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Create a shared memory segment
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Fork to create a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        // Attach to shared memory
        char *shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1) {
            perror("shmat failed");
            exit(1);
        }

        // Write a message to the shared memory
        char writeMsg[] = "Message from Child";
        strcpy(shared_memory, writeMsg);

        // Detach from shared memory
        shmdt(shared_memory);
    } else {
        // Parent process
        // Wait for child process to write
        sleep(1);

        // Attach to shared memory
        char *shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1) {
            perror("shmat failed");
            exit(1);
        }

        // Read the message from shared memory
        printf("Parent read: %s\n", shared_memory);

        // Detach from shared memory
        shmdt(shared_memory);

        // Destroy the shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
