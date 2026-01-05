
#include "push_swap.h"

/*
* insert_after:
*   pos の直後に node を差し込む
*/
// link_between(left, node, right)の引数一個減らしたバージョン
static void insert_after(t_node *pos, t_node *node)
{
	//... <-> a <-> pos <-> b <-> ...
	node->next = pos->next; // node <-> b
	node->prev = pos; 		// pos <-> node <-> b → ちゃんとnextとprevにbとposをセットしてあげる

	pos->next->prev = node; // pos->next->prev は b->prev
	pos->next = node;
}

void push_front_stack(t_stack *stack, t_node *node)
{
    if (!stack || !node)
        return;
    // 先頭に挿入：sentinel と sentinel.next の間
    insert_after(&stack->sentinel, node);
    stack->size++;
}

/* 末尾追加：O(1)（番兵の prev が末尾を指す） */
void push_back_stack(t_stack *stack, t_node *node)
{
	if (!stack || !node)
		return ;
    // 末尾に挿入：末尾(stack->sentinel.prev) と sentinel の間
	insert_after(stack->sentinel.prev, node);
	stack->size++;
}

