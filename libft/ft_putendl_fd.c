/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:58:08 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 17:13:39 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	(void)write(fd, s, len);
	(void)write(fd, "\n", 1);
}

// int	main(void)
//{
//	ft_putendl_fd("42Tokyo", 1);
//	ft_putendl_fd("Apple", 2);
//	return (0);
//}
