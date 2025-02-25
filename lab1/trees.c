#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./inputs/lab1/Trees"

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
    int FileSize = GetFileSize(fptr);
    char *buff = malloc(FileSize);
    buff = fgets(buff, FileSize, fptr);
    char *parts = strtok(buff, " ");
    int length = atoi(parts);
    parts = strtok(NULL, " ");
    int trees = atoi(parts);

    int result = 0;
    int distance = 0;
    while(trees + (trees-1)*distance <= length)
    {
        int PathDistance = trees + (trees-1)*distance;
        result += 1 + length - PathDistance;
        distance++;
    }
    printf("%d\n", result);


    free(buff);
    fclose(fptr);
    return 0;
}

