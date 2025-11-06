/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:07:11 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/06 17:54:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_putchar(int c);
int		ft_putstr(char *c);
int		ft_put_hex_x(unsigned int n, int i);
int		ft_put_itoa(int n);
int		ft_put_itoa_u(unsigned int n);
int		ft_put_hex_itoa(void *p);
char	*ft_itoa(int num);
char	*ft_itoa_u(unsigned int num);
char	*ft_itoa_hex(unsigned long long num);

#endif
