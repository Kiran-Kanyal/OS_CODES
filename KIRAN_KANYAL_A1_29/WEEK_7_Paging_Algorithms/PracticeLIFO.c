#include<stdio.h>
#include<stdbool.h>
#include<string.h> //for memset method or initialize by yourself using for loop
struct PageTable{
    int frame_no;
    bool valid;
};

void updatePageTable (struct PageTable PT[],int page,int fr_no,int status){
    PT[page].valid = status;
    if (status == 1) PT[page].frame_no = fr_no;
}

bool isPagePresent (struct PageTable PT[], int page){
    if (PT[page].valid == 1) return true;
    return false;
}

void printFrameContents (int frame[], int no_of_frames){
    for (int i=0; i<no_of_frames; i++){
        if (frame[i] != -1) printf("%d ",frame[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter total number of page requests: ");
    scanf("%d",&n);
    int reference_string[n];
    printf("Enter pages in order of request: \n");
    for (int i=0; i<n; i++){
        scanf("%d", &reference_string[i]);
    }
    int no_of_frames;
    printf("Enter the no. of frames allowed for the process: ");
    scanf("%d", &no_of_frames);
    int frame[no_of_frames];
    // IMPORTANT YOU FORGETTED : MEMSET
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
            if (flag == false && current<no_of_frames){
                frame[current] = reference_string[i];
                updatePageTable(PT,reference_string[i],current,1);
                printFrameContents(frame,no_of_frames);
                current+=1;
                if (current == no_of_frames){
                    current=0;
                    flag = true;
                }
            }
            else{
                // Apply LIFO
                updatePageTable(PT,frame[current],-1,0);
                updatePageTable(PT,reference_string[i],current,1);
                frame[current] = reference_string[i];
                printFrameContents(frame,no_of_frames);
                current = (current+1)%no_of_frames;
            }
        }
    }
    printf("Number of Page Faults: %d",page_fault);
    printf("Page Fault Ration = %f", (float)page_fault/n);
    printf("Hit Ratio : %f", (float) (n-page_fault)/n);
}
