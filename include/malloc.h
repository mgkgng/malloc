#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>

typedef struct s_block {
    size_t size;
    int free;
    void *ptr;
    char data[1];
    struct s_block *next;
} t_block;

typedef struct s_area {
    t_block *tiny;
    t_block *small;
    t_block *large;
} t_area;

extern t_area area;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();