/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:42:02 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/21 15:48:48 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* stash も buf も free して stash を NULL にしてから NULL */
static char	*free_all(char **stash, t_gnl *g)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	free(g->buf);
	return (NULL);
}

/* fd に対応するノードを探す。なければ新しく作る。*/
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

/* fd のノードをリストから削除して free */
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

/*
 * その fd 用の node->stash に対して mandatory と同じ読み込み処理。
 */
static char	*read_and_stash_bonus(int fd, t_gnl_list *node)
{
	t_gnl	g;

	g.buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!g.buf)
		return (NULL);
	g.n = 1;
	while (!ft_has_newline(node->stash) && g.n > 0)
	{
		g.n = read(fd, g.buf, BUFFER_SIZE);
		if (g.n < 0)
			return (free_all(&(node->stash), &g));
		if (g.n == 0)
			break ;
		g.buf[g.n] = '\0';
		node->stash = gnl_strjoin(node->stash, g.buf);
		if (!node->stash)
			return (free(g.buf), NULL);
	}
	free(g.buf);
	if (!node->stash || !*(node->stash))
	{
		free(node->stash);
		return (node->stash = NULL, NULL);
	}
	return (node->stash);
}

char	*get_next_line(int fd)
{
	t_gnl_list	*node;
	char		*line;

	static t_gnl_list *list = NULL; //「全 fd 分のノードがつながっているリストの先頭ポインタ」だと思えばOK。
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

#include <stdio.h>

//int	main(void)
//{
//	int fd1 = open("test.txt", O_RDONLY);
//	int fd2 = open("test2.txt", O_RDONLY);
//	int fd3 = open("test3.txt", O_RDONLY);

//	printf("%s", get_next_line(fd1)); // a.txt の1行目
//	printf("%s", get_next_line(fd2)); // b.txt の1行目
//	printf("%s", get_next_line(fd3)); // b.txt の1行目
//	printf("%s", get_next_line(fd1)); // a.txt の2行目
//	printf("%s", get_next_line(fd2)); // b.txt の2行目
//	printf("%s", get_next_line(fd3)); // b.txt の1行目
//}