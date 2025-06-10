#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/ms"

typedef struct {
    uint64_t Rank;
    char *Name;
} Record;

void swapRecords(Record *array, int i, int j)
{
    uint64_t rankBuf = array[i].Rank;
    char *nameBuf = array[i].Name;
    array[i].Rank = array[j].Rank;
    array[i].Name = array[j].Name;
    array[j].Rank = rankBuf;
    array[j].Name = nameBuf;
}


void QuickSortRecords(Record* array, int start, int end)
{
    uint64_t pivot = array[start].Rank;
    // Partitioning
    int leftPos = start;
    int rightPos = end;
    while(leftPos <= rightPos)
    {
        while(array[leftPos].Rank < pivot)
            leftPos++;
        while(array[rightPos].Rank > pivot)
            rightPos--;
        if(leftPos <= rightPos)
        {
            swapRecords(array, rightPos, leftPos);
            leftPos++;
            rightPos--;
      }
    }
    // Recursion
    if(start < rightPos)
        QuickSortRecords(array, start, rightPos);
    if(leftPos < end)
        QuickSortRecords(array, leftPos, end);
}

void BubblesortNames(Record* array, int start, int end)
{
    if(end - start < 2)
        return;
    bool IsSorted = false;
    while(!IsSorted)
    {
        IsSorted = true;
        int index = start;
        if(index == end)
            continue;
        for(int i = start; i < end; i++)
        {
            if(strcmp(array[i].Name, array[i+1].Name) < 0)
            {
                swapRecords(array, i, i+1);
                IsSorted = false;
            }
        }
    }
}


void SortByNames(Record *array, int len) {
    if(len < 1)
        return;
    uint64_t prevScore = array[0].Rank;
    int start = 0;
    for(int i = 1; i < len; i++) {
        if(prevScore != array[i].Rank) {
            prevScore = array[i].Rank;
            BubblesortNames(array, start, i);
            start = i;
        }
    }
    BubblesortNames(array, start, len-1);
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int records = ReadIntFromFile(fptr, FileSize);
    Record *RecordList = malloc(sizeof(Record) * records);
    int paramsLen = ReadIntFromFile(fptr, FileSize);

    // Reading params weights
    int *weights = malloc(sizeof(int)* paramsLen);
    buf = fgets(buf, FileSize, fptr);
    char *weightInp = strtok(buf, " ");
    for(int i = 0; i < paramsLen; i++) {
        int param = (int)atoi(weightInp);
        weights[i] = param;
        weightInp = strtok(NULL, " ");
    }

    // Reading input
    ushort *ParamInp = malloc(sizeof(ushort) * paramsLen);
    for(int i = 0; i < records; i++) {
        buf = fgets(buf, FileSize, fptr);
        char *parts = strtok(buf, " ");
        RecordList[i].Name = malloc(strlen(parts) + 1);
        strcpy(RecordList[i].Name, parts);
        parts = strtok(NULL, " ");
        for(int j = 0; j < paramsLen; j++) {
            ParamInp[j] = (ushort)atoi(parts);
            parts = strtok(NULL, " ");
        }
        for(int j = 0; j < paramsLen; j++) {
            int weightInd = weights[j] - 1;
            // printf("Index %d - %d\n", weightInd, ParamInp[weightInd]);
            RecordList[i].Rank += (ParamInp[weightInd] & 0b1111) << (40 - (4 * j));
        }
    }

    QuickSortRecords(RecordList, 0, records - 1);
    SortByNames(RecordList, records);
    for(int i = records - 1; i >= 0; i--) {
        printf("%s \n", RecordList[i].Name);
    }

    free(buf);
    fclose(fptr);
    return 0;
}
