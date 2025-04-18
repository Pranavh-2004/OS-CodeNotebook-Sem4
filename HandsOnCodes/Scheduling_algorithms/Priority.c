#include <stdio.h>

int main()
{
    int n, i, j, total_wt = 0, total_tat = 0;
    int process[100], burst_time[100], priority[100];
    int waiting_time[100], turnaround_time[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input Burst Time and Priority for each process
    printf("Enter Burst Time and Priority for each process:\n");
    for (i = 0; i < n; i++)
    {
        process[i] = i + 1;
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("P%d Priority: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sorting processes based on Priority (lower priority number = higher priority)
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (priority[i] > priority[j])
            {
                // Swap priority
                int temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // Swap burst time
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                // Swap process ID
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    // Calculate Waiting Time and Turnaround Time
    waiting_time[0] = 0; // First process has no waiting time
    for (i = 1; i < n; i++)
    {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
        total_wt += waiting_time[i];
    }

    for (i = 0; i < n; i++)
    {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
        total_tat += turnaround_time[i];
    }

    // Display Process details
    printf("\nP\tBT\tPriority\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t\t%d\t%d\n", process[i], burst_time[i], priority[i],
               waiting_time[i], turnaround_time[i]);
    }

    // Display Average Waiting Time and Turnaround Time
    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}