/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:09 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/13 11:33:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *q)
{
	unsigned long long	addr;
	int					count;
	char				*p;
	int					r;

	count = 0;
	if (!q)
	{
		if (write(1, "(nil)", 5) != 5)
			return (-1);
		return (5);
	}
	r = write(1, "0x", 2);
	if (r <= 0)
		return (-1);
	count += r;
	addr = (unsigned long long)q;
	p = ft_itoa_hex(addr);
	r = ft_putstr(p);
	free(p);
	if (r < 0)
		return (-1);
	count += r;
	return (count);
}

// int	main(void)
//{
//	char *p;
//	void *q;
//	unsigned char *r = NULL;
//	void *s = NULL;

//	printf("\n%d\n", ft_putptr(p));
//	printf("\n%d\n", ft_putptr(q));
//	printf("\n%d\n", ft_putptr(r));
//	printf("\n%d\n", ft_putptr(s));

//}