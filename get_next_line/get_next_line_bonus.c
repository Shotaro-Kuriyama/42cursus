/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:42:02 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/07 19:31:54 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_all(char **stash, t_gnl *reader)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (reader && reader->buf)
	{
		free(reader->buf);
		reader->buf = NULL;
	}
	return (NULL);
}

static t_gnl_list	*get_node(t_gnl_list **list, int fd)
{
	t_gnl_list	*cur;
	t_gnl_list	*new_node;

	cur = *list;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	new_node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = NULL;
	new_node->next = *list;
	*list = new_node;
	return (new_node);
}

static void	remove_node(t_gnl_list **list, int fd)
{
	t_gnl_list	*cur;
	t_gnl_list	*prev;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (prev)
				prev->next = cur->next;
			else
				*list = cur->next;
			if (cur->stash)
				free(cur->stash);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static char	*read_and_stash_bonus(int fd, t_gnl_list *node)
{
	t_gnl	reader;

	reader.buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!reader.buf)
		return (NULL);
	reader.bytes_read = 1;
	while (!ft_has_newline(node->stash) && reader.bytes_read > 0)
	{
		reader.bytes_read = read(fd, reader.buf, BUFFER_SIZE);
		if (reader.bytes_read < 0)
			return (free_all(&(node->stash), &reader));
		if (reader.bytes_read == 0)
			break ;
		reader.buf[reader.bytes_read] = '\0';
		node->stash = gnl_strjoin(node->stash, reader.buf);
		if (!node->stash)
			return (free(reader.buf), NULL);
	}
	free(reader.buf);
	if (!node->stash || !*(node->stash))
	{
		free(node->stash);
		return (node->stash = NULL, NULL);
	}
	return (node->stash);
}

char	*get_next_line(int fd)
{
	t_gnl_list			*node;
	char				*line;
	static t_gnl_list	*list = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&list, fd);
	if (!node)
		return (NULL);
	if (!read_and_stash_bonus(fd, node))
	{
		remove_node(&list, fd);
		return (NULL);
	}
	line = gnl_get_line(node->stash);
	if (!line)
	{
		remove_node(&list, fd);
		return (NULL);
	}
	node->stash = gnl_get_rest(node->stash);
	if (!node->stash)
		remove_node(&list, fd);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		perror("open");
		return (1);
	}

	char *line;
	char *fd3_line;
	while ((fd3_line = get_next_line(fd3)) != NULL)
	{
		if ((line = get_next_line(fd1)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd2)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		printf("%s", fd3_line);
		free(fd3_line);
	}
        printf("-------2-------------------------------agjorioajoijoijmo");
		printf("%s", get_next_line(fd1)); // test.txt の1行目
		printf("%s", get_next_line(fd2)); // test2.txt の1行目
		printf("%s", get_next_line(fd3)); // test3.txt の1行目

		printf("%s", get_next_line(fd1)); // test.txt の2行目
		printf("%s", get_next_line(fd2)); // test2.txt の2行目
		printf("%s", get_next_line(fd3)); // test3.txt の2行目

		printf("%s", get_next_line(fd1)); // test.txt の3行目
		printf("%s", get_next_line(fd2)); // test2.txt の3行目
		printf("%s", get_next_line(fd3)); // test3.txt の3行目

		printf("%s", get_next_line(fd2)); // test2.txt の4行目
		printf("%s", get_next_line(fd3)); // test3.txt の4行目

		printf("%s", get_next_line(fd3)); // test3.txt の5行目
	
}