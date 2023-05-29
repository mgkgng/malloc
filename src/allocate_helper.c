#include "malloc.h"

void *malloc_helper(size_t size, bool realloc) {
    t_zone *zone = get_zone((size <= ALLOC_TINY) ? SMALL : (size <= ALLOC_SMALL) ? MEDIUM : LARGE, size);
    if (!zone)
        return NULL;
    t_block *block = get_block(zone, size);
    block->free = false;
    block->size = size;
    
    void *ptr = DATA(block);
    manage_log("%s: %zu bytes at %p\n", (realloc) ? "Realloc" : "Malloc", size, ptr);
    return ptr;
}

void free_helper(void *ptr) {
    t_block *block = BLOCK(ptr);
    t_zone *zone = block->zone;
    block->free = true;
    verify_mem_state(block, zone);
    manage_log("Free: %zu bytes at %p\n", block->size, ptr);
}

void *realloc_helper(void *ptr, size_t size) {
    t_block *block = BLOCK(ptr);
    if (block->size >= size)
        return ptr;
    void *new_ptr = malloc_helper(size, true);
    if (!new_ptr)
        return NULL;
    ft_memcpy(new_ptr, ptr, block->size);
    free_helper(ptr);
    return new_ptr;
}