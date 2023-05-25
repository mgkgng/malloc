#include "libft.h"

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_putstr(char *s) {
    while (*s)
        ft_putchar(*s++);
}