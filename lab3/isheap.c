#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab3/isheap"

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int n = ReadIntFromFile(fptr, FileSize);
    int *a = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++) {
        a[i] = ReadIntFromFile(fptr, FileSize);
    }
    for(int i = 1; i <= n/2+1; i++) {
        if(2*i <= n && a[i-1]>a[2*i-1]) {
            printf("NO\n");
            return 0;
        }
        if(2*i+1 <= n && a[i-1]>a[2*i]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    free(buf);
    fclose(fptr);
    return 0;
}
