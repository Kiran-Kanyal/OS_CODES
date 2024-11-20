// SJF NON PREEMPTIVE
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    int tat;
    int wt;
    int rt;
};
int findMax(int a, int b)
{
    return (a > b) ? a : b;
}
int findMin(int a, int b)
{
    return (a < b) ? a : b;
}
int main()
{
    int n;
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter Arrival Time of each Process:  ");
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        scanf("%d", &p[i].at);
    }
    printf("Enter Burst Time of each Process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].bt);
    }
    int completed = 0, currTime = 0, prev = 0;
    int sumtat = 0, sumwt = 0, sumrt = 0, total_idleTime = 0, lengthCycle = 0;
    bool is_Complete[n];
    for (int i = 0; i < n; i++)
        is_Complete[i] = false;
    int gantt[n];
    int ganttIndex = 0;
    while (completed != n)
    {
        int minidx = -1;
        int mini = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && !is_Complete[i])
            {
                if (p[i].bt < mini)
                {
                    mini = p[i].bt;
                    minidx = i;
                }
                if (p[i].bt == mini && p[i].at < p[minidx].at)
                {
                    mini = p[i].bt;
                    minidx = i;
                }
            }
        }
        if (minidx == -1)
            currTime++;
        else
        {
            p[minidx].st = currTime;
            p[minidx].ct = p[minidx].st + p[minidx].bt;
            p[minidx].tat = p[minidx].ct - p[minidx].at;
            p[minidx].wt = p[minidx].tat - p[minidx].bt;
            p[minidx].rt = p[minidx].wt;

            sumtat += p[minidx].tat;
            sumwt += p[minidx].wt;
            sumrt += p[minidx].rt;
            total_idleTime += (ganttIndex == 0) ? 0 : p[minidx].st - prev;

            gantt[ganttIndex++] = p[minidx].pid;

            completed++;
            currTime = p[minidx].ct;
            prev = currTime;
            is_Complete[minidx] = true;
        }
    }
    int max_completionTime = INT_MIN;
    int min_ArrivalTime = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        max_completionTime = findMax(max_completionTime, p[i].ct);
        min_ArrivalTime = findMin(min_ArrivalTime, p[i].at);
    }
    lengthCycle = max_completionTime - min_ArrivalTime;
    float cpu_Utilization = (float)(lengthCycle - total_idleTime) * 100 / lengthCycle;
    float throughput = (float)n / lengthCycle;
    printf("Gantt's Chart: ");
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("P%d ", gantt[i]);
    }
    printf("\n");
    printf("Total Turn Around Time = %d\n", sumtat);
    printf("Total Waiting Time = %d\n", sumwt);
    printf("Total Response Time = %d\n", sumrt);
    printf("Total Idle Time = %d\n", total_idleTime);
    printf("Length Cycle = %d\n", lengthCycle);
    printf("Average Turn Around Time = %.2f\n", (float)sumtat / n);
    printf("Average Waiting Time = %.2f\n", (float)sumwt / n);
    printf("Average Response Time = %.2f\n", (float)sumrt / n);
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("CPU Utilization = %.2f\n", cpu_Utilization);
    printf("Throughput = %.2f\n", throughput);
    return 0;
}
