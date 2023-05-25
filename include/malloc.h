#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>

#include "libft.h"

#define TINY 128
#define SMALL 1024
#define PAGE_SIZE getpagesize()

typedef struct s_block {
    size_t size;
    int free;
    void *ptr;
    char data[1];
    struct s_block *next;
} t_block;

typedef struct s_area {
    size_t area_size;
    struct s_area *next;
    t_block *tiny;
    t_block *small;
    t_block *large;
} t_area;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

t_area *create_area(size_t size);
t_area *get_area();
void show_alloc_mem();