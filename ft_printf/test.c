


/*
関数 	詳細
va_start 	可変長引数関数の引数にアクセスできるようにします。
va_arg 	可変長引数関数の次の引数にアクセスします。
va_copy 	可変長引数関数の引数をコピーします。
va_end 	可変長引数関数の引数の巡回を終了します
va_list 	va_start, va_arg, va_end, va_copyで使用される情報を保存します。
*/

#include <stdio.h>
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list ap; //これはポインタ変数

	if (!format)
		return -1;
	va_start(ap, format); //apにformatの先頭ポインタをセットする。（ここではprintfの"%s %d"の""の先頭アドレス）
	int total; //出力した文字の合計
	total = 0;
	while (*format)
	{
		while (*format && *format != '%')
		{
			write(1, format, 1);
			total += 1;
			format++;
			continue;
		}
		format++;
		if (*format == '\0')
			break;
		if (*format == 'c')
			total += ft_putchar(va_arg(ap, int));
		else if (*format == 's')
			total += ft_putstr((char *)va_arg(ap, char *));
		else if (*format == 'p')
			total += ft_put_hex_ul(va_arg(ap, void *));
		else if (*format == 'd' || *format == 'i')
			total += ft_putnbr(va_arg(ap, int));
		else if (*format == 'u')
			total += ft_putunbr(va_arg(ap, unsigned int));
		else if (*format == 'x')
			total += ft_put_hex_x(va_arg(ap, unsigned int), 1);
		else if (*format == 'X')
			total += ft_put_hex_x(va_arg(ap, unsigned int), 0);
		else if (*format == '%')
			total += write(1, "%", 1);
		format++;
	}
	va_end(ap); //apにNULLポインタがセットされて使えなくなる。
	return total;
}
#include <limits.h>
int main(void)
{
	char s[] = "42Tokああああyo";
	void *p = s;

	unsigned int i = -5432452;
	unsigned int j = -62380252;
	//printf(" %x, %X, \n", i, j);
	//ft_printf(" %x, %X, \n", i, j);
	//printf("%u\n", -42);
	//printf("%zu\n", UINT_MAX - 42);
	//ft_printf("%p\n",p);
	printf("こんにちは %c, %s, %p, %d, %i, %u, %x, %X, %%\n", 'A', s, p,-42, -42, -42, i, j);
	ft_printf("こんにちは %c, %s, %p, %d, %i, %u, %x, %X, %%\n", 'A', s, p,-42, -42, -42, i, j);

//	printf("%d\n",printf(NULL));
//	ft_printf("%d\n",ft_printf(NULL));
//
}
