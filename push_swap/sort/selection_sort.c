/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:44:00 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/03 21:01:43 by skuriyam         ###   ########.fr       */
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
	int min_i;

	i = 0;
	j = 0;
	
	while (i < n - 1)
	{
		min_i = i;
		j = 0;
		while (j < n)
		{
			if (a[min_i] > a[j + i])
				min_i = a[j + i];
			j++;
		}
		a[i] =min_i;
		i++;
	}
}

int main(void)
{
	int a[] = {9, 2, 7, 5, 1, 3};
	int i;

	selection_sort(a, 6);
	i = 0;
	while (i < 6)
	{
		printf ("%d, ", a[i]);
		i++;
	}
	printf("\n");
}