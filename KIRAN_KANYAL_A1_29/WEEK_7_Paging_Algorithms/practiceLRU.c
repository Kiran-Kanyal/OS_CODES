#include<stdio.h>
#include<stdbool.h> // for bool 
#include<string.h>  // for memset 

struct PageTable{
    int frame_no;
    bool valid;
    int last_time_of_access;
};

bool isPagePresent(struct PageTable PT[],int page){
    if (PT[page].valid==1) return true;
    return false;
}

void updatePageTable(struct PageTable PT[],int page,int fr_no,int status, int access_time){
    PT[page].valid = status;
    if (status==1) 
    {
        PT[page].frame_no = fr_no;
        PT[page].last_time_of_access = access_time;
    }
}

void printFrameContents (int frame[],int no_of_frames){
    for (int i=0; i<no_of_frames; i++){
        if (frame[i]!=-1) printf("%d ",frame[i]);
    }
    printf("\n");
}

int searchLRUPage(int frame[],struct PageTable PT[], int no_of_frames){
    int idx = -1;
    for (int i=0; i<no_of_frames; i++){
        if (idx==-1 || PT[frame[idx]].last_time_of_access>PT[frame[i]].last_time_of_access){
            idx = i;
        }
    }
    return idx;
}

int main(){
    int n;
    printf("Enter the number of page requests: ");
    scanf("%d", &n);
    int reference_string[n];
    printf("Enter the pages in order of their requests: ");
    for (int i=0; i<n; i++){
        scanf("%d", &reference_string[i]);
    }
    int no_of_frames;
    printf("Enter the number of frames allocated to the process: ");
    scanf("%d", &no_of_frames);
    int frame[no_of_frames];
    memset(frame,-1,sizeof(int)*no_of_frames);
    struct PageTable PT[50];
    for (int i=0; i<50; i++){
        PT[i].valid = 0;
    }
    int current = 0, page_fault = 0;
    bool flag = false;

    for (int i=0; i<n; i++){
        if (!isPagePresent(PT,reference_string[i])){
            page_fault++;
            if (flag==false && current<no_of_frames){
                frame[current] = reference_string[i];
                updatePageTable(PT,reference_string[i],current,1,i);
                current++;
                if (current==no_of_frames) flag = true;
            }
            else{
                int idx = searchLRUPage(frame,PT,no_of_frames);
                updatePageTable(PT,frame[idx],-1,0,i);
                frame[idx] = reference_string[i];
                updatePageTable(PT,reference_string[i],idx,1,i);
            }
            printFrameContents(frame,no_of_frames);
        }
        PT[reference_string[i]].last_time_of_access = i;
    }
    printf("Total number of Page Fault: %d\n",page_fault);
    printf("Page Fault Ratio: %f\n", (float)(page_fault)/n);
    printf("Hit Ratio: %f\n", (float)(n-page_fault)/n);
}




