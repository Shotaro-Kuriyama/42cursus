/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:47 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 14:30:39 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"


// 先頭→末尾
static bool op_rotate(t_stack *stack)
{
	t_node *node;

	if (!stack || stack->size < 2)
		return false;

	node = stack->sentinel.next; //先頭
	detach(node);			 //先頭を抜き取る
	insert_after(stack->sentinel.prev, node); //末尾の直後にnodeを繋げる
	return true;
}


void ra(t_stack *a)
{
	if (op_rotate(a))
		write(1, "ra\n", 3);
}
void rb(t_stack *b)
{
	if (op_rotate(b))
		write(1, "rb\n", 3);
}
void rr(t_stack *a, t_stack *b)
{
	if (op_rotate(a) || op_rotate(b))
		write(1, "rr\n", 3);
}

