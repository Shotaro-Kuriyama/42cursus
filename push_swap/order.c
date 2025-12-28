/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shotarokuriyama <shotarokuriyama@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:53:08 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/26 18:32:32 by shotarokuri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sa(t_node **a)
{
	t_node *node2;
	t_node *cur;
	int swap;

	if (!*a)
		return ;
	cur = *a;

	if (cur->next == NULL)
		return ;
	node2 = cur->next;

	swap = cur->value;
	cur->value = node2->value;
	node2->value = swap;
}

void sb(t_node **b)
{
	t_node *node_idx2;
	t_node *cur;
	int swap;

	if (!*b)
		return ;
	cur = *b;

	if (cur->next == NULL)
		return ;
	node_idx2 = cur->next;

	swap = cur->value;
	cur->value = node_idx2->value;
	node_idx2->value = swap;
}

void ss(t_node **a, t_node **b)
{
	sa(a);
	sb(b);
}

void pa(t_node **a, t_node **b)
{
	t_node *b_start;

	if (!b || !*b)
		return;

	b_start = *b;
	*b = b_start->next;

	b_start->next = *a;
	*a = b_start;
} 

void pb(t_node **a, t_node **b)
{
	t_node *a_start;

	if (!a || !*a)
		return ;
	
	a_start = *a;
	*a = a_start->next;

	a_start->next = *b;
	b = a_start;
}

void ra(t_node **a)
{
	t_node *first;
	t_node *last;

	if (!a || !*a || !(*a)->next)
		return ;

	first = *a;
	*a = first->next;

	last = *a;
	while(last->next)
		last = last->next;
	
	first->next = NULL;
	last->next = first;
}

void rb(t_node **b)
{
    t_node *first;
    t_node *last;

    if (!b || !*b || !(*b)->next)
        return;

    first = *b;
    *b = first->next;

    first->next = NULL;

    last = *b;
    while (last->next)
        last = last->next;

    last->next = first;
}

void rr(t_node **a, t_node **b)
{
	ra(a);
	rb(b);
}

//末尾ノードを外す
//それを先頭にする
void rra (t_node **a)
{
	t_node *prev_last;
	t_node *last;

	prev_last = *a;

	while (prev_last->next->next)
		prev_last = prev_last->next;

	last = prev_last->next;
	last->next = *a;
	*a = last;
}

void rrb(t_node **b)
{
	t_node *prev_last;
	t_node *last;

	prev_last = *b;

	while (prev_last->next->next)
		prev_last = prev_last->next;

	last = prev_last->next;
	last->next = *b;
	*b = last;
}

void rrr(t_node **a, t_node **b)
{
	rra(a);
	rrb(b);
}





int main(int argc, char **argv)
{
    t_node *a = NULL;
    t_node *b = NULL;
    int i;
    int v;

    (void)b;

    if (argc < 2)
        return 1;

    i = 1;
    while (i < argc)
    {
        if (!parse_int_strict_by_atoi(argv[i], &v))
        {
            write(2, "Error\n", 6);
            free_list(a);
            return 1;
        }

        if (!push_back(&a, new_node(v)))
        {
            write(2, "Error\n", 6);
            free_list(a);
            return 1;
        }
        i++;
    }

    print_list(a);

	sa(&a);

	print_list(a);
    free_list(a);
    return 0;
}
