#include "malloc.h"

static t_zone *create_zone(int zone_type, size_t size) {
    size_t zone_size = GET_ZONE_SIZE(zone_type, size);
    t_zone *zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;
    zone->space = zone_size - sizeof(t_zone);
    zone->block = NULL;
    zone->next = NULL;
    return zone;
}

static t_zone *find_free_zone(t_zone *zone, size_t size) {
    while (zone) {
        if (zone->space >= BLOCK_SIZE(size))
            return zone;
        zone = zone->next;
    }
    return NULL;
}

t_zone *get_zone(int zone_type, size_t size) {
    static t_heap heap = {0};

    t_zone *zone = find_free_zone(GET_ZONE(zone_type), size);
    if (zone)
        return zone;
    t_zone *new_zone = create_zone(zone_type, size);
    if (!new_zone)
        return NULL;
    if (zone_type == SMALL) {
        new_zone->next = heap.small;
        heap.small = new_zone;
    } else if (zone_type == MEDIUM) {
        new_zone->next = heap.medium;
        heap.medium = new_zone;
    } else {
        new_zone->next = heap.large;
        heap.large = new_zone;
    }
    return new_zone;
}