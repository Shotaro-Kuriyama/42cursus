#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <unistd.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif

/* 読み込み用の一時変数をまとめる構造体*/
typedef struct s_gnl
{
    char *buf;
    ssize_t n;
}   t_gnl;

/* bonus用：fdごとのstashを持つ線形リスト */
typedef struct s_gnl_list
{
    int     fd;
    char    *stash;
    struct s_gnl_list *next;
}   t_gnl_list;

char	*get_next_line(int fd);

/* utils */
size_t ft_strlen(const char *s);
size_t ft_newline_len(const char *s);
int ft_has_newline(const char *s);
char *gnl_strjoin(char *s1, char *s2);
char *gnl_get_line(char *stash);
char *gnl_get_rest(char *stash);

#endif