#include "malloc.h"

t_heap heap = {0};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
