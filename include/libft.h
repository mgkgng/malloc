#pragma once

#include <stdarg.h>
#include <unistd.h>

void ft_bzero(void *s, size_t n);
void ft_memcpy(void *dst, void *src, size_t size);
int ft_strcmp(const char *s1, const char *s2);
int ft_printf(const char *s, ...);