#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/guards"

typedef struct {
    int Start;
    int End;
} Span;


void swapRecords(Span *array, int i, int j)
{
    int Start= array[i].Start;
    int End = array[i].End;
    array[i].Start = array[j].Start;
    array[i].End = array[j].End;
    array[j].Start = Start;
    array[j].End = End;
}


void QuickSortRecords(Span* array, int start, int end)
{
    int pivot = array[start].Start;
    // Partitioning
    int leftPos = start;
    int rightPos = end;
    while(leftPos <= rightPos)
    {
        while(array[leftPos].Start < pivot)
            leftPos++;
        while(array[rightPos].Start > pivot)
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

bool isSafe(char *inp);
bool TryToExclude(Span* periods, int guards, int toExclude);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int iter = ReadIntFromFile(fptr, FileSize);
    for(int i = 0; i < iter; i++) {
        buf = fgets(buf, FileSize, fptr);
        printf(isSafe(buf) ? "Accepted" : "Wrong Answer");
        printf("\n");
    }
    free(buf);
    fclose(fptr);
    return 0;
}

bool isSafe(char *inp) {
    char *parts = strtok(inp, " ");
    int guards = atoi(parts);
    parts = strtok(NULL, " ");
    Span *periods = malloc(sizeof(Span) * guards);
    for(int i = 0; i < guards; i++) {
        periods[i].Start = atoi(parts);
        parts = strtok(NULL, " ");
        periods[i].End = atoi(parts);
        parts = strtok(NULL, " ");
    }
    QuickSortRecords(periods, 0, guards - 1);
    for(int i = 0; i < guards; i++) 
        if(TryToExclude(periods, guards, i))
            return false;
    return true;
}

bool TryToExclude(Span* periods, int guards, int toExclude) {
    if(periods[0].Start != 0)
        return false;
    int endTime = 0;
    for(int i = 0; i < guards; i++) {
        if(i == toExclude) continue;
        if(periods[i].Start > endTime)
            return false;
        if(periods[i].End > endTime) endTime = periods[i].End;
    }
    if(endTime < 10000) return false;
    return true;
}
