
#include <stdio.h>
#include <unistd.h>

int	ft_putunbr(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	// 再帰で上位桁を出力し、その「書いた桁数」を合算
	if (n > 9)
		count += ft_putunbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	count += 1; // 末尾の1桁をカウント
	return (count);
}

// int	main(void)
//{
//	int i;

//	i = 12321432;
//	printf("\n%d\n", ft_putunbr(i));
//}