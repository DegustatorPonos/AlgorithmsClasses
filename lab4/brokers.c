#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/brokers"

typedef struct {
    int value;
    void *NextNode;
} QueueElement;

QueueElement *Insert(QueueElement *base, int value);
void PrintQueue(QueueElement *base);
QueueElement *Pop(QueueElement *base, int *outp);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    QueueElement *queue;
    int inpAmm = ReadIntFromFile(fptr, FileSize);
    int *inps = malloc(sizeof(int) * inpAmm);
    for(int i = 0; i < inpAmm; i++) {
        queue = Insert(queue, ReadIntFromFile(fptr, FileSize));
    }

    double outp = 0.0;
    while(queue->NextNode != NULL) {
        int a, b;
        queue = Pop(queue, &a);
        queue = Pop(queue, &b);
        outp += (double)(a + b) * 0.01;
        queue = Insert(queue, a+b);
    }
    printf("%.2f\n", outp);
    free(buf);
    fclose(fptr);
    return 0;
}

// Smallest element first, autosort 
QueueElement *Insert(QueueElement *base, int value) {
    if(base == NULL || base->value > value) {
        QueueElement *new = malloc(sizeof(QueueElement));
        new->NextNode = base;
        new->value = value;
        return new;
    }
    base->NextNode = Insert(base->NextNode, value);
    return base;
}

QueueElement *Pop(QueueElement *base, int *outp) {
    *outp = base->value;
    return base->NextNode;
}
void PrintQueue(QueueElement *base) {
    if(base == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", base->value);
    PrintQueue(base->NextNode);
}
