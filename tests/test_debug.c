#include "malloc.h"
#include <string.h>

int main() {
    char *ptr = calloc(256, 3);
    
    show_alloc_mem_ex(ptr, HEX);
}