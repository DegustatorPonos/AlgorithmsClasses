#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/List.h"

#define FILE_NAME "./inputs/lab1/DuoArrays"

int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int *ReadArray(FILE *fptr, int fileSize, int length)
{
    int *returnArray = malloc(sizeof(int) * length);
    char *buffer = malloc(sizeof(char) * fileSize);
    for(int i = 0; i < length; i++)
    {
        buffer = fgets(buffer, fileSize, fptr);
        if(buffer == NULL)
            return returnArray;
        returnArray[i] = atoi(buffer);
    }
    free(buffer);
    return returnArray;
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    
    // Getting the sizes of the arrays
    char *buf = malloc(sizeof(char) * FileSize);
    buf = fgets(buf, FileSize, fptr);
    char *parts = strtok(buf, " ");
    int FirstArraySize = atoi(parts);
    parts = strtok(NULL, " ");
    int SecondArraySize = atoi(parts);
    parts = strtok(NULL, " ");
    free(parts);
    free(buf);
    // printf("%d and %d\n", FirstArraySize, SecondArraySize);
    
    int *array1 = ReadArray(fptr, FileSize, FirstArraySize);
    int *array2 = ReadArray(fptr, FileSize, SecondArraySize);
    // LIST *outpList = ListInit(); // Debug
    int outp = 0;

    int pos2 = 0;
    for(int pos1 = 0; pos1 < FirstArraySize; pos1++)
    {
        while(pos2 < SecondArraySize && array2[pos2] < array1[pos1])
            pos2++;
        if(pos2 == SecondArraySize)
            break;
        if(array1[pos1] == array2[pos2])
        {
            // AppendToList(outpList, array1[pos1]);
            outp++;
            pos2++;
            continue;
        }
    }
    printf("%d\n", outp);

    // ClearList(outpList);
    // free(outpList);
    free(array1);
    free(array2);
    fclose(fptr);
}
