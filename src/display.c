#include "malloc.h"

void show_alloc_mem() {
    t_zone *small_zone = get_zone(SMALL, 0);
    t_zone *medium_zone = get_zone(MEDIUM, 0);
    t_zone *large_zone = get_zone(LARGE, 0);

    int total = 0;
    ft_printf("SMALL ZONE\n");
    int zone_count = 0;
    while (small_zone) {
        ft_printf("ZONE %d: %p\n", zone_count, small_zone);
        t_block *block = small_zone->block;
        while (block) {
            ft_printf("%p - %p : %zu bytes\n", DATA(block), DATA(block) + block->size, block->size);
            total += block->size;
            block = block->next;
        }
        zone_count++;
        small_zone = small_zone->next;
    }

    ft_printf("MEDIUM ZONE\n");
    zone_count = 0;
    while (medium_zone) {
        ft_printf("ZONE %d: %p\n", zone_count, medium_zone);
        t_block *block = medium_zone->block;
        while (block) {
            ft_printf("%p - %p : %zu bytes\n", DATA(block), DATA(block) + block->size, block->size);
            total += block->size;
            block = block->next;
        }
        zone_count++;
        medium_zone = medium_zone->next;
    }

    ft_printf("LARGE ZONE\n");
    zone_count = 0;
    while (large_zone) {
        ft_printf("ZONE %d: %p\n", zone_count, large_zone);
        t_block *block = large_zone->block;
        while (block) {
            ft_printf("%p - %p : %zu bytes\n", DATA(block), DATA(block) + block->size, block->size);
            total += block->size;
            block = block->next;
        }
        zone_count++;
        large_zone = large_zone->next;
    }

    ft_printf("Total : %d bytes\n", total);
}