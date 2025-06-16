#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/combstr"
#define MAX_LEN 1000

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int amm = ReadIntFromFile(fptr, FileSize);
    char **inps = malloc(sizeof(char*) * amm);
    for(int i = 0; i < amm; i++) {
        inps[i] = malloc(sizeof(char) * MAX_LEN);
        inps[i] = fgets(inps[i], MAX_LEN, fptr);
        inps[i][strlen(inps[i]) - 1] = 0x0; // Removing \n char
    }

    qsort(inps, amm, sizeof(char*), compareStrings);
    for (int i = 0; i < amm; i++) {
        char *s = inps[i];
        int len = strlen(s);
        int found = 0;

        // Перебираем все возможные разбиения s = a + b
        for (int j = 1; j < len && !found; j++) {
            char a[1001], b[1001];
            strncpy(a, s, j);
            a[j] = '\0';
            strncpy(b, s + j, len - j);
            b[len - j] = '\0';

            // Проверяем, есть ли a и b в множестве (бинарный поиск)
            char *key = a;
            char **foundA = (char **)bsearch(&key, inps, amm, sizeof(char *), compareStrings);
            if (foundA) {
                key = b;
                char **foundB = (char **)bsearch(&key, inps, amm, sizeof(char *), compareStrings);
                if (foundB) {
                    found = 1;
                }
            }
        }

        if (found) {
            printf("%s\n", s);
        }
    }
    
    free(buf);
    fclose(fptr);
    return 0;
}
