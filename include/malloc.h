#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>

#include "libft.h"
#include "ft_printf.h"

#define PAGE_SIZE getpagesize()
#define ALLOC_TINY PAGE_SIZE / 32
#define ALLOC_SMALL PAGE_SIZE / 4
#define ZONE_SMALL PAGE_SIZE * 4
#define ZONE_MEDIUM PAGE_SIZE * 32

#define GET_ZONE(x) (x == SMALL) ? heap.small : (x == MEDIUM) ? heap.medium : heap.large
#define GET_ZONE_SIZE(x, y) (x == SMALL) ? ZONE_SMALL : (x == MEDIUM) ? ZONE_MEDIUM : y
#define MOVE_ZONE(x) if (zone_type == SMALL) heap.small = zone; else if (zone_type == MEDIUM) heap.medium = zone; else heap.large = zone;

#define BLOCK_SIZE(x) x + sizeof(t_block)
#define DATA(x) (char *)(x + 1)
#define BLOCK(x) (t_block *)((char *)x - sizeof(t_block))


enum ZONE_TYPE {
    SMALL,
    MEDIUM,
    LARGE
};

enum CREATE_ZONE_TYPE {
    EMPTY,
    FULL
};

typedef struct s_block {
    size_t size;
    bool free;
    struct s_block *next;
} t_block;

typedef struct s_zone {
    size_t space;
    struct s_block *block;
    struct s_zone *next;
} t_zone;

typedef struct s_heap {
    t_zone *small;
    t_zone *medium;
    t_zone *large;
} t_heap;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();
t_zone *get_zone(int zone_type, size_t size);
t_block *get_block(t_zone *zone, size_t size);