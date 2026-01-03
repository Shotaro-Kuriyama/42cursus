/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:42:41 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/08 17:15:17 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(const char *s, char c)
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
	size_t	i;
	char	*p;

	count = 0;
	len = ft_strlen(s1);
	while (s1[count] && is_in_set(set, s1[count]) == 1)
		count++;
	while (len > count && is_in_set(set, s1[len - 1]) == 1)
		len--;
	p = malloc(sizeof(*p) * (len - count + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < (len - count))
	{
		p[i] = s1[i + count];
		i++;
	}
	p[i] = '\0';
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