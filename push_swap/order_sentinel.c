
#include "push_swap.h"

// 先頭を取り出す
t_node *pop_front_stack(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;

    node = stack->sentinel.next;
    detach(node);
    stack->size--;
    return node;
}


void sa(t_stack *stack)
{
    t_node *first;
    t_node *second;
    t_node *third;

    if (!stack || stack->size < 2)
        return;
    
    first = stack->sentinel.next;
    second = first->next;
    third = second->next;

    // sentinel <-> first <-> second <-> third
    // を
    // sentinel <-> second <-> first <-> third
    stack->sentinel.next = second;
    second->prev = &stack->sentinel;

    second->next = first;
    first->prev = second;

    first->next = third;
    third->prev = first;

}

//pbは変数をstack_bにするだけ

void pa(t_stack *stack_a, t_stack *stack_b)
{
    if (!stack_a)
        return;
}



