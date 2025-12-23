#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_node {
    int value;  //箱の中身（数値）
    struct s_node *next; //次の箱への矢印（ポインタ）
} t_node;


#endif