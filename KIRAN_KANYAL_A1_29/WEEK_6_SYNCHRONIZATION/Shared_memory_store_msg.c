// storing message in shared memory
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
int main() // MAIN FUNCTION
{
    key_t key;
    int shmid;
    void *ptr;
    key = ftok("shmfile", 'A');
    shmid = shmget(key, 1024, 0666 | IPC_C REAT);
    ptr = shmat(shmid, (void *)0, 0);
    printf("\nInput Data : ");
    gets(ptr);
    shmdt(ptr);
    return 0;
}
