#include <stdio.h>

typedef struct process
{
    char pid;
    int bt;          // Burst Time
    int at;          // Arrival Time
    int priority;    // Priority (higher value = higher priority)
    int ct;          // Completion Time
    int tat;         // Turnaround Time
    int wt;          // Waiting Time
    int isCompleted; // 0 = Not Completed, 1 = Completed
} process;

// Higher value -> higher priority
int findNextProcess(process processes[], int n, int currTime)
{
    int idx = -1;
    int highestPriority = -1;

    for (int i = 0; i < n; i++)
    {
        if (processes[i].at <= currTime && !processes[i].isCompleted)
        {
            if (processes[i].priority > highestPriority)
            {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }
    }

    return idx;
}

void calculateTime(process processes[], int n)
{
    int currTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int idx = findNextProcess(processes, n, currTime);

        if (idx == -1)
        {
            // Jump to the next process arrival time
            int nextArrivalTime = 1000000; // Initialize to a large value
            for (int i = 0; i < n; i++)
            {
                if (!processes[i].isCompleted && processes[i].at > currTime)
                {
                    if (processes[i].at < nextArrivalTime)
                    {
                        nextArrivalTime = processes[i].at;
                    }
                }
            }
            currTime = nextArrivalTime;
            continue;
        }

        processes[idx].ct = currTime + processes[idx].bt;
        processes[idx].tat = processes[idx].ct - processes[idx].at;
        processes[idx].wt = processes[idx].tat - processes[idx].bt;
        processes[idx].isCompleted = 1;

        currTime = processes[idx].ct;
        completed++;
    }
}

void printDetails(process processes[], int n)
{
    printf("Process ID\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%c\t\t%d\t%d\t%d\n", processes[i].pid, processes[i].ct, processes[i].tat, processes[i].wt);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter PID, Arrival Time, Burst Time, and Priority in the same sequence:\n");

    process processes[n];

    for (int i = 0; i < n; i++)
    {
        scanf(" %c %d %d %d", &processes[i].pid, &processes[i].at, &processes[i].bt, &processes[i].priority);
        processes[i].isCompleted = 0;
    }

    calculateTime(processes, n);
    printDetails(processes, n);

    return 0;
}
