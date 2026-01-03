/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:17:33 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/09 18:12:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
{
	long	num;
	size_t	len;
	char	*p;

	num = n;
	len = count_len(n);
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
		p[--len] = (char)((num % 10) + '0');
		num = num / 10;
	}
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	int i = INT_MIN;

//	char *p = ft_itoa(i);
//	printf("%s\n", p);

//	free(p);
//}