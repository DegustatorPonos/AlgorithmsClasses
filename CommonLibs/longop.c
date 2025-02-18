#include "longop.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

LARGE_INT *MakeLargeInt()
{
    LARGE_INT *outp = malloc(sizeof(LARGE_INT));
    outp->Numbers = ListInit();
    return outp;
}

void freeLargeInt(LARGE_INT *trg)
{
    ClearList(trg->Numbers);
    free(trg->Numbers);
    free(trg);
}


LARGE_INT *atoli(char *str)
{
    LARGE_INT *outp = MakeLargeInt();
    char currentChar = str[0];
    int i = 0;
    while(currentChar != '\0')
    {
        currentChar = str[i];
        i++;
        if(currentChar == '-')
        {
            outp->isNegative = true;
            continue;
        }
        if(currentChar < '0')
            continue;
        InsertAt(outp->Numbers, 0, (int)(currentChar - '0'));
    }
    return outp;
}

void PrintLargeInt(LARGE_INT *toPrint)
{
    if(toPrint->Numbers->Length == 0)
    {
        printf("0\n");
        return;
    }
    if(toPrint->isNegative)
        printf("-");
    for(int i = toPrint->Numbers->Length - 1; i >= 0; i--)
        printf("%d", toPrint->Numbers->array[i]);
    printf("\n");
}

LARGE_INT *PerformOperation(char *firstOperand, char *secondOperand, char operation)
{
    LARGE_INT *op1 = atoli(firstOperand);
    LARGE_INT *op2 = atoli(secondOperand);
    switch(operation)
    {
        case '+':
            return Add(op1, op2);
        case '-':
            return Subtract(op1, op2);
    }
    return 0;
}

int Max(int a, int b) {
    if(a > b)
        return a;
    return b;
}

// 1 = a is greater, 2 = b is greater, 0 = they are equal
int MaxLargeInt(LARGE_INT *a, LARGE_INT *b)
{
    if(a->Numbers->Length > b->Numbers->Length) 
        return 1;
    if(a->Numbers->Length == b->Numbers->Length) 
    {
        int GreatestNumberIndex = a->Numbers->Length-1;
        while(GreatestNumberIndex >= 0)
        {
            if(a->Numbers->array[GreatestNumberIndex] > b->Numbers->array[GreatestNumberIndex])
                return 1;
            if(a->Numbers->array[GreatestNumberIndex] < b->Numbers->array[GreatestNumberIndex])
                return 2;
            GreatestNumberIndex--;
        }
        return 0;
    }
    return 2;
}

// Adds 1st number to a 2nd
LARGE_INT *Add(LARGE_INT *first, LARGE_INT *second)
{
    // Just so we don't have to deal with the negative values
    if(first->isNegative && !second->isNegative)
    {
        first->isNegative = false;
        LARGE_INT *outp = Subtract(second, first);
        outp->isNegative = true;
        return outp;
    }
    if(!first->isNegative && second->isNegative)
        return Subtract(first, second);

    int extra = 0;
    int i = 0;
    // printf("Adding numbers with length %d and %d\n", first->Numbers->Length, second->Numbers->Length);
    while(i < Max(first->Numbers->Length, second->Numbers->Length) || extra != 0)
    {
        int currentValue = extra;
        extra = 0;
        if(i < first->Numbers->Length)
            currentValue += first->Numbers->array[i];
        if(i < second->Numbers->Length)
            currentValue += second->Numbers->array[i];

        extra = currentValue / 10;
        currentValue = currentValue % 10;
        if(i < first->Numbers->Length)
            first->Numbers->array[i] = currentValue;
        else
            AppendToList(first->Numbers, currentValue);
        i++;
    }

    // If both were negative then the result is negative, else the result is positive
    // either way it does not change
    return first;
}

// Suntracts 1st number from a 2nd
LARGE_INT *Subtract(LARGE_INT *first, LARGE_INT *second)
{
    if(first->isNegative && !second->isNegative)
        return Add(first, second);
    if(!first->isNegative && second->isNegative)
    {
        second->isNegative = false;
        return Add(first, second);
    }

    // At this point we are only getting the positive and positive as inputs
    // Get the biggest value of them
    bool shouldBeNegative = first->isNegative;
    LARGE_INT *minuend;
    LARGE_INT *subtracthead;
    switch (MaxLargeInt(first, second)) {
        // They are equal(ly shitty)
        case 0:
            return MakeLargeInt();
        // first is bigger than the second
        case 1:
            minuend = first;
            subtracthead = second;
            break;
        // second is bigger than the first
        case 2:
            minuend = second;
            subtracthead = first;
            shouldBeNegative = true;
            break;
    }

    // Subtraction
    // Set this bool to true if you loan from the nextpower of 10
    bool isLoaned = false;
    for(int i = 0; i < minuend->Numbers->Length; i++)
    {
        if(isLoaned)
        {
            minuend->Numbers->array[i]--;
            isLoaned = false;
        }
        if(subtracthead->Numbers->Length > i)
            minuend->Numbers->array[i] -= subtracthead->Numbers->array[i];
        if(minuend->Numbers->array[i] < 0)
        {
            minuend->Numbers->array[i]+=10;
            isLoaned = true;
        }
    }

    if(shouldBeNegative)
        minuend->isNegative = !minuend->isNegative;
    while(minuend->Numbers->array[minuend->Numbers->Length-1] == 0)
        RemoveAt(minuend->Numbers, minuend->Numbers->Length-1);
    return minuend;
}
