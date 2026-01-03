/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:08:05 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:57:23 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d == s || len == 0)
		return (dst);
	if (d < s)
		ft_memcpy(d, s, len);
	else
	{
		i = len;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dst);
}

//#include <stdio.h>
//#include <string.h>

//int	main(void)
//{
//	char	buf[] = "apple";
//	char	buf2[] = "apple";

//	printf("%s\n", buf + 2);
//	memmove(buf + 2, buf, 2);
//	printf("%s\n", buf + 2);
//	ft_memmove(buf2 + 2, buf2, 2);
//	printf("%s\n", buf2 + 2);
//	return (0);
//}
