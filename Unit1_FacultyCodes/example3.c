// program to demonstrate creation of child and grandchild processes using fork() and wait()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;

    int y = 0;

    p1 = fork();

    if (p1 > 0) // parent process
    {
        wait(NULL);

        y = y - 1;

        printf("This is parent. Process Id = %d, y = %d\n", getpid(), y);
    }
    else if (p1 == 0) // child process
    {
        p2 = fork();

        if (p2 > 0)
        {
            wait(NULL);
        }
        else if (p2 == 0)
        {
            y = y + 5;

            printf("This is grandchild. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

            exit(0);
        }

        y = y + 1;

        printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

        exit(0);
    }
    else // fork failed
    {
        printf("fork creation failed!!!\n");
    }
}

/*
// program to demonstrate creation of child and grandchild processes using fork() and wait()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;

    p1 = fork();

    if (p1 > 0) //parent process
    {
        wait(NULL);

        printf("This is parent. Process Id = %d", getpid());
    }
    else if (p1 == 0) // child process
    {
        p2 = fork();

        if (p2 > 0)
        {
           wait(NULL);
        }
        else if (p2 == 0)
        {

           printf("This is grandchild. Process Id = %d, Parent Process Id = %d", getpid(), getppid());

           exit(0);
        }

        printf("This is child. Process Id = %d, Parent Process Id = %d", getpid(), getppid());

        exit(0);
    }
    else //fork failed
    {
        printf("fork creation failed!!!\n");
    }
}
*/