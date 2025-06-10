#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/List.h"
#define FILE_NAME "./inputs/lab3/deck"

#define ERR_MSG "error\n"

void push_front(LIST *deck, int maxVal, int value) {
    if(deck->Length == maxVal - 1) {
        printf(ERR_MSG);
        return;
    }
    AppendToList(deck, value);
}

void push_back(LIST *deck, int maxVal, int value) {
    if(deck->Length == maxVal - 1) {
        printf(ERR_MSG);
        return;
    }
    InsertAt(deck, 0, value);
}

void pop_front(LIST *deck, int maxVal) {
    if(deck->Length == 0) {
        printf(ERR_MSG);
        return;
    }
    printf("%d\n", deck->array[deck->Length-1]);
    RemoveAt(deck, deck->Length - 1);
}

void pop_back(LIST *deck, int maxVal) {
    if(deck->Length == 0) {
        printf(ERR_MSG);
        return;
    }
    printf("%d\n", deck->array[0]);
    RemoveAt(deck, 0);
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    LIST *deck = ListInit();
    int Commands = ReadIntFromFile(fptr, FileSize);
    int MaxLength = ReadIntFromFile(fptr, FileSize);

    for(int i = 0; i < Commands; i++) {
        buf = fgets(buf, FileSize, fptr);
        char *parts = strtok(buf, " ");
        if(strcmp(parts, "push_front") == 0) {
            parts = strtok(NULL, "");
            push_front(deck, MaxLength, atoi(parts));
            continue;
        }
        if(strcmp(parts, "push_back") == 0) {
            parts = strtok(NULL, "");
            push_back(deck, MaxLength, atoi(parts));
            continue;
        }
        if(strcmp(buf, "pop_front\n") == 0) {
            pop_front(deck, MaxLength);
            continue;
        }
        if(strcmp(buf, "pop_back\n") == 0) {
            pop_back(deck, MaxLength);
            continue;
        }
    }

    ClearList(deck);
    free(deck);
    free(buf);
    fclose(fptr);
    return 0;
}
