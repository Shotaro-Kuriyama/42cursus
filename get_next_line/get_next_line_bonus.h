/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:28:32 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/21 17:53:56 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	char				*buf;
	ssize_t				n;
}						t_gnl;

typedef struct s_gnl_list
{
	int					fd;
	char				*stash;
	struct s_gnl_list	*next;
}						t_gnl_list;

char					*get_next_line(int fd);

t_gnl_list				*gnl_get_node(t_gnl_list **list, int fd);
void					gnl_remove_node(t_gnl_list **list, int fd);

size_t					ft_strlen(const char *s);
size_t					ft_newline_strlen(const char *s);
int						ft_has_newline(const char *s);
char					*gnl_strjoin(char *s1, char *s2);
char					*gnl_get_line(char *stash);
char					*gnl_get_rest(char *stash);

#endif