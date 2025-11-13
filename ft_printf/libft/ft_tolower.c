/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:19:02 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 16:03:14 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc >= 'A' && uc <= 'Z')
		return (uc + ('a' - 'A'));
	return (c);
}

//#include <stdio.h>

// int	main(void)
//{
//	unsigned char c = 'A';
//	unsigned char d = '1';

//	printf("%c\n", (unsigned char)ft_tolower(c));
//}