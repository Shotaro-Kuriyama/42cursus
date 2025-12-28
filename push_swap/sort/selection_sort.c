/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:44:00 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/28 18:16:37 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ゴール（到達ライン）

insertion / selection を 何も見ずに書ける（基本形）

途中経過を言葉で言える

insertion：「左側が常にソート済み。key を正しい位置に差し込む」

selection：「未確定部分から最小を探して、先頭に持ってくる」
*/

#include <stddef.h>
#include <stdio.h>

//発想：**“最小を見つけて確定”**を繰り返す

void selection_sort(int *a, int n) //*a:配列、 n:配列のindexの数
{
	int i;
	int j;
	int int_min;

	int_min = i;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (j < n)
		
		i++;
	}
}


void print_arr(const int *a, int n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		printf("%d, ", a[i]);
		i++;
	}
	printf("\n");
}

void swap_int(int *x, int *y)
{
	int t;

	t = *x;
	*x = *y;
	*y = t;
}


int main(void)
{
	int a1[] = {3, 1, 5, 2, 4};
	int a2[] = {5, 4, 3, 2, 1};
	int a3[] = {1, 2, 3, 4, 5};

	print_arr(a1, 5);
	selection_sort(a1, 5);
	print_arr(a1, 5);
}