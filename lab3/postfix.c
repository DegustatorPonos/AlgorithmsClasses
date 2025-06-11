#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/List.h"
#define FILE_NAME "./inputs/lab3/postfix"

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    IntStackElement *stack = NULL;
    int opCount = ReadIntFromFile(fptr, FileSize);

    buf = fgets(buf, FileSize, fptr);
    char *parts = strtok(buf, " "); 
    for(int i = 0; i < opCount; i++) {
        char f = parts[0];
        int a, b;
        switch (f) {
            case '+':
                stack = Pop(stack, &a);
                stack = Pop(stack, &b);
                stack = Push(stack, a + b);
                break;
            case '-':
                stack = Pop(stack, &a);
                stack = Pop(stack, &b);
                stack = Push(stack, a - b);
                break;
            case '*':
                stack = Pop(stack, &a);
                stack = Pop(stack, &b);
                stack = Push(stack, a * b);
                break;
            default: // Number
                a = atoi(parts);
                stack = Push(stack, a);
                break;
        }
        parts = strtok(NULL, " ");
    }

    PrintStack(stack); // Ensuring it's ok
    free(buf);
    fclose(fptr);
    return 0;
}
