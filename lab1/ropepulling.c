#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/BitUtils.h"
#define FILE_NAME "./inputs/lab1/RopePulling"

// We create a matrix and then calculate every result
// Matrix - 1 if they know each other and 0 if they don't

bool GetRelationship(uint *relMatrix, int a, int b)
{
    return GetBitFromUInt(relMatrix[a], b);
}

uint GetPowerOfTwo(int power)
{
    uint outp = 1;
    for(int i = 0; i < power; i++)
    {
         outp *=2;
    }
    return outp;
}

void AddRelationship(uint *relMatrix, char *relationship)
{
    char *parts =  strtok(relationship, " ");
    int index = atoi(parts);
    parts =  strtok(NULL, " ");
    uint player2 = strtoul(parts, NULL, 10);
    printf("Adding a relationship to %d with %u\n", index, player2);
    relMatrix[index] += (1 << (player2));
    relMatrix[player2] += (1 << (index));
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
            if(AddedPlayers == TeamSize)
            {
                free(outp);
                return NULL;
            }
            outp[AddedPlayers] = i + 1;
            AddedPlayers++;
        }
    }
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

    uint CombinationsAmmount = GetPowerOfTwo(PlayerCount);
    uint CombinationsStart = 0;
    uint outp = 0;
    uint MaxRelationshipAmmount = 0;
    for(uint i = CombinationsStart; i < CombinationsAmmount; i++)
    {
        int *Players = GetPlayersFromIndexes(TeamSize, PlayerCount, i);
        if(Players == NULL)
        {
            free(Players);
            continue;
        }
        printf("%d =========================\n", i);
        int CurrentTeamRel = 0;
        for(int pa = 0; pa < TeamSize; pa++)
            for(int pb = pa; pb < TeamSize; pb++)
            {
                // printf("Checking the relationship between %d and %d;\n", pa, pb);
                if(GetRelationship(RelationshipMatrix, Players[pa], Players[pb]))
                {
                    printf("Relationship %d and %d;\n", Players[pa], Players[pb]);
                    CurrentTeamRel++;
                }
            }
        if(CurrentTeamRel > MaxRelationshipAmmount)
        {
            printf("New team! \n");
            MaxRelationshipAmmount = CurrentTeamRel;
            outp = i;
        }
        free(Players);
    }


    int *Players = GetPlayersFromIndexes(TeamSize, PlayerCount, outp);
    for(int i= 0; i< TeamSize; i++)
    {
        printf("%d ", Players[i]);
    }
    printf("\n");
    PrintMatrix(RelationshipMatrix, PlayerCount);
    free(buf);
    free(RelationshipMatrix);
    free(Players);
    fclose(fptr);
    return 0;
}
