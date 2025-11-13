/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:07:11 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/10 15:06:01 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_putchar(int c);
int		ft_putstr(const char *c);
int		ft_putptr(void *p);
int		ft_put_hex(unsigned int n, int i);
int		ft_putnbr(int n);
int		ft_putunbr(unsigned int n);
char	*ft_itoa_u(unsigned int num);
char	*ft_itoa_hex(unsigned long long num);
int		ft_printf(const char *format, ...);

#endif
