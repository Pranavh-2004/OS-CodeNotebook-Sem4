#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p1 = fork();

    if (p1 > 0)
    { // Parent process
        sleep(50);
        printf("This is Parent. The PID is: %d", getpid());
    }
    else if (p1 == 0)
    { // Child process
        printf("This is Child. The PID is: %d, The PID is: %d", getpid(), getppid());
        exit(0);
    }
    else
    { // Fork failed
        printf("Fork creation failed!");
    }
    return 0;
}