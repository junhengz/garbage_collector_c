#include<stdio.h>
#include<stdlib.h>

struct Node {
    void *address;             // Address of the alloc object
    size_t size;               // Size of the object
} Node;

struct Node* newNode(void *address, size_t size);
