#include "libft.h"

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_putstr(char *s) {
    while (*s)
        ft_putchar(*s++);
}

