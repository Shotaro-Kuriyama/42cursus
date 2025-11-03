
#include "ft_printf.h"

int	ft_put_hex_X(unsigned int ul)
{

	int		count;
	char	c;

	count = 0;
	if (ul > 15)
		count += ft_put_hex_X(ul / 16);
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


//int	main(void)
//{
//	int i = 87965407;

//	printf("\n%d\n", ft_put_hex_X(i));

//}