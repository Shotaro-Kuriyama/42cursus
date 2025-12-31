/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:49:55 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/31 23:51:55 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_node {
    int             value;
    struct s_node   *prev;
    struct s_node   *next;
} t_node;

typedef struct s_stack {
    t_node   sentinel;   // 番兵ノード（常に存在するダミーノード）
    size_t   size;       // 要素数（番兵は含まない）
} t_stack;

/*
なぜ番兵ノードが入っている構造体がスタックと命名されているのか？
それは番兵自体は実体だが、そこの中に入っている*nextと*prevにノードを連結していくから。
つまり、番兵ノードを受け取ればスタックのすべての中身を走査することができる。
*/

/* stack base */
void    stack_init(t_stack *stack);
t_node  *new_node(int value);
int     push_back_stack(t_stack *stack, t_node *node);
void    free_stack(t_stack *stack);
void    print_stack(t_stack *stack);
bool    contains_stack(t_stack *stack, int value);

/* parse */
bool    parse_int_strict(const char *p, int *out_value);

/* split */
char    **split_ws(const char *text);
void    free_split(char **words);

/* stack debug */
bool    stack_validate(const t_stack *stack);

#endif