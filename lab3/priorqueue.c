#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab3/priorities"

typedef struct {
    uint ID;
    int value;
    void *NextNode;
} QueueElement;

uint GLOBAL_INDEX = 0;

QueueElement *Enqueue(QueueElement *base, int value, int *newId);
void printQueue(QueueElement *base);
int FindSmallest(QueueElement *base);
QueueElement *DeleteSmallest(QueueElement *base, int smallest);
void ReplaceValue(QueueElement *base, uint id, int value);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int ops = ReadIntFromFile(fptr, FileSize);
    QueueElement *q = NULL;

    int *OperationID = malloc(sizeof(int) * ops);
    int op = 0;
    while((buf = fgets(buf, FileSize, fptr)) != NULL) {
        switch (buf[0]) {
            case 'A':
                int value;
                sscanf(buf, "A %d", &value);
                q = Enqueue(q, value, &OperationID[op]);
                break;
            case 'X':
                int smallest = FindSmallest(q);
                q = DeleteSmallest(q, smallest);
                printf("%d\n", smallest);
                break;
            case 'D':
                int a, b;
                sscanf(buf, "D %d %d", &a, &b);
                printf("Replacing node w/ ID %d\n", OperationID[a]);
                ReplaceValue(q, OperationID[a], b);
                break;
        }
        op++;
    }

    free(buf);
    fclose(fptr);
    return 0;
}

QueueElement *Enqueue(QueueElement *base, int value, int *newId) {
    if(base == NULL) {
        QueueElement *new = malloc(sizeof(QueueElement));
        new->ID = GLOBAL_INDEX;
        *newId = GLOBAL_INDEX;
        GLOBAL_INDEX++;
        new->value = value;
        return new;
    }
    base->NextNode = Enqueue(base->NextNode, value, newId);
    return base;
}

void printQueue(QueueElement *base) {
    if(base == NULL) {
        printf("\n");
        return;
    }
    printf("%d(%d) ", base->value, base->ID);
    printQueue(base->NextNode);
}

QueueElement *DeleteSmallest(QueueElement *base, int smallest) {
    if(base == NULL) return NULL;
    if (base->value == smallest) {
        QueueElement *buf = base->NextNode;
        free(base);
        return buf;
    }
    base->NextNode = DeleteSmallest(base->NextNode, smallest);
    return base;
}

int FindSmallest(QueueElement *base) {
    if(base == NULL) return 10000; // Bigger than allowed, 100% not the smallest
    int nextValues = FindSmallest(base->NextNode);
    return base->value < nextValues? base->value : nextValues;
}

void ReplaceValue(QueueElement *base, uint id, int value) {
    if(base == NULL) return;
    if(base->ID == id ) {
        base->value = value;
        return;
    }
    ReplaceValue(base->NextNode, id, value);
}
