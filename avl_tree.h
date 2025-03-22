#include "node.h"

void printTree(struct Node *root, int space);
struct Node *avl_insert(struct Node *root, void *address, size_t size);
struct Node *deleteNode(struct Node *root, void *address);
struct Node *avl_search(struct Node *root, void *address);
