
#include "push_swap.h"

bool op_swap(t_stack *stack)
{
    t_node *first;
    t_node *second;
    t_node *third;

    if (!stack || stack->size < 2)
        return false;
    
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
	return true;
	/*
	size==2 のときに third が sentinel になって sentinel.prev が更新されるので、
	その点もちゃんと成立しています（third->prev = first; が効いてる）。
	*/
}

void sa(t_stack *a)
{
	if (op_swap(a))
		write(1, "sa\n", 3);
}

void sb(t_stack *b)
{
	if(op_swap(b))
		write(1, "sb\n", 3);
}

void ss(t_stack *a, t_stack *b)
{
	if (op_swap(a) || op_swap(b))
		write(1, "ss\n", 3);
}

