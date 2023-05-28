#include "malloc.h"

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    if (!size) {
        free(ptr);
        return NULL;
    }
    t_block *block = GET_BLOCK(ptr);
    if (block->size >= size)
        return ptr;
    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    ft_memcpy(new_ptr, ptr, block->size);
    free(ptr);
    return new_ptr;
}