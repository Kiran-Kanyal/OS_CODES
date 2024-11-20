// FCFS SCHEDULING ALGO
#include <stdio.h>
#include <stdlib.h>
struct Process
{
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int st;  // Start Time
    int ct;  // Completion Time
    int tat; // Turn Around Time
    int wt;  // Waiting Time
    int rt;  // Response Time
};
int findMax(int a, int b)
{

    return (a > b) ? a : b;
}
int comparatorAT(const void *a, const void *b)
{
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;

    return (p1->at - p2->at);
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    int totalTAT = 0, totalWT = 0, totalRT = 0, totalIdleTime = 0;
    float cpuUtilization, throughput;
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

    qsort(p, n, sizeof(struct Process), comparatorAT);
    for (int i = 0; i < n; i++)
    {
        p[i].st = (i == 0) ? p[i].at : findMax(p[i].at, p[i - 1].ct);
        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        totalRT += p[i].rt;
        if (i > 0)
        {
            totalIdleTime += p[i].st - p[i - 1].ct;
        }
    }
    int totalTime = p[n - 1].ct - p[0].st;
    cpuUtilization = ((totalTime - totalIdleTime) / (float)totalTime) * 100;
    throughput = (float)n / totalTime;
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\nGantt chart: ");
    for (int i = 0; i <n; i++)
    {
        printf("P%d ", p[i].pid);
    }
    printf("\nAverage Turnaround Time: %.2f", (float)totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Response Time: %.2f", (float)totalRT / n);
    printf("\nCPU Utilization: %.2f%%", cpuUtilization);
    printf("\nThroughput: %.2f processes/unit time\n", throughput);
    return 0;
}