
#include "ft_printf.h"

int ft_putstr(char *c)
{
	int i;

	unsigned char uc;

	i = 0;
	while(*c)
	{
		uc = *c;
		write(1, &uc, 1);
		c++;
		i++;
	}
	return (i);
}