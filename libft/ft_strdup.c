/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:19:10 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 18:40:02 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式

#include <string.h>


char *
strdup(const char *str);
解説
strdup() 関数は、文字列 str のコピーのために十分なメモリを割り当て、コピーを行い、 
コピーへのポインタを返します。ポインタは後で関数 free(3) の引数として使ってください。

利用可能なメモリが十分ではない場合、NULL を返します。 
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return i;
}



char *ft_strdup(const char *s)
{
	size_t s_len;
	char *p;
	size_t i;

	s_len = ft_strlen(s);

	p = malloc(sizeof(*p) *(s_len + 1));
	if (!p)
		return NULL;

	i = 0;
	while(i < s_len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return p;
}

int main(void)
{
	char s[] = "42Tokyo";


	char *p = ft_strdup(s);
	printf("%s\n", p);

	free(p);
	return 0;
}
