#include <stdbool.h>
#include "List.h"

typedef struct {
    // Strores numbers in reverse, aka the lower number has the lesser index
    LIST *Numbers;
    bool isNegative;
} LARGE_INT;

LARGE_INT *MakeLargeInt();
void freeLargeInt(LARGE_INT *trg);
LARGE_INT *atoli(char *str);
void PrintLargeInt(LARGE_INT *toPrint);
LARGE_INT *PerformOperation(char *firstOperand, char *secondOperand, char operation);


// ============= MATH =============

// Adds 1st number to a 2nd
LARGE_INT *Add(LARGE_INT *first, LARGE_INT *second);

// Suntracts 1st number from a 2nd
LARGE_INT *Subtract(LARGE_INT *first, LARGE_INT *second);
