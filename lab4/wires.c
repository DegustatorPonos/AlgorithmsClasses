#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/wires"

int GetWiresCount(int *wires, int amm, int length);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int K, wiresCount;
    fscanf(fptr, "%d %d", &K, &wiresCount);
    int *wires = malloc(sizeof(int) * wiresCount);

    // Reading wires lengths
    int maxLen = 0;
    for(int i = 0; i < wiresCount; i++) {
        int inp;
        fscanf(fptr, "%d", &inp);
        if(inp > maxLen) maxLen = inp;
        wires[i] = inp;
    }
    
    // binary search
    int left = 0;
    int right = wiresCount - 1;
    int outp = 0;
    while(left <= right) {
        int mid = (left + right) / 2;
        int total = GetWiresCount(wires, wiresCount, K);
        if(total >= K) {
            outp = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", outp);
    free(buf);
    fclose(fptr);
    return 0;
}

int GetWiresCount(int *wires, int amm, int length) {
    int outp = 0;
    for(int i = 0; i < amm; i++)
        outp += wires[i]/length;
    return outp;
}
