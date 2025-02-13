#include "List.c"
#include "sort.c"
#include <stdio.h>

int main()
{
    int initDataLength = 9;
    int initListData[] = {1, 9, 3 ,4, 1, 7, 9, 12, 11};

    LIST *list = ListInit();
    for(int i = 0; i < initDataLength; i++)
        AppendToList(list, initListData[i]);
    printf("Unsorted: ");
    PrintListInfo(list);
    QuickSort(list->array, list->Length);
    printf("Sorted: ");
    PrintListInfo(list);
    // RemoveAt(list, 1);
    // printf("Removed 2nd element: ");
    // PrintListInfo(list);
    // MapSortedList(list);
    // printf("Mapping: ");
    // PrintListInfo(list);
    ClearList(list);
    free(list);
    return 0;
}
