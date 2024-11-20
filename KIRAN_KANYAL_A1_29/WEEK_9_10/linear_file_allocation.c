#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int disk_block[100];

struct File {
    char name[20];
    int start_block;
    int length;
};

bool memoryAvailable(int start_block, int file_length) {
    if (start_block + file_length >= 100)
        return false;

    for (int i = start_block; i < start_block + file_length; i++) {
        if (disk_block[i] != 0)
            return false;
    }
    return true;
}

void searchDetails(char file_name[20], struct File files[], int no_of_files) {
    for (int i = 0; i < no_of_files; i++) {
        if (strcmp(files[i].name, file_name) == 0) { 
            if (files[i].start_block != -1) {
                printf("File name: %s\n", file_name);
                printf("Starting block: %d\n", files[i].start_block);
                printf("Number of blocks: %d\n", files[i].length);
                printf("Blocks occupied: ");
                for (int j = files[i].start_block; j < files[i].start_block + files[i].length; j++) {
                    printf("%d ", j);
                }
                printf("\n");
            } else {
                printf("File not allocated memory.\n");
            }
            return; 
        }
    }
    printf("File not found.\n");
}

int main() {
    memset(disk_block, 0, sizeof(int) * 100);
    int n;
    printf("Enter the number of files: ");
    scanf("%d", &n);

    struct File files[n];
    for (int i = 0; i < n; i++) {
        int starting_block, file_length;
        printf("Enter the file name: ");
        scanf("%s", files[i].name);
        printf("Enter the file length: ");
        scanf("%d", &file_length);
        printf("Enter the start block: ");
        scanf("%d", &starting_block);

        if (memoryAvailable(starting_block, file_length)) {
            for (int j = starting_block; j < starting_block + file_length; j++) {
                disk_block[j] = 1;
            }
            printf("File successfully allocated memory.\n");
            files[i].start_block = starting_block;
            files[i].length = file_length;
        } else {
            printf("Block not available. You may try some other starting block.\n");
            files[i].start_block = -1;
            files[i].length = file_length;
        }
    }

    int choice = 1;
    while (choice) {
        printf("Enter 1 to search file & 0 to quit: ");
        scanf("%d", &choice);
        if (choice) {
            char file_name[20];
            printf("Enter the file name: ");
            scanf("%s", file_name);
            searchDetails(file_name, files, n);
        }
    }

    return 0;
}
