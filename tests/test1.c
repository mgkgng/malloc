#include "malloc.h"

int main() {
    char *addr;

    for (int i = 0; i < 1024; i++) {
        addr = (char *) malloc(1024);
        addr[0] = 42;
    }
    return (0);
}