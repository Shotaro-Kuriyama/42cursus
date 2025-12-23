/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:16:21 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:57:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (s[i] && i < dstsize)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;
	size_t	space;

	src_len = ft_strlen(src);
	dst_len = ft_strnlen(dst, dstsize);
	if (dstsize == dst_len)
		return (dstsize + src_len);
	space = dstsize - dst_len - 1;
	i = 0;
	while (i < space && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

//#include <stdio.h>

// int	main(void)
//{
//	char	dst[16] = "42Tokyo";
//	char	src[8] = "Skytree";
//	size_t	i;

//	i = ft_strlcat(dst, src, (size_t)11);
//	printf("%zu\n", i);
//	printf("%s\n", dst);
//	return (0);
//}
