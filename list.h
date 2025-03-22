struct ref {
    void *ptr
    struct ref *next;
    struct ref *prev;
};

struct ref *ref_init();
void ref_del(struct ref *);
struct ref *ref_ins(struct ref *, void *ptr);
