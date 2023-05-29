#include "malloc.h"

static t_zone *create_zone(int zone_type, size_t size) {
    static long long int rlim = 0;
    if (!rlim) {
        struct rlimit rlim_struct;
        getrlimit(RLIMIT_AS, &rlim_struct);
        rlim = rlim_struct.rlim_cur;
    }

    size_t zone_size = GET_ZONE_SIZE(zone_type, size);
    if (heap.total + (long long int) zone_size > rlim)
        return NULL;
    t_zone *zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;
    zone->space = zone_size - sizeof(t_zone);
    zone->block = NULL;
    zone->next = NULL;
    zone->type = zone_type;
    zone->size = zone_size;
    heap.total += zone_size;
    return zone;
}

// TODO : having enough space doesn't mean that the zone is free for the block (consider fragmentation)
static t_zone *find_free_zone(t_zone *zone, size_t size) {
    while (zone) {
        if (zone->space >= BLOCK_SIZE(size))
            return zone;
        zone = zone->next;
    }
    return NULL;
}

bool is_zone_empty(t_zone *zone) {
    while (zone) {
        if (zone->block && !zone->block->free)
            return false;
        zone = zone->next;
    }
    return true;
}

t_zone *get_zone(int zone_type, size_t size) {
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