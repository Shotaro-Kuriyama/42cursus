/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:57:02 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/23 16:50:51 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return i;

}

static int trim_count(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return 1;
		s++;
	}
	return 0;
}

char *ft_strtrim(const char *s1, const char *set)
{
	size_t i;
	size_t count;
	size_t len;
	size_t count2;
	char *p;

	count = 0;
	count2 = 0;
	len = ft_strlen(s1);
	i = 0;
	while (s1[count] && trim_count(set, s1[count]))
			count++;
	
	i = len;
	while (i > 0)
	{
		if(trim_count(set, s1[i - 1]))
			count2++;
		else
			break;
		i--;
	}

	p = malloc(sizeof(*p) * (len - count - count2 + 1));

	i = 0;
	while (i < (len - count - count2))
	{
		p[i] = s1[i + count];
		i++;
	}
	p[i] = '\0';
	return p;
	
}
int main(void)
{
	char s1[] = "42Tokyo";
	char set[] = "42ok";
	char *p;

	p = ft_strtrim(s1, set);
	printf("%s\n", p);
	free(p);
	return 0;
}

