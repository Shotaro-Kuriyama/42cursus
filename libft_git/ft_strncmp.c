/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:58:09 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 16:22:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	if (i == len)
		return (0);
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

//#include <stdio.h>

// int	main(void)
//{
//	char	s1[] = "42Tokyo";
//	char	s2[] = "\0";
//	size_t	len;

//	len = 3;
//	printf("%d\n", ft_strncmp(s1, s2, len));
//}
