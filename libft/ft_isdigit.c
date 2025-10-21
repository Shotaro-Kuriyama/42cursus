/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:43:49 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/16 10:49:44 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

/*
isdigit()
checks for a digit (0 through 9).

約
isdigit()
数字（0から9）かどうかを確認します。

int isdigit(int c);
*/

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return 1;

	return 0;
}

int main(void)
{
	char c = 'A';
	printf("%d\n", isdigit(c));
	printf("%d\n", ft_isdigit(c));
}	

