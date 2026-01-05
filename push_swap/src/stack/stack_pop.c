/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:41:11 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 15:00:10 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"



t_node *stack_pop_front(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;
    node = stack->sentinel.next;
    detach(node);
    stack->size--;
    return node;
}
// 末尾を取り出す
t_node *stack_pop_back(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;
    node = stack->sentinel.prev;
    detach(node);
    stack->size--;
    return node;
}