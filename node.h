#include<stdio.h>
#include<stdlib.h>

struct Node {
    void *address;             // Address of the alloc object
    size_t size;               // Sizeof alloc object
    int marked;                // GC flag
    int height;                // Height of node
    struct Node *left, *right; // left and right child of node
};

struct Node* newNode(void *address, size_t size);

