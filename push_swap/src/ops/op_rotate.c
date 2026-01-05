

#include "push_swap.h"


// 先頭→末尾
bool op_rotate(t_stack *stack)
{
	t_node *node;

	if (!stack || stack->size < 2)
		return false;

	node = stack->sentinel.next; //先頭
	detach(node);			 //先頭を抜き取る
	insert_after(stack->sentinel.prev, node); //末尾の直後にnodeを繋げる
	return true;
}


void ra(t_stack *a)
{
	if (op_rotate(a))
		write(1, "ra\n", 3);
}
void rb(t_stack *b)
{
	if (op_rotate(b))
		write(1, "rb\n", 3);
}
void rr(t_stack *a, t_stack *b)
{
	if (op_rotate(a) || op_rotate(b))
		write(1, "rr\n", 3);
}

