#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/List.h"
#include "../CommonLibs/sort.h"
#define FILE_NAME "./inputs/lab1/SymDiff"

LIST *GetArrayUntilZero(char *input, const char* separator);
LIST *GetCommonElements(LIST *FirstList, LIST *SecondList);


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
    MapSortedList(List1);
    // PrintListInfo(List1);

    // Filling up and sorting the second array
    LIST *List2 = GetArrayUntilZero(parts, " ");
    Bubblesort(List2->array, List2->Length);
    MapSortedList(List2);
    // PrintListInfo(List2);

    LIST *result = GetCommonElements(List1, List2);
    // PrintListInfo(result);

    if(result->Length == 0)
        printf("0");
    else
    {
        for(int i = 0; i < result->Length; i++)
        {
            printf("%d ", result->array[i]);
        }
    }
    printf("\n");


    free(buff);
    ClearList(List1);
    free(List1);
    ClearList(List2);
    free(List2);
    ClearList(result);
    free(result);
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

// Lists should be mapped and sorted
LIST *GetCommonElements(LIST *FirstList, LIST *SecondList)
{
    LIST *outpList = ListInit();
    if(FirstList->Length == 0 || SecondList->Length == 0)
        return outpList;
    int SecondListIndex = 0;
    for(int FirstArrayIndex = 0; FirstArrayIndex < FirstList->Length; FirstArrayIndex++)
    {
        if(FirstArrayIndex > SecondList->Length - 1)
        {
            AppendToList(outpList, FirstList->array[FirstArrayIndex]);
            continue;
        }
        int toCompare = FirstList->array[FirstArrayIndex];

        if(SecondList->array[SecondListIndex] != toCompare && SecondList->array[SecondListIndex+1] != toCompare )
            AppendToList(outpList, toCompare);

        while(SecondList->array[SecondListIndex] <= toCompare && SecondListIndex < SecondList->Length)
        {
            if(SecondList->array[SecondListIndex] != toCompare)
                AppendToList(outpList, SecondList->array[SecondListIndex]);
            SecondListIndex++;
        }
    }
    for(int i = SecondListIndex; i < SecondList->Length; i++)
    {
        AppendToList(outpList, SecondList->array[i]);
    }
    return outpList;
}
