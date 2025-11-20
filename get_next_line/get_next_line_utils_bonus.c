/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:20:16 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/20 16:34:50 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_newline_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (++i);
		i++;
	}
	return (i);
}

int	ft_has_newline(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(*res) * (len1 + len2 + 1));
	if (!res)
		return (free(s1), NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*gnl_get_line(char *stash)
{
	size_t	i;
	size_t	len;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	len = ft_newline_strlen(stash);
	line = (char *)malloc(sizeof(*line) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_get_rest(char *stash)
{
	size_t	total;
	size_t	len;
	char	*rest;
	size_t	i;

	if (!stash)
		return (NULL);
	total = ft_strlen(stash);
	len = ft_newline_strlen(stash);
	if (len >= total)
		return (free(stash), NULL);
	rest = (char *)malloc(sizeof(*rest) * ((total - len) + 1));
	if (!rest)
		return (free(stash), (NULL));
	i = 0;
	while (i < (total - len))
	{
		rest[i] = stash[len + i];
		i++;
	}
	rest[i] = '\0';
	free(stash);
	return (rest);
}
