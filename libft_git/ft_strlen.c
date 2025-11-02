/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:42:54 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:58:00 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//#include <stddef.h>
//#include <stdio.h>

// int	main(void)
//{
//	char	str[] = "42Tokyo";

//	printf("%zu\n", ft_strlen(str)); // size_t型は%zu
//	return (0);
//}
