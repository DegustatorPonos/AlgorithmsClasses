#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

IntLinkedListNode *GenerateLL(unsigned long startVal) {
    IntLinkedListNode *startNode = malloc(sizeof(IntLinkedListNode));
    startNode->Value = startVal;
    startNode->NextNode = NULL;
    startNode->PreviousNode = NULL;
    return startNode;
}

void PrintLL(IntLinkedListNode *node) {
    printf("%d ",node->Value);
    if(node->NextNode == NULL) {
        return;
    }
    PrintLL(node->NextNode);
}

IntLinkedListNode *InstertInOrder(unsigned long value, IntLinkedListNode *node) {
    if(value < node->Value) {
        IntLinkedListNode *newNode = GenerateLL(value);
        newNode->NextNode = node;
        newNode->PreviousNode = node->PreviousNode;
        if(newNode->PreviousNode != NULL) {
            IntLinkedListNode *prevNode = newNode->PreviousNode;
            prevNode->NextNode = newNode;
        }
        node->PreviousNode = newNode;
        return newNode;
    }

    if(node->NextNode == NULL) {
        IntLinkedListNode *newNode = GenerateLL(value);
        node->NextNode = newNode;
        newNode->PreviousNode = node;
        return node;
    }

    InstertInOrder(value, node->NextNode);
    return node;
}
