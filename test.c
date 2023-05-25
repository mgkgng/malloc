#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    struct rlimit rlim;
    printf("Page size: %d\n", getpagesize());
    getrlimit(RLIMIT_AS, &rlim);
    printf("RLIMIT_AS: %llu\n", rlim.rlim_cur);
}