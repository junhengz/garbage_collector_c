static ref *ref_init() {
    struct ref *list = malloc(sizeof(*list)); 
    list->ptr = NULL;
};

void ref_del(ref *list) {
    struct ref *prev = list->prev;
    struct ref *next = list->next;
    if (prev) {
        prev->next = next;
    }
    if (next) {
        next->prev = prev;
    }
    free(list); 
};

struct ref *ref_ins(ref *head, void *ptr) {
    struct ref *list = malloc(sizeof(struct ref));
    list->ptr = ptr; 
    list->prev = head; 
    struct ref *next = list->next;
    list->next = next;
    if (next) {
        next->prev = list;
    }
    head->next = list;
};

