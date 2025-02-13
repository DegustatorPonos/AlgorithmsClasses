#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./inputs/lab1/hands"


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
    int sum = 0;
    int file_size = GetFileSize(fptr);
    int maxAmmount;
    char* buf = malloc(file_size);
    int* numbersOnField = malloc(sizeof(int) * 10);
    int possibleSolutions = 0;
    buf = fgets(buf, file_size, fptr);
    maxAmmount = atoi(buf) * 2;
    char currentChar;
    while((currentChar = fgetc(fptr)) != EOF)
    {
            if(currentChar == '\n' || currentChar == ' ' || currentChar == '.')
                continue;
            int inpNum = (int)currentChar - '0';
            if(numbersOnField[inpNum] == 0)
                possibleSolutions++;
            numbersOnField[inpNum]++;
            if(numbersOnField[inpNum] == maxAmmount + 1)
                possibleSolutions--;
    }
    printf("Result: %d\n", possibleSolutions);
    free(buf);
    free(numbersOnField);
    fclose(fptr);
    return 0;
}
