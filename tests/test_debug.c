#include "malloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *addr = malloc(1);
    printf("heap total: %llu\n", heap.total / getpagesize());

    char *ptr = calloc(256, 3);
    // display_log();
}