// Main program receives a string as runtime argument
// Create a child process to reverse the string
// The parent program should send signal to pause the child process
// The parent program should send a signal to continue the child process
// The child process should print the reversed string

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

void reverse_and_print(const char *str);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string_to_reverse>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        printf("Child process (PID: %d) started and waiting to be resumed...\n", getpid());

        // A delay to prevent SIGSTOP and SIGCONT from running at once
        for (int i = 5; i > 0; i--)
        {
            printf("Child preparing in %d...\n", i);
            sleep(1);
        }

        reverse_and_print(argv[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        sleep(2);
        printf("Parent pausing child process (PID: %d)\n", pid);
        kill(pid, SIGSTOP);

        sleep(3);
        printf("Parent resuming child process (PID: %d)\n", pid);
        kill(pid, SIGCONT);

        wait(NULL);
        printf("Child process finished.\n");
    }

    return EXIT_SUCCESS;
}

void reverse_and_print(const char *str)
{
    int len = strlen(str);
    printf("Reversed string: ");
    for (int i = len - 1; i >= 0; i--)
    {
        putchar(str[i]);
    }
    putchar('\n');
}