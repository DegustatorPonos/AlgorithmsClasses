#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/sort.h"
#define FILE_NAME "./inputs/lab4/book"

bool CanSplit(int *chapters, int len, int trgToms, int trgLen);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    // Reading inp
    int chapersAmm = ReadIntFromFile(fptr, FileSize);
    int *chapters = malloc(sizeof(int) * chapersAmm);
    for(int i = 0; i < chapersAmm; i++) {
         fscanf(fptr, "%d", &chapters[i]);
    }
    int toms;
    fscanf(fptr, "%d", &toms);
    QuickSort(chapters, 0, chapersAmm-1);
    int start = chapters[chapersAmm-1]; // max value
    while(true) {
        if(CanSplit(chapters, chapersAmm, toms, start)) {
            printf("%d\n", start);
            break;
        }
        start++;
    }

    free(buf);
    fclose(fptr);
    return 0;
}

bool CanSplit(int *chapters, int len, int trgToms, int trgLen) {
    int left = 0;
    int right = len-1;
    int toms = 0;
    while(left <= right) {
        int currentTomLen = 0;
        while (currentTomLen + chapters[right] <= trgLen && right >= left)  {
            currentTomLen += chapters[right];
            right--;
        }
        while (currentTomLen + chapters[left] <= trgLen && right >= left) {
            printf("Adding %d to %d\n", chapters[left], currentTomLen);
            currentTomLen += chapters[left];
            left++;
        }
        toms++;
    }
    return toms == trgToms;
}
