#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t lock;
pthread_t tid[2];
int counter = 0;

void *thread_function(void *arg);

int main(void)
{
    int i = 0;
    int error;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\nMutex init failed\n");
        return 1;
    }

    // Create threads
    while (i < 2) // Fixed condition to create two threads
    {
        error = pthread_create(&(tid[i]), NULL, &thread_function, NULL);
        if (error != 0)
        {
            printf("\nThread can't be created: [%s]\n", strerror(error));
        }
        i++;
    }

    // Wait for threads to finish
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

void *thread_function(void *arg)
{
    pthread_mutex_lock(&lock); // Fixed typo from 'phtread_mutex_lock'
    unsigned long i = 0;

    counter += 1;
    printf("\nJob %d has started\n", counter);
    sleep(2); // Simulating some work
    printf("\nJob %d has finished\n", counter);

    pthread_mutex_unlock(&lock); // Fixed typo from 'phtread_mutex_unlock'
    return NULL;
}