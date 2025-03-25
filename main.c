#include <assert.h>
#include "gc.h"
#include "list.h"

struct test_obj {
	int val;
};

int test_run()
{
	gc_init();

	struct ref *objref = gc_alloc(sizeof(struct test_obj));
	struct test_obj *obj = (struct test_obj *)objref->ptr;
	obj->val = 3;
	assert(obj && "obj is null");

	// Test that object is still accessable after gc, as we 
	// still hold reference to it
	garbage_collect();
	assert(obj && "obj is null");
	assert(obj->val == 3 && "obj value changed");
	
	// We free the object
	gc_free(objref);
	garbage_collect();
	
	// Try to get a reference to that object after free
	// we should not be able to get it as it is garbage collected
	objref = gc_ref(obj);
	assert(!(objref) && "obj is not null");
	return 0;
}

int main()
{
    /*struct Node *root = NULL;*/
    /*size_t size = 10*sizeof(char); */
    /**/
    /*// Insert nodes*/
    /*char *string1 = (char*) malloc(size);*/
    /*char *string2 = (char*) malloc(size);*/
    /*char *string3 = (char*) malloc(size);*/
    /*char *string4 = (char*) malloc(size);*/
    /*char *string5 = (char*) malloc(size);*/
    /*char *string6 = (char*) malloc(size);*/
    /**/
    /*root = avl_insert(root, string1, size);*/
    /*root = avl_insert(root, string2, size);*/
    /*root = avl_insert(root, string3, size);*/
    /*root = avl_insert(root, string4, size);*/
    /*root = avl_insert(root, string5, size);*/
    /*root = avl_insert(root, string6, size);*/
    /**/
    /*printf("Visualized AVL tree:\n");*/
    /*printTree(root, 0);*/
    /**/
    /*printf("after delete AVL tree:\n");*/
    /*root = avl_delete(root, string1);*/
    /*root = avl_delete(root, string2);*/
    /*printTree(root, 0);*/
    return test_run();
}
