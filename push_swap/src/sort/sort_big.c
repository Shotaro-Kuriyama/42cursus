/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:12 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/11 19:20:37 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
0. 大前提（この radix が成立する条件）

この radix_sort は value（元の整数）ではなく rank（0〜n-1の連番） 
を並べ替える前提です。

・要素数が n なら、rank は必ず 0,1,2,...,n-1
・つまり最大 rank は n-1
・rank は重複しない（ユニーク）

この前提があるから、ビットだけ見れば必ず完全に順序が確定します。
*/


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

//80726354
/*
二進数でそれぞれ表すと
8 = 1000
0 = 0000
7 = 0110
2 = 0010
6 = 0110
3 = 0011
5 = 0101
4 = 0100

これの 2の0乗から見て1と0を分ける（スタックaとスタックbに）
それを繰り返して行く。

今わかっていないところは、これを0をスタックbに送り、
最後に戻すときにスタックbをスタックaに先頭から入れるのを繰り返す
だけで昇順になっているのかがわからない。
*/