#include "malloc.h"

int main() {
    char *addr;

    for (int i = 0; i < 1024; i++) {
        addr = (char *) malloc(256);
        addr[0] = 42;
        free(addr);
    }
    show_alloc_mem();
    return (0);
}