#include "malloc.h"

int main() {
    char *addr;

    for (int i = 0; i < 1024; i++) {
        addr = (char *) malloc(256);
        addr[0] = 42;
        free(addr);
    }
    return (0);
}