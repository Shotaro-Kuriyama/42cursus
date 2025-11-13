/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:12 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/11 17:30:41 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex(unsigned int n, int i)
{
	int		count;
	char	*nbraddr;
	char	*toupper;

	count = 0;
	nbraddr = ft_itoa_hex(n);
	toupper = nbraddr;
	if (i == 1)
	{
		while (*toupper)
		{
			*toupper = ft_toupper(*toupper);
			toupper++;
		}
	}
	count = ft_putstr(nbraddr);
	free(nbraddr);
	if (count < 0)
		return (-1);
	return (count);
}

// int	main(void)
//{
//	int i = 12831084;

//	printf("\n%d\n", ft_put_hex(i, 1));
//	printf("%x\n", i);
//}