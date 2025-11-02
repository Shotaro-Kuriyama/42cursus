/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:46:20 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 11:39:04 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static char	*empty_string(void)
{
	char	*p;

	p = (char *)malloc(1);
	if (!p)
		return (NULL);
	p[0] = '\0';
	return (p);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	copy_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= (size_t)start)
		return (empty_string());
	copy_len = s_len - (size_t)start;
	if (copy_len < len)
		len = copy_len;
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s + (size_t)start, len);
	result[len] = '\0';
	return (result);
}

//#include <stdio.h>

// int	main(void)
//{
//	char s[] = "ToKyoSkytree";
//	unsigned int start = 3;
//	size_t len = 4;

//	printf("%s\n", ft_substr(s, start, len));
//}