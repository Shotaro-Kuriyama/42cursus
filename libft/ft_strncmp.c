/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:58:09 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 15:08:08 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式

#include <string.h>

int
strcmp(const char *s1, const char *s2);

int
strncmp(const char *s1, const char *s2, size_t len);

解説
strcmp() および strncmp() 関数は、ヌル文字で終了する文字列 s1 および s2 を辞書式順序で比較します。

strncmp() 関数は、 len 文字分の比較をします。 strncmp() は、バイナリデータより 文字列の比較のために設計されているので、
 ‘\0’ 文字の後に現れる文字列は比較されません。

 戻り値
strcmp() および strncmp() は、 s1 が s2 よりも大きいか、等しいか、あるいは小さいかに応じて、 
それぞれ 0 よりも大きい、0 に等しい、 あるいは 0 よりも小さい整数を返します。
比較は、 ‘\200’ が ‘\0’ よりも大きくなるように、unsigned char を使って行います。
*/

#include <stddef.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t i;
	
	i = 0;

	  if (len == 0)
        return 0;

	while (i < len && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	  if (i == len)                     // len文字すべて一致
        return 0;
    // どちらかが '\0' で止まった／または最後の1文字比較
    return (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(void)
{
    char s1[] = "42Tokyo";
    char s2[] = "ず";
    size_t len = 3;

    printf("%d\n", ft_strncmp(s1, s2, len));
}
