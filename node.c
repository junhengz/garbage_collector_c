#include "node.h"

struct Node* newNode(void *address, size_t size)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->address = address;
    newNode->size = size;
    return newNode;
}
