/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:04:55 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/09 18:35:00 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int n)
{
	int		count;
	char	*nbraddr;

	count = 0;
	nbraddr = ft_itoa_u(n);
	count = ft_putstr(nbraddr);
	if (count < 0)
	{
		free(nbraddr);
		return (-1);
	}
	free(nbraddr);
	return (count);
}

// int	main(void)
//{
//	int i = -423;

//	printf("\n%d\n", ft_putunbr(i));
//	printf("%u\n", i);

//}