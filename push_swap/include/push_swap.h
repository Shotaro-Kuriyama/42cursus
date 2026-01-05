/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shotarokuriyama <shotarokuriyama@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:49:55 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/04 14:36:59 by shotarokuri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>

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
void    stack_init(t_stack *st);
void    stack_free(t_stack *st);
t_node  *stack_pop_front(t_stack *st);
t_node  *stack_pop_back(t_stack *st);
void    stack_push_front(t_stack *st, t_node *n);
void    stack_push_back(t_stack *st, t_node *n);
bool    stack_contains(const t_stack *st, int v);
bool    stack_is_sorted(const t_stack *st);

/* node */
t_node  *node_new(int v);

/* parse public */
bool    parse_args_to_stack(int argc, char **argv, t_stack *a);

/* split */
char    **split_ws(const char *s);
void    free_split(char **toks);

/* strict int */
bool    parse_int_strict(const char *s, int *out);

/* ops public（命令はここだけを使う） */
void    op_sa(t_stack *a);
void    op_sb(t_stack *b);
void    op_ss(t_stack *a, t_stack *b);
void    op_pa(t_stack *a, t_stack *b);
void    op_pb(t_stack *a, t_stack *b);
void    op_ra(t_stack *a);
void    op_rb(t_stack *b);
void    op_rr(t_stack *a, t_stack *b);
void    op_rra(t_stack *a);
void    op_rrb(t_stack *b);
void    op_rrr(t_stack *a, t_stack *b);

/* sort */
void    sort_small(t_stack *a, t_stack *b);  // 2~5の入口
void    sort_big(t_stack *a, t_stack *b);    // 本番入口

/* error */
int     ps_error(t_stack *a, t_stack *b, char **words);

# ifdef DEBUG
bool    stack_validate(const t_stack *st);
#  define PS_VALIDATE(p) do { if (!stack_validate(p)) _exit(1); } while (0)
# else
#  define PS_VALIDATE(p) ((void)0)
# endif

#endif
