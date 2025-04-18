#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILDREN 5

int main()
{
    pid_t pid;
    int i;
    int stack_var = 42; // Stack variable

    printf("Parent Process PID: %d (Stack address: %p, Main function frame: %p)\n",
           getpid(), (void *)&stack_var, (void *)&pid);

    for (i = 0; i < NUM_CHILDREN; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            // Child process
            int child_stack_var = i; // Stack variable in child

            // Dynamically allocate memory
            int *arr = malloc(100 * sizeof(int));
            if (!arr)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            printf("Child %d with PID %d (Stack address: %p, Heap address: %p)\n",
                   i, getpid(), (void *)&child_stack_var, (void *)arr);

            // Keep the child running
            while (1)
            {
                sleep(1);
            }

            free(arr);
            exit(0);
        }
    }

    printf("\nAll children created. Press Enter to terminate all processes...\n");
    getchar();

    // Kill all children
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        kill(0, SIGTERM);
    }

    // Wait for all children
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        wait(NULL);
    }

    return 0;
}