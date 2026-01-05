
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

