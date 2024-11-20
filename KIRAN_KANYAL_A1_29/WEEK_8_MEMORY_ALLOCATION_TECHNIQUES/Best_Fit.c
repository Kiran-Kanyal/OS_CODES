#include<stdio.h>
#include<string.h>
#include<limits.h>
// CONFIRM IF MORE THAN ONE PROCESS CAN BE ASSIGNED TO THE SAME BLOCK OR NOT
int main(){
    int no_of_blocks;
    printf("Enter the number of blocks: ");
    scanf("%d",&no_of_blocks);
    int blocks[no_of_blocks];
    printf("Enter the size of each block: \n");
    for (int i=0; i<no_of_blocks; i++){
        scanf("%d",&blocks[i]);
    }
    int no_of_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &no_of_processes);
    int given_block[no_of_processes],process[no_of_processes];
    memset(given_block,-1,sizeof(int)*no_of_processes);
    printf("Enter the memory requirement of each process: \n");
    for (int i=0; i<no_of_processes; i++){
        scanf("%d", &process[i]);
    }
    for (int i=0; i<no_of_processes; i++){
        int minFragmentation = INT_MAX;
        int blockNo=-1;
        for (int j=0; j<no_of_blocks; j++){
            if (blocks[j]>=process[i]){
                if (minFragmentation > (blocks[j] - process[i])){
                    minFragmentation = blocks[j]-process[i];
                    blockNo = j;
                }
            }
        }
        if (blockNo!=-1){
            given_block[i] = blockNo+1;
            blocks[blockNo] = 0;
        }
    }
    for (int i=0; i<no_of_processes; i++){
        if (given_block[i] != -1){
            printf("Memory block assigned to Process %d: %d\n",process[i],given_block[i]);
        }
        else{
            printf("No memory block could be assigned.\n");
        }
    }
}