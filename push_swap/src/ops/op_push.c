
#include "push_swap.h"

//from→toへpush
bool op_push(t_stack *from, t_stack *to)
{
	t_node *node;

    if (!from || !to)
    	return false;
	if (from->size == 0)
		return false;
	node = pop_front_stack(from);
	if (!node)
		return false;
	push_front_stack(to, node);
	return true;
}

void pa(t_stack *a, t_stack *b)
{
	if (op_push(b, a))
		write(1, "pa\n", 3);
}

void pb(t_stack *a, t_stack *b)
{
	if (op_push(a, b))
		write(1, "pb\n", 3);
}