/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:37:54 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 17:14:18 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if ((const unsigned char)*s == uc)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == '\0' && uc == '\0')
		return ((char *)s);
	return (NULL);
}

//#include <stdio.h>
//#include <string.h>

// int	main(void)
//{
//	char s[] = "42Tokyo";
//	int c = 'T';

//	printf("%s\n", ft_strchr(s, c));
//}