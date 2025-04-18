#include <stdio.h>
#include <unistd.h>

int main()
{
    int x, y;

    // Input two integers
    printf("Enter the first integer (x): ");
    scanf("%d", &x);
    printf("Enter the second integer (y): ");
    scanf("%d", &y);

    // Convert integers to strings
    char str_x[20], str_y[20];
    snprintf(str_x, sizeof(str_x), "%d", x);
    snprintf(str_y, sizeof(str_y), "%d", y);

    // Execute the external program
    execl("./test_prod", "/Users/pranavhemanth/Code/Academics/OS-S4", str_x, str_y, NULL);

    // If execl fails
    perror("execl failed");
    return 1;
}