#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <unistd.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


# define BUFFER_SIZE 3

//typedef struct s_gnl
//{
//    char    *stash;      // 前回からの余り
//    char    *buf;        // read用バッファ
//    char    *line;       //今作っている１行（最終的に返すもの）
//    ssize_t n;       // readが返したバイト数
//}   t_gnl;

#endif