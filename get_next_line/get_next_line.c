/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:41:59 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/23 11:04:31 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cleanup(char **stash, t_gnl *reader)
{
	if (reader && reader->buf)
	{
		free(reader->buf);
		reader->buf = NULL;
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
	t_gnl	reader;

	reader.buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!reader.buf)
		return (cleanup(stash, &reader));
	reader.bytes_read = 1;
	while (!ft_has_newline(*stash) && reader.bytes_read > 0)
	{
		reader.bytes_read = read(fd, reader.buf, BUFFER_SIZE);
		if (reader.bytes_read < 0)
			return (cleanup(stash, &reader));
		if (reader.bytes_read == 0)
			break ;
		reader.buf[reader.bytes_read] = '\0';
		*stash = gnl_strjoin(*stash, reader.buf);
		if (!*stash)
			return (cleanup(stash, &reader));
	}
	free(reader.buf);
	reader.buf = NULL;
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

#include <fcntl.h>
#include <stdio.h>

 int	main(void)
{
	int		fd;
	char	*line;

	fd = open("mandatory_test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
