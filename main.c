#include "gc.h"

int test_alloc()
{
    //alloc different objects
    printf("Alloc objects\n");
    return 0;
}

int test_unlink()
{
    //unlink some objects for gc to collect
    printf("unlink objects\n");
    return 0;
}

int test_run()
{
    if (test_alloc()) {
        printf("ERROR: alloc objects failed\n");
        return -1;
    }
    if (test_unlink()) {
        printf("ERROR: unlink objects failed\n");
        return -1;
    }
    if (garbage_collect()) {
        printf("ERROR: garbage collection failed\n");
        return -1;
    }
    printf("gc finished\n");
    return 0;
}

int main()
{
    struct Node *root = NULL;
    size_t size = 10*sizeof(char); 

    // Insert nodes
    char *string1 = (char*) malloc(size);
    char *string2 = (char*) malloc(size);
    char *string3 = (char*) malloc(size);
    char *string4 = (char*) malloc(size);
    char *string5 = (char*) malloc(size);
    char *string6 = (char*) malloc(size);

    root = avl_insert(root, string1, size);
    root = avl_insert(root, string2, size);
    root = avl_insert(root, string3, size);
    root = avl_insert(root, string4, size);
    root = avl_insert(root, string5, size);
    root = avl_insert(root, string6, size);

    printf("Visualized AVL tree:\n");
    printTree(root, 0);

    printf("after delete AVL tree:\n");
    root = avl_delete(root, string1);
    root = avl_delete(root, string2);
    printTree(root, 0);
    return test_run();
}
