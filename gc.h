#include "avl_tree.h"

void* gc_malloc(size_t size);
void gc_free(void *ptr);
int garbage_collect();
