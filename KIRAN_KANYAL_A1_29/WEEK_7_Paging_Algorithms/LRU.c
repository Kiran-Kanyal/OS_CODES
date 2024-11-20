#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

struct PageTable{
    int frame_no;
    int last_time_of_access;
    bool valid;
};

bool isPagePresent (struct PageTable PT[], int page){
    if (PT[page].valid == 1) return true;
    return false;
}

void updatePageTable (struct PageTable PT[], int page, int fr_no, int status, int access_time){
    PT[page].valid = status;
    if (status == 1){
        PT[page].frame_no = fr_no;
        PT[page].last_time_of_access = access_time;
    }
}

void printFrameContents(int frame[], int no_of_frames){
    for (int i=0; i<no_of_frames; i++){
        if (frame[i]!=-1) printf("%d ",frame[i]);
    }
    printf("\n");
}

int searchLRUPage (struct PageTable PT[], int frame[],int no_of_frames){
    int idx = -1;
    for (int i=0; i<no_of_frames; i++){
        if (idx==-1 || PT[frame[i]].last_time_of_access < PT[frame[idx]].last_time_of_access){
            idx = i;
        }
    }
    return idx;
}

int main(){
    int n;
    printf("Enter the no. of pages: ");
    scanf("%d", &n);
    int reference_string[n];
    printf("Enter the reference string (different page numbers):\n");
    for (int i=0; i<n; i++){
        scanf("%d", &reference_string[i]);
    }
    int no_of_frames;
    printf("Enter the no. of frames you want to give to the process: ");
    scanf("%d", &no_of_frames);
    int frame[no_of_frames];
    memset(frame, -1, no_of_frames*sizeof(int));
    struct PageTable PT[50];
    for (int i=0; i<50; i++){
        PT[i].valid = 0;
    }
    printf("***The Contents inside the Frame array at different time.***\n");
    int pageFault =0, current = 0;
    bool flag = false;
    for (int i=0; i<n; i++){
        if (!isPagePresent(PT, reference_string[i])){
            pageFault++;
            if (flag==false && current<no_of_frames){
                frame[current] = reference_string[i];
                updatePageTable(PT,reference_string[i],current,1,i);
                current = current + 1;
                if (current == no_of_frames){
                    flag = true;
                }
            }
            else{
                int LRU_page_index = searchLRUPage (PT,frame,no_of_frames);
                updatePageTable(PT,frame[LRU_page_index],-1,0,i);
                frame[LRU_page_index] = reference_string[i];
                updatePageTable(PT, reference_string[i],LRU_page_index,1,i);
            }
        }
        printFrameContents(frame, no_of_frames);
        PT[reference_string[i]].last_time_of_access = i;
    }
    printf("Total number of Page Fault: %d\n",pageFault);
    printf("Page Fault Ratio: %f\n", (float)(pageFault)/n);
    printf("Hit Ratio: %f\n", (float) (n-pageFault)/n);
}

