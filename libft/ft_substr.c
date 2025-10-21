/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:46:20 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 20:51:00 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while(s[i])
		i++;
	return i;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{

	unsigned char *p;
	const unsigned char *q;
	size_t i;

	p = (unsigned char*)dest;
	q = (const unsigned char*)src;


	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dest);
}

static char	*ft_empty_string()
{
	char *p;

	p = malloc(1);
	if (!p)
		return NULL;
	
	p[0] = '\0';
	return p;
}


char *ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t st;
	char *ret;
	size_t s_len;

	if (!s)
		return NULL;

	s_len = ft_strlen(s);

	st = start;
	if (s_len <= st)
		return (ft_empty_string());

	if(s_len - st < len)
		len = s_len - st;

	ret = malloc(sizeof(*ret) * (len + 1));
	if (!ret)
		return NULL;

	ft_memcpy(ret, s+st, len);
	ret[len] = '\0';
	return ret;
}

int main(void)
{
	char s[] = "ToKyoSkytree";
	unsigned int start = 3;
	size_t len = 4;
	
	printf("%s\n", ft_substr(s, start, len));
}