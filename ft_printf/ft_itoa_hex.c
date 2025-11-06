/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:04:56 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 17:22:28 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	count_len(unsigned long long n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static char	*num_zero(char *p)
{
	p[0] = '0';
	p[1] = '\0';
	return (p);
}

char	*ft_itoa_hex(unsigned long long num)
{
	size_t	len;
	char	*p;
	char 	*hex;

	hex = "0123456789abcdef";
	len = count_len(num);
	p = (char *)malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (NULL);
	if (num == 0)
		return (num_zero(p));
	p[len] = '\0';
	if (num < 0)
	{
		p[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		p[--len] = hex[num % 16];
		num = num / 16;
	}
	return (p);
}
//int	main(void)
//{
//	unsigned long i = 488952871;
//	printf("%s", ft_itoa_hex(i));
//}