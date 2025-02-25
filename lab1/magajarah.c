#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./inputs/lab1/Magajarah"

// Returns file size to assign to a buffer
int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

typedef struct {
    unsigned char X;
    unsigned char Y;
}Vector2;

typedef struct {
    int MapSize;
    int **Map;
    int discovededCombinationsAmmount;
    Vector2 **CurrentStack;
    int MaxStackLength;
    int CurrentStackLength;
} Map;

void ClearMap(Map *ToClear)
{
    for(int x = 0; x < ToClear->MapSize; x++)
        for(int y = 0; y < ToClear->MapSize; y++)
            ToClear->Map[x][y] = false;
}

bool IsInBounds(int x, int y, Map *map)
{
    if(x < 0 || x >= map->MapSize)
        return false;
    if(y < 0 || y >= map->MapSize)
        return false;
    return true;
}


// Places 
void RecalculateMap(Map *ToRecalculate)
{
    if(ToRecalculate == NULL || ToRecalculate->Map == NULL || ToRecalculate->CurrentStack == NULL)
    {
        printf("The ptr in NULL\n");
        return;
    }
    ClearMap(ToRecalculate);
    for(int i = 0; i < ToRecalculate->CurrentStackLength; i++)
    {    
        Vector2 *currentPos = ToRecalculate->CurrentStack[i];
        // Horizontal/vertical
        for(int x = 0; x < ToRecalculate->MapSize; x++)
            ToRecalculate->Map[x][currentPos->Y] = true;
        for(int y = 0; y < ToRecalculate->MapSize; y++)
            ToRecalculate->Map[currentPos->X][y] = true;
        // Horse
        if(IsInBounds(currentPos->X + 2,currentPos->Y + 1, ToRecalculate)) ToRecalculate->Map[currentPos->X + 2][currentPos->Y + 1] = true;
        if(IsInBounds(currentPos->X + 2,currentPos->Y - 1, ToRecalculate)) ToRecalculate->Map[currentPos->X + 2][currentPos->Y - 1] = true;
        if(IsInBounds(currentPos->X - 2,currentPos->Y + 1, ToRecalculate)) ToRecalculate->Map[currentPos->X - 2][currentPos->Y + 1] = true;
        if(IsInBounds(currentPos->X - 2,currentPos->Y - 1, ToRecalculate)) ToRecalculate->Map[currentPos->X - 2][currentPos->Y - 1] = true;
        if(IsInBounds(currentPos->X + 1,currentPos->Y + 2, ToRecalculate)) ToRecalculate->Map[currentPos->X + 1][currentPos->Y + 2] = true;
        if(IsInBounds(currentPos->X + 1,currentPos->Y - 2, ToRecalculate)) ToRecalculate->Map[currentPos->X + 1][currentPos->Y - 2] = true;
        if(IsInBounds(currentPos->X - 1,currentPos->Y + 2, ToRecalculate)) ToRecalculate->Map[currentPos->X - 1][currentPos->Y + 2] = true;
        if(IsInBounds(currentPos->X - 1,currentPos->Y - 2, ToRecalculate)) ToRecalculate->Map[currentPos->X - 1][currentPos->Y - 2] = true;
        // Diagonal
        bool flag = true;
        int delta = 1;
        while(flag)
        {
            flag = false;
            if(IsInBounds(currentPos->X - delta,currentPos->Y - delta, ToRecalculate))
            {
                flag = true;
                ToRecalculate->Map[currentPos->X - delta][currentPos->Y - delta] = true;
            }
            if(IsInBounds(currentPos->X + delta,currentPos->Y - delta, ToRecalculate))
            {
                flag = true;
                ToRecalculate->Map[currentPos->X + delta][currentPos->Y - delta] = true;
            }
            if(IsInBounds(currentPos->X - delta,currentPos->Y + delta, ToRecalculate))
            {
                flag = true;
                ToRecalculate->Map[currentPos->X - delta][currentPos->Y + delta] = true;
            }
            if(IsInBounds(currentPos->X + delta,currentPos->Y + delta, ToRecalculate))
            {
                flag = true;
                ToRecalculate->Map[currentPos->X + delta][currentPos->Y + delta] = true;
            }
            delta++;
        }
    }
}

void PrintMap(Map *inp)
{
    for(int x = 0; x < inp->MapSize; x++)
    {
        printf("%d ", x);
        for(int y = 0; y < inp->MapSize; y++)
        {
            if(inp->Map[x][y])
                printf("#");
            else
                printf("0");
        }
        printf("\n");
    }
}

void Bubblesort(unsigned short *array, int length)
{
    if(length < 2)
        return;
    bool IsSorted = false;
    while(!IsSorted)
    {
        IsSorted = true;
        int index = 0;
        if(index == length - 1)
            continue;
        for(int i = 0; i < length - 1; i++)
        {
            if(array[i] > array[i+ 1])
            {
                IsSorted = false;
                unsigned short buffer = array[i];
                array[i] = array[i+ 1];
                array[i+ 1] = buffer;
            }
        }
    }
}

void AddIfUnique(Map *inp)
{
    // inp->combinations[inp->discovededCombinationsAmmount] = (char*)serialized;
    inp->discovededCombinationsAmmount++;
    return;
}

bool CanPlaceHere(int x, int y, Map *inp)
{
    for(int i = 0; i < inp->CurrentStackLength; i++)
    {
        if(x == inp->CurrentStack[i]->X || y == inp->CurrentStack[i]->Y 
                || (x - y) == (inp->CurrentStack[i]->X - inp->CurrentStack[i]->Y)
                || (x + y) == (inp->CurrentStack[i]->X + inp->CurrentStack[i]->Y))
            return false;
        int dx = x - inp->CurrentStack[i]->X;
        if(dx < 0) dx *= -1;
        int dy = y - inp->CurrentStack[i]->Y;
        if(dy < 0) dy *= -1;
        if((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
            return false;
    }
    return true;
}

void SolveForMap(Map *inp, int start) 
{
    if(inp->CurrentStackLength == inp->MaxStackLength)
    {
        AddIfUnique(inp);
        return;
    }
    for(int i = start; i < inp->MapSize * inp->MapSize; i++)
    {
        int x = i / inp->MapSize;
        int y = i % inp->MapSize;
        if(!CanPlaceHere(x, y, inp))
            continue;
        int j = inp->CurrentStackLength;
        inp->CurrentStack[j]->X = x;
        inp->CurrentStack[j]->Y = y;
        inp->CurrentStackLength++;
        SolveForMap(inp, i+1);
        inp->CurrentStackLength--;
    }
}

int main() 
{
    FILE* fptr = fopen(FILE_NAME, "r");
    if(fptr == NULL)
    {
        printf("Error while opening the file\n");
        return 1;
    }
    int FileSize = GetFileSize(fptr);
    char *buff = malloc(FileSize);
    buff = fgets(buff, FileSize, fptr);
    char *parts = strtok(buff, " ");
    int size = atoi(parts);
    parts = strtok(NULL, " ");
    int ammount = atoi(parts);
    Map *mainMap = malloc(sizeof(Map));
    mainMap->MapSize = size;
    mainMap->MaxStackLength = ammount;
    mainMap->CurrentStack = malloc(sizeof(Vector2*));
    for(int i = 0; i < ammount; i++)
        mainMap->CurrentStack[i] = malloc(sizeof(Vector2));

    // Solving

    SolveForMap(mainMap, 0);
    printf("%d\n", mainMap->discovededCombinationsAmmount);
    // PrintMap(mainMap);

    // I don't posess the willpower to free this abomination
    free(buff);
    fclose(fptr);
    return 0;
}
