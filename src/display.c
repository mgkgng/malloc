#include "malloc.h"

void show_alloc_mem() {
    pthread_mutex_lock(&lock);

    t_zone *small_zone = heap.small;
    t_zone *medium_zone = heap.medium;
    t_zone *large_zone = heap.large;

    int total = 0;
    if (small_zone)
        ft_printf("SMALL ZONE\n");
    int zone_count = 1;
    while (small_zone) {
        printf("ZONE %d: %p\n\n", zone_count, small_zone);
        t_block *block = small_zone->block;
        while (block && !block->free) {
            printf("%p - %p : %zu bytes\n", DATA(block), DATA(block) + block->size, block->size);
            total += block->size;
            block = block->next;
        }
        zone_count++;
        small_zone = small_zone->next;
    }

    if (medium_zone)
        ft_printf("MEDIUM ZONE\n");
    zone_count = 1;
    while (medium_zone) {
        printf("ZONE %d: %p\n", zone_count, medium_zone);
        t_block *block = medium_zone->block;
        while (block && !block->free) {
            printf("%p - %p : %zu bytes\n", DATA(block), DATA(block) + block->size, block->size);
            total += block->size;
            block = block->next;
        }
        zone_count++;
        medium_zone = medium_zone->next;
    }

    if (large_zone)
        ft_printf("LARGE ZONE\n");
    zone_count = 1;
    while (large_zone) {
        t_block *block = large_zone->block;
        printf("%p - %p : %zu bytes\n", DATA(block), DATA(block) + block->size, block->size);
        total += block->size;
        large_zone = large_zone->next;
    }

    ft_printf("Total : %d bytes\n", total);

    pthread_mutex_unlock(&lock);
}

void show_alloc_mem_ex(void *ptr, int mode) {
    if (!ptr)
        return;

    pthread_mutex_lock(&lock);

    t_block *block = BLOCK(ptr);
    size_t block_size = block->size + sizeof(t_block);
    unsigned char *byte_ptr = (unsigned char *) block;

    printf("\nAddress: %p, Size: %zu\n", ptr, block_size);

    size_t i = 0;
    for (; i < block_size; i++) {
        printf((i < sizeof(t_block)) ? "\033[0;31m" : ""); // Put color for t_block part

        if (i % 16 == 0) // Start a new line every 16 bytes
            printf("\n%07zx ", i);

        if (mode == HEX || mode == HEX + ASCII) // Print Hexadecimal representation
            printf("%02x ", byte_ptr[i]);

        if (mode == ASCII || mode == HEX + ASCII) { // Print ASCII representation
            if (i % 16 == 8) { printf(" "); }
            if (i % 16 == 0) { printf(" |"); }


            if (isprint(byte_ptr[i]))
                printf("%c", byte_ptr[i]);
            else
                printf(".");

            if ((i + 1) % 16 == 0) { printf("|"); }
        }
        printf((i < sizeof(t_block)) ? "\033[0m" : "");
    }
    printf("\n");

    pthread_mutex_unlock(&lock);
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

void display_log() {
    static char *debug = NULL;
    static bool debug_init = false;

    if (!debug_init) {
        debug = getenv("MALLOC_DEBUG");
        debug_init = true;
    }
    if (!debug || ft_strcmp(debug, "1") != 0)
        return;

    FILE *log_file = fopen("malloc.log", "r");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, log_file)) != -1)
        printf("%s", line);

    fclose(log_file);
    if (line)
        free(line);
}
