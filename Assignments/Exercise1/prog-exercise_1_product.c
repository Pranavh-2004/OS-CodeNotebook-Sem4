// External product program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments");
        return 1;
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    int prod = x * y;

    printf("Product of %d and %d is: %d", x, y, prod);

    return 0;
}