/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:24 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 16:11:53 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"

//Aの先頭/2番目/末尾の値を取る（番兵つき前提）
//前提：sort3（Aが3個）を前提とする。


static void sort2(t_stack *a)
{
	if (top_value(a) > second_value(a))
		sa(a);
}

//sort3（Aが3要素）— 最短で強い定番ロジック
static void sort3(t_stack *a)
{
	int top;
	int mid;
	int bot;

	top = top_value(a);
	mid = second_value(a);
	bot = bottom_value(a);

	//　最大値を必ず末尾に送る
	if (top > mid && top > bot)
		ra(a);
	else if (mid > top && mid > bot)
		rra(a);
	
	// 最大値は末尾→先頭2つ整えて終わり
	if (top_value(a) > second_value(a))
		sa(a);
}

static void sort4(t_stack *a, t_stack *b)
{
	bring_index_to_top_a(a, min_index(a));
	pb(a, b);
	sort3(a);
	pa(a, b);
}

static void sort5(t_stack *a, t_stack *b)
{
	// 1つ目の最小をBへ
	bring_index_to_top_a(a, min_index(a));
	pb(a, b);

	// 2つ目の最小をBへ
	bring_index_to_top_a(a, min_index(a));
	pb(a, b);

	// 残りの3つをソート
	sort3(a);

	// Bから戻す（この順でOK)
	pa(a,b);
	pa(a,b);
}
/*
なぜ pa×2 だけでいい？
このやり方だと B はだいたい [2nd_min, min] の並びになります。
pa すると 2nd_min がAの先頭、次の pa で min がさらに先頭になるので、
結果として Aの先頭2つは [min, 2nd_min] になり、後ろの3要素（すでにソート済み）と自然につながります。
*/

void sort_small(t_stack *a, t_stack *b)
{
	//if (is_sorted(a))
	//	return;
	if (a->size == 2)
		sort2(a);
	else if (a->size == 3)
		sort3(a);
	else if (a->size == 4)
		sort4(a, b);
	else if (a->size == 5)
		sort5(a, b);
}