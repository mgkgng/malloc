#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct rlimit rlim;
    printf("Page size: %d\n", getpagesize());
    getrlimit(RLIMIT_AS, &rlim);
    printf("RLIMIT_AS: %llu\n", rlim.rlim_cur);

    char *test_buf = malloc(24);
    for (int i = 0; i < 200; i++) {
        test_buf[i] = 'a';
    }
    printf("no problemo\n");
    printf("here problemo %lu\n", strlen(test_buf));
    free(test_buf);
    printf("test problemo %s\n", test_buf);
    printf("wtf problemo %lu\n", strlen(test_buf));
}