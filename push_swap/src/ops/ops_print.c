

#include "push_swap.h"

void print_stack(t_stack *stack)
{
	t_node *current;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
}