/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:39:32 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:54:06 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*q;
	size_t				i;

	p = (unsigned char *)dest;
	q = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dest);
}

//#include <stdio.h>
//#include <string.h>
//#include <stddef.h>

// int	main(void)
//{
//	char	src[] = "123456789";
//	char	dst1[] = "ABCDDEFG";
//	char	dst2[] = "ABCDDEFG";
//	char	a1[] = "ABCDE";
//	char	a2[] = "ABCDE";

//	// 3バイトだけコピー（重なりなしの基本ケース）
//	memcpy(dst1, src, 3);
//	ft_memcpy(dst2, src, 3);
//	printf("コピー後 dst1(標準) → %s\n", dst1); // "123DDEFG"
//	printf("コピー後 dst2(自作) → %s\n", dst2); // "123DDEFG"
//	printf("元の src         → %s\n", src);
//	// 重なりあり: 右へ1バイトずらす
//	// a1はmemcpy（未定義動作の例）、a2はmemmove（定義済み）
//	ft_memcpy(a1 + 1, a1, 3); // 未定義動作：多くの実装で "AAAAE"
//	memmove(a2 + 1, a2, 3);   // 定義された動作："AABCE"
//	printf("memcpy : %s\n", a1);
//	printf("memmove: %s\n", a2);
//	return (0);
//}
