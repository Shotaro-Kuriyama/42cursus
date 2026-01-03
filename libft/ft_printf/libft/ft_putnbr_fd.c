/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:33:02 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:25:17 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	char	c;

	i = n;
	if (i < 0)
	{
		(void)write(fd, "-", 1);
		i = -i;
	}
	if (i > 9)
		ft_putnbr_fd(i / 10, fd);
	c = (char)((i % 10) + '0');
	ft_putchar_fd(c, fd);
}

// int	main(void)
//{
//	ft_putnbr_fd(0, 1);
//	(void)write(1, "\n", 1);
//	ft_putnbr_fd(7, 1);
//	(void)write(1, "\n", 1);
//	ft_putnbr_fd(-42, 1);
//	(void)write(1, "\n", 1);
//	ft_putnbr_fd(2147483647, 1);
//	(void)write(1, "\n", 1);
//	ft_putnbr_fd(-2147483648, 1);
//	(void)write(1, "\n", 1);
//	return (0);
//}