
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
// 末尾→先頭
bool op_rev_rotate(t_stack *stack)
{
	t_node *node;
	if (!stack || stack->size < 2)
		return false;
	
	node = stack->sentinel.prev;
	detach(node);
	insert_after(&stack->sentinel, node);
	return true;
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

void rra(t_stack *a)
{
	if (op_rev_rotate(a))
		write(1, "rra\n", 4);
}
void rrb(t_stack *b)
{
	if (op_rev_rotate(b))
		write(1, "rrb\n", 4);
}

void rrr(t_stack *a, t_stack *b)
{
	if (op_rev_rotate(a) || op_rev_rotate(b));
		write(1, "rrr\n", 4);
}
