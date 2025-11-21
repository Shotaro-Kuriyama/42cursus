/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:41:59 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/21 17:54:46 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cleanup(char **stash, t_gnl *g)
{
	if (g && g->buf)
	{
		free(g->buf);
		g->buf = NULL;
	}
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (0);
}

static int	read_and_stash(int fd, char **stash)
{
	t_gnl	g;

	g.buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!g.buf)
		return (cleanup(stash, &g));
	g.n = 1;
	while (!ft_has_newline(*stash) && g.n > 0)
	{
		g.n = read(fd, g.buf, BUFFER_SIZE);
		if (g.n < 0)
			return (cleanup(stash, &g));
		if (g.n == 0)
			break ;
		g.buf[g.n] = '\0';
		*stash = gnl_strjoin(*stash, g.buf);
		if (!*stash)
			return (cleanup(stash, &g));
	}
	free(g.buf);
	g.buf = NULL;
	if (!*stash || !**stash)
		return (cleanup(stash, NULL));
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_and_stash(fd, &stash))
		return (NULL);
	line = gnl_get_line(stash);
	if (!line)
	{
		cleanup(&stash, NULL);
		return (NULL);
	}
	stash = gnl_get_rest(stash);
	return (line);
}

//#include <stdio.h>

//int	main(void)
//{
//	int fd;
//	char *p;

//	fd = open("test.txt", O_RDONLY);

//	while ((p = get_next_line(fd)) != NULL)
//	{
//		printf("%s", p);
//		free(p);
//	}
//	close(fd);
//}