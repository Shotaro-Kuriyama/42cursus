/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_base10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:47:12 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/11 17:36:48 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
前提
実装的には「各桁に対して安定なカウントソート」を繰り返す説明が王道

・「0〜9の出現回数を数えて並べ直す」＝カウントソート
・これを 1の位→10の位→100の位… と繰り返すのが（LSD方式の）基数ソート、
  という理解がよく使われます。
*/


/*
1. カウントソートは何をするソート？
前提：値の範囲が小さいときに強い

例えば、配列の中身が
・0〜9 の整数だけ
・0〜100 の点数だけ
・0〜999 のIDだけ
みたいに「取りうる値の範囲（K）が小さい」なら、
カウントソートはめちゃくちゃ速いです。

基本アイデア
・値を比較しない
・各値が何個あるか数える
・数えた情報から 正しい順番で並べ直す
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * exp = 1  -> 1の位
 * exp = 10 -> 10の位
 * exp = 100-> 100の位
 *
 * arr を「expの桁」で安定に並べ替える（counting sort）
 * ※arr は 0以上の整数を前提
 */

static void counting_sort_base10(int *arr, int n, int exp)
{
	int count[10] = {0}; // 0〜9 の出現回数を数える配列 0で初期化
	int *out = (int *)malloc(sizeof(int) * n);
	if (!out)
		return;

	int i;
	int digit;


	// 1) 各要素の digit を数える
    // digit = (arr[i] / exp) % 10
	i = 0;
	while (i < n)
	{
		digit = (arr[i] / exp) % 10;
		count[digit]++;
		i++;
	}

	// 2) count を「累積和」に変換する
    // count[d] = 「digit <= d の要素数」
    // これで out に置く“最終位置”がわかる
	i = 1;
	while (i < 10)
	{
		count[i] += count[i - 1];
		i++;
	}

	// 3) 後ろから走査して out に置く（ここが "安定" の要）
    // 後ろから入れることで、同じdigit同士の相対順序が保たれる
	
}

//　配列の一番大きい値（valuex）を返す
static int get_max(const int *arr, int n)
{
	int mx;
	mx = arr[0];
	int i;

	i = 0;
	while (i < n)
	{
		if (arr[i] > mx)
			mx = arr[i];
		i++;
	}
	return mx;
}



void radix_sort_base10(int *arr, int n)
{
	int mx;
	int exp;

	if (!arr || n <= 1)
		return;

	mx = get_max(arr, n);

	exp = 1;
	while (mx / exp > 0)
	{
		counting_sort_base10(arr, n, exp);
		exp *= 10;
	}
}
	

/* 動作確認 */
static void print_arr(const int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d%s", a[i], (i + 1 == n) ? "\n" : " ");
}

int main(void)
{
    int a[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = (sizeof(a) / sizeof(a[0]));
	/*
	sizeof(a)
	→ 配列 a 全体の バイト数（メモリサイズ）
	sizeof(a[0])
	→ a の 1要素ぶんのバイト数
	*/

    printf("before: ");
    print_arr(a, n);

    radix_sort_base10(a, n);

    printf("after : ");
    print_arr(a, n);
    return 0;
}

 