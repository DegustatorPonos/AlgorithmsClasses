#include "List.c"
#include "sort.c"
#include <stdio.h>

int main()
{
    int initDataLength = 8;
    int initListData[] = {1, 2, 3 ,4, 1, 1, 2, 4};

    LIST *list = ListInit();
    for(int i = 0; i < initDataLength; i++)
        AppendToList(list, initListData[i]);
    printf("Unsorted: ");
    PrintListInfo(list);
    Bubblesort(list->array, list->Length);
    printf("Sorted: ");
    PrintListInfo(list);
    RemoveAt(list, 1);
    printf("Removed 2nd element: ");
    PrintListInfo(list);
    MapSortedList(list);
    printf("Mapping: ");
    PrintListInfo(list);
}
