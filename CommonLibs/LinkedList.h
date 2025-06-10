typedef struct {
    unsigned long Value;
    void *PreviousNode;
    void *NextNode;
} IntLinkedListNode;

IntLinkedListNode *GenerateLL(unsigned long startVal);
void PrintLL(IntLinkedListNode *node);
IntLinkedListNode *InstertInOrder(unsigned long value, IntLinkedListNode *node);
