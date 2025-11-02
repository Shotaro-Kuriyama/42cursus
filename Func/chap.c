
#include <stdio.h>
#include <unistd.h>

int	ft_putnbr(int n)
{
	long nb = n;
	int  count = 0;
	char c;

	if (nb < 0) {
		write(1, "-", 1);
		count += 1;        // マイナスをカウント
		nb = -nb;
	}

	// 再帰で上位桁を出力し、その「書いた桁数」を合算
	if (nb > 9)
		count += ft_putnbr((int)(nb / 10));

	c = (char)((nb % 10) + '0');
	write(1, &c, 1);
	count += 1;           // 末尾の1桁をカウント

	return count;
}

static int put_hex_ul(unsigned long ul)
{
	int count;
	char c;

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
	return count;
}

int put_address(void *p)
{

	unsigned long addr;
	addr = (unsigned long)p;

	int count;

	count = 0;
	if (!p)
	{
		write(1, "(nil)", 5);
		return 5;
	}
	count = write(1, "0x", 2);

	count = put_hex_ul(addr);
	return count;
}

int	main(void)
{
	int i;

	i = 123456;

	printf("\n%d\n", ft_putnbr(i));
}