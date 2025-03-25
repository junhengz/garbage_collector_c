#include <stdlib.h>
#include "list.h"

struct ref *ref_init() {
    struct ref *list = malloc(sizeof(struct ref *)); 
    list->ptr = NULL;
    return list;
}

// delete and return the next
struct ref *ref_del(struct ref *list) {
    struct ref *prev = list->prev;
    struct ref *next = list->next;
    if (prev) {
        prev->next = next;
    }
    if (next) {
        next->prev = prev;
    }
    free(list); 
	return next;
}

struct ref *ref_ins(struct ref *head, void *ptr) {
    struct ref *list = malloc(sizeof(struct ref));
    list->ptr = ptr; 
    list->prev = head; 
    struct ref *next = head->next;
    list->next = next;
    if (next) {
        next->prev = list;
    }
    head->next = list;
    return list;
}
