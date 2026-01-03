/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:26 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/13 17:38:42 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *c)
{
	int				i;
	int				r;
	unsigned char	uc;

	r = 0;
	i = 0;
	if (!c)
	{
		if (write(1, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (*c)
	{
		uc = *c;
		r = write(1, &uc, 1);
		if (r < 0)
			return (-1);
		c++;
		i++;
	}
	return (i);
}
