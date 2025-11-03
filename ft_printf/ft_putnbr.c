
#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		count;
	char	c;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		count += 1; // マイナスをカウント
		nb = -nb;
	}
	// 再帰で上位桁を出力し、その「書いた桁数」を合算
	if (nb > 9)
		count += ft_putnbr((int)(nb / 10));
	c = (char)((nb % 10) + '0');
	write(1, &c, 1);
	count += 1; // 末尾の1桁をカウント
	return (count);
}

//int	main(void)
//{
//	int i;

//	i = 123456;

//	printf("\n%d\n", ft_putnbr(i));
//}