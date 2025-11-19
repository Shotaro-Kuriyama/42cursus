#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <unistd.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
#endif


char	*get_next_line(int fd);

//typedef struct s_gnl
//{
//    char    *stash;      // 前回からの余り
//    char    *buf;        // read用バッファ
//    char    *line;       //今作っている１行（最終的に返すもの）
//    ssize_t n;       // readが返したバイト数
//}   t_gnl;

#endif