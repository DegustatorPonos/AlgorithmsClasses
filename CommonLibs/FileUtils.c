#include <stdlib.h>
#include <stdio.h>
#include "FileUtils.h"

long GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    long outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int ReadIntFromFile(FILE *fptr, long BufSize)
{
    char *buff = malloc(BufSize);
    buff = fgets(buff, BufSize, fptr);
    int outp = atoi(buff);
    free(buff);
    return outp;
}
