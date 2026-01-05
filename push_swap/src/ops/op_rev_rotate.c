/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rev_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:40 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 16:02:32 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

// 末尾→先頭
static bool op_rev_rotate(t_stack *stack)
{
	t_node *node;
	if (!stack || stack->size < 2)
		return false;
	
	node = stack->sentinel.prev;
	detach(node);
	insert_after(&stack->sentinel, node);
	return true;
}

void rra(t_stack *a)
{
	if (op_rev_rotate(a))
		write(1, "rra\n", 4);
}
void rrb(t_stack *b)
{
	if (op_rev_rotate(b))
		write(1, "rrb\n", 4);
}

void rrr(t_stack *a, t_stack *b)
{
	if (op_rev_rotate(a) || op_rev_rotate(b))
		write(1, "rrr\n", 4);
}