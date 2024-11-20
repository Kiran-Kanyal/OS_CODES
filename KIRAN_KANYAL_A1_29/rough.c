#include<stdio.h>
#include<stdlib.h>

typedef struct process{
    int pid, at,bt,st,ct,tat,rt,wt;
} process;

int findMax(int a,int b){
    return a>b?a:b;
}

int comparator (const void* a, const  void *b){
    const process* p1 = (const process*)a;
    const process* p2 = (const process*)b;

    if (p1->at < p2->at) return -1;
    else if (p1->at > p2->at) return 1;
    else{
        if (p1->pid < p2->pid) return -1;
        else if (p1->pid > p2->pid) return 1;
    } 
    return 0;
}

int comparatorId (const void* a, const  void *b){
    const process* p1 = (const process*)a;
    const process* p2 = (const process*)b;

    if (p1->pid < p2->pid) return -1;
    return 1;
}


int main(){
    int n;
    printf("Enter the total number of Processes: ");
    scanf("%d",&n);

    process p[n];
    for (int i=0;i<n; i++){
        printf("Enter the arrival time and burst time for P%d",i+1);
        scanf("%d%d",&p[i].at, &p[i].bt);
        p[i].pid = i;
    }

    qsort(p,n,sizeof(process),comparator);  // qsort((void *) p,n,sizeof(process),comparator);

    int sum_tat=0, sum_wt=0, sum_rt=0, idle_time = 0;
//st, ct, tat, wt, rt,
    for (int i=0; i<n; i++){
        p[i]
    }

}