#include "malloc.h"

static t_block *find_free_block(t_zone *zone, size_t size) {
    t_block *block = zone->block;
    while (block) {
        if (block->free && block->size >= size)
            return block;
        block = block->next;
    }
    return NULL;
}

static t_block *create_new_block(t_zone *zone, size_t size) {
    t_block *block = zone->block;
    if (!block) {
        block = (t_block *)((char *)(zone + 1));
        block->size = size;
        block->free = false;
        block->next = NULL;
        zone->block = block;
        zone->space -= BLOCK_SIZE(size);
        return block;
    }
    while (block->next)
        block = block->next;
    block->next = (t_block *)((char *)(block + 1) + block->size);
    block->next->size = size;
    block->next->free = false;
    block->next->next = NULL;
    zone->space -= BLOCK_SIZE(size);
    return block->next;
}

t_block *get_block(t_zone *zone, size_t size) {
    t_zone *curr = zone;
    while (curr) {
        t_block *block = find_free_block(curr, size);
        if (block)
            return block;
        curr = curr->next;
    }
    return create_new_block(zone, size);
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
    
    // blah blah ...

    return ;
}