#include <stdio.h>

int main()
{
    // Matrix for storing Process Id, Burst Time,
    // Waiting Time, and Turn Around Time.
    int A[100][4];
    int i, n;
    float total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]); // Burst Time
        A[i][0] = i + 1;       // Process ID
    }

    // Initialize Waiting Time for the first process to 0
    A[0][2] = 0;

    // Calculate Waiting Time for all other processes
    for (i = 1; i < n; i++)
    {
        A[i][2] = A[i - 1][2] + A[i - 1][1];
        total_wt += A[i][2];
    }

    // Calculate Turn Around Time for all processes
    printf("P\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        A[i][3] = A[i][1] + A[i][2]; // TAT = BT + WT
        total_tat += A[i][3];
        printf("P%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    // Calculate and display Average Waiting Time and Turn Around Time
    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}