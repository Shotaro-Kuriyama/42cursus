/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:43:49 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:50:52 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//#include <ctype.h>
//#include <stdio.h>

// int	main(void)
//{
//	char	c;

//	c = 'A';
//	printf("%d\n", isdigit(c));
//	printf("%d\n", ft_isdigit(c));
//}
