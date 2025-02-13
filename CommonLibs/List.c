#include <array>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"


LIST *ListInit()
{
    LIST *outp = malloc(sizeof(LIST));
    outp->array = malloc(sizeof(int));
    return outp;
}

// Frees the list array memory
void ClearList(LIST *list)
{
    free(list->array);
}

void AppendToList(LIST *list, int toAdd)
{
    int newLength = list->Length + 1;
    if(newLength > list->Capacity)
        AddCapacityToList(list);
    list->array[list->Length] = toAdd;
    list->Length = newLength;
}

// Doubles the capacity of the list
void AddCapacityToList(LIST *list)
{
//    printf("Adding capacity\n");
    if(list->Capacity == 0)
        list->Capacity = 1;
    else
        list->Capacity *= 2;
    int *newArray = malloc(sizeof(int) * list->Capacity);
    // Copying the array
    for(int i = 0; i < list->Length; i++)
    {
        // UNSAFE BUT FUN
        *(newArray + i) = *(list->array + i);
    }
    free(list->array);
    list->array = newArray;
}

// TEMP
void PrintIntArray(int *array, int length)
{
    printf("{");
    for(int i = 0; i < length; i++)
    {
        if(i < length - 1)
            printf("%d, ", array[i]);
        else 
            printf("%d", array[i]);
    }
    printf("}\n");
}

void RemoveAt(LIST *list, int position)
{
    if(position >= list->Length)
        return;
    if(list->Length == 1)
    {
        free(list->array);
        list->array = malloc(sizeof(int));
        return;
    }
    for(int i = position; i < list->Length - 1; i++)
    {
        *(list->array + i) = *(list->array + i + 1);
    }
    list->Length -= 1;
}

void PrintListInfo(LIST *list)
{
    printf("Length: %d; Capacity: %d; Contents: ", list->Length, list->Capacity);
    PrintIntArray(list->array, list->Length);
}
