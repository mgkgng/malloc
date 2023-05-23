#include "malloc.h"

t_area *create_area() {
    t_area *res = (t_area *) mmap(0, sizeof(t_area), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (res == MAP_FAILED)
        return (NULL);
    res->tiny = NULL;
    res->small = NULL;
    res->large = NULL;
    return (res);
}

t_area *get_area() {
    static t_area *area = NULL;
    if (!area)
        area = create_area();
    return (area);
}

void show_alloc_mem() {
    t_area *area = get_area();
    
    // blah blah ...

    return ;
}