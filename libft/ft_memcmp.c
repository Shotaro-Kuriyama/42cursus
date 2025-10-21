/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:10:05 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/21 12:02:50 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
書式

#include <string.h>

int
memcmp(const void *b1, const void *b2, size_t len);

解説
memcmp() 関数は、バイト列 b1 をバイト列 b2 と比較します。 両方のバイト列は、 len の長さのバイト列であるとみなされます。

戻り値
memcmp() 関数は、2 つのバイト列が一致する場合、0 を返します。 そうでない時は、
最初に一致しなかった 2 つのバイト間の差 (unsigned char の値として扱われます。たとえば '\00' は 'amp;\0' よりも大きくなります。) が返されます。 
長さが 0 のバイト列は常に一致します。
*/

#include <stddef.h>
#include <stdio.h>

//バイト列一つ一つに入っている値が一致しているかを確認する

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *b1;
	const unsigned char *b2;
	size_t i;

	b1 = (const unsigned char *)s1;
	b2 = (const unsigned char *)s2;

	i = 0;
	while (i < n)
	{
		if (b1[i] != b2[i])
			return ((int)b1[i] - (int)b2[i]);
		i++;
	}

	return 0;

}
static void dump_bytes(const void *p, size_t n)
{
    const unsigned char *b = (const unsigned char *)p;
    size_t i = 0;

    while (i < n)
    {
        printf("%02X ", b[i]);
        i++;
    }
    puts("");
}

int main(void)
{
    char s1[] = "42Tokyo";
    char s2[] = "42Kyoto";
    size_t n1 = 4;

    int j = 123173831;
    int k = 182874326;
    size_t n2 = sizeof j; // 可搬性◎

    printf("ft_memcmp(s1,s2,%zu) = %d\n", n1, ft_memcmp(s1, s2, n1)); // 例：9

    printf("j bytes: "); dump_bytes(&j, n2);
    printf("k bytes: "); dump_bytes(&k, n2);
    printf("ft_memcmp(&j,&k,%zu) = %d\n", n2, ft_memcmp(&j, &k, n2));
}