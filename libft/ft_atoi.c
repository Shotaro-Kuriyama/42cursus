/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:32:25 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 15:51:01 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
名前

       atoi, atol, atoll - 文字列を整数型に変換する

書式

       #include <stdlib.h>

       int atoi(const char *nptr);
       long atol(const char *nptr);
       long long atoll(const char *nptr);

   glibc 向けの機能検査マクロの要件 (feature_test_macros(7)  参照):

       atoll():
           _BSD_SOURCE || _SVID_SOURCE || _XOPEN_SOURCE >= 600 || _ISOC99_SOURCE || _POSIX_C_SOURCE >= 200112L;
           または cc -std=c99

説明

       atoi()   関数は、nptr  によって指示される文字列のはじめの部分を  int  型整数に変換する。 この振る舞いは、
       atoi()  関数がエラーを見つけない点以外は、

           strtol(nptr, NULL, 10);

       と同じである。

       atol()  関数と atoll()  関数は atoi()  と同様の振る舞いをするが、 文字列のはじめの部分をそれぞれ long  や
       long long に変換する。

返り値

       変換された値。
*/

#include <stdio.h>

int ft_atoi(const char *nptr)
{
	int a;
	int result;

	a = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			a = -a;
		nptr++;
	}
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (a * result);
}

int main(void)
{

	char nptr[] = "  \n\t   -123155343";

	printf("%d\n", ft_atoi(nptr));

}