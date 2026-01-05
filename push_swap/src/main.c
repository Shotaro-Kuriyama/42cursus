/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:41:21 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 17:33:11 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

void print_stack_value_rank(t_stack *st)
{
    t_node *cur = st->sentinel.next;
    while (cur != &st->sentinel)
    {
        printf("value=%d rank=%d\n", cur->value, cur->rank);
        cur = cur->next;
    }
}


int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

    if (argc < 2)
        return 0;

    stack_init(&a);
    stack_init(&b);

	if (!parse_args_to_stack(argc, argv, &a))
        return 1;

    if (stack_is_sorted(&a))
        return 0;
    //print_stack(&stack_a);
    PS_VALIDATE(&a);

    //print_stack(&a); // 必要なら有効化
	//print_stack_value_rank(&a); // valueとrankの確認用
	stack_rankify(&a); // rank化実行
	//print_stack_value_rank(&a); // rank化後の確認用
    if (a.size <= 5)
        sort_small(&a, &b);
    else
        radix_sort(&a, &b);

   // print_stack(&a); // 必要なら有効化
        
    stack_free(&a);
    stack_free(&b);
    return 0;
}
