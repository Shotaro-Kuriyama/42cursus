/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:46:55 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/21 17:54:03 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	char	*buf;
	ssize_t	n;
}			t_gnl;

char		*get_next_line(int fd);

size_t		ft_strlen(const char *s);
size_t		ft_newline_len(const char *s);
int			ft_has_newline(const char *s);
char		*gnl_strjoin(char *s1, char *s2);
char		*gnl_get_line(char *stash);
char		*gnl_get_rest(char *stash);

#endif