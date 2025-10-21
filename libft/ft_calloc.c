/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:31:53 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 17:27:15 by skuriyam         ###   ########.fr       */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char *p;
	unsigned char s;
	size_t i;

	if (nmemb == 0 || size == 0)
	{
		p = malloc(1);
		return p;
	}
	s = (unsigned char)size;

	p = (unsigned char *)malloc(size * nmemb);
	if (!p)
		return NULL;

	i = 0;
	while(i < size * nmemb)
	{
		p[i] = 0;
		i++;
	}
	return p;
}

int main(void)
{
	size_t nmemb = 10;
	size_t size = 0;
	size_t i = 0;

	unsigned char *p = ft_calloc(nmemb, size);
	while (i < nmemb * size)
	{
		printf ("%02X", p[i]);
		printf ("%c", ' ');
		i++;
	}
	printf("%c", '\n');
}