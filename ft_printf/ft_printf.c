/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:57:18 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 17:35:16 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static int ft_select(const char format, va_list ap)
{

	int total;

	total = 0;
	if (format == 'c')
			total += ft_putchar(va_arg(ap, int));
		else if (format == 's')
			total += ft_putstr((char *)va_arg(ap, char *));
		else if (format == 'p')
			total += ft_put_hex_itoa(va_arg(ap, void *));
		else if (format == 'd' || format == 'i')
			total += ft_put_itoa(va_arg(ap, int));
		else if (format == 'u')
			total += ft_put_itoa_u(va_arg(ap, unsigned int));
		else if (format == 'x')
			total += ft_put_hex_x(va_arg(ap, unsigned int), 0);
		else if (format == 'X')
			total += ft_put_hex_x(va_arg(ap, unsigned int), 1);
		else if (format == '%')
			total += write(1, "%", 1);
		return total;
}

static 

int	ft_printf(const char *format, ...)
{
	va_list ap; //これはポインタ変数
	if (!format)
		return -1;
	va_start(ap, format); //apにformatの先頭ポインタをセットする。（ここではprintfの"%s %d"の""の先頭アドレス）
	int total; //出力した文字の合計
	int r;
	r = 0;
	total = 0;
	while (*format)
	{
		if (*format != '%')
		{
			r = write(1, format,1);
			if (r < 0)
				return -1;
			else
				total += r;
		}
		else if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break;
			total += ft_select(*format, ap);
		}
		format++;
	}
	va_end(ap); //apにNULLポインタがセットされて使えなくなる。
	return total;
}
#include <limits.h>
int main(void)
{
	char s[] = "42東京";
	void *p = s;



	unsigned int i = -5432452;
	unsigned int j = -62380252;

	printf("こんにちは %c, %s, %p, %d, %i, %u, %x, %X, %%\n", 'A', s, p,-42, -42, -42, i, j);
	ft_printf("こんにちは %c, %s, %p, %d, %i, %u, %x, %X, %%\n", 'A', s, p,-42, -42, -42, i, j);

	//printf("%d\n",printf(NULL));
	//ft_printf("%d\n",ft_printf(NULL));

	//setvbuf( stdout, NULL, _IONBF, 0);
    //close(1);
    //int rev1 = printf("%c", 'A');
    //int rev2 = ft_printf("%c", 'A');
    //dprintf(2, "rev1: %d\n", rev1);
    //dprintf(2, "rev2: %d\n", rev2);
    //return (0);
}