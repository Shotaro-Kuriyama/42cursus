/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:31:22 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:12:02 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	count_word(const char *s, char c)
{
	size_t	in_word;
	size_t	count;

	in_word = 1;
	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s != c && in_word == 1)
		{
			count++;
			in_word = 0;
		}
		else if (*s == c)
			in_word = 1;
		s++;
	}
	return (count);
}

static char	*str_dup(const char *start, size_t len)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = start[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void	*free_all(char **arr, size_t filled)
{
	while (filled > 0)
	{
		--filled;
		free(arr[filled]);
	}
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char		**p;
	size_t		word;
	size_t		i;
	const char	*start;

	word = count_word(s, c);
	p = (char **)malloc(sizeof(*p) * (word + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (*s && i < word)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		p[i] = str_dup(start, (size_t)(s - start));
		if (!p[i])
			return (free_all(p, i));
		i++;
	}
	p[i] = NULL;
	return (p);
}

//#include <stdio.h>

// int	main(void)
//{
//	char s[] = {",,,,,42Tokyo,Apple,,,Google,,,"};
//	char c = ',';
//	char **p = ft_split(s, c);

//	size_t i;

//	i = 0;
//	while (p[i])
//	{
//		printf("%s\n", p[i]);
//		free(p[i]);
//		i++;
//	}
//	free(p);
//}