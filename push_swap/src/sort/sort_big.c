/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:12 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 17:59:28 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static int big_length(size_t n)
{
	// n は要素数。最大rankは n-1
    // 例: n=5 -> max=4(100b) -> 3bit必要
	size_t max;
	int bits;

	bits = 0;
	if (n == 0)
		max = 0;
	else
		max = n - 1;
	while ((max >> (size_t)bits) != 0)
		bits++;
	return bits; //n <= 1なら0になる
}


void radix_sort(t_stack *a, t_stack *b)
{
	int bits;
	int bit;
	size_t n;
	int r;
	bits = big_length(a->size);
	bit = 0;
	while (bit < bits)
	{
		n = a->size;
		while (n--)
		{
			r = top_value(a);
			if (((r >> bit) & 1) == 0)
				pb(a, b);
			else
				ra(a);
		}
		while (b->size > 0)
			pa(a, b);
		bit++;
	}
}
