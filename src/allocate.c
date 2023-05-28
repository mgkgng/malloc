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

void free(void *ptr) {
    if (!ptr)
        return ;
    t_block *block = BLOCK(ptr);
    block->free = true;
    return ;
}

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    if (!size) {
        free(ptr);
        return NULL;
    }
    t_block *block = BLOCK(ptr);
    if (block->size >= size)
        return ptr;
    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    ft_memcpy(new_ptr, ptr, block->size);
    free(ptr);
    return new_ptr;
}