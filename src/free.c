#include "malloc.h"

void free(void *ptr) {
    if (!ptr)
        return ;
    t_block *block = GET_BLOCK(ptr);
    block->free = true;
    return ;
}