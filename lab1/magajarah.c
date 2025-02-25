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
    char X;
    char Y;
}Vector2;

typedef struct {
    int MapSize;
    int **Map;
    int discovededCombinationsAmmount;
    char **combinations;
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

void AddIfUnique(Map *inp, char x, char y)
{
    // Getting the "hashe"
    unsigned char *serialized = malloc(inp->MaxStackLength + 1);
    for(int i = 0; i < inp->MaxStackLength; i++)
    {
        serialized[i] = inp->CurrentStack[i]->Y + (inp->CurrentStack[i]->X << 4);
    }
    serialized[inp->MaxStackLength] = EOF;
    for(int i = 0; i < inp->discovededCombinationsAmmount; i++)
        if(strcmp((char*)serialized, inp->combinations[i]) == 0)
            return;
    inp->combinations[inp->discovededCombinationsAmmount] = (char*)serialized;
    inp->discovededCombinationsAmmount++;
}

void SolveForMap(Map *inp) 
{
    for(char x = 0; x < inp->MapSize; x++)
        for(char y = 0; y < inp->MapSize; y++)
        {
            if(inp->Map[x][y])
                continue;
            if(inp->CurrentStackLength == inp->MaxStackLength - 1)
            {
                inp->CurrentStack[inp->CurrentStackLength]->X = x;
                inp->CurrentStack[inp->CurrentStackLength]->Y = y;
                inp->CurrentStackLength++;
                AddIfUnique(inp, x, y);
                inp->CurrentStackLength--;
            }
            else
            {
                int i = inp->CurrentStackLength;
                inp->CurrentStack[i]->X = x;
                inp->CurrentStack[i]->Y = y;
                inp->CurrentStackLength++;
                // Recutsion
                RecalculateMap(inp);
                SolveForMap(inp);
                inp->CurrentStackLength--;
                RecalculateMap(inp);
            }
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
    mainMap->Map = malloc(sizeof(bool*) * size);
    for(int i = 0; i < size; i++)
        mainMap->Map[i] = malloc(sizeof(int) * size);
    mainMap->combinations = malloc(sizeof(char*) * 1024*1024);

    // Solving

    SolveForMap(mainMap);
    printf("hashe len: %d\n", mainMap->discovededCombinationsAmmount);
    PrintMap(mainMap);

    // I don't posess the willpower to free this abomination
    free(buff);
    fclose(fptr);
    return 0;
}
