#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab_/"

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);


    free(buf);
    fclose(fptr);
    return 0;
}
