#include "libft.h"

int ft_putchar(char c) {
    write(1, &c, 1);
    return 1;
}

int ft_putstr(char *s) {
    int len = 0;
    while (s[len])
        ft_putchar(s[len++]);
    return len;
}

void ft_memcpy(void *dst, void *src, size_t size) {
    while (size--)
        ((char *)dst)[size] = ((char *)src)[size];
}
