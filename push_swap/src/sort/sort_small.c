

#include "push_swap.h"

//Aの先頭/2番目/末尾の値を取る（番兵つき前提）
//前提：sort3（Aが3個）を前提とする。


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

void sort_small(t_stack *a, t_stack *b)
{
	// if (is_sorted_asc(a))
	// 	return;
	if (a->size == 2)
		sort2_a(a);
	else if (a->size == 3)
		sort3_a(a);
	else if (a->size == 4)
		sort4(a, b);
	else if (a->size == 5)
		sort5(a, b);
}