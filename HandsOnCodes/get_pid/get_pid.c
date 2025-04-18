#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int *array = (int *)malloc(sizeof(int) * 10);

    pid_t pid = getpid();
    printf("The PID is: %d", pid);

    fflush(stdout);

    while (1)
    {
        sleep(1);
    }

    free(array);
}