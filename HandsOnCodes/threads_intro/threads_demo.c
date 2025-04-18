#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int g = 0; // global var to be changed my threads

void *myThreadFunction(void *vargp); // function to be submitted by all threads

int main()
{
    pthread_t tid;

    for (int i = 0; i < 3; i++) // create 3 threads
    {
        pthread_create(&tid, NULL, myThreadFunction, (void *)&tid);
        pthread_join(tid, NULL);
    }
    return 0;
}

void *myThreadFunction(void *vargp)
{
    int *myid = (int *)vargp; // store value argument to be passed to threads
    static int s = 0;         // static var to observe changes
    int l = 0;                // local var to observe changes
    ++l, ++s, ++g;
    printf("Thread ID: %d, Local: %d, Static: %d, Global: %d\n", *myid, l, s, g);
    pthread_exit(NULL);
}