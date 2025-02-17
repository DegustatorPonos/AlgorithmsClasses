#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#define FILE_NAME "./inputs/lab1/ClosestZero"


void ClaculateDistance(int* street, int len);

// Returns file size to assign to a buffer
int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int main()
{
    FILE* fptr = fopen(FILE_NAME, "r");
    if(fptr == NULL)
    {
        printf("Error while opening the file\n");
        return 1;
    }

    int stage = 0;
    int sum = 0;
    int file_size = GetFileSize(fptr);
    int streetLength;
    int index = 0;
    char* buf = malloc(file_size);
    int* street;

    // This is not a right way to read the file; the method will be changed later
    while((buf = fgets(buf, file_size, fptr)) != NULL)
    {
        if(stage == 0)
        {
            street = malloc(sizeof(int) * atoi(buf));
            streetLength = atoi(buf);
            stage = 1;
            continue;
        }

        char* parts = strtok(buf, " ");
        while(parts != NULL)
        {
            if(index < streetLength)
            {
                int res = atoi(parts);
                street[index] = res;
            }
            index++;
            parts = strtok(NULL, " ");
        }
        free(parts);
    }

    ClaculateDistance(street, streetLength);
    for(int i = 0; i < streetLength; i++)
    {
        printf("%d", street[i]);
        if(i != streetLength - 1)
            printf(" ");
    }
    printf("\n");
    free(buf);
    free(street);
    fclose(fptr);
    return 0;
}

void FillUntilTheStart(int *street, int FirstZeroPosition)
{
    if(FirstZeroPosition < 2)
        return;
    int distance = 1;
    for(int i = FirstZeroPosition - 1; i >= 0; i--)
    {
        street[i] = distance;
        distance++;
    }
}

void ClaculateDistance(int* street, int len)
{
    int distance = 0;
    bool IsFirstZero = true;
    for(int i = 0; i < len; i++)
    {
        if(street[i] == 0)
        {
            if(i < 0)
                continue;
            if(IsFirstZero)
            {
                FillUntilTheStart(street, i);
                IsFirstZero = false;
                distance = 0;
                continue;
            }
            int reverceIndex = i - 1;
            int val = 1;
            while(street[reverceIndex] >= val && reverceIndex >= 0)
            {
                street[reverceIndex] = val;
                val++;
                reverceIndex--;
            }
            street[i] = 0;
            distance = 0;
            continue;
        }
        distance++;
        street[i] = distance;
    }
}
