/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:41:19 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 16:26:11 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ps_error(t_stack *a, t_stack *b, char **words)
{
    write(2, "Error\n", 6);
    free_split(words);
    if (a) 
		stack_free(a);
    if (b) 
		stack_free(b);
    return 0; // false扱いでも1でも、統一が大事
}
