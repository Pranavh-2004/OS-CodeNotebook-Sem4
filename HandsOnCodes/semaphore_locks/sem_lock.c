#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

sem_t semaphore;

void *worker1(void *argp);
void *worker2(void *argp);

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker1, NULL);
    pthread_create(&t2, NULL, worker2, NULL);
    sem_init(&semaphore, 0, 1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

void *worker1(void *argp)
{
    char s[] = "abcde";

    sem_wait(&semaphore);
    for (int i = 0; i < 5; i++)
    {
        putchar(s[i]);
        fflush(stdout);
        sleep(2);
    }
    sem_post(&semaphore);
}

void *worker2(void *argp)
{
    char s[] = "ABCDE";

    sem_wait(&semaphore);
    for (int i = 0; i < 5; i++)
    {
        putchar(s[i]);
        fflush(stdout);
        sleep(2);
    }
    sem_post(&semaphore);
}