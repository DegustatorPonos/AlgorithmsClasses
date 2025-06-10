#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/sort.h"
#define FILE_NAME "./inputs/lab2/topthree"

int Solution(int *inp, int len);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int len = ReadIntFromFile(fptr, FileSize);
    int *inps = malloc(sizeof(int) * len);
    for(int i = 0; i < len; i++) {
        inps[i] = ReadIntFromFile(fptr, FileSize);
    }
    printf("%d\n", Solution(inps, len));
    free(buf);
    free(inps);
    fclose(fptr);
    return 0;
}

int Solution(int *inp, int len) {
    QuickSort(inp, 0, len);
    int opt1 = inp[len-1] * inp[len-2] * inp[len-3];
    int opt2 = inp[0] * inp[1] * inp[len-1];
    if(opt1 > opt2) {
        return opt1;
    } else {
        return opt2;
    }
}
