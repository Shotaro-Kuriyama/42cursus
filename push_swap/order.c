/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:53:08 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/26 03:17:49 by skuriyam         ###   ########.fr       */
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
	t_node *a_start;
	t_node *b_start;

	a_start = *a;
	b_start = *b;

	*b = b_start->next;

	b_start->next = a_start;
	*a = b_start;
} 

void pb(t_node **a, t_node **b)
{
	t_node *a_start;
	t_node *b_start;

	a_start = *a;
	b_start = *b;

	*a = a_start->next;
	a_start->next = b_start;

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
