/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:48:06 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/12 13:29:17 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	(void)write(fd, s, ft_strlen(s));
}

// int	main(void)
//{
//	char s[] = "42Tokyo";

//	ft_putstr_fd(s, 2);
//}