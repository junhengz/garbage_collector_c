#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "gc.h"
#include "avl_tree.h"

static struct gc gc;

void gc_init() {
    gc.refs = ref_init();
	gc.objs = ref_init();
    gc.tree = NULL;
}

struct ref *gc_alloc(size_t size) {
    void *obj = malloc(size);
	gc.tree = avl_insert(gc.tree, obj, size);
	ref_ins(gc.objs, obj);
	printTree(gc.tree, 0);
    return gc_ref(obj);
}

struct ref *gc_ref(void *ptr) {
	if (!avl_search(gc.tree, ptr)) {
		return NULL;
	}
    struct ref *ref = ref_ins(gc.refs, ptr);
    return ref;
}

void gc_free(struct ref *ref){
    ref_del(ref);
}

int garbage_collect()
{
    // Mark
    for (struct ref *ref = gc.refs; ref != NULL; ref = ref->next) {
        struct Node *node = avl_search(gc.tree, ref->ptr);
		if (ref->ptr && node) {
			if ((unsigned long)(ref->ptr) < (unsigned long)node->address + (unsigned long)node->size ) {
				printf("Marking ptr:%p\n", ref->ptr);
				node->marked = 1;
			}
		}	
    }

	// Sweep
	struct ref *ref = gc.objs;
	while (ref) {
        struct Node *node = avl_search(gc.tree, ref->ptr);
        if (!node || node->marked) {
			ref = ref->next;
			if (node) {
				node->marked = 0;
			}	
			continue;
        }
		printf("[Del] ptr:%p\n", ref->ptr);
		printTree(gc.tree, 0);
		avl_delete(gc.tree, ref->ptr);
		printTree(gc.tree, 0);
		free(ref->ptr);
		ref = ref_del(ref);
    }
	
    return 0;
}

void gc_dbg() {
	printf("Active Pointers List\n");
    for (struct ref *ref = gc.refs; ref != NULL; ref = ref->next) {
		printf("%p \n", ref->ptr);
	}
	printf("Object List\n");
    for (struct ref *ref = gc.objs; ref != NULL; ref = ref->next) {
		printf("%p \n", ref->ptr);
	}
	printTree(gc.tree, 0);
}
