/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int_strict.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:32 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/08 13:11:53 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"

static void sign_judgement(const char **p, int *sign)
{
	if (**p == '+' || **p == '-')
	{
		if (**p == '-')
			*sign = -1;
		(*p)++;
	}
}

static bool accumulate_digits(const char **p, int sign, int64_t *acc, int *digits)
{
    int digit;

    while (**p >= '0' && **p <= '9')
    {
        digit = **p - '0';
		(*digits)++;
        if (sign == 1)
        {
            if (*acc > ((int64_t)INT_MAX - digit) / 10)
                return false;
        }
        else
        {
            if (*acc > (((int64_t)INT_MAX + 1) - digit) / 10)
                return false;
        }
        *acc = *acc * 10 + digit;
        (*p)++;
    }
    return true;
}

//static bool isdigit(char *p)
//{
//	while(p)
//	{
//		if (!(*p >= '0' && *p <= '9'))
//			return 

//	}
//}


// 絶対に自分で理解すること　そうじゃなきゃ許されない
bool parse_int_strict(const char *p, int *out_value)
{
    int     sign;
    int64_t accumulator;
    int     num_digits;

	if (!p || !out_value)
		return false;
    sign = 1;
    accumulator = 0;
    num_digits = 0;
    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;
    sign_judgement(&p, &sign);
    if (!accumulate_digits(&p, sign, &accumulator, &num_digits))
        return false;
    if (num_digits == 0)
        return false;
    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;
    if (*p != '\0')
        return false;
    *out_value = (int)(sign * accumulator);
    return true;
}
