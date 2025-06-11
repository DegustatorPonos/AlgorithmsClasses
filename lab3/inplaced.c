#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab3/lines"

typedef struct {
    void **Branches;
    int Start;
    int End;
    int Id;
    int BranchesAmount;
} TreeElement;

TreeElement *CreateBaseElement(int sections);
void InsertInTree(TreeElement *base, int a, int b, int sections, int id);
int GetSmallestSectionID(TreeElement *base, int point);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    // Reading sections
    int SectAmm = ReadIntFromFile(fptr, FileSize);
    TreeElement* tree = CreateBaseElement(SectAmm);
    for(int i = 0; i < SectAmm; i++) {
        int a, b;
        fscanf(fptr, "%d %d\n", &a, &b); 
        InsertInTree(tree, a, b, SectAmm, i+1);
    }
    // printf("Smallest element at 2: %d\n", GetSmallestSectionID(tree, 2));
    
    // Reading points
    int PointsAmm = ReadIntFromFile(fptr, FileSize);
    // printf("Ponts: %d\n", PointsAmm);
    for(int i = 0; i < PointsAmm; i++) {
        printf("%d\n", GetSmallestSectionID(tree, ReadIntFromFile(fptr, FileSize)));
    }

    free(buf);
    fclose(fptr);
    return 0;
}

TreeElement *CreateBaseElement(int sections) {
    TreeElement *out = malloc(sizeof(TreeElement));
    out->Branches = malloc(sizeof(TreeElement*) * sections);
    out->Start = INT_MIN;
    out->End = INT_MAX;
    out->Id = -1;
    return out;
}

void InsertInTree(TreeElement *base, int a, int b, int sections, int id) {
    // Trying to insert in a deeper level
    for(int i = 0; i < base->BranchesAmount; i++) {
        TreeElement *current = base->Branches[i];
        if(current->Start <= a && current->End >= b) {
            InsertInTree(current, a, b, sections, id);
            return;
        }
    }
    // Inserting as a child
    TreeElement *out = malloc(sizeof(TreeElement));
    out->Branches = malloc(sizeof(TreeElement*) * sections);
    out->Start = a;
    out->End = b;
    out->Id = id;
    // printf("new segment: %d-%d with id %d\n", a, b, id);
    base->Branches[base->BranchesAmount] = out;
    base->BranchesAmount++;
} 

int GetSmallestSectionID(TreeElement *base, int point) {
    // Trying to search smaller section in the children
    for(int i = 0; i < base->BranchesAmount; i++) {
        TreeElement *current = base->Branches[i];
        // printf("Trying to fit %d in the sector %d-%d from sector %d-%d\n", point, current->Start, current->End, base->Start, base->End);
        if(current->Start <= point && current->End >= point)
            return GetSmallestSectionID(current, point);
    }
    return base->Id;
}
