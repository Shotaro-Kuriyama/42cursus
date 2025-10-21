/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:37:54 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 12:14:30 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
書式

#include <string.h>


char *
strchr(const char *s, int c);

解説
strchr() 関数は、 s によって指される文字列の中で最初に出会う文字 c を見つけます。
終端のヌル文字は、文字列の一部とみなします。 c が ‘\0’ である場合は、 strchr() は終端の ‘\0’ を見つけます。

戻り値
関数 strchr() は、見つけた文字へのポインタか、 または文字が文字列中に見つからない場合は NULL を返します。
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			return (char*)s;
		s++;
	}
	if ((unsigned char)*s == '\0' && uc == '\0') //最後にucがnullのときにちゃんとヌル文字を返す
		return (char*)s;
	return NULL;
}

int main(void)
{
	char s[] = "42Tokyo";
	int c = 'T';

	printf("%s\n", ft_strchr(s, c));
}