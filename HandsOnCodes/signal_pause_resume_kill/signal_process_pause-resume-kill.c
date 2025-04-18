#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t p1;
    p1 = fork();

    if (p1 > 0)
    { // Parent process
        sleep(1);
        printf("This is Parent. The PID is: %d\n", getpid());
        kill(p1, SIGSTOP);
        sleep(1);
        printf("This is Parent after pausing Child. The PID is: %d\n", getpid());
        sleep(1);
        kill(p1, SIGCONT);
        sleep(1);
        printf("This is Parent after resuming/restarting Child. The PID is: %d\n", getpid());
        sleep(1);
        kill(p1, SIGKILL);
        sleep(1);
        printf("This is Parent after terminating Child. The PID is: %d\n", getpid());
        sleep(1);
    }
    else if (p1 == 0)
    { // Child process
        while (1)
        {
            printf("This is Child. The PID is: %d, The PID is: %d\n", getpid(), getppid());
        }
    }
    else
    { // Fork failed
        printf("Fork creation failed!");
    }
}