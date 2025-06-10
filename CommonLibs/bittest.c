#include "BitUtils.c"
#include <stdbool.h>
#include <stdio.h>

int main() {
    LBS *lbs = GenerateLBS(10000000);
    PassValueInLBS(lbs, 42069, true);
    if (GetValueFromLBS(lbs, 42069)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    PassValueInLBS(lbs, 42069, true);
    if (GetValueFromLBS(lbs, 42069)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    PassValueInLBS(lbs, 42069, false);
    if (GetValueFromLBS(lbs, 42069)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    free(lbs->container);
    free(lbs);
}
