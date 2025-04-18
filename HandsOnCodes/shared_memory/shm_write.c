#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    void *shared_memory;
    char buff[100] = "";
    int shmid = 0;

    // create shm with key 2345, having size 1024 bytes
    //  IPC_CREAT is used to create shared segment if it does not exist. 0666 are permissions on shared segment
    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
    printf("Key of shared memory is: %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0); // Process attached to share memory segment
    printf("Process attached at: %p\n", shared_memory);

    printf("Enter some data to be written to shared memory segment\n");
    read(0, buff, 100);

    strcpy(shared_memory, buff);

    sleep(10);
}