#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/intersect"

typedef struct {
    int value;
    void *NextNode;
} QueueElement;

QueueElement *Insert(QueueElement *base, int value);
void PrintQueue(QueueElement *base);
QueueElement *Pop(QueueElement *base, int *outp);
int FindIntersection(QueueElement *a, QueueElement *b);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int x, y;
    fscanf(fptr, "%d %d", &x, &y);
    QueueElement **InputValues = malloc(sizeof(QueueElement*) * x);
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            int inp;
            fscanf(fptr, "%d ", &inp);
            InputValues[i] = Insert(InputValues[i], inp);
        }
    }

    int outp = 0;
    for(int a = 0; a < x; a++) {
        for(int b = a+1; b < x; b++) {
            if(a == b) continue;
            int res = FindIntersection(InputValues[a], InputValues[b]);
            if(res > outp) outp = res;
        }
    }

    printf("%d\n", outp);

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

int FindIntersection(QueueElement *a, QueueElement *b) {
    int out = 0;
    QueueElement *tempa = a;
    QueueElement *tempb = b;
    while(tempa != NULL) {
        while (tempb != NULL && tempb->value < tempa->value) {
            tempb = tempb->NextNode;
        }
        if(tempb == NULL) return out;
        if(tempb->value == tempa->value) out++;
        tempa = tempa->NextNode;
    }
    return out;
}
