#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "libft.h"

#define PAGE_SIZE (size_t) getpagesize()
#define ALLOC_TINY PAGE_SIZE / 32
#define ALLOC_SMALL PAGE_SIZE / 4
#define ZONE_SMALL PAGE_SIZE * 4
#define ZONE_MEDIUM PAGE_SIZE * 32

#define GET_ZONE(x) (x == SMALL) ? heap.small : (x == MEDIUM) ? heap.medium : heap.large
#define GET_ZONE_SIZE(x, y) (x == SMALL) ? ZONE_SMALL : (x == MEDIUM) ? ZONE_MEDIUM : y

#define BLOCK_SIZE(x) x + sizeof(t_block)
#define DATA(x) (char *)(x + 1)
#define BLOCK(x) (t_block *)((char *)x - sizeof(t_block))

#define HEX 1
#define ASCII 2

enum ZONE_TYPE {
    SMALL,
    MEDIUM,
    LARGE
};

typedef struct s_block {
    size_t size;
    bool free;
    void *zone;
    struct s_block *next;
} t_block;

typedef struct s_zone {
    int type;
    size_t size;
    size_t space;
    struct s_block *block;
    struct s_zone *next;
} t_zone;

typedef struct s_heap {
    t_zone *small;
    t_zone *medium;
    t_zone *large;
    long long int total;
} t_heap;

extern t_heap heap;
extern pthread_mutex_t lock;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

void *malloc_helper(size_t size, bool realloc);
void free_helper(void *ptr);
void *realloc_helper(void *ptr, size_t size);
void *calloc_helper(size_t count, size_t size);

void show_alloc_mem();
void show_alloc_mem_ex(void *ptr, int mode);
void manage_log(const char *format, ...);

t_zone *get_zone(int zone_type, size_t size);
t_block *get_block(t_zone *zone, size_t size);
void verify_mem_state(t_block *block, t_zone *zone);
void *split_block(t_block *block, size_t alloc_size);