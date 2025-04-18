#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p1 = fork();

    if (p1 > 0)
    { // Parent process
        printf("This is Parent. The PID is: %d", getpid());
        exit(0);
    }
    else if (p1 == 0)
    { // Child process
        sleep(30);
        printf("This is Child. The PID is: %d, The PID is: %d", getpid(), getppid());
    }
    else
    { // Fork failed
        printf("Fork creation failed!");
    }
}