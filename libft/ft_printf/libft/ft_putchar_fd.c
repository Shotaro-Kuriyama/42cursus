/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:25:27 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:56:38 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	(void)write(fd, &c, 1);
}

//#include <fcntl.h>

//int	main(void)
//{
//	ft_putchar_fd('A', 1);
//	ft_putchar_fd('\n', 1);

//	ft_putchar_fd('E', 2);
//	ft_putchar_fd('\n', 2);

//	int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

//	if (fd < 0)
//		return (1);

//	ft_putchar_fd('H', fd);
//	ft_putchar_fd('i', fd);
//	ft_putchar_fd('\n', fd);

//	close(fd);
//}