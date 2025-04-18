#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void my_signal_handler(int sig);

int main()
{
    (void)signal(SIGFPE, my_signal_handler);

    int n = 0, d = 0;

    printf("Enter the numerator: ");
    scanf("%d", &n);

    printf("Enter the denomrator: ");
    scanf("%d", &d);

    int res = n / d;

    printf("The result is: %d", res);
}

void my_signal_handler(int sig)
{
    printf("Encountered floating point error\n");
    (void)signal(SIGFPE, SIG_DFL);
}
