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
void RemoveAt(LIST *list, int position);
