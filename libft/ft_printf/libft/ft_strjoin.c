/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:00:50 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/09 18:08:25 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	join(const char *s, char *p)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*p;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		i = join(s1, p);
	j = 0;
	if (s2 != NULL)
		j = join(s2, (p + i));
	p[i + j] = '\0';
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	char	s2[] = "Skytree";
//	char	*s1;
//	char	*joined;

//	// char	s1[] = "42Tokyo";
//	s1 = NULL;
//	joined = ft_strjoin(s1, s2);
//	printf("%s\n", joined);
//	free(joined);
//}
