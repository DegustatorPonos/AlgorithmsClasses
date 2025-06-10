#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


LIST *ListInit()
{
    LIST *outp = malloc(sizeof(LIST));
    outp->array = malloc(sizeof(int));
    outp->Capacity=1;
    return outp;
}

// Frees the list array memory
void ClearList(LIST *list)
{
    free(list->array);
    list->Length = 0;
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

void PrintIntArray(int *array, int length, bool PrintBrackets)
{
    if(PrintBrackets)
        printf("{");
    for(int i = 0; i < length; i++)
    {
        if(i < length - 1)
            printf("%d, ", array[i]);
        else 
            printf("%d", array[i]);
    }
    if(PrintBrackets)
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
        list->Length = 0;
        return;
    }
    for(int i = position; i < list->Length - 1; i++)
    {
        *(list->array + i) = *(list->array + i + 1);
    }
    list->Length -= 1;
}

void InsertAt(LIST *list, int position, int toInsert)
{
    AppendToList(list, toInsert);
    if(position == list->Length-1)
        return;
    for(int i = list->Length-1; i > position; i--)
        *(list->array + i) = *(list->array + i - 1);
    *(list->array + position ) = toInsert;
}

void MapSortedList(LIST *list)
{
    if(list->Length <= 1)
        return;
    int PreviousValue = list->array[0];
    int i = 1;
    while(i < list->Length)
    {
        if(PreviousValue == list->array[i])
        {
            RemoveAt(list, i);
            continue;
        }
        PreviousValue = list->array[i];
        i++;
    }
}

void PrintListInfo(LIST *list)
{
    printf("Length: %d; Capacity: %d; Contents: ", list->Length, list->Capacity);
    PrintIntArray(list->array, list->Length, true);
}

// RING BUFFER

RING_BUFFER *RingBufferInit(int length) {
    RING_BUFFER *rb = malloc(sizeof(RING_BUFFER));
    rb->length = length;
    rb->buffer = malloc(sizeof(int) * length);
    return rb;
}

RING_BUFFER *RingBufferInitFromArray(int length, int *baseArray, bool UseExistingArray) {
    RING_BUFFER *rb = malloc(sizeof(RING_BUFFER));
    rb->length = length;
    if(UseExistingArray) {
        rb->buffer = baseArray;
    } else {
        rb->buffer = malloc(sizeof(int) * length);
        memcpy(rb->buffer, baseArray, sizeof(int) * length);
    }
    return rb;
}

int GetRingBufferIndex(RING_BUFFER *inp, int rawIndex) {
    if(rawIndex >= 0 && rawIndex < inp->length)
        return rawIndex;
    int InRangeByMod = rawIndex % inp->length;
    if(InRangeByMod >= 0)
        return InRangeByMod;
    return inp->length + InRangeByMod;
}

// Returns the value from ring buffer. 
// The index is not required to be in the borders of the array.
int GetFromRingBuffer(RING_BUFFER *inp, int position) {
    int InArrayIndex = GetRingBufferIndex(inp, position);
    return inp->buffer[InArrayIndex];
    printf("Requested value from %d\n", InArrayIndex);
}

// Writes the value in the ring buffer.
// The index is not required to be in the borders of the array.
void WriteInRingBuffer(RING_BUFFER *inp, int position, int value) {
    int InArrayIndex = GetRingBufferIndex(inp, position);
    inp->buffer[InArrayIndex] = value;
    // printf("Written %d in %d\n", value, InArrayIndex);
}

void PrintRingBuffer(RING_BUFFER *rb) {
    printf("[");
    for(int i = 0; i < rb->length; i++) {
        printf("%d", rb->buffer[i]);
        if(i != rb->length-1)
            printf(" ");
    }
    printf("] Length: %d\n", rb->length);
}
