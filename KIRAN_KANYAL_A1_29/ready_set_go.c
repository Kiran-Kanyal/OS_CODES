//multi level scheduling 
#include<stdio.h>
#include<stdlib.h>

struct Process{
    int pid,at,bt,st,ct,rt,tat,wt;
};

int compare (const void* p1, const void* p2){
    int a = ((struct Process *) p1)->at;
    int b= ((struct Process *) p2)->at;
    return a<b?-1:1;
}

void calculateTimes(struct Process ps[], int n, int* currTime ){
    for (int i=0; i<n; i++){
        if (i==0){
            ps[i].st = (currTime>ps[i].at)?currTime:ps[i].at;
        }
        else{
            ps[i].st = (ps[i-1].ct > ps[i].at)?ps[i-1].ct:ps[i].at;
        }
        ps[i].ct = ps[i].st+ps[i].bt;
        ps[i].rt = ps[i].st-ps[i].at;
        ps[i].tat = ps[i].ct-ps[i].at;
        ps[i].wt = ps[i].tat-ps[i].bt;
        currTime = ps[i].ct;
    }
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct Process ps[n];
    for (int i=0; i<n; i++){
        ps[i].pid = i+1;
        printf("Enter the value of arrival time and burst time for %d Process: ",i+1);
        scanf("%d%d", &ps[i].at,&ps[i].bt);
    }
    int sys_count;
    printf("Enter the number of system processes: ");
    scanf("%d", &sys_count);
    int sys_pid[sys_count];
    for (int i=0; i<n; i++){
        scanf("%d", &sys_pid[i]);
    }
    int sys_idx  = 0, user_idx = 0;
    struct Process system_queue[sys_count], user_queue[n-sys_count];
    for (int i=0; i<n; i++){
        int is_system = 0;
        for (int j=0; j<sys_count;j++){
            if (ps[i].pid == sys_pid[j]){
                is_system = 1;
                break;
            }
        }
        if (is_system){
            system_queue[sys_idx++] = ps[i];
        }
        else{
            user_queue[user_idx++] = ps[i];
        }
    }

    qsort(system_queue,sys_count,sizeof(struct Process),compare);
    qsort(user_queue, n-sys_count, sizeof(struct Process), compare);
    int currentTime= 0;
    calculateTimes(system_queue, sys_count,&currentTime);
    calculateTimes(user_queue,n-sys_count,&currentTime);
    printf("Gantts Chart : \n");
    for (int i=0; i<sys_idx; i++){
        printf("P%d\t", system_queue[i].pid);
    }
    for (int i=0; i<user_idx; i++){
        printf("P%d\t",user_queue[i].pid);
    }
    int totat_wt=0,total_tat = 0;
    for (int i=0; i<n; i++){
        
    }
}