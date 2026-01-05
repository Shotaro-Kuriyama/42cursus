

#include "push_swap.h"

//Aの先頭/2番目/末尾の値を取る（番兵つき前提）
//前提：sort3（Aが3個）を前提とする。

static int top_value(t_stack *st)
{
	return st->sentinel.next->value; //next->rank
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
