#include "node.h"

/*
 * Create a new node with init values
 */
struct Node* newNode(void *address)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->address = address;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; //init the leaf height as 1
    return newNode;
}
