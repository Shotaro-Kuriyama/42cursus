/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:25 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/18 11:08:03 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
       bzero, explicit_bzero - バイト文字列をゼロで埋める

SYNOPSIS
       #include <strings.h>

       void bzero(void *s, size_t n);

       #include <string.h>

       void explicit_bzero(void *s, size_t n);

説明
bzero() 関数は、s が指す位置から始まるメモリの n バイト分のデータを、
その領域にゼロ（『\0』 を含むバイト）を書き込むことで消去します。

explicit_bzero() 関数は bzero() と同じ処理を行う。bzero() との違いは、コンパイラが
この操作を「不要」と判断した場合に、コンパイラの最適化によって消去操作が除去されないことを
保証する点にある。

戻り値
なし。

バージョン
explicit_bzero() は glibc 2.25 で初めて登場した。

属性
このセクションで使用される用語の説明については attributes(7) を参照のこと。
*/

#include <stdio.h>
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	size_t i;
	unsigned char *p;

	p = (unsigned char*)s;
	
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

int main(void)
{
	char buf[] = "ABCDEFGHIJK";
	char buf2[] = "ABCDEFGHIJK";

	bzero(buf+2, 5);
	ft_bzero(buf2+2, 5);

	printf("%s\n", buf);
	printf("%s\n", buf2);
}