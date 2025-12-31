/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:05:39 by shotarokuri       #+#    #+#             */
/*   Updated: 2025/12/31 17:52:05 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DCLIST_H
# define DCLIST_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_node {
    int             value;  // もとの v
    struct s_node  *prev;
    struct s_node  *next;
} t_node;

//双方向リスト
typedef struct s_list {
    t_node  sentinel; //番兵（sentinel）ノードは「実体」として中に埋め込む
    size_t  size;     //要素数（番兵は含めない）
} t_list;

// --- core ---
void    dclist_init(t_list *list);
bool    dclist_empty(const t_list *list);

t_node  *dclist_node_new(int value);
void    dclist_node_free(t_node *node);

void    dclist_push_front(t_list *list, t_node *node);
void    dclist_push_back(t_list *list, t_node *node);

t_node  *dclist_pop_front(t_list *list);
t_node  *dclist_pop_back(t_list *list);

void    dclist_clear(t_list *list, void (*del)(t_node *));

// --- debug / learning helpers ---
void    dclist_print_forward(const t_list *list);
void    dclist_print_backward(const t_list *list);
bool    dclist_validate(const t_list *list);

#endif

