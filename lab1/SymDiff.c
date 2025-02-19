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
    QuickSort(List1->array, 0, List1->Length - 1);
    MapSortedList(List1);
    // PrintListInfo(List1);

    // Filling up and sorting the second array
    LIST *List2 = GetArrayUntilZero(parts, " ");
    QuickSort(List2->array, 0, List2->Length - 1);
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
    while(input != NULL && strcmp(input, "0") != 0)
    {
        int part = atoi(input);
        if(part != 0)
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
    // Iterating over the first array
    for(int FirstArrayIndex = 0; FirstArrayIndex < FirstList->Length; FirstArrayIndex++)
    {
        // If the second array is smaller than the first
        if(FirstArrayIndex > SecondList->Length - 1)
        {
            AppendToList(outpList, FirstList->array[FirstArrayIndex]);
            continue;
        }

        int toCompare = FirstList->array[FirstArrayIndex];
        // If the next element is still bigger than the one in the first array
        // => there is no such element in the 2nd array
        if(SecondList->array[SecondListIndex] > toCompare)
        {
            AppendToList(outpList, toCompare);
            continue;
        }

        // Iterating through second array. Since they are sorted and mapped, if the element is greater than
        // the one in the second it cannot be before the lesser one
        while(SecondList->array[SecondListIndex] <= toCompare && SecondListIndex < SecondList->Length)
        {
            if(SecondList->array[SecondListIndex] != toCompare)
                AppendToList(outpList, SecondList->array[SecondListIndex]);
            SecondListIndex++;
        }
    }

    // If the first array is smaller than the second
    for(int i = SecondListIndex; i < SecondList->Length; i++)
    {
        AppendToList(outpList, SecondList->array[i]);
    }
    return outpList;
}
