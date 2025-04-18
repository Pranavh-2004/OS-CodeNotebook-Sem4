#include <stdio.h>

int main()
{
    int n, i, j, time = 0, remaining_processes;
    int quantum, total_wt = 0, total_tat = 0;
    int bt[100], wt[100], tat[100], rem_bt[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i]; // Copy burst times to remaining burst times
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    remaining_processes = n;

    // Process until all processes are finished
    while (remaining_processes > 0)
    {
        for (i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0) // If the process still has burst time left
            {
                if (rem_bt[i] > quantum)
                {
                    time += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    time += rem_bt[i];
                    wt[i] = time - bt[i]; // Waiting time = current time - burst time
                    rem_bt[i] = 0;
                    remaining_processes--;
                }
            }
        }
    }

    // Calculate Turnaround Time
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i]; // Turnaround time = burst time + waiting time
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Display Process details
    printf("\nP\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    // Display Average Waiting Time and Turnaround Time
    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}