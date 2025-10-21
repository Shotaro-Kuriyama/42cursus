/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:39:32 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/18 19:15:07 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
       memcpy - メモリ領域のコピー

SYNOPSIS
       #include <string.h>

       void *memcpy(void *dest, const void *src, size_t n);

DESCRIPTION
       memcpy() 関数は、メモリ領域 src から n バイトをメモリ領域 dest にコピーします。
	   メモリ領域は重複してはいけません。 領域が重複する場合は memmove(3) を使用すること。

戻り値
       memcpy() 関数は dest へのポインタを返す。

属性
       この節で使用される用語の説明については attributes(7) を参照のこと。
*/

#include <stddef.h>


void	*ft_memcpy(void *dest, const void *src, size_t n)
{

	unsigned char *p;
	const unsigned char *q;
	size_t i;

	p = (unsigned char*)dest;
	q = (const unsigned char*)src;


	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dest);
}

#include <stdio.h>
#include <string.h>

int main(void)
{
	char src[]  = "123456789";
	char dst1[] = "ABCDDEFG";
	char dst2[] = "ABCDDEFG";

	// 3バイトだけコピー（重なりなしの基本ケース）
	memcpy(dst1, src, 3);
	ft_memcpy(dst2, src, 3);

	printf("コピー後 dst1(標準) → %s\n", dst1); // "123DDEFG"
	printf("コピー後 dst2(自作) → %s\n", dst2); // "123DDEFG"
	printf("元の src         → %s\n", src);

	char a1[] = "ABCDE";
    char a2[] = "ABCDE";

    // 重なりあり: 右へ1バイトずらす
    // a1はmemcpy（未定義動作の例）、a2はmemmove（定義済み）
    ft_memcpy(a1 + 1, a1, 3);    // 未定義動作：多くの実装で "AAAAE"
    memmove(a2 + 1, a2, 3);   // 定義された動作："AABCE"

    printf("memcpy : %s\n", a1);
    printf("memmove: %s\n", a2);

    return 0;
}



