typedef struct {
    int *array;
    int length;
    int head;
    int tail;
} DECK;

DECK *DeckInit(int length);
void PrintDeck(DECK *inp);
