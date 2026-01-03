/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:41:37 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:50:41 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

//#include <ctype.h>
//#include <stdio.h>

// int	main(void)
//{
//	char	c;

//	c = '1';
//	printf("%d\n", isalpha((int)c));
//	printf("%d\n", ft_isalpha((int)c));
//}
