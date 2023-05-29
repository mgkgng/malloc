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

void show_alloc_mem_ex(void *ptr) {
    t_block *block = BLOCK(ptr);
    size_t block_size = block->size + sizeof(t_block);
    unsigned char *byte_ptr = (unsigned char *) BLOCK(ptr);

    size_t i = 0;
    printf("\033[0;31m");
    for (; i < sizeof(t_block); i++) {
        printf("%02x ", byte_ptr[i]);
        if ((i + 1) % 16 == 0)
            ft_printf("\n");
    }
    printf("\033[0m");
    for (; i < block_size; i++) {
        printf("%02x ", byte_ptr[i]);
        if ((i + 1) % 16 == 0)
            ft_printf("\n");
    }
    ft_printf("\n");
}

void manage_log(const char *format, ...) {
    static char *debug = NULL;
    static bool debug_init = false;

    if (!debug_init) {
        debug = getenv("MALLOC_DEBUG");
        debug_init = true;
    }
    if (!debug || ft_strcmp(debug, "1") != 0)
        return;

    FILE *log_file = fopen("malloc.log", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    fclose(log_file);
}
