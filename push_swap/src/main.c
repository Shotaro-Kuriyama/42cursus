
#include "push_swap.h"

int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	(void)b;

    if (argc < 2)
        return 0;

    stack_init(&a);
    stack_init(&b);

	if (!parse_args_to_stack(argc, argv, &a))
        return 1;

    if (stack_is_sorted(&a))
        return 0;
    //print_stack(&stack_a);
    PS_VALIDATE(&a);

    if (a.size <= 5)
        sort_small(&a, &b);
    else
        sort_big(&a, &b);
        
    stack_free(&a);
    stack_free(&b);
    return 0;
}
