/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:41:37 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/16 10:42:10 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

/*
isalpha()
アルファベット文字かどうかを判定します。標準の「C」ロケールでは、
(isupper(c) || islower(c)) と同等です。一部のロケールでは、
isalpha() が真となる追加の文字（大文字でも小文字でもない文字）が存在する可能性があります。

  int isalpha(int c);
*/

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;

	return 0;
}


int main(void)
{
	char c = '1';

	printf("%d\n",isalpha(c));
	printf("%d\n",ft_isalpha(c));
}

