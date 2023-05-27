#include "malloc.h"

t_zone *create_zone(t_zone **prev, int zone_type, size_t size) {
    size_t zone_size = GET_ZONE_SIZE(zone_type, size);
    t_zone *zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;
    zone->space = zone_size - sizeof(t_zone);
    zone->block = NULL;
    zone->next = NULL;
    return zone;
}

t_zone *get_zone(int zone_type, size_t size) {
    static t_heap heap = {0};

    t_zone *zone = GET_ZONE(zone_type);
    if (!zone || zone->space < BLOCK_SIZE(size)) {
        zone = create_zone(zone, zone_type, size);
        if (!zone)
            return NULL;
        MOVE_ZONE(zone_type);
    }
    return zone;
}

t_zone *find_free_zone(t_zone *zone, size_t size) {
    while (zone) {
        if (zone->space >= BLOCK_SIZE(size))
            return zone;
        zone = zone->next;
    }
    return NULL;
}

t_block *find_free_block(t_zone *zone, size_t size) {
    t_block *block = zone->block;
    while (block) {
        if (block->free && block->size >= size)
            return block;
        block = block->next;
    }
    return NULL;
}

t_block *get_block(t_zone *zone, size_t size) {
    t_zone *curr = zone;
    while (curr) {
        t_block *block = find_free_block(curr, size);
        if (block)
            return block;
        curr = curr->next;
    }
    t_zone *target_zone = find_free_zone(zone, size);

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