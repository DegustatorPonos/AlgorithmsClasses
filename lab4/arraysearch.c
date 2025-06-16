#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/arrays"

typedef struct {
    void **ChildrenNodes;
    int childrenCount;
    unsigned long value;
} TreeNode;

void swap(unsigned long *array, unsigned long i, unsigned long j)
{
    int buf = array[i];
    array[i] = array[j];
    array[j] = buf;
}

void QuickSort(unsigned long* array, int start, int end)
{
    int pivot = array[start];
    // Partitioning
    int leftPos = start;
    int rightPos = end;
    while(leftPos <= rightPos)
    {
        while(array[leftPos] < pivot)
            leftPos++;
        while(array[rightPos] > pivot)
            rightPos--;
        if(leftPos <= rightPos)
        {
            swap(array, rightPos, leftPos);
            leftPos++;
            rightPos--;
      }
    }
    // Recursion
    if(start < rightPos)
        QuickSort(array, start, rightPos);
    if(leftPos < end)
        QuickSort(array, leftPos, end);
}

int ChildIndex(TreeNode *base, unsigned long value);
void AppendListToTree(TreeNode *base, unsigned long *array, int len, int index, int childrenMax);
bool ContainsArray(TreeNode *base, unsigned long *array, int len, int index);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int keys, len, seqs;
    fscanf(fptr, "%d %d %d", &keys, &len, &seqs);

    TreeNode *base = malloc(sizeof(TreeNode));
    base->ChildrenNodes = malloc(sizeof(TreeNode*) * keys);
    unsigned long *inps = malloc(sizeof(unsigned long) * len);
    for(int i = 0; i < keys; i++) {
        for(int j = 0; j < len; j++) {
            fscanf(fptr, "%lu", &inps[j]);
        }
        QuickSort(inps, 0, len-1);
        AppendListToTree(base, inps, len, 0, keys);
    }

    for(int i = 0; i < seqs; i++) {
        for(int j = 0; j < len; j++) {
            fscanf(fptr, "%lu", &inps[j]);
        }
        QuickSort(inps, 0, len-1);
        printf("%d\n", ContainsArray(base, inps, len, 0));
    }

    free(buf);
    fclose(fptr);
    return 0;
}

int ChildIndex(TreeNode *base, unsigned long value) {
    for(int i = 0; i < base->childrenCount; i++) {
        TreeNode *child = base->ChildrenNodes[i];
        if(child->value == value) 
            return i;
    }
    return -1;
}

void AppendListToTree(TreeNode *base, unsigned long *array, int len, int index, int childrenMax) {
    if(index == len) return;
    int childIndex = ChildIndex(base, array[index]);
    if(childIndex == -1) {
        TreeNode *new = malloc(sizeof(TreeNode));
        new->ChildrenNodes = malloc(sizeof(TreeNode*) * childrenMax);
        new->value = array[index];
        base->ChildrenNodes[base->childrenCount] = new;
        childIndex = base->childrenCount;
        base->childrenCount++;
    }
    AppendListToTree(base->ChildrenNodes[childIndex], array, len, index+1, childrenMax);
}

bool ContainsArray(TreeNode *base, unsigned long *array, int len, int index) {
    if(index == len) return true;
    int childIndex = ChildIndex(base, array[index]);
    if(childIndex == -1) return false;
    TreeNode *child = base->ChildrenNodes[childIndex];
    return ContainsArray(child, array, len, index+1);
}
