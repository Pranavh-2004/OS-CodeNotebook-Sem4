#include <stdio.h>

int main()
{
    int A[100][4]; // Array to store Process ID, Burst Time, Waiting Time, and Turn Around Time
    int i, j, n, total = 0, temp;
    float avg_wt, avg_tat;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]); // Burst Time
        A[i][0] = i + 1;       // Process ID
    }

    // Sort processes based on Burst Time (Ascending Order)
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j][1] > A[j + 1][1])
            {
                // Swap Burst Time
                temp = A[j][1];
                A[j][1] = A[j + 1][1];
                A[j + 1][1] = temp;

                // Swap Process ID
                temp = A[j][0];
                A[j][0] = A[j + 1][0];
                A[j + 1][0] = temp;
            }
        }
    }

    // Initialize Waiting Time for the first process to 0
    A[0][2] = 0;

    // Calculate Waiting Time for all processes
    for (i = 1; i < n; i++)
    {
        A[i][2] = A[i - 1][2] + A[i - 1][1];
        total += A[i][2];
    }
    avg_wt = (float)total / n;

    // Calculate Turn Around Time for all processes
    total = 0;
    printf("P\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        A[i][3] = A[i][1] + A[i][2]; // TAT = BT + WT
        total += A[i][3];
        printf("P%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }
    avg_tat = (float)total / n;

    // Display Average Waiting Time and Turn Around Time
    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}