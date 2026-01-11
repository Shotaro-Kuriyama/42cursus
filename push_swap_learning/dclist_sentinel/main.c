/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 15:40:10 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/31 19:12:43 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dclist.h"
#include <stdio.h>

int main(void)
{
	t_list list;
	t_node *node;

	dclist_init(&list); //番兵初期化
	
	dclist_push_back(&list, dclist_node_new(10));
	dclist_push_back(&list, dclist_node_new(20));
	dclist_push_front(&list, dclist_node_new(5));

	dclist_print_forward(&list);
	dclist_print_backward(&list);

	if (dclist_validate(&list))
		printf("validate=OK\n");
	else
		printf("validate=NG\n");
	
	node = dclist_pop_front(&list);
	if(node)
		printf("pop_front=%d\n", node->value);
	else
		printf("pop_front=%d\n", -1);
	dclist_node_free(node);

	node = dclist_pop_back(&list);
	if(node)
		printf("pop_back=%d\n", node->value);
	else
		printf("pop_back=%d\n", -1);
	dclist_node_free(node);

	dclist_print_forward(&list);
	dclist_print_backward(&list);

	if (dclist_validate(&list))
		printf("validate=OK\n");
	else
		printf("validate=NG\n");

	dclist_clear(&list, dclist_node_free);
	printf("after clear: ");
	dclist_print_forward(&list);
	if (dclist_validate(&list))
		printf("validate=OK\n");
	else
		printf("validate=NG\n");

	return 0;
}

/*
出力を順に確認すると：

追加後（push_back(10), push_back(20), push_front(5)）
	・forward: 5 10 20 ✅
	・backward: 20 10 5 ✅	
	・validate=OK ✅（リンクが壊れてない）
・pop_front → 先頭の 5 が取れる ✅
・pop_back → 末尾の 20 が取れる ✅
・残りが 10 だけになる ✅
	・forward/backward ともに 10 ✅
	・validate=OK ✅
・clear 後
	・size=0 ✅
	・validate=OK ✅
	・空のときに sentinel が自分を指す形が保たれてる証拠

加えて、
・pop_* で返ってきた node を dclist_node_free(node) していて、
メモリ管理もOKです（node == NULL のとき free(NULL) は安全）。
*/