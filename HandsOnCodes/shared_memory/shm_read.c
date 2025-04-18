#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    void *shared_memory;
    int shmid = 0;

    // Access the shared memory with the same key 2345
    shmid = shmget((key_t)2345, 1024, 0666);
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }
    printf("Key of shared memory is: %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0); // Process attached to shared memory segment
    if (shared_memory == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }
    printf("Process attached at: %p\n", shared_memory);

    printf("Data read from shared memory: %s\n", (char *)shared_memory);

    // Detach from shared memory
    if (shmdt(shared_memory) == -1)
    {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}