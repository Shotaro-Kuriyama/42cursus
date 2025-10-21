/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:12 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 12:49:03 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式

#include <string.h>


char *
strrchr(const char *s, int c);

解説
strrchr() 関数は、文字列 s 中の (char に変換された) c が最後に出現する位置を探します。 c が ‘\0’ のときは strrchr() は終端の ‘\0’ の位置を示します。

戻り値
strrchr() 関数は該当する文字へのポインタを返します。 また、 s 中のどこにも c が出現しない場合は NULL ポインタを返します。
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char uc;
	int i;
	int j;

	uc = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;

	j = 0;
	if (uc == '\0')
	{
		while(j < i)
		{
			s++;
			j++;
		}
		return (char *)s;
	}
	i--;
	while(i > 0)
	{
		if ((unsigned char)s[i] == uc)
		{
			while(j < i)
			{
				s++;
				j++;
			}
			return (char *)s;
		}
		i--;
	}
	return NULL;
}

int main(void)
{
	char s[] = "42Tokyo";
	int c = 'o';

	printf("%s\n", strrchr(s, c));
}