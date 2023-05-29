#include "malloc.h"

void *malloc_helper(size_t size) {
    t_zone *zone = get_zone((size <= ALLOC_TINY) ? SMALL : (size <= ALLOC_SMALL) ? MEDIUM : LARGE, size);
    if (!zone)
        return NULL;
    t_block *block = get_block(zone, size);
    return DATA(block);
}

void free_helper(void *ptr) {
    t_block *block = BLOCK(ptr);
    t_zone *zone = block->zone;
    block->free = true;
    verify_mem_state(block, zone);
}

void *realloc_helper(void *ptr, size_t size) {
    t_block *block = BLOCK(ptr);
    if (block->size >= size)
        return ptr;
    void *new_ptr = malloc_helper(size);
    if (!new_ptr)
        return NULL;
    ft_memcpy(new_ptr, ptr, block->size);
    free_helper(ptr);
    return new_ptr;
}