// FCFS – First Come First Served : process which arrives first will get the CPU first
#include <stdio.h>
#include <stdlib.h>
struct process_struct
{
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // CPU Burst time
    int ct;         // Completion time
    int wt;         // Waiting time
    int tat;        // Turnaround time
    int rt;         // Response time
    int start_time; // Start time
} ps[100];          // Array of structures to store the info of each process

// Function to find the maximum of two integers
int findmax(int a, int b)
{
    return (a > b) ? a : b;
}

// Comparator function for sorting by arrival time
int comparatorAT(const void *a, const void *b)
{
    return ((struct process_struct *)a)->at - ((struct process_struct *)b)->at;
}

int main()
{
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int total_idle_time = 0;

    for (int i = 0; i < n; i++)
    {
        ps[i].pid = i;
        printf("Enter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        printf("Enter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
    }

    // Sort processes by arrival time
    qsort(ps, n, sizeof(struct process_struct), comparatorAT);

    // Calculations
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            ps[i].start_time = ps[i].at; // Start time for first process
        }
        else
        {
            ps[i].start_time = findmax(ps[i].at, ps[i - 1].ct);
        }
        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].wt; // In FCFS, response time is same as waiting time

        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;

        total_idle_time += (i == 0) ? 0 : (ps[i].start_time - ps[i - 1].ct);
    }

    int length_cycle = ps[n - 1].ct - ps[0].start_time;

    // Output
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }

    // Calculate CPU utilization
    float cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    // Print average times and CPU utilization
    printf("\nAverage Turnaround Time = %f ", sum_tat / n);
    printf("\nAverage Waiting Time = %f ", sum_wt / n);
    printf("\nAverage Response Time = %f ", sum_rt / n);
    printf("\nThroughput = %f", n / (float)length_cycle);
    printf("\nCPU Utilization (Percentage) = %f%%\n", cpu_utilization * 100);

    return 0;
}
