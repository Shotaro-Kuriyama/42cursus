/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:38 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 16:01:58 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

//from→toへpush
static bool op_push(t_stack *from, t_stack *to)
{
	t_node *node;

	if (!from || !to)
		return false;
	if (from->size == 0)
		return false;
	node = stack_pop_front(from);
	if (!node)
		return false;
	stack_push_front(to, node);
	return true;
}

void pa(t_stack *a, t_stack *b)
{
	if (op_push(b, a))
		write(1, "pa\n", 3);
}

void pb(t_stack *a, t_stack *b)
{
	if (op_push(a, b))
		write(1, "pb\n", 3);
}