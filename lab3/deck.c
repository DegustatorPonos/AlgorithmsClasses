#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/List.h"
#define FILE_NAME "./inputs/lab3/deck"

#define ERR_MSG "error\n"

void push_front(RING_BUFFER *deck, int maxVal, int value, int left, int right) {
    if(GetRingBufferIndex(deck, left) == GetRingBufferIndex(deck, right) && right != left)
        return;
    WriteInRingBuffer(deck, right, value);
}

void push_back(RING_BUFFER *deck, int maxVal, int value, int left, int right) {
    if(GetRingBufferIndex(deck, left) == GetRingBufferIndex(deck, right) && right != left)
        return;
    WriteInRingBuffer(deck, left, value);
}

void pop_front(RING_BUFFER *deck, int maxVal, int left, int right) {
    if(GetRingBufferIndex(deck, left) == GetRingBufferIndex(deck, right))
        return;
    printf("%d\n", GetFromRingBuffer(deck, right));
}

void pop_back(RING_BUFFER *deck, int maxVal, int left, int right) {
    if(GetRingBufferIndex(deck, left) == GetRingBufferIndex(deck, right))
        return;
    printf("%d\n", GetFromRingBuffer(deck, left));
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int Commands = ReadIntFromFile(fptr, FileSize);
    int MaxLength = ReadIntFromFile(fptr, FileSize);
    RING_BUFFER *deck = RingBufferInit(MaxLength);

    int rightBorder = 0;
    int leftBorder = -1;

    for(int i = 0; i < Commands; i++) {
        buf = fgets(buf, FileSize, fptr);
        char *parts = strtok(buf, " ");
        if(strcmp(parts, "push_front") == 0) {
            parts = strtok(NULL, "");
            push_front(deck, MaxLength, atoi(parts), leftBorder, rightBorder);
            rightBorder++;
            continue;
        }
        if(strcmp(parts, "push_back") == 0) {
            parts = strtok(NULL, "");
            push_back(deck, MaxLength, atoi(parts), leftBorder, rightBorder);
            leftBorder--;
            continue;
        }
        if(strcmp(buf, "pop_front\r\n") == 0) {
            pop_front(deck, MaxLength, leftBorder, rightBorder);
            rightBorder--;
            continue;
        }
        if(strcmp(buf, "pop_back\r\n") == 0) {
            leftBorder++; 
            pop_back(deck, MaxLength, leftBorder, rightBorder);
            continue;
        }
    }

    free(deck);
    free(buf);
    fclose(fptr);
    return 0;
}
