#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

// Function prototypes
void *my_thread_1(void *arg);
void *my_thread_2(void *arg);

int main()
{
    pthread_t t1, t2;

    // Create the first thread
    pthread_create(&t1, NULL, my_thread_1, NULL);

    // Delay to simulate staggered thread creation
    sleep(2);

    // Create the second thread
    pthread_create(&t2, NULL, my_thread_2, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n");
    return 0;
}

void *my_thread_1(void *arg)
{
    char s[] = "abcdefgh";
    int l = strlen(s);

    for (int i = 0; i < l; ++i)
    {
        // Critical section
        putchar(s[i]);
        fflush(stdout);
        sleep(2);
    }

    return NULL; // Return from thread
}

void *my_thread_2(void *arg)
{
    char s[] = "ABCDEFGH";
    int l = strlen(s);

    for (int i = 0; i < l; ++i)
    {
        // Critical section
        putchar(s[i]);
        fflush(stdout);
        sleep(2);
    }

    return NULL; // Return from thread
}