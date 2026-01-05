

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

static void insertion_sort_int(int *a, size_t n)
{
    int i;
    int j;
    int key;

    // a[0..0] は要素1つなので「ソート済み」とみなせる → i=1から挿入開始
    i = 1;
    while (i < n) // i=1..n-1 の n-1回
    {
        key = a[i];       // 挿入したい値を退避（これがあるから上書きしてもOK）
        j = i - 1;        // ソート済み部分の右端から左へ比較していく

        // keyより大きい要素を1つずつ右へシフトして、keyの入る穴を作る
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j]; // 右へずらす（swapではない）
            j--;
        }

        // whileを抜けた位置の「右隣」が key の入るべき場所
        a[j + 1] = key;
        i++;
    }
}

static bool has_duplicate_sorted(const int *sorted, size_t n)
{
    size_t i;

    i = 1;
    while (i < n)
    {
        if (sorted[i] == sorted[i - 1])
            return true;

        i++;
    }
    return false;
}

// 二分探索
//sorted は「小さい順に並んだ値の一覧」。
//sorted の中で value が見つかる位置 = 「小さい順の番号」= rank。
static size_t lower_bound_int(const int *sorted, size_t n, int x)
{
    // sorted の中で「x以上が初めて現れる位置」を返す
    // （xが必ず存在する前提なら、その位置がxのindexになる）

    size_t lo;
    size_t hi;
    size_t mid;

    lo = 0;
    hi = n;

    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        if (sorted[mid] < x)
            lo = mid + 1;
        else    
            hi = mid;
    }
    return lo;
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
        if (i >= n) //念のため
            return false;
        out[i++] = cur->value;
        cur = cur->next;   
    }
    return (i == n);
}

static void apply_rank_to_stack(t_stack *st, const int *sorted, size_t n)
{
    // 各 node の value を見て rank を決め、node->rank に保存する
    t_node *cur;
    size_t r;

    cur = st->sentinel.next;

    while (cur != &st->sentinel)
    {
        r = lower_bound_int(sorted, n, cur->value);
        // r は 0..n-1 のはず（重複なし・値は必ず存在）
        cur->rank = (int)r;
        cur = cur->next;
    }
}

/*
** 公開関数（例）
** 成功: true
** 失敗: false（malloc失敗 or 重複あり 等）
*/

bool stack_rankify(t_stack *a)
{
    size_t n;
    int *values;
    int *sorted;

    if (!a)
        return false;
    n = a->size;
    if (n <= 1)
        return false;
    
    values = (int *)malloc(sizeof(int) * n);
    sorted = (int *)malloc(sizeof(int) * n);
    if (!values || !sorted)
    {
        free(values);
        free(sorted);
        return false;
    }

    if (!stack_to_array_values(a, values, n))
    {
        free(values);
        free(sorted);
        return false;
    }

    // sorted = vals のコピーを作ってソート
    memcpy(sorted, values, sizeof(int) * n);
    insertion_sort_int(sorted, n);

    // 重複チェック（push_swapでは必須）
    if (has_duplicate_sorted(sorted, n))
    {
        free(values);
        free(sorted);
        return false;
    }
    
    // rank を埋める（value は残す）
    apply_rank_to_stack(a, sorted, n);

    free(values);
    free(sorted);
    return true;
}