#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/BitUtils.h"
#define FILE_NAME "./inputs/lab1/RopePulling"

// We create a matrix and then calculate every result
// Matrix - 1 if they know each other and 0 if they don't

bool GetRelationship(uint *relMatrix, int a, int b)
{
    return GetBitFromUInt(relMatrix[a], b);
}

void AddRelationship(uint *relMatrix, char *relationship)
{
    char *parts =  strtok(relationship, " ");
    int index = atoi(parts);
    parts =  strtok(NULL, " ");
    uint player2 = strtoul(parts, NULL, 10);
    printf("Adding a relationship to %d with %u\n", index, player2);
    relMatrix[index-1] += (1 << (player2-1));
  relMatrix[player2-1] += (1 << (index-1));
}

void PrintMatrix(uint *relMatrix, int size)
{
    printf("  ");
    for(int i = 0; i < size; i++)
        printf("%d", i+1);
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        printf("%d ", i+1);
        for(int j = 0; j < size; j++)
            printf("%d", GetBitFromUInt(relMatrix[i],j ));
        printf("\n");
    }
}

// Teturns if the ammount of 1s in the inp is equal to TeamSize
int *GetPlayersFromIndexes(int TeamSize, int playerAmmount, uint inp)
{
    int *outp = malloc(sizeof(int) * TeamSize);
    int AddedPlayers = 0;
    for(int i = 0; i < playerAmmount; i++)
    {
        if(GetBitFromUInt(inp, i))
        {
            printf("Detected 1 at %d;\n", i);
            if(AddedPlayers == TeamSize)
            {
                free(outp);
                return NULL;
            }
            outp[AddedPlayers] = i;
            AddedPlayers++;
        }
    }
    printf("Added %d players\n", AddedPlayers);
    if(AddedPlayers != TeamSize)
    {
        free(outp);
        return NULL;
    }
    return outp;
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int PlayerCount, TeamSize, Couples;
    buf = fgets(buf, FileSize, fptr);
    char *parts = strtok(buf, " ");
    PlayerCount = atoi(parts);
    parts = strtok(NULL, " ");
    TeamSize= atoi(parts);
    parts = strtok(NULL, " ");
    Couples = atoi(parts);

    // Each uint - does the player knows nth player
    uint *RelationshipMatrix = malloc(sizeof(uint) * PlayerCount);
    for(int i = 0; i < Couples; i++)
    {
        buf = fgets(buf, FileSize, fptr);
        AddRelationship(RelationshipMatrix, buf);
    }
    PrintMatrix(RelationshipMatrix, PlayerCount);

    printf("\nTEST\n");
    int *temp = GetPlayersFromIndexes(TeamSize, PlayerCount, 19);
    if(temp == NULL)
    {
        printf("Not enough 1s\n");
    }
    else {
        for(int i = 0; i < TeamSize; i++)
            printf("%d ", temp[i]);
        printf("\n");
    }

    free(buf);
    free(RelationshipMatrix);
    fclose(fptr);
    return 0;
}
