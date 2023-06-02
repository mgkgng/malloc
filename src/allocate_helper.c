#include "malloc.h"

void *malloc_helper(size_t size, bool realloc) {
    t_zone *zone = get_zone(GET_ZONE_TYPE(size), size);
    if (!zone)
        return NULL;
    t_block *block = get_block(zone, size);
    void *ptr = DATA(block);
    manage_log("%s: %zu bytes at %p\n", (realloc) ? "Realloc" : "Malloc", size, ptr);
    return ptr;
}

void free_helper(void *ptr) {
    t_block *block = BLOCK(ptr);
    if (block->magic != MAGIC) {
        manage_log("Free: invalid pointer %p\n", ptr);
        return;
    }
    t_zone *zone = block->zone;
    block->free = true;
    manage_log("Free: %zu bytes at %p\n", block->size, ptr);
    verify_mem_state(block, zone);
}

void *realloc_helper(void *ptr, size_t size) {
    t_block *block = BLOCK(ptr);
    if (block->magic != MAGIC) {
        manage_log("Realloc: invalid pointer %p\n", ptr);
        return NULL;
    }
    if (block->size >= size)
        return ptr;
    void *new_ptr = malloc_helper(size, true);
    if (!new_ptr)
        return NULL;
    ft_memcpy(new_ptr, ptr, block->size);
    free_helper(ptr);
    return new_ptr;
}

void *calloc_helper(size_t count, size_t size) {
    size_t total = count * size;
    void *ptr = malloc_helper(total, false);
    if (!ptr)
        return NULL;
    ft_bzero(ptr, total);
    manage_log("Calloc: %zu bytes at %p\n", total, ptr);
    return ptr;
}