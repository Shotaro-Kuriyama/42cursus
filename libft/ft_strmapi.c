/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:18:38 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 17:14:37 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*p;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	p = (char *)malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = f((unsigned int)i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}

//#include <stdio.h>

// static char	ft_toupper1(unsigned int i, char c)
//{
//	unsigned char	uc;

//	(void)i;
//	uc = (unsigned char)c;
//	if (uc >= 'a' && uc <= 'z')
//		return (uc - ('a' - 'A'));
//	return (c);
//}
// int	main(void)
//{
//	char s[] = "42Tokyo";

//	char *f;

//	f = ft_strmapi(s, ft_toupper1);
//	printf("%s\n", f);
//}