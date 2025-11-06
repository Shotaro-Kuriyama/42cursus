/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:03 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 15:07:51 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	count_len(int n)
{
	size_t	len;
	long	num;

	len = 0;
	num = n;
	if (num <= 0)
		len = 1;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static char	*num_zero(char *p)
{
	p[0] = '0';
	p[1] = '\0';
	return (p);
}

char	*ft_itoa(int num)
{
	size_t	len;
	char	*p;
	
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
		p[--len] = num % 10 + '0';
		num = num / 10;
	}
	return (p);
}

// int	main(void)
//{
//	int i = -5879872;
//	printf("%s\n", ft_itoa(i));
//}