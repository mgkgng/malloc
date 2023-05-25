#include "malloc.h"

t_area *create_area(size_t size) {
    size_t area_size = size + sizeof(t_area);
    if (area_size % PAGE_SIZE)
        area_size += PAGE_SIZE - (area_size % PAGE_SIZE);

    t_area *res = (t_area *) mmap(0, area_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (res == MAP_FAILED)
        return (NULL);
    res->area_size = area_size;
    res->next = NULL;
    res->tiny = NULL;
    res->small = NULL; 
    res->large = NULL;
    return (res);
}

t_area *get_area() {
    static t_area *area = NULL;
    if (!area)
        area = create_area(0);
    return (area);
}

// Example:
// TINY : 0xA0000
// 0xA0020 - 0xA004A : 42 bytes
// 0xA006A - 0xA00BE : 84 bytes
// SMALL : 0xAD000
// 0xAD020 - 0xADEAD : 3725 bytes
// LARGE : 0xB0000
// 0xB0020 - 0xBBEEF : 48847 bytes
// Total : 52698 bytes
void show_alloc_mem() {
    t_area *area = get_area();
    
    // blah blah ...

    return ;
}