/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:25:27 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/24 19:13:57 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>   // open
#include <unistd.h>  // close

void	ft_putchar_fd(char c, int fd)
{
	(void)write(fd, &c, 1);
}

int main(void)
{

	//標準出力に出す
	ft_putchar_fd('A', 1);
	ft_putchar_fd('\n', 1);

	//標準エラー出力に出す
	ft_putchar_fd('E', 2);
	ft_putchar_fd('\n', 2);

	//ファイルに書く
	int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); //fd = 3に該当する　
	//O_WRONLY | O_CREAT | O_TRUNC 左から、out.txtがあったら作る、的な感じ
	if (fd < 0)
		return 1;

	ft_putchar_fd('H', fd);
	ft_putchar_fd('i', fd);
	ft_putchar_fd('\n', fd);

	close(fd);



}