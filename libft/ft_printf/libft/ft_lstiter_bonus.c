/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:38:17 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:00:08 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		(f)(lst->content);
		lst = lst->next;
	}
}

//#include <stdio.h>

//static void	print_str(void *p)
//{
//	const char	*s;

//	s = (const char *)p;
//	if (s)
//		printf("%s\n", s);
//	else
//		printf("(null)\n");
//}

//int	main(void)
//{
//	t_list *lst = NULL;

//	ft_lstadd_back(&lst, ft_lstnew("hello"));
//	ft_lstadd_back(&lst, ft_lstnew("42Tokyo"));
//	ft_lstadd_back(&lst, ft_lstnew("libft"));

//	ft_lstiter(lst, print_str);

//	ft_lstclear(&lst, (void (*)(void *))0);
//	return (0);
//}