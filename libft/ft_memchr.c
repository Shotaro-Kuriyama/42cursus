/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:09:38 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 11:07:45 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式

#include <string.h>


void *
memchr(const void *b, int c, size_t len);

解説
memchr() 関数は、 バイト列 b 中で (unsigned char に変換された) c が最初に見つかった位置を示します。

戻り値
memchr() 関数は、該当するバイトのポインタ、 または該当するバイトが len 個のバイト中に存在しない時は NULL を返します。

*/

#include <stddef.h>
#include <stdio.h>


void	*ft_memchr(const void *s, int c, size_t len)
{
	const unsigned char *p;
	size_t i;
	unsigned char uc;

	uc = (unsigned char)c;
	p = (const unsigned char *)s;	//voidのポインタsは任意のポインタを指す→(unsigned char)、つまり1バイトずつ操作できる型にキャストする

	i = 0;
	while (i < len)
	{
		if (p[i] == uc)
			return (void *)(p + i);
		i++;
	}

	/*
	 while (len--)
    {
        if (*p == uc)
            return (void *)p;   // 明示キャストは任意（なくてもOK）
        p++;
    }
	*/

	return NULL;
}


int main(void)
{
	char str[] = "42Tokyo";
	int c = 'o';
	size_t len = sizeof(str);

	char *p;

	p = ft_memchr(str, c, len);

	printf ("%s\n", p);
}