#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/LinkedList.h"
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/vq"

int main()
{
    // Reading inp
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    fgets(buf, FileSize, fptr);
    char *parts = strtok(buf, " ");
    int seqLen = atoi(parts);
    parts = strtok(NULL, " ");
    int start = atoi(parts);
    parts = strtok(NULL, " ");
    int step = atoi(parts);
    parts = strtok(NULL, " ");
    int cap = atoi(parts);

    IntLinkedListNode *ll = GenerateLL(start);

    unsigned long currentValue = start;
    for(int i = 0; i < seqLen - 1; i++) {
        currentValue = ((currentValue*(unsigned int)step)&0xFFFFFFFFU)%cap;
        ll = InstertInOrder(currentValue, ll);
    }

    unsigned long outp = 0;
    bool isOdd = true;
    while(ll != NULL) {
        if(isOdd) {
            unsigned long long newValue = outp + ll->Value;
            outp = newValue % cap;
        } 
        isOdd = !isOdd;
        ll = ll->NextNode;
    }
    printf("%lu\n", outp);

    free(buf);
    fclose(fptr);
    return 0;
}
