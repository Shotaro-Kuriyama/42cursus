/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shotarokuriyama <shotarokuriyama@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:16 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/04 10:26:56 by shotarokuri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		count;
	char	*nbraddr;
	long	num;

	num = n;
	count = 0;
	nbraddr = ft_itoa(num);
	count = ft_putstr(nbraddr);
	free(nbraddr);
	if (count < 0)
		return (-1);
	return (count);
}

// int	main(void)
//{
//	int i = -87965407;

//	printf("\n%d\n", ft_putnbr(i));

//}