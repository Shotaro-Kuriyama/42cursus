/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:49:55 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 16:03:13 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
#include <stdio.h>

typedef struct s_node {
    int             value; //入力の“元の値”を保持
    int             rank;  // 0..n-1（ソート・chunk・radixで使う）
    struct s_node   *prev;
    struct s_node   *next;
} t_node;

typedef struct s_stack {
    t_node   sentinel;  // 番兵ノード（常に存在するダミーノード）
    size_t   size;      // 要素数（番兵は含まない）
} t_stack;

/*
なぜ番兵ノードが入っている構造体がスタックと命名されているのか？
それは番兵自体は実体だが、そこの中に入っている*nextと*prevにノードを連結していくから。
つまり、番兵ノードを受け取ればスタックのすべての中身を走査することができる。
*/

/* stack public */
void    stack_init(t_stack *stack);
void    stack_free(t_stack *stack);
void 	insert_after(t_node *pos, t_node *node);
void 	detach(t_node *node);
t_node  *stack_pop_front(t_stack *stack);
t_node  *stack_pop_back(t_stack *stack);
void    stack_push_front(t_stack *stack, t_node *node);
void    stack_push_back(t_stack *stack, t_node *node);
bool    stack_contains(const t_stack *stack, int value);
bool    stack_is_sorted(const t_stack *a);

/* node */
t_node  *new_node(int value);

/* parse public */
bool    parse_args_to_stack(int argc, char **argv, t_stack *a);

/* strict int */
bool    parse_int_strict(const char *s, int *out);

/* split */
char    **split_ws(const char *s);
void    free_split(char **toks);


/* ops public（命令はここだけを使う） */
void    sa(t_stack *a);
void    sb(t_stack *b);
void    ss(t_stack *a, t_stack *b);
void    pa(t_stack *a, t_stack *b);
void    pb(t_stack *a, t_stack *b);
void    ra(t_stack *a);
void    rb(t_stack *b);
void    rr(t_stack *a, t_stack *b);
void    rra(t_stack *a);
void    rrb(t_stack *b);
void    rrr(t_stack *a, t_stack *b);

/* print */
void print_stack(t_stack *stack);

/* sort */
int		top_value(t_stack *st);
int 	second_value(t_stack *st);
int 	bottom_value(t_stack *st);
size_t 	min_index(t_stack *st);
void 	bring_index_to_top_a(t_stack *a, size_t idx);
void    sort_small(t_stack *a, t_stack *b);  // 2~5の入口

/* rank */
bool stack_rankify(t_stack *a);

/* sort_big*/
void 	radix_sort(t_stack *a, t_stack *b);
//void    sort_big(t_stack *a, t_stack *b);    // 本番入口

/* error */
int     ps_error(t_stack *a, t_stack *b, char **words);

# ifdef DEBUG
bool    stack_validate(const t_stack *st);
#  define PS_VALIDATE(p) do { if (!stack_validate(p)) _exit(1); } while (0)
# else
#  define PS_VALIDATE(p) ((void)0)
# endif

#endif
