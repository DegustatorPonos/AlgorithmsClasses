#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/longop.h"

#define FILE_NAME "./inputs/lab1/LongSum"

int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize= GetFileSize(fptr);
    char *buf1 = malloc(sizeof(char) * FileSize);
    char *buf2 = malloc(sizeof(char) * FileSize);
    char *opSymbol = malloc(3); // op char + \n + 0l

    buf1 = fgets(buf1, FileSize, fptr);
    opSymbol = fgets(opSymbol, 3, fptr);
    buf2 = fgets(buf2, FileSize, fptr);


    long result = PerformPoeration(buf1, buf2, opSymbol[0]);
    printf("%ld\n", result);


    free(buf1);
    free(opSymbol);
    free(buf2);
    fclose(fptr);
}
