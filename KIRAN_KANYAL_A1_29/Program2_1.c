// Write a program to open a directory and list its contents. (use opendir(), readdir(), closedir() )

#include <stdio.h>
#include <dirent.h>

int main()
{
    DIR *dir;
    struct dirent *dirEntry;

    dir = opendir(".");
    if (dir)
    {
        printf("Contents of directory:\n");
        while ((dirEntry = readdir(dir)) != NULL)
        {
            printf("%s\n", dirEntry->d_name);
        }
        closedir(dir);
    }
    else
    {
        perror("opendir");
    }
    return 0;
}
