#include "List.c"
#include "sort.c"
#include <stdio.h>

int main()
{
    int initDataLength = 9;
    int initListData[] = {1, 9, 3, 52, 10, 7, 9, 12, 10};

    LIST *list = ListInit();
    for(int i = 0; i < initDataLength; i++)
        AppendToList(list, initListData[i]);
    printf("Unsorted: ");
    PrintListInfo(list);
    QuickSort(list->array, 0, list->Length - 1);
    printf("Sorted: ");
    PrintListInfo(list);
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
