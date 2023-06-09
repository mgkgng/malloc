#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "libft.h"

enum ZONE_TYPE {
    SMALL,
    MEDIUM,
    LARGE
};

#define PAGE_SIZE (size_t) getpagesize()
#define ZONE_SMALL PAGE_SIZE * 4
#define ZONE_MEDIUM PAGE_SIZE * 32
#define ALLOC_TINY ZONE_SMALL / 128
#define ALLOC_SMALL ZONE_MEDIUM / 128

#define GET_HEAP_BY_SIZE(x) (x <= ALLOC_TINY) ? heap.small : (x <= ALLOC_SMALL) ? heap.medium : heap.large
#define GET_HEAP_BY_TYPE(x) (x == SMALL) ? heap.small : (x == MEDIUM) ? heap.medium : heap.large
#define GET_ZONE_SIZE(x) (x <= ALLOC_TINY) ? ZONE_SMALL : (x <= ALLOC_SMALL) ? ZONE_MEDIUM : x
#define GET_ZONE_TYPE(x) (x <= ALLOC_TINY) ? SMALL : (x <= ALLOC_SMALL) ? MEDIUM : LARGE

#define BLOCK_SIZE(x) x + sizeof(t_block)
#define DATA(x) (char *)(x + 1)
#define BLOCK(x) (t_block *)((char *)x - sizeof(t_block))

#define HEX 1
#define ASCII 2

#define MAGIC 0x23581321

typedef struct s_block {
    size_t size;
    bool free;
    void *zone;
    size_t magic;
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
void display_log();

t_zone *get_zone(int zone_type, size_t size);
t_block *get_block(t_zone *zone, size_t size);
void verify_mem_state(t_block *block, t_zone *zone);
void *split_block(t_block *block, size_t alloc_size);