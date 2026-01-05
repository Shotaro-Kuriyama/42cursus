/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int_strict.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:32 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/05 12:40:33 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"

bool parse_int_strict(const char *p, int *out_value)
{
    int     sign;
    int64_t accumulator;
    int     digit;
    int     num_digits;

    sign = 1;
    accumulator = 0;
    num_digits = 0;

    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;

    if (*p == '+' || *p == '-')
    {
        if (*p == '-')
            sign = -1;
        p++;
    }

    while (*p >= '0' && *p <= '9')
    {
        digit = *p - '0';
        num_digits++;

        if (sign == 1)
        {
            if (accumulator > ((int64_t)INT_MAX - digit) / 10)
                return false;
        }
        else
        {
            if (accumulator > (((int64_t)INT_MAX + 1) - digit) / 10)
                return false;
        }

        accumulator = accumulator * 10 + digit;
        p++;
    }

    if (num_digits == 0)
        return false;

    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;

    if (*p != '\0')
        return false;

    *out_value = (int)(sign * accumulator);
    return true;
}