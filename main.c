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

    // Insert nodes
    char *string1 = (char*) malloc(10*sizeof(char));
    char *string2 = (char*) malloc(10*sizeof(char));
    char *string3 = (char*) malloc(10*sizeof(char));
    char *string4 = (char*) malloc(10*sizeof(char));
    char *string5 = (char*) malloc(10*sizeof(char));
    char *string6 = (char*) malloc(10*sizeof(char));

    root = avl_insert(root, string1);
    root = avl_insert(root, string2);
    root = avl_insert(root, string3);
    root = avl_insert(root, string4);
    root = avl_insert(root, string5);
    root = avl_insert(root, string6);

    printf("Visualized AVL tree:\n");
    printTree(root, 0);

    printf("after delete AVL tree:\n");
    root = avl_delete(root, string1);
    root = avl_delete(root, string2);
    printTree(root, 0);
    return test_run();
}
