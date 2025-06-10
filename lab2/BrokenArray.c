#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/BrokenArray"

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int ArrayLen = ReadIntFromFile(fptr, FileSize);
    int trg = ReadIntFromFile(fptr, FileSize);
    int *arr = malloc(sizeof(int) * ArrayLen);
    buf = fgets(buf, FileSize, fptr);
    char *parts = strtok(buf, " ");
    for(int i = 0; i < ArrayLen; i++) {
        arr[i] = atoi(parts);
        parts = strtok(NULL, " ");
    }


    int index = 1;
    if(trg >= arr[0]) {
        int i = 0;
        int prevValue = arr[i];
        while(i < ArrayLen && arr[i] >= prevValue) {
            if(arr[i] == trg) {
                index = i;
                break;
            }
            i++;
        }
    } else {
      int i = ArrayLen - 1;
        int prevValue = arr[i];
        while(i > 0 && arr[i] <= prevValue) {
            if(arr[i] == trg) {
                index = i;
                break;
            }
          i--;
        }
    }

    printf("%d\n", index);


    free(buf);
    fclose(fptr);
    return 0;
}
