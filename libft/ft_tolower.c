/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:19:02 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 11:38:30 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式

#include <ctype.h>


int
tolower(int c);
解説
tolower() 関数は大文字を対応する小文字に変換します。 C 言語の chars 型ひとつに関するロケール ( multibyte(3) 参照 ) のことを考慮して、
引数の値は unsigned char または EOF の値として表されなければなりません。

戻り値
引数が大文字である場合は、その文字に対応する小文字がある場合は tolower() 関数はそれを返します。
それ以外の場合は、その引数が変更されないまま返されます。

*/

#include <stdio.h>

#include <ctype.h>

int	ft_tolower(int c)
{
	unsigned char uc;

	uc = (unsigned char)c;

	if (uc >= 'A' && uc <= 'Z')
		return (uc + ('b' - 'B'));

	return uc;
}

int main(void)
{
	unsigned char c = 'A';
	unsigned char d = '1';


	printf("%c\n", (unsigned char)ft_tolower(c));
	printf("%c\n", tolower(d));
}