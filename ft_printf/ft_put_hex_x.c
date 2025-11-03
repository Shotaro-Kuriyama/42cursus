
#include "ft_printf.h"

static char	ft_tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + ('a' - 'A');
	return (c);
}

int	ft_put_hex_x(unsigned int ul, int i)
{
	int		count;
	char	c;

	count = 0;
	if (ul > 15)
		count += ft_put_hex_x(ul / 16, i);
	if (ul % 16 >= 10)
	{
		c = 'A' + (ul % 16 - 10);
		if(i == 1)
			c = ft_tolower(c);
		count += write(1, &c, 1);
	}
	else
	{
		c = ul % 16 + '0';
		count += write(1, &c, 1);
	}
	return (count);
}


//int	main(void)
//{
//	int i = 12831084;

//	printf("\n%d\n", ft_put_hex_x(i));
//}