#include <stdbool.h>

typedef struct{
    int *array;
    int Capacity;
    int Length;
} LIST;

LIST *ListInit();
void ClearList(LIST *list);
void AppendToList(LIST *list, int toAdd);
void AddCapacityToList(LIST *list);
void PrintListInfo(LIST *list);
void InsertAt(LIST *list, int position, int toInsert);
void RemoveAt(LIST *list, int position);
void MapSortedList(LIST *list);
void PrintIntArray(int *array, int length, bool PrintBrackets);
