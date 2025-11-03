
#include "ft_printf.h"

int ft_putchar(int c)
{
	unsigned char uc;

	uc = (unsigned char)c;
	write(1, &uc, 1);
	return 1;
}