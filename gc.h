#include "avl_tree.h"
#include "list.h"
#include "node.h"

struct gc {
    // Ideally we should scan through the process's address space to obtain 
    // list of active references to all objects Since we are doing simulation
    // we manually collect a list of such references.
    struct ref *refs;
    // List of allocated object
    struct ref *objs;
    // Search for 
    struct Node *tree;
};

void gc_init();
struct ref *gc_alloc(size_t);
struct ref *gc_ref(void *);
void gc_free(struct ref *);
int garbage_collect();

void gc_dbg();
