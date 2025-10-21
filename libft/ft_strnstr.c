/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:10:27 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 15:31:42 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式
     #include <string.h>

     char *
     strstr(const char *big, const char *little);

     char *
     strcasestr(const char *big, const char *little);

     char *
     strnstr(const char *big, const char *little, size_t len);

     #include <string.h>
     #include <xlocale.h>

     char *
     strcasestr_l(const char *big, const char *little, locale_t loc);

解説
     strstr() 関数は、ヌル文字で終了する文字列 big 中に最初に出現するヌル文字
     で終了する文字列 little に位置付けます。

     strcasestr() 関数は、strstr() と同様ですが、両方の文字列の大文字と小文字
     を無視します。

     strcasestr_l() 関数は、strcasestr() と同じこと行いますが、現在のロケール
     を使用するのではなく明示的なロケールを試みます。

     strnstr() 関数は、文字列 big 中に最初に出現するヌル文字で終了する文字列
     little に位置付けます、ここで、len 文字を越える文字は、検索されません。
     `\0' 文字の後に現れる文字は、検索されません。strnstr() 関数は、FreeBSD 特
     有の API であるので、移植性に関係がないときのみ利用されるべきです。

戻り値
     little が空の文字列であるなら、big が返されます。little が big のどこにも
     現れないなら、NULL が返されます。そうでなければ、最初に出現した little の
     最初の文字へのポインタが返されます。

使用例
     次は、largestring の "Bar Baz" 部分にポインタ ptr を設定します。

           const char *largestring = "Foo Bar Baz";
           const char *smallstring = "Bar";
           char *ptr;

           ptr = strstr(largestring, smallstring);

     次は、ポインタ ptr を NULL に設定します、なぜなら largestring の最初の 4
     文字だけが検索されるためです:

           const char *largestring = "Foo Bar Baz";
           const char *smallstring = "Bar";
           char *ptr;

           ptr = strnstr(largestring, smallstring, 4);
*/


#include <stddef.h>
#include <stdio.h>


char *ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (little[0] == '\0')
		return (char *)big;
	if (len == 0)
		return NULL;
	
		while(i < len && big[i])
		{
			j = 0;
			while (i + j < len && big[i + j] && little[j] && big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return (char *)(big + i);
			i++;
		}
		return NULL;
}

int main(void)
{
	char big[] = "42Tokyo";
	char little[] = "o";
	size_t i = 2;

	printf ("%s\n", ft_strnstr(big, little, i));
}

