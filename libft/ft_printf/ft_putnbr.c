/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:16 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/09 18:35:24 by skuriyam         ###   ########.fr       */
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