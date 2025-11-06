/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:05:20 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 10:05:21 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

int	ft_putchar(int c)
{
	unsigned char uc;

	uc = (unsigned char)c;
	return (write(1, &uc, 1));
}