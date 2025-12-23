/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:29:45 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:55:38 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

//#include <stdio.h>

//static void	to_upper_cb(unsigned int i, char *c)
//{
//	(void)i;
//	if (*c >= 'a' && *c <= 'z')
//		*c = (char)(*c - ('a' - 'A'));
//}

//static void	zigzag_cb(unsigned int i, char *c)
//{
//	if (*c >= 'a' && *c <= 'z')
//	{
//		if (i % 2 == 0)
//			*c = (char)(*c - ('a' - 'A'));
//	}
//	else if (*c >= 'A' && *c <= 'Z')
//	{
//		if (i % 2 == 1)
//			*c = (char)(*c + ('a' - 'A'));
//	}
//}

//int	main(void)
//{
//	char	s[] = "LibftStrIteri";
//	char	s1[] = "42Tokyo";

//	ft_striteri(s, zigzag_cb);
//	printf("%s\n", s);
//	ft_striteri(s1, to_upper_cb);
//	printf("%s\n", s1);
//	return (0);
//}
