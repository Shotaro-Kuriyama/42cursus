/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:16 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 15:57:49 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_put_itoa(int n)
{
	int		count;
	char	*nbrAddr;

	count = 0;
	nbrAddr = ft_itoa(n);
	count = ft_putstr(nbrAddr);
	if (count < 0)
	{
		free(nbrAddr);
		return (-1);
	}
	return (count);
}

// int	main(void)
//{
//	int i = -87965407;

//	printf("\n%d\n", ft_put_itoa(i));

//}