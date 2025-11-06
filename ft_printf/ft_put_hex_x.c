/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:12 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 16:58:05 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_put_hex_x(unsigned int n, int i)
{
	unsigned int	count;
	char			*nbrAddr;
	char			*tolower;

	nbrAddr = ft_itoa_hex(n);
	tolower = nbrAddr;
	if (i == 1)
	{
		while (*tolower)
		{
			if (*tolower >= 'a' && *tolower <= 'z')
				*tolower -= ('a' - 'A');
			tolower++;
		}
	}
	count = ft_putstr(nbrAddr);
	if (count < 0)
	{
		free(nbrAddr);
		return (-1);
	}
	free(nbrAddr);
	return (count);
}

// int	main(void)
//{
//	int i = 12831084;

//	printf("\n%d\n", ft_put_hex_x(i, 0));
//	printf("%x\n", i);
//}