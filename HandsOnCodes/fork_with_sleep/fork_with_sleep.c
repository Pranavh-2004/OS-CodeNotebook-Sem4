#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t p1;
    int y = 0;
    p1 = fork();

    if (p1 > 0)
    { // Parent process
        for (int i = 0; i < 5; i++)
        {
            sleep(i);
            y = y - 1;
            printf("This is Parent. The PID is: %d, y = %d\n", getpid(), y);
        }
    }
    else if (p1 == 0)
    { // Child process
        for (int i = 0; i < 5; i++)
        {
            sleep(i);
            y = y + 1;
            printf("This is Child. The PID is: %d, The PID is: %d, y = %d\n", getpid(), getppid(), y);
        }
    }
    else
    { // Fork failed
        printf("Fork creation failed!");
    }
}