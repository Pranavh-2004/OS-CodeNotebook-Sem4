#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <x> <y>\n", argv[0]);
        return 1;
    }

    // Convert command-line arguments to integers
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    // Compute and print the product
    printf("The product of %d and %d is: %d\n", x, y, x * y);

    return 0;
}