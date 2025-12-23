/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:25 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:50:22 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

//#include <stdio.h>
//#include <strings.h>

// int main(void)
//{
//	char buf[] = "ABCDEFGHIJK";
//	char buf2[] = "ABCDEFGHIJK";

//	bzero(buf+2, 5);
//	ft_bzero(buf2+2, 5);

//	printf("%s\n", buf);
//	printf("%s\n", buf2);
//}