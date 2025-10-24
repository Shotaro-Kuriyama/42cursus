/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:18:38 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/24 17:28:02 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while(s[i])
		i++;

	return i;
}

char *ft_strmapi(const char *s, char (*f)(unsigned int, char))
{

	size_t len;
	char *p;
	size_t i;

	if (!s || !f)
		return NULL;
	len = ft_strlen(s);
	p = (char *)malloc(sizeof(*p) * (len + 1));
	if (!p)
		return NULL;

	i = 0;
	while (i < len)
	{
		p[i] = f((unsigned int)i, s[i]); //文字列sの各文字に対して関数fを適用
		//fの内容としては、そのインデックスを最初の引数として渡し、文字自体を二番目の引数として渡すので課題の内容そのもの。
		i++;
	}
	p[i] = '\0';
	return p;
}

static char ft_toupper(unsigned int i, char c)
{
	(void)i;
	unsigned char uc;

	uc = (unsigned char)c;
	if (uc >= 'a' && uc <= 'z')
       return (uc - ('a' - 'A'));
    return c;
}
int main(void)
{
	char s[] = "42Tokyo";

	char *f;

	f = ft_strmapi(s, ft_toupper);
	if (!f)
		return 1;

	printf("%s\n", f);
	
}