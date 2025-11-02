/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:10:05 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:53:55 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*b1;
	const unsigned char	*b2;
	size_t				i;

	b1 = (const unsigned char *)s1;
	b2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (b1[i] != b2[i])
			return ((int)b1[i] - (int)b2[i]);
		i++;
	}
	return (0);
}

//#include <stdio.h>

// static void	dump_bytes(const void *p, size_t n)
//{
//	const unsigned char	*b = (const unsigned char *)p;
//	size_t				i;

//	i = 0;
//	while (i < n)
//	{
//		printf("%02X ", b[i]);
//		i++;
//	}
//	printf("\n");
//}

// int	main(void)
//{
//	char s1[] = "42Tokyo";
//	char s2[] = "42Kyoto";
//	size_t n1 = 4;

//	int j = 123173831;
//	int k = 182874326;
//	size_t n2 = sizeof j; // 可搬性◎

//	printf("ft_memcmp(s1,s2,%zu) = %d\n", n1, ft_memcmp(s1, s2, n1)); // 例：9

//	printf("j bytes: ");
//	dump_bytes(&j, n2);
//	printf("k bytes: ");
//	dump_bytes(&k, n2);
//	printf("ft_memcmp(&j,&k,%zu) = %d\n", n2, ft_memcmp(&j, &k, n2));
//}