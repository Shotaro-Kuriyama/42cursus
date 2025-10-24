/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:58:08 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/24 19:15:14 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

static size_t ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while(s[i])
		i++;
	return i;
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t len;

	len = ft_strlen(s);

	(void)write(fd, s, len);
	(void)write(fd, "\n", 1);
}

void ft_putendl_fd(char *s, int fd);

int main(void)
{
    ft_putendl_fd("Hello stdout", 1); // 画面(標準出力)
    ft_putendl_fd("Hello stderr", 2); // 画面(標準エラー)

    // 挙動の違い（シェルで）
    // ./a.out > out.txt
    // → "Hello stdout" は out.txt に、"Hello stderr" は画面に表示
    //
    // ./a.out 1> out.txt 2> err.txt
    // → stdout と stderr を別々のファイルに保存
    return 0;
}
