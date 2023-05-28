#include "ft_printf.h"

int	ft_nbrlen(long long int n, int base) {
	int len = 1;
	if (n < 0) {
		n *= -1;
		len++;
	}
	while (n > base - 1) {
		len++;
		n /= base;
	}
	return len;
}

int	ft_putnbr(long long int n) {
	int	len = ft_nbrlen(n, 10);
	if (n < 0) {
		ft_putchar('-');
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
	return len;
}


int	ft_puthex(unsigned int n, int upper) {
	char *set = (!upper) ? "0123456789abcdef" : "0123456789ABCDEF";
	if (n > 15)
		ft_puthex(n / 16, upper);
	ft_putchar(set[n % 16]);
	return (ft_nbrlen(n, 16));
}

int	ft_ptrlen(unsigned long long n) {
	int	len = 3;
	while (n > 15) {
		n /= 16;
		len++;
	}
	return len;
}

int	ft_putptr(unsigned long long n, int on) {
	char *set = "0123456789abcdef";
    if (on)
		ft_putstr("0x");
	if (n > 15)
		ft_putptr(n / 16, 0);
	ft_putchar(set[n % 16]);
	return (ft_ptrlen(n));
}

int	print(const char *s, int *i, va_list arg_n) {
	if (!s[*i])
		return (0);
	char type = s[(*i)++];
	if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(arg_n, int)));
	else if (type == 'u')
		return (ft_putnbr(va_arg(arg_n, unsigned int)));
	else if (type == 'x')
		return (ft_puthex(va_arg(arg_n, unsigned int), 0));
	else if (type == 'X')
		return (ft_puthex(va_arg(arg_n, unsigned int), 1));
	else if (type == 'c')
		return (ft_putchar(va_arg(arg_n, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(arg_n, char *)));
	else if (type == 'p')
		return (ft_putptr(va_arg(arg_n, unsigned long long), 1));
	else
		return (ft_putchar(type));
}

int	ft_printf(const char *s, ...)
{
	va_list arg_n;

	va_start(arg_n, s);
	int len = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] == '%' && ++i)
			len += print(s, &i, arg_n);
		else
			len += ft_putchar(s[i]);
	}
	va_end(arg_n);
	return len;
}