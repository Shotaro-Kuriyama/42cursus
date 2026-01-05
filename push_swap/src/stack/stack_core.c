/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:41:09 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 15:00:39 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

//番兵の初期化（空のリングを作る）
void stack_init(t_stack *stack)
{
	stack->sentinel.next = &stack->sentinel;
	stack->sentinel.prev = &stack->sentinel;
	stack->sentinel.rank = -1;
	stack->size = 0;
}

void stack_free(t_stack *stack)
{
	t_node *current;
	t_node *next_node;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	stack_init(stack);
	//stackは結局番兵なので最後に番兵を初期化する。
}

t_node *new_node(int value)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return NULL;
	node->value = value;
	node->rank = -1;
	node->prev = NULL;
	node->next = NULL;
	return node;	
}

/*
* insert_after:
*   pos の直後に node を差し込む
*/
// link_between(left, node, right)の引数一個減らしたバージョン
void insert_after(t_node *pos, t_node *node)
{
	//... <-> a <-> pos <-> b <-> ...
	node->next = pos->next; // node <-> b
	node->prev = pos; 		// pos <-> node <-> b → ちゃんとnextとprevにbとposをセットしてあげる

	pos->next->prev = node; // pos->next->prev は b->prev
	pos->next = node;
}

/*
* detach:
*   node をリストから抜き取る（前後をつなぎ直す）
*/
//unlink_node(node)
void detach(t_node *node)
{
	node->prev->next = node->next; // L <-> node <-> Rで、node->prev->next → L->next = R
	node->next->prev = node->prev; // L <-> node <-> Rで、node->next->prev → R->prev = L
	//よってL <-> Rとなりnodeが外れた
	
	node->prev = NULL;
	node->next = NULL;
}

