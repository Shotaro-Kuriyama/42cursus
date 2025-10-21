/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:53:42 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/16 10:58:16 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
isalnum()
英数字文字をチェックします。これは (isalpha(c) || isdigit(c)) と同等です。
int isalnum(int c);
*/

#include <ctype.h>
#include <stdio.h>

 int ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return 1;

	return 0;

}

int main(void)
{

}


