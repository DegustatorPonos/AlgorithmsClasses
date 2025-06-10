#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/ips"

// fuck it we bubblesort

int main()
{

    bool sorted = false;
    int i = 0;
    char *currentFile = malloc(64);
    currentFile = FILE_NAME;
    char* fn = malloc(64);
    while(!sorted) {
        char *nextstr = malloc(sizeof(char) * 10000);
        char *basestr = malloc(sizeof(char) * 10000);
        sorted = true;
        sprintf(fn, "b%d.t", i);
        FILE *fprt = fopen(currentFile, "r");
        FILE *tfptr = fopen(fn, "w");
        basestr = fgets(basestr, 10000, fprt);
        while (true) {
            nextstr = fgets(nextstr, 10000, fprt);
            if(nextstr == NULL) {
                fputs(basestr, tfptr);
                break;
            }
            if(strcmp(basestr, nextstr) > 0) { // If the later string is smaller than the previous
                sorted = false;
                // printf("Swapping \n\n");
                fputs(nextstr, tfptr);
            } else { // the previous string is smaller as god intended
                fputs(basestr, tfptr);
                // printf("Leaving\n\n");
                strcpy(basestr, nextstr);
            }
        }
        fclose(fprt);
        fclose(tfptr);
        free(nextstr);
        free(basestr);
        currentFile = malloc(64);
        strcpy(currentFile, fn);
        i++;
    }
    return rename(currentFile, "result.txt");
}
