#include "malloc.h"

t_zone *create_zone(t_zone **prev, int zone_type, size_t size) {
    size_t zone_size = GET_ZONE_SIZE(zone_type, size);
    t_zone *zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;
    if (!*prev)
        zone->prev = NULL;
    else {
        zone->prev = *prev;
        (*prev)->next = zone;
    }
    zone->size = zone_size;
    zone->block = NULL;
    zone->next = NULL;
    return zone;
}

t_zone *get_zone(int zone_type, size_t size) {
    static t_heap heap = {0};

    t_zone *zone = GET_ZONE(zone_type);
    if (!zone || zone->size < size) {
        zone = create_zone(zone, zone_type, size);
        if (!zone)
            return NULL;
        MOVE_ZONE(zone_type);
    }
    return zone;
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