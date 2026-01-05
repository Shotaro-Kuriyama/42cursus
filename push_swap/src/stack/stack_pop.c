
#include "push_swap.h"

/*
* detach:
*   node をリストから抜き取る（前後をつなぎ直す）
*/
//unlink_node(node)
static void detach(t_node *node)
{
	node->prev->next = node->next; // L <-> node <-> Rで、node->prev->next → L->next = R
	node->next->prev = node->prev; // L <-> node <-> Rで、node->next->prev → R->prev = L
	//よってL <-> Rとなりnodeが外れた
	
	node->prev = NULL;
	node->next = NULL;
}

t_node *stack_pop_front(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;
    node = stack->sentinel.next;
    detach(node);
    stack->size--;
    return node;
}
// 末尾を取り出す
t_node *stack_pop_back(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;
    node = stack->sentinel.prev;
    detach(node);
    stack->size--;
    return node;
}