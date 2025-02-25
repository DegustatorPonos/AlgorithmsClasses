#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./inputs/lab1/TwoHeaps"


/*
   The fastets to make idea is to go through every possible combination and to
   find the smallest output
*/

int GetSum(int *heap, uint length, uint mask);
int GetLowestSum(int *heap, uint length);

// Returns file size to assign to a buffer
int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int main()
{
    // Reading the input
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buffer = malloc(FileSize);
    buffer = fgets(buffer, FileSize, fptr);
    int heapLength = atoi(buffer);
    int *heap = malloc(sizeof(int) * heapLength);
    buffer = fgets(buffer, FileSize, fptr);
    char *parts = strtok(buffer, " ");
    for(int i = 0; i < heapLength; i++)
    {
        heap[i] = atoi(parts);
        parts = strtok(NULL, " ");
    }

    int result = GetLowestSum(heap, heapLength);
    printf("%d\n", result);

    // Free
    if(parts != NULL)
        free(parts);
    free(buffer);
    fclose(fptr);

    return 0;
}

int GetSum(int *heap, uint length, uint mask)
{
    int sum = 0;
    for(int i = 0; i < length; i++)
    {
        if((mask >> i) & 1)
            sum += heap[i];
        else 
            sum -= heap[i];
    }

    if(sum < 0)
        sum *= -1;
    return sum;
}

uint PowerOfTwo(uint pow)
{
    uint res = 2;
    for(uint i = 1; i < pow; i++)
        res *= 2;
    return res;
}

int GetLowestSum(int *heap, uint length)
{
    int lowestSum = -1;
    uint mask = 0;
    uint maskLimit = PowerOfTwo(length);
    while(mask <= maskLimit)
    {
        int res = GetSum(heap, length, mask);
        if(res < lowestSum || lowestSum == -1)
            lowestSum = res;
        mask++;
    }
    return lowestSum;
}

