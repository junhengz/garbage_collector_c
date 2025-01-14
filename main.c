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
    return test_run();
}
