#include "malloc.h"

t_block *find_free_block(t_zone *zone, size_t size) {
    t_block *block = zone->block;
    while (block) {
        if (block->free && block->size >= size)
            return block;
        block = block->next;
    }
    return NULL;
}

t_block *create_new_block(t_zone *zone, size_t size) {
    t_block *block = (zone) ? zone->block : NULL;
    if (!block) {
        block = (t_block *)((char *)(zone + 1));
        block->size = size;
        block->free = false;
        block->next = NULL;
        block->zone = zone;
        block->magic = MAGIC;
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
    if (size > ALLOC_SMALL)
        return create_new_block(zone, size);
    t_block *block = find_free_block(zone, size);
    if (block) {
        if (block->size - size > sizeof(t_block))
            return split_block(block, size);
        return block;
    }
    return create_new_block(zone, size);
}