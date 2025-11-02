/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:10:27 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:05:11 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (i < len && big[i])
	{
		j = 0;
		while (i + j < len && big[i + j]
			&& little[j] && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

//#include <stdio.h>

// int	main(void)
//{
//	char	big[] = "42Tokyo";
//	char	little[] = "o";
//	size_t	i;

//	i = 2;
//	printf("%s\n", ft_strnstr(big, little, i));
//}
