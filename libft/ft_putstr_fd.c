/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:48:06 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/24 18:57:25 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{

	if (!s)
		return ;
		
	while (*s)
	{
		(void)write(fd, s, 1);
		s++;
	}
}

int main(void)
{
	char s[] = "42Tokyo";

	ft_putstr_fd(s, 2);

}