#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

DECK *DeckInit(int length) {
    DECK *outp = malloc(sizeof(DECK));
    outp->length = length;
    outp->head = length / 2;
    outp->tail = length / 2;
    outp->array = malloc(sizeof(int) * length);
    return outp;
}

void PrintDeck(DECK *inp) {
    for(int i = 0; i < inp->length; i++) {
        printf("%d ", inp->array[i]);
        if(i == inp->tail || i == inp->head) 
            printf("<-");
        printf("\n");
    }
}
