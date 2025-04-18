#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 20
#define READ_END 0
#define WRITE_END 1

int main()
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE] = "";
    int fd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(fd) == -1)
    {
        printf("Pipe creation failed!");
        return 1;
    }

    // fork a child process
    pid = fork();

    if (pid > 0)
    { // Parent process
        printf("This is Parent\n");

        // Close unused end of pipe
        close(fd[READ_END]);

        // Write to pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        // Close write end of pipe
        close(fd[WRITE_END]);

        wait(NULL);
    }
    else if (pid == 0)
    { // Child process
        printf("This is Child\n");

        // Close unused end of pipe
        close(fd[WRITE_END]);

        // Read from pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Child process read: %s", read_msg);

        // Close read end of pipe
        close(fd[READ_END]);
    }
    else
    { // Fork failed
        printf("Fork creation failed!");
    }
}