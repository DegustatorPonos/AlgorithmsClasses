#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/List.h"
#define FILE_NAME "./inputs/lab3/queue"
#define MAX_ELEMENTS 106

typedef struct{
    RING_BUFFER *rb;
    int rightPosition;
    int leftPosition;
} Queue;

int FindMin(Queue *q);
void Enqueue(Queue *q, int value);
int Dequeue(Queue *q);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    Queue *queue = malloc(sizeof(Queue));
    queue->rb = RingBufferInit(MAX_ELEMENTS);

    while((buf = fgets(buf, FileSize, fptr)) != NULL) {
        switch (buf[0]) {
            case '+':
                int value;
                sscanf(buf, "+ %d", &value);
                Enqueue(queue, value);
                break;
            case '-':
                printf("%d\n", Dequeue(queue));
                break;
            case '?':
                printf("%d\n", FindMin(queue));
                break;
        }
    }

    free(buf);
    fclose(fptr);
    return 0;
}

int FindMin(Queue *q) {
    int min = GetFromRingBuffer(q->rb, q->leftPosition);
    for(int i = q->leftPosition + 1; i < q->rightPosition; i++) {
        if(GetFromRingBuffer(q->rb, i) < min) {
            min = GetFromRingBuffer(q->rb, i);
        }
    }
    return min;
}

void Enqueue(Queue *q, int value) {
    WriteInRingBuffer(q->rb, q->rightPosition, value);
    q->rightPosition++;
}

int Dequeue(Queue *q) {
    int outp = GetFromRingBuffer(q->rb, q->leftPosition);
    q->leftPosition++;
    return outp;
}
