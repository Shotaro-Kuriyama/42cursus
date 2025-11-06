/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_itoa_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:04:55 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 16:58:09 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_put_itoa_u(unsigned int n)
{
	int		count;
	char	*nbrAddr;

	count = 0;
	nbrAddr = ft_itoa_u(n);
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
//	int i = -423;

//	printf("\n%d\n", ft_put_itoa_u(i));
//	printf("%u\n", i);

//}