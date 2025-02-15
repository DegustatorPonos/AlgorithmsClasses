#include "longop.h"
#include <stdlib.h>

long PerformPoeration(char *firstOperand, char *secondOperand, char operation)
{
    long op1 = atol(firstOperand);
    long op2 = atol(secondOperand);
    switch (operation) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
    }
    return 0;
}
