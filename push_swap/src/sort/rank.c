/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:07 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/10 16:43:59 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // memcpy


/*
** rank化（座標圧縮）
** - stack の value を 0..n-1 の rank に置き換える
** - ついでに重複チェックもできる（sorted配列の隣同士を見る）
**
** 前提：t_stack は番兵つき循環双方向リスト
**  - st->sentinel.next から始めて sentinel に戻るまでが要素
*/


// a[l..r) をソートする（rは含まない）
static void merge_sort_rec(int *a, int *buf, size_t l, size_t r)
{
	size_t mid;
	size_t i;
	size_t j;
	size_t k;

	if (r - l <= 1) //停止条件
		return;

	mid = l + (r - l) / 2; //真ん中を作る（オーバーフロー対策で式変形してる）
	merge_sort_rec(a, buf, l, mid);
	merge_sort_rec(a, buf, mid, r);
	// ↑ この2行が終わった時点で a[l..mid) と a[mid..r) は「それぞれソート済み」になっている

	// merge: a[l..mid) と a[mid..r) を buf に統合
	i = l;     // 左列の読み取り位置
	j = mid;   // 右列の読み取り位置
	k = l;     // buf へ書き込む位置


	//左列と右列を比較して、
	while (i < mid && j < r)//左列がまだ残ってる&&右列もまだ残ってる
	{
		if (a[i] <= a[j])
			buf[k++] = a[i++];
		else
			buf[k++] = a[j++];
	}
	//　この時点で左列と右列を「比較して片方代入」してるので、
	//　必ずどちらかが残ることになる（片方が終端に到達したので比較を終える）

	//奇数で左右のサイズが違っても、
	//比較ループのあとに “残りを全部流し込む処理” があるから大丈夫
	while (i < mid) //左がまだ残ってたら
		buf[k++] = a[i++];
	while (j < r) //右がまだ残ってたら
		buf[k++] = a[j++];

	// buf[l..r) を a[l..r) に戻す
	k = l;
	while (k < r)
	{
		a[k] = buf[k];
		k++;
	}
}

static bool merge_sort_int(int *a, size_t n)
{
	int *buf;

	if (!a)
		return false;

	buf = (int *)malloc(sizeof(int) * n);
	if (!buf)
		return false;

	merge_sort_rec(a, buf, 0, n);
	free(buf);
	return true;
}

// 二分探索
//sorted は「小さい順に並んだ値の一覧」。
//sorted の中で value が見つかる位置 = 「小さい順の番号」= rank。
static size_t binary_search(const int *sorted, size_t n, int x)
{
    // sorted の中で「x以上が初めて現れる位置」を返す
    // （xが必ず存在する前提なら、その位置がxのindexになる）

    size_t start;
    size_t last;
    size_t mid;

    start = 0;
    last = n;

    while (start < last)
    {
        mid = start + (last - start) / 2;
        if (sorted[mid] < x)
            start = mid + 1;
        else
            last = mid;
    }
    return start;
}

static bool stack_to_array_values(const t_stack *st, int *out, size_t n)
{
    // スタックの要素を out[0..n-1] にコピー
    // n は st->size と一致している前提

    t_node *cur;
    size_t i;

    cur = st->sentinel.next;
    i = 0;

    while (cur != &st->sentinel)
    {
        out[i++] = cur->value;
        cur = cur->next;   
    }
    return (i == n);
}

static void apply_rank_to_stack(t_stack *st, const int *sorted, size_t n)
{
    // 各 node の value を見て rank を決め、node->rank に保存する
    t_node *cur;
    size_t rank;

    cur = st->sentinel.next;

    while (cur != &st->sentinel)
    {
        rank = binary_search(sorted, n, cur->value);
        // r は 0..n-1 のはず（重複なし＆値は必ず存在する前提）
        cur->rank = (int)rank;
        cur = cur->next;
    }
}

/*
** 公開関数
** 成功: true
** 失敗: false（malloc失敗 or 重複あり 等）
*/

bool stack_ranking(t_stack *a)
{
    size_t n;
    int *sorted;
    if (!a)
        return false;
    n = a->size;
    // rank を int に入れるので（念のため）上限チェック
    if (n > (size_t)INT_MAX)
        return false;

    sorted = (int *)malloc(sizeof(int) * n);
    if (!sorted)
        return (free(sorted), false);

    if (!stack_to_array_values(a, sorted, n))
        return (free(sorted), false);

    if (!merge_sort_int(sorted, n))
        return (free(sorted), false);

    // rank を埋める（value は残す）
    apply_rank_to_stack(a, sorted, n);

    return (free(sorted), true);
}
