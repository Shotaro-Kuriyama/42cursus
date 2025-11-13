/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:42:54 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 18:18:20 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// int	main(void)
//{
//	char	*p;

//	// char	str[] = "42Tokyo";
//	p = NULL;
//	printf("%zu\n", ft_strlen(p)); // size_t型は%zu
//	return (0);
//}
