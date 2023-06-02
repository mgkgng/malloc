#include "malloc.h"

void *split_block(t_block *block, size_t alloc_size) {
    t_block *new_block = (t_block *)((char *)block + alloc_size);
    new_block->size = block->size - alloc_size - sizeof(t_block);
    new_block->free = true;
    new_block->zone = block->zone;
    new_block->next = block->next;
    block->size = alloc_size;
    block->next = new_block;
    return block;
}

t_block *merge_block(t_block *b1, t_block *b2) {
    b1->size += b2->size + sizeof(t_block);
    b1->next = b2->next;
    return b1;
}

void verify_mem_state(t_block *block, t_zone *zone) {
    printf("compare! %p %p \n", block->zone, zone);

    bool empty = true;
    t_block *curr = zone->block;
    t_block *prev = NULL;
    while (curr) {
        if (empty && !curr->free)
            empty = false;
        if (curr == block) {
            if (prev && prev->free) {
                curr = merge_block(prev, curr);
            }
            if (curr->next && curr->next->free) {
                curr = merge_block(curr, curr->next);
            }
        }
        prev = curr;
        curr = curr->next;
    }
    if (!empty)
        return ;

    int zone_type = zone->type;
    t_zone *start = GET_ZONE(zone_type);
    if (start == zone) {
        if (zone_type == SMALL)
            heap.small = zone->next;
        else if (zone_type == MEDIUM)
            heap.medium = zone->next;
        else
            heap.large = zone->next;
    } else {
        while (start->next != zone)
            start = start->next;
        start->next = zone->next;
    }
    printf("munmap: %p\n", zone);
    munmap(zone, zone->size);
    printf("munmap: %p\n", zone);

    printf("checking heap\n");
    if (zone_type == SMALL)
        printf("small: %p\n", heap.small);
    else if (zone_type == MEDIUM)
        printf("medium: %p\n", heap.medium);
    else
        printf("large: %p\n", heap.large);
}