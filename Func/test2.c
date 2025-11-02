

#include <stdio.h>
#include <unistd.h>

static int	put_hex_ul(unsigned long ul)
{
	int		count;
	char	c;

	count = 0;
	if (ul > 15)
		count += put_hex_ul(ul / 16);
	if (ul % 16 >= 10)
	{
		c = 'A' + (ul % 16 - 10);
		count += write(1, &c, 1);
	}
	else
	{
		c = ul % 16 + '0';
		count += write(1, &c, 1);
	}
	return (count);
}

int	put_address(void *p)
{
	unsigned long	addr;
	int				count;

	addr = (unsigned long)p;
	count = 0;
	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count += write(1, "0x", 2);
	count += put_hex_ul(addr);
	return (count);
}

int	main(void)
{
	char *p;
	void *q;
	unsigned char *r = NULL;
	void *s;

	printf("\n%d\n", put_address(p));
	printf("\n%d\n", put_address(q));
	printf("\n%d\n", put_address(r));
	printf("\n%d\n", put_address(s));
}