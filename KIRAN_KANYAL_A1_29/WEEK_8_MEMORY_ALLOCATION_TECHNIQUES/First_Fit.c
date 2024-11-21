#include<stdio.h>
#include<string.h>
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
        for (int j=0; j<no_of_blocks; j++){
            if (blocks[j]>=process[i]){
                given_block[i] = j+1;
                blocks[j] = 0;
                break;
            }
        }
    }
    for (int i=0; i<no_of_processes; i++){
        if (given_block[i] != -1){
            printf("Memory block assigned to Process %d: %d\n",process[i],given_block[i]);
        }
        else{
            printf("%d: No memory block could be assigned.\n",process[i]);
        }
    }
}