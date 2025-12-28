/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:49:55 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/28 18:55:25 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct s_node {
    int value;  //箱の中身（数値）
    struct s_node *next; //次の箱への矢印（ポインタ）
} t_node;



/*
typedef struct s_node {
    int value;  //箱の中身（数値）
    struct s_node *next; //次の箱への矢印（ポインタ）
	struct s_node *prev; (previous = 前の)
} t_node;
*/

// head = 先頭、 tail = 最後


//ここはスタックaを作るための関数群
t_node *new_node(int v);
int push_back (t_node **a, t_node *n);
void free_list(t_node *a);
bool parse_int_strict_by_atoi(const char *s, int *out);
void print_list(t_node *a);




#endif