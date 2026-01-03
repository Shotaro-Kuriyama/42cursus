/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:09:38 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/09 16:51:04 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t len)
{
	const unsigned char	*p;
	size_t				i;
	unsigned char		uc;

	if (!s)
		return (NULL);
	uc = (unsigned char)c;
	p = (const unsigned char *)s;
	i = 0;
	while (i < len)
	{
		if (p[i] == uc)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}

//#include <stdio.h>

// int	main(void)
//{
//	char str[] = "42Tokyo";
//	int c = 'o';
//	size_t len = sizeof(str);

//	char *p;

//	p = ft_memchr(str, c, len);

//	printf("%s\n", p);
//}