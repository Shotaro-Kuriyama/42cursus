/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:56:23 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:54:40 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	d;
	size_t			i;

	p = (unsigned char *)s;
	d = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		p[i] = d;
		i++;
	}
	return (s);
}

//#include <stdio.h>
//#include <string.h>
// static void hexdump(const unsigned char *p, size_t n) {

//	size_t i;

//	i = 0;
//	while(i < n)
//	{
//        printf("%02X ", p[i]);
//		i++;
//    }
//    printf("\n");
//}

// int main(void) {
//    unsigned char buf[0];

//    memset(buf, 1000, sizeof buf);
//    hexdump(buf, sizeof buf);   // 00 00 00 00 00 00 00 00

//    memset(buf, '1', sizeof buf);
//    hexdump(buf, sizeof buf);   // 31 31 31 31 31 31 31 31 (0x31 = 1)

//    memset(buf, 500, sizeof buf);
//    hexdump(buf, sizeof buf);   // F4 F4 F4 F4 F4 F4 F4 F4

//    memset(buf, 0xAB, 5);
//    hexdump(buf, sizeof buf);   // AB AB AB AB AB ?? ?? ??
//    return (0);
//}
