#include "include/malloc.h"

int main() {
    // char *test_buf = malloc(24);
    // for (int i = 0; i < 200; i++) {
    //     test_buf[i] = 'a';
    // }
    // printf("no problemo\n");
    // printf("here problemo %lu\n", strlen(test_buf));
    // free(test_buf);
    // printf("test problemo %s\n", test_buf);
    // printf("wtf problemo %lu\n", strlen(test_buf));

    char *test_buf = malloc(24);
    test_buf[1] = 'a';
    test_buf[2] = 'b';
    show_alloc_mem();
    show_alloc_mem_ex(test_buf);
}