// Write a program which accepts two integers x and y.
// Now use exec to execute another user defined program that prints the product of x and y

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int x, y;

    printf("Enter the value of X: ");
    scanf("%d", &x);

    printf("Enter the value of Y: ");
    scanf("%d", &y);

    // test part
    /*
    int prod = x * y;
    printf("Product is %d", prod);
    */

    char strx[20], stry[20];
    snprintf(strx, sizeof(strx), "%d", x);
    snprintf(stry, sizeof(stry), "%d", y);

    execl("./prog-exercise_1_product", "/Users/pranavhemanth/Code/Academics/OS-S4", strx, stry, NULL);

    perror("execl failed");
    return 1;
}