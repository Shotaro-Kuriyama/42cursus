/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:51:39 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/23 19:31:54 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static size_t word_count(const char *s, char c)
{
	size_t count;
	size_t i;
	size_t	l;

	i = 0;
	l = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && l == 0)
		{
			count++;
			l = 1;
		}
		else if(s[i] == c)
			l = 0;
		i++;
	}
	return count;
}

static char *count(const char *start, size_t len)
{
	char	*ret;
	size_t	i;

	ret = malloc(sizeof(*start) * (len+ 1));
	i = 0;
	while (i < len)
	{
		ret[i] = start[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	size_t len;
	char **temp;
	const char *start;
	size_t i;

	len = word_count(s, c);

	temp = (char **)malloc(sizeof(*s) * (len + 1));
	if(!s)
		return NULL;
	i = 0;
	while (i < len)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		temp[i] = count(start, (size_t)(s - start));
		if (!temp)
			
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

int main(void)
{
	char *s = "42Tokyo Apple Google";
	char c = ' ';
	char **result = ft_split(s,c);
	for(int i = 0; result[i]; i++)
	printf("%s\n", result[i]);
}