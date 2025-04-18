#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

// Global semaphore declaration
sem_t mutex;

// Function prototypes
void *my_thread_1(void *arg);
void *my_thread_2(void *arg);

int main()
{
    pthread_t t1, t2;

    // Initialize the semaphore with a value of 1
    sem_init(&mutex, 0, 1);

    // Create the first thread
    pthread_create(&t1, NULL, my_thread_1, NULL);

    // Delay to simulate staggered thread creation
    sleep(2);

    // Create the second thread
    pthread_create(&t2, NULL, my_thread_2, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the semaphore
    sem_destroy(&mutex);

    printf("\n");
    return 0;
}

void *my_thread_1(void *arg)
{
    char s[] = "abcdefgh";
    int l = strlen(s);

    for (int i = 0; i < l; ++i)
    {
        // Wait (lock the semaphore)
        sem_wait(&mutex);

        // Critical section
        putchar(s[i]);
        fflush(stdout);
        sleep(2);

        // Signal (unlock the semaphore)
        sem_post(&mutex);
    }

    return NULL; // Return from thread
}

void *my_thread_2(void *arg)
{
    char s[] = "ABCDEFGH";
    int l = strlen(s);

    for (int i = 0; i < l; ++i)
    {
        // Wait (lock the semaphore)
        sem_wait(&mutex);

        // Critical section
        putchar(s[i]);
        fflush(stdout);
        sleep(2);

        // Signal (unlock the semaphore)
        sem_post(&mutex);
    }

    return NULL; // Return from thread
}

/*
To guarantee order of execution

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

// Global semaphore and shared variable
sem_t sem1, sem2;

// Function prototypes
void *my_thread_1(void *arg);
void *my_thread_2(void *arg);

int main()
{
    pthread_t t1, t2;

    // Initialize semaphores
    sem_init(&sem1, 0, 1); // Start with thread 1 allowed
    sem_init(&sem2, 0, 0); // Block thread 2 initially

    // Create the threads
    pthread_create(&t1, NULL, my_thread_1, NULL);
    pthread_create(&t2, NULL, my_thread_2, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the semaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    printf("\n");
    return 0;
}

void *my_thread_1(void *arg)
{
    char s[] = "abcdefgh";
    int l = strlen(s);

    for (int i = 0; i < l; i++)
    {
        // Wait for permission to execute
        sem_wait(&sem1);

        // Critical section
        putchar(s[i]);
        fflush(stdout);
        sleep(1);

        // Signal the next thread
        sem_post(&sem2);
    }

    return NULL;
}

void *my_thread_2(void *arg)
{
    char s[] = "ABCDEFGH";
    int l = strlen(s);

    for (int i = 0; i < l; i++)
    {
        // Wait for permission to execute
        sem_wait(&sem2);

        // Critical section
        putchar(s[i]);
        fflush(stdout);
        sleep(1);

        // Signal the next thread
        sem_post(&sem1);
    }

    return NULL;
}

*/