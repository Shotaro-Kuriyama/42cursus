/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:02:09 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/03 20:22:53 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

//隣同士を比べて、でかいのを右へ押し出す

void bubble_sort(int *a, int n)
{
	int i;
	int j;
	int swap;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			if (a[j] > a[j + 1])
			{
				swap = a[j];
				a[j] = a[j + 1];
				a[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

int main(void)
{
	int a[] = {9, 2, 7, 5, 1, 3};
	int i;

	bubble_sort(a, 6);
	i = 0;
	while (i < 6)
	{
		printf ("%d, ", a[i]);
		i++;
	}
	printf("\n");
}