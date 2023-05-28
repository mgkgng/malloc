#include "malloc.h"

void *malloc(size_t size) {
    if (!size)
        return NULL;
    t_zone *zone = get_zone((size <= ALLOC_TINY) ? SMALL : (size <= ALLOC_SMALL) ? MEDIUM : LARGE, size);
    if (!zone)
        return NULL;
    t_block *block = get_block(zone, size);
    return DATA(block);
}