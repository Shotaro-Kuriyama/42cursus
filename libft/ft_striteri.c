/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:29:45 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/24 18:20:40 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#ft_striteri は「各文字に対して ‘インデックス付きで’ コールバックを呼び出し、
文字を“その場で”書き換えられるように文字のアドレスを渡す」関数です。返り値はありません。

仕様のポイント（超要約）

s が指す“既存の文字列”を破壊的に変更したいときに使う

コールバック f(i, &s[i]) は i 番目の文字を自由に変更してOK

s == NULL または f == NULL のときは何もしないで終了

追加の確保は不要（外部関数なし）
*/

#include <stddef.h>
#include <stdio.h>

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int i;

	if (!s || !f)
		return;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]); 
		i++;
	}
}

static void to_upper_cb(unsigned int i, char *c)
{
	(void)i;                // インデックスを使わない場合は無視でOK
	if (*c >= 'a' && *c <= 'z')
		*c = (char)(*c - ('a' - 'A')); // または *c = (char)toupper((unsigned char)*c);
}


static void zigzag_cb(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
	{
		if (i % 2 == 0) 
			*c = (char)(*c - ('a' - 'A')); // 偶数は大文字
	}
	else if (*c >= 'A' && *c <= 'Z')
	{
		if (i % 2 == 1) 
			*c = (char)(*c + ('a' - 'A')); // 奇数は小文字
	}
}

int main(void)
{
	char s[] = "LibftStrIteri";
	char s1[] = "42Tokyo";
	ft_striteri(s, zigzag_cb);
	printf("%s\n", s);
	
	ft_striteri(s1, to_upper_cb);
	printf("%s\n", s1);
	return 0;
}

