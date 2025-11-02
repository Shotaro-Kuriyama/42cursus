/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:00:50 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:57:06 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*p;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	char	s1[] = "42Tokyo";
//	char	s2[] = "Skytree";
//	char	*joined;

//	joined = ft_strjoin(s1, s2);
//	printf("%s\n", joined);
//	free(joined); // ← 必ず解放！
//}
