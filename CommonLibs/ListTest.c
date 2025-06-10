#include "List.h"
#include "sort.c"
#include <stdio.h>

void TestRingBuffers();

int main()
{
    TestRingBuffers();
    return 0;

    int initDataLength = 9;
    int initListData[] = {1, 9, 3, 52, 10, 7, 9, 12, 10};

    LIST *list = ListInit();
    for(int i = 0; i < initDataLength; i++)
        AppendToList(list, initListData[i]);
    printf("Unsorted: ");
    PrintListInfo(list);
    // SwapSort(list->array, list->Length);
    InsersionSort(list->array, list->Length);
    // QuickSort(list->array, 0, list->Length - 1);
    printf("Sorted: ");
    PrintListInfo(list);
    return 0;

    RemoveAt(list, 1);
    printf("Removed 2nd element: ");
    PrintListInfo(list);
    InsertAt(list, 1, 2);
    printf("Insterted 2nd element: ");
    PrintListInfo(list);
    MapSortedList(list);
    printf("Mapping: ");
    PrintListInfo(list);
    // printf("Pointer to %d\n", list->array);

    ClearList(list);
    // free(list);
    return 0;
}

void TestRingBuffers() {
    RING_BUFFER *rb = RingBufferInit(3);
    for(int i = 0; i < 4; i++)
        WriteInRingBuffer(rb, i, i);
    PrintRingBuffer(rb);
}
