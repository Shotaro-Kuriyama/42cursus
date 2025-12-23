/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:53:49 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 17:15:12 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	const char		*last;

	uc = (unsigned char)c;
	last = NULL;
	while (*s)
	{
		if ((const unsigned char)*s == uc)
			last = s;
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return ((char *)last);
}

//#include <stdio.h>

// int	main(void)
//{
//	char	s[] = "42Tokyo";
//	char	c;
//	char	*p;

//	c = 'o';
//	p = ft_strrchr(s, (int)c);
//	printf("%s\n", p);
//}
