/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:19:10 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:56:33 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*p;
	size_t	i;

	s_len = ft_strlen(s);
	p = malloc(sizeof(*p) * (s_len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	char	s[] = "42Tokyo";
//	char	*p;

//	p = ft_strdup(s);
//	printf("%s\n", p);
//	free(p);
//	return (0);
//}
