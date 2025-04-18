#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2)
    {
        printf("Invalid file\n");
    }

    if (access(argv[1], R_OK) < 0)
    {
        printf("Read access error for %s\n", argv[1]);
    }
    else
    {
        printf("Read access OK\n");
    }

    if (access(argv[1], W_OK) < 0)
    {
        printf("Write access error for %s\n", argv[1]);
    }
    else
    {
        printf("Write access OK\n");
    }

    if (access(argv[1], X_OK) < 0)
    {
        printf("exec access error for %s\n", argv[1]);
    }
    else
    {
        printf("exec access OK\n");
    }

    if (access(argv[1], O_RDONLY) < 0)
    {
        printf("Open error for %s\n", argv[1]);
    }
    else
    {
        printf("Opened for reading\n");
    }

    close(fd);
    exit(0);
}