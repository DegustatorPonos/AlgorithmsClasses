#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/eqs"

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
    for(int i = 0; i < records; i++) {
        buf = fgets(buf, FileSize, fptr);
        char *parts = strtok(buf, " ");
        RecordList[i].Name = malloc(strlen(parts) + 1);
        strcpy(RecordList[i].Name, parts);
        parts = strtok(NULL, " ");
        ushort solved = (ushort)atoi(parts);
        RecordList[i].Rank = solved;
        RecordList[i].Rank = RecordList[i].Rank << 32;
        parts = strtok(NULL, " ");
        ushort penalty = USHRT_MAX - (ushort)atoi(parts);
        RecordList[i].Rank += penalty;
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
