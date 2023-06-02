#include "malloc.h"

void *malloc(size_t size) {
    if (!size)
        return NULL;
    pthread_mutex_lock(&lock);
    void *res = malloc_helper(size, false);
    pthread_mutex_unlock(&lock);
    return res;
}

void free(void *ptr) {
    if (!ptr)
        return ;
    pthread_mutex_lock(&lock);
    free_helper(ptr);
    pthread_mutex_unlock(&lock);
}

void *realloc(void *ptr, size_t size) {
    pthread_mutex_lock(&lock);
    void *new_ptr = realloc_helper(ptr, size);
    pthread_mutex_unlock(&lock);
    return new_ptr;
}

void *calloc(size_t count, size_t size) {
    if (!count || !size)
        return NULL;
    pthread_mutex_lock(&lock);
    void *ptr = calloc_helper(count, size);
    pthread_mutex_unlock(&lock);
    return ptr;
}