/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:15:21 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 16:03:25 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc >= 'a' && uc <= 'z')
		return (uc - ('a' - 'A'));
	return (c);
}

//#include <stdio.h>

// int	main(void)
//{
//	unsigned char c = 'b';

//	c = (unsigned char)ft_toupper(c);
//	printf("%c\n", c);
//}