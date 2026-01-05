
#include "push_swap.h"

bool stack_contains(t_stack *stack, int value)
{
	t_node *current;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		if (current->value == value)
			return true;
		current = current->next;
	}
	return false;
}

// 最初から並んでたら何も出力しないのが大事。
bool stack_is_sorted(const t_stack *a)
{
	t_node *cur;

	if (!a || a->size < 2)
		return false;
	
	cur = a->sentinel.next;
	while (cur->next != &a->sentinel)
	{	
		if (cur->value > cur->next->value)
			return false;
		cur = cur->next;
	}
	return true;
}