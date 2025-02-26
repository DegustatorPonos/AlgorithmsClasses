#include <stdio.h>
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
}
