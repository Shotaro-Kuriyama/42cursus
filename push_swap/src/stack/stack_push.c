/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:41:13 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 15:00:23 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"



void stack_push_front(t_stack *stack, t_node *node)
{
    if (!stack || !node)
        return;
    // 先頭に挿入：sentinel と sentinel.next の間
    insert_after(&stack->sentinel, node);
    stack->size++;
}

/* 末尾追加：O(1)（番兵の prev が末尾を指す） */
void stack_push_back(t_stack *stack, t_node *node)
{
	if (!stack || !node)
		return ;
    // 末尾に挿入：末尾(stack->sentinel.prev) と sentinel の間
	insert_after(stack->sentinel.prev, node);
	stack->size++;
}

