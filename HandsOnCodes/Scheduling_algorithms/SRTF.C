#include <stdio.h>
#include <limits.h>

int main()
{
    int n, i, j, time = 0, smallest, count = 0;
    int arrival_time[100], burst_time[100], remaining_time[100];
    int waiting_time[100], turnaround_time[100];
    float total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i]; // Initialize remaining times
    }

    // Process until all processes are completed
    printf("\nP\tAT\tBT\tWT\tTAT\n");
    while (count < n)
    {
        smallest = -1;
        int min_remaining_time = INT_MAX;

        // Find the process with the shortest remaining time
        for (i = 0; i < n; i++)
        {
            if (arrival_time[i] <= time && remaining_time[i] > 0 && remaining_time[i] < min_remaining_time)
            {
                smallest = i;
                min_remaining_time = remaining_time[i];
            }
        }

        if (smallest == -1) // If no process is ready at the current time
        {
            time++;
            continue;
        }

        // Execute the selected process
        remaining_time[smallest]--;
        time++;

        // If the process is completed
        if (remaining_time[smallest] == 0)
        {
            count++;
            int completion_time = time;
            turnaround_time[smallest] = completion_time - arrival_time[smallest];
            waiting_time[smallest] = turnaround_time[smallest] - burst_time[smallest];

            total_wt += waiting_time[smallest];
            total_tat += turnaround_time[smallest];

            printf("P%d\t%d\t%d\t%d\t%d\n", smallest + 1, arrival_time[smallest],
                   burst_time[smallest], waiting_time[smallest], turnaround_time[smallest]);
        }
    }

    // Display Average Waiting Time and Turn Around Time
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}