/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:30 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/06 16:35:12 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"


void free_split(char **words)
{
    size_t index;

    if (!words)
        return;

    index = 0;
    while (words[index])
    {
        free(words[index]);
        index++;
    }
    free(words);
}

static bool words_to_stack(char **words, t_stack *a)
{
	int value;
	t_node *n;
	int i;

	i = 0;
	while (words[i])
	{
		if (!parse_int_strict(words[i], &value))
			return false;
		if (stack_contains(a, value))
			return false;
		n = new_node(value);
		if (!n)
			return false;
		stack_push_back(a, n);
		i++;
	}
	return true;
}

bool parse_args_to_stack(int argc, char **argv, t_stack *a)
{
    char **words;
    int i;

    i = 1;
    while (i < argc)
    {
        words = split_ws(argv[i]);
        if (!words || !words[0])
            return (ps_error(a, NULL, words));
        if (!words_to_stack(words, a))
			return ps_error(a, NULL, words);
        free_split(words);
        i++;
    }
    return true;
}
