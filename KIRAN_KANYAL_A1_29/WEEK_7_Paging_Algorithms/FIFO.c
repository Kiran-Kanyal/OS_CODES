// FIFO Page Replacement
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
// Example:
// No of frames = 3
// No of request = 12
// 2 3 2 1 5 2 4 5 3 1 5 2
struct PageTable{
    int frame_no;
    bool valid;
};
bool isPagePresent(struct PageTable PT[], int page){
    if (PT[page].valid == 1){
        return true;
    }
    return false;
}
void updatePageTable (struct PageTable PT[], int page, int fr_no, int status){
    PT[page].valid = status;
    if (status == 1) PT[page].frame_no = fr_no;
}
void printFrameContents (int frame[], int no_of_frames){
    for (int i=0; i<no_of_frames; i++){
        if (frame[i] != -1) printf("%d ",frame[i]);
    }
    printf("\n");
}
int main(){
    int n, no_of_frames;
    printf("Enter the number of pages (page requests): ");
    scanf("%d", &n);
    int reference_string[n];
    printf("\nEnter the reference string(different page numbers):\n");
    for (int i=0; i<n; i++){
        scanf("%d",&reference_string[i]);
    }
    printf("Enter the no. of frames you want to give to the process:");
    scanf("%d", &no_of_frames);
    int frame[no_of_frames];
    memset(frame,-1,no_of_frames*sizeof(int));
    struct PageTable PT[50];
    for (int i=0; i<50; i++){
        PT[i].valid = 0;
    }
    printf("\n***The contents inside the Frame array at different time: ***\n");
    int page_fault = 0, current = 0, flag = false;
    for (int i=0; i<n; i++){
        if (!isPagePresent(PT, reference_string[i])){
            page_fault++;
            if (flag==false && current<no_of_frames){
                frame[current] = reference_string[i];
                updatePageTable(PT, reference_string[i],current,1);
                current+=1;
                if (current==no_of_frames){
                    current = 0;
                    flag = true;
                }
            }
            else{
                updatePageTable(PT,frame[current],-1,0);
                frame[current] = reference_string[i];
                updatePageTable(PT, reference_string[i], current,1);
                current = (current+1)%no_of_frames;
            }
            printFrameContents(frame, no_of_frames);
        }
    }
    printf("\nTotal No. of Page Faults = %d\n",page_fault);
    printf("\nPage Fault Ratio = %.2f\n", (float) page_fault/n);
    printf("\nPage Hit Ratio = %.2f", (float) (n-page_fault)/n);
    return 0;
}
