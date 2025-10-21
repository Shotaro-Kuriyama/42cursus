/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:31:53 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 18:04:45 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
#include <stdlib.h>
void *calloc(size_t nmemb, size_t size);

callocの説明
calloc関数は、大きさがsizeであるオブジェクトのnmemb個の配列の領域を割り付ける。その領域のすべてのビットは、0で初期化する
JISX3010 プログラム言語Ｃ

nmemb
nmembには、sizeで指定したサイズの領域が何個必要か、個数を指定します。

size
sizeには、1単位あたりのバイトサイズを指定します。

返却値
nmemb * sizeで指定したサイズのメモリ領域確保に
成功した場合は、確保したメモリ領域の先頭ポインタを返します。
失敗した場合は、NULLポインタを返します。
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *p;
	unsigned char d;
	size_t i;
	
	p = (unsigned char*)s;
	d = (unsigned char)c;
	
	i = 0;
	while (i < n)
	{
		p[i] = d;
		i++;
	}

	return s;
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;

	if (nmemb == 0 || size == 0)
	{
		p = malloc(1);
		if (!p)
			return NULL;
		return p;
	}
	if (nmemb > SIZE_MAX / size)
		return NULL;

	p = (unsigned char *)malloc(nmemb * size);
	if (!p)
		return NULL;
	
	ft_memset(p, 0, nmemb * size);
	return p;	
}

int main(void)
{
	size_t nmemb = 10;
	size_t size = 2;


	unsigned char *p = ft_calloc(nmemb, size);

	size_t i = 0;
	while (i < nmemb * size)
	{
		printf ("%02X ", p[i]);
		i++;
	}
	printf("%c", '\n');

	free(p);
	return 0;
}