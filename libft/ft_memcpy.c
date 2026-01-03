/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:39:32 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/09 17:24:20 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*q;
	size_t				i;

	if (!dest || !src)
		return (NULL);
	p = (unsigned char *)dest;
	q = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dest);
}

//int	main(void)
//{
//	char	*src1;
//	char	src2[] = "42Tokyo";
//	char	src3[] = "42Tokyo";
//	char	*dest1;
//	char	*p;

//	src1 = "42Tokyo";
//	dest1 = NULL;
//	p = ft_memcpy(dest1, src1, 2);
//	printf("%s\n", p);
//	ft_memcpy(src2 + 2, src2, 4);
//	printf("memcpy : %s\n", src2 + 2);
//	memmove(src3 + 2, src3, 4);
//	printf("memmove: %s\n", src3 + 2);
//	return (0);
//}
