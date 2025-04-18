#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;
    int y = 0;
    p1 = fork();

    if (p1 > 0)
    { // Parent process
        wait(NULL);
        y = y - 1;
        printf("This is Parent. The PID is: %d, y = %d\n", getpid(), y);
    }
    else if (p1 == 0)
    { // Child process
        p2 = fork();

        if (p2 > 0)
        {
            wait(NULL);
        }
        else if (p2 == 0)
        {
            y = y + 5;
            printf("This is Grandchild. The PID is: %d, The PID is: %d, y = %d\n", getpid(), getppid(), y);
            exit(0);
        }

        y = y + 1;
        printf("This is Child. The PID is: %d, The PID is: %d, y = %d\n", getpid(), getppid(), y);
        exit(0);
    }
    else
    { // Fork failed
        printf("Fork creation failed!");
    }
}