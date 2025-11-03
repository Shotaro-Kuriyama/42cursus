/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:07:11 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/03 17:27:58 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>

int ft_putchar(int c);
int ft_putstr(char *c);
int	ft_putnbr(int n);
int	ft_putunbr(int n);
int	ft_put_hex_x(unsigned int ul, int i);
int	ft_put_hex_X(unsigned int ul);
int	ft_put_hex_ul(void *p);


#endif




