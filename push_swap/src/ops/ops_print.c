/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:54 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 12:40:55 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"

void print_stack(t_stack *stack)
{
	t_node *current;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
}