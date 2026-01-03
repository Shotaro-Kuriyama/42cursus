/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:31:53 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 17:11:48 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;

	if (nmemb == 0 || size == 0)
	{
		p = malloc(1);
		if (!p)
			return (NULL);
		return (p);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	p = (unsigned char *)malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, nmemb * size);
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	size_t nmemb = 20;
//	size_t size = 4;

//	unsigned char *p = ft_calloc(nmemb, size);

//	size_t i = 0;
//	while (i < nmemb * size + 1)
//	{
//		printf("%02X ", p[i]);
//		i++;
//	}
//	printf("%c", '\n');

//	free(p);
//	return (0);
//}