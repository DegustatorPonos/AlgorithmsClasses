#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "../CommonCFiles/List.h"
#include "../CommonCFiles/sort.h"
#define FILE_NAME "SymmDiffInp"

LIST *GetArrayUntilZero(char *input, const char* separator);

int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    if(fptr == NULL)
    {
        printf("Error while opening the file\n");
        return 1;
    }
    int FileSize = GetFileSize(fptr);
    char *buff = malloc(FileSize);
    if(fgets(buff, FileSize, fptr) == NULL)
    {
        printf("Error while reading the file\n");
        return 1;
    }
    char *parts = strtok(buff, " ");
    
    // Filling up and sorting the first array
    LIST *List1 = GetArrayUntilZero(parts, " ");
    Bubblesort(List1->array, List1->Length);
    // Filling up and sorting the second array
    LIST *List2 = GetArrayUntilZero(parts, " ");
    Bubblesort(List2->array, List2->Length);
    printf("\nDone");


    free(buff);
    ClearList(List1);
    free(List1);
    ClearList(List2);
    free(List2);
    fclose(fptr);
    return 0;
}

LIST *GetArrayUntilZero(char *input, const char* separator)
{
    LIST *outpList = ListInit();
    while(strcmp(input, "0"))
    {
        int part = atoi(input);
        AppendToList(outpList, part);
        input = strtok(NULL, separator);
    }
    return outpList;
}
