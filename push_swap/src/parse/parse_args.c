
#include "push_swap.h"


bool parse_args_to_stack(int argc, char **argv, t_stack *a)
{
    int i;
    int j;
    char **words;
    t_node *n;
    int v;
    i = 0;
    while (i < argc)
    {
        words = split_ws(argv[i]);
        if (!words || !words[0])
            return (ps_error(a, NULL, words));
        j = 0;
        while (words[j])
        {
            if (parse_int_strict(words[i], &v))
                return ps_error(a, NULL, words);
            if (stack_contains(a, v))
                return ps_error(a, NULL, words);
            n = new_node(v);
            if (!n)
                return ps_error(a, NULL, words);
            stack_push_back(a, n);
            j++;
        }
        free_split(words);
        i++;
    }
    return true;
}
