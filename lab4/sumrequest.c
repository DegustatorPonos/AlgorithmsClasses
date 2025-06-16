// https://en.wikipedia.org/wiki/Fenwick_tree
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/sum"

void UpdateFenwick(unsigned long *base, unsigned long index, int value, int len);
unsigned long Query(unsigned long *base, int index);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    unsigned long test = 20;
    
    int len, requestAmm;
    unsigned long *fenwickTree = malloc(sizeof(unsigned long) * len + 1);
    fscanf(fptr, "%d %d", &len, &requestAmm); 
    for(int i = 1; i <= len; i++) {
        unsigned long value;
        fscanf(fptr, "%lu", &value); 
        // printf("I=%d, v = %lu\n", i, value);
        UpdateFenwick(fenwickTree, i, value, len);
    }

    for(int i = 0; i < requestAmm; i++) {
        int type;
        unsigned long a, b;
        fscanf(fptr, "%d %lu %lu", &type, &a, &b);
        a++;
        b++;

        if (type == 1) {
            unsigned long sum = Query(fenwickTree, b) - Query(fenwickTree, a-1);
            printf("%lu\n", sum);
            continue;
        } else {
            // printf("Updating\n");
            unsigned long old_value = Query(fenwickTree, a) - Query(fenwickTree, a-1);
            unsigned long delta = b - old_value - 1;
            UpdateFenwick(fenwickTree, a, delta, len);
        }
    }

    free(buf);
    fclose(fptr);
    return 0;
}

void UpdateFenwick(unsigned long *base, unsigned long index, int value, int len) {
    while(index <= len) {
        // printf("Index=%lu\n", index);
        base[index] += value;
        index += index & -index;
    }
}

unsigned long Query(unsigned long *base, int index) {
    unsigned long sum = 0;
    while(index > 0) {
        sum += base[index];
        index -= index & (-index);
    }
    return sum;
}
