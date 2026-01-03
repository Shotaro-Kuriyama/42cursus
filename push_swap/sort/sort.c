/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:55:07 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/03 19:19:41 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../push_swap.h"

//Aの先頭/2番目/末尾の値を取る（番兵つき前提）
//前提：sort3（Aが3個）を前提とする。

static int top_value(t_stack *st)
{
	return st->sentinel.next->value;
}

static int second_value(t_stack *st)
{
	return st->sentinel.next->next->value;
}

static int bottom_value(t_stack *st)
{
	return st->sentinel.prev->value;
}

//最小値の位置（index）を探す
//index=0 が先頭。見つけたら、その位置を返す。
static size_t min_index(t_stack *st)
{
	size_t idx;
	size_t best_idx;
	int	   best_value;
	t_node *cur;

	if (!st || st->size == 0)
		return 0;

	cur = st->sentinel.next;
	best_value = cur->value;

	idx = 0;
	best_idx = 0;
	while (cur != &st->sentinel)
	{
		if (cur->value < best_value)
		{
			best_value = cur->value;
			best_idx = idx;
		}
		cur = cur->next;
		idx++;
	}
	return best_idx;
}

//指定indexを先頭に持ってくる（回転の選択が学習ポイント）

static void bring_index_to_top_a(t_stack *a, size_t idx)
{
	size_t n;
	size_t rev;

	n = a->size;
	if (n < 2)
		return;
	if (idx <= n / 2) //idx[0], idx[1], idx[2]の3つ、つまりn = 3
	{
		while (idx > 0) //idx = 0ならfalseで抜ける
		{
			ra(a);
			idx--;
		}
	}
	else
	{
		rev = n - idx;  //真ん中より後ろなら、末尾から回転させたほうが速い
		while (rev > 0)
		{
			rra(a);
			rev--;
		}		
	}
}

// 最初から並んでたら何も出力しないのが大事。
static bool is_sorted_asc(const t_stack *a)
{
	t_node *cur;

	if (!a || a->size < 2)
		return false;
	
	cur = a->sentinel.next;
	while (cur->next != &a->sentinel)
	{	
		if (cur->value > cur->next->value)
			return false;
		cur = cur->next;
	}
	return true;
}

static void sort2_a(t_stack *a)
{
	if (top_value(a) > second_value(a))
		sa(a);
}

//sort3（Aが3要素）— 最短で強い定番ロジック
static void sort3_a(t_stack *a)
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
	sort_3(a, b);
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
	sort3_a(a);

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

void solve_small(t_stack *a, t_stack *b)
{
	if (is_sorted_asc(a))
		return;
	if (a->size == 2)
		sort2_a(a);
	else if (a->size == 3)
		sort3_a(a);
	else if (a->size == 4)
		sort4(a, b);
	else if (a->size == 5)
		sort5(a, b);
}
