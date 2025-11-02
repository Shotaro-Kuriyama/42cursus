


/*
関数 	詳細
va_start 	可変長引数関数の引数にアクセスできるようにします。
va_arg 	可変長引数関数の次の引数にアクセスします。
va_copy 	可変長引数関数の引数をコピーします。
va_end 	可変長引数関数の引数の巡回を終了します
va_list 	va_start, va_arg, va_end, va_copyで使用される情報を保存します。
*/

#include <stdio.h>
#include "../libft.h"

int	ft_printf(const char *format, ...)
{

	va_list ap; //これはポインタ変数
	
	va_start(ap, format); //apにformatの先頭ポインタをセットする。（ここではprintfの"%s %d"の""の先頭アドレス）



	char c;
	char *p;
	void *q;
	int j;
	int total; //出力した文字の合計

	total = 0;

	while (*format)
	{
		while (*format != '%')
		{
			write(1, format, 1);
			total = total + 1;
			format++;
			continue;
		}

		//format == '%

		format++;
		if (*format == 'c')
			total += ft_putchar(va_arg(ap, int));
		else if (*format == 's')
			total += ft_putstr(va_arg(ap, char *));
		else if (*format == 'p')
		{
			q = va_arg(ap, void *);
		}
		else if (*format == 'd')
		{
			j = va_arg(ap, int);
		}
		else if (*format == 'i')
		{
			
		}
		else if (*format == 'u')
		{
		
			
		}
		else if (*format == 'x')
		{

		}
		else if (*format == 'X')
		{

		}
		else if (*format == '%')
			write(1, format, 1);

	}
	va_end(ap); //apにNULLポインタがセットされて使えなくなる。

	return total;

}


int putchar;
int putstr;
int putnbr;
int putunbr;
int puthex;
int putptr;

int ft_putstr(char *c)
{
	int i;

	i = 0;
	while(*c)
	{
		write(1, c. 1);
		c++;
		i++;
	}
	return (i);
}

int ft_putchar(int c)
{
	write(1, &c, 1);
	return 1;
}
int ft_putnbr(int n)
{
	long nb;

	nb = n;

	char c;
	static int count;

	count = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		count++;
	}

	if(nb > 9)
		ft_putnbr(nb / 10);
	
	c = nb % 10 + '0';
	write(1, &c, 1);

	return ++count;
}

int

int main(void)
{
	printf("こんにちは %c, %d", 'A', 3);
}
