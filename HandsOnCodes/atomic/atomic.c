#include <stdio.h>
#include <unistd.h>
#include "atomic.h"

int main()
{
    atomic_t counter;
    int value;

    atomic_set(&counter, 5);
    atomic_add(10, &counter);
    atomic_sub(4, &counter);
    sleep(2);
    atomic_inc(&counter);
    value = atomic_read(&counter);
    printf("Value = %d\n", value);
}