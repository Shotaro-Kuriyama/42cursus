/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:53:49 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 12:57:33 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

char *ft_strrchr(const char *s, int c)
{
    unsigned char uc;
    const char *last;

	uc = (unsigned char)c;
	last = NULL;

    while (*s)
    {
        if ((unsigned char)*s == uc)
            last = s;           // 最後に見つかった位置を保持
        s++;
    }
    if (uc == '\0')              // 終端は s が今指している場所
        return (char *)s;
    return (char *)last;         // 見つからなければ NULL
}

int main(void)
{
    char s[] = "42Tokyo";
    int c = 'o';

    char *p = ft_strrchr(s, c);
    printf("%s\n", p);
}
