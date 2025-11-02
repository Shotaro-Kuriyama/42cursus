/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:42:41 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 11:55:48 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	trim_count(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	count;
	size_t	len;
	size_t	start;
	char	*p;

	count = 0;
	len = ft_strlen(s1);
	while (s1[count] && trim_count(set, s1[count]) == 1)
		count++;
	while (len > count && trim_count(set, s1[len - 1]) == 1)
		len--;
	p = malloc(sizeof(*p) * (len - count + 1));
	if (!p)
		return (NULL);
	start = 0;
	while (start < (len - count))
	{
		p[start] = s1[start + count];
		start++;
	}
	p[start] = '\0';
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	char s1[] = "42Tokyo";
//	char set[] = "42o";
//	char *p;

//	p = ft_strtrim(s1, set);
//	printf("%s\n", p);
//	free(p);
//	return (0);
//}