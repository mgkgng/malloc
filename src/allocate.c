#include "malloc.h"

void *malloc(size_t size) {
    if (!size)
        return NULL;
    pthread_mutex_lock(&lock);
    t_zone *zone = get_zone((size <= ALLOC_TINY) ? SMALL : (size <= ALLOC_SMALL) ? MEDIUM : LARGE, size);
    if (!zone) {
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    t_block *block = get_block(zone, size);
    pthread_mutex_unlock(&lock);
    return DATA(block);
}

void free(void *ptr) {
    if (!ptr)
        return ;
    pthread_mutex_lock(&lock);
    t_block *block = BLOCK(ptr);
    t_zone *zone = block->zone;
    block->free = true;
    verify_zone_state(zone);
    pthread_mutex_unlock(&lock);
    return ;
}

void *realloc(void *ptr, size_t size) {
    pthread_mutex_lock(&lock);
    if (!ptr) {
        void *res = malloc(size);
        pthread_mutex_unlock(&lock);
        return res;
    }
    if (!size) {
        free(ptr);
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    t_block *block = BLOCK(ptr);
    if (block->size >= size) {
        pthread_mutex_unlock(&lock);
        return ptr;
    }
    void *new_ptr = malloc(size);
    if (!new_ptr) {
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    ft_memcpy(new_ptr, ptr, block->size);
    free(ptr);
    pthread_mutex_unlock(&lock);
    return new_ptr;
}