/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_itoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:09 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 17:10:36 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>


int	ft_put_hex_itoa(void *p) //ポインタをもらう
{
	unsigned long long addr;
	int count;
	char *nbrAddr;
	int r;
	count = 0;
	if (!p)
		return (write(1, "(nil)", 5));
	r = write(1, "0x", 2);
	if (r < 0)
		return (-1);
	count += r;
	addr = (unsigned long long)p;     //アドレスをunsigned longにしてあげてft_itoa_hexに渡してあげる
	nbrAddr = ft_itoa_hex(addr); //文字列を持っている先頭アドレスがここにできた
	r = ft_putstr(nbrAddr);
	if (r < 0)
		return (free(nbrAddr), (-1));
	count += r;
	free(nbrAddr);
	return (count);
}

//int	main(void)
//{
//	char *p;
//	void *q;
//	unsigned char *r = NULL;
//	void *s = NULL;

//	printf("\n%d\n", ft_put_hex_itoa(p));
//	printf("\n%d\n", ft_put_hex_itoa(q));
//	printf("\n%d\n", ft_put_hex_itoa(r));
//	printf("\n%d\n", ft_put_hex_itoa(s));
	
//}