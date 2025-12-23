/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:58:31 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:01:02 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

//#include <stdio.h>

//void	del_str(void *p)
//{
//	free(p);
//}

//void	print_list(t_list *head)
//{
//	while (head != NULL)
//	{
//		printf("%s -> ", (char *)head->content);
//		head = head->next;
//	}
//	printf("NULL\n");
//}

//int	main(void)
//{
//	t_list *a = ft_lstnew(ft_strdup("AAA"));
//	t_list *b = ft_lstnew(ft_strdup("BBB"));
//	t_list *c = ft_lstnew(ft_strdup("CCC"));

//	a->next = b;
//	b->next = c;

//	print_list(a);

//	t_list *old_head;

//	old_head = a;

//	a = a->next;
//	ft_lstdelone(old_head, del_str);
//	print_list(a);

//	t_list *prev = a;
//	t_list *target = a->next;

//	prev->next = target->next;
//	ft_lstdelone(target, del_str);
//	print_list(a);

//	ft_lstdelone(a, del_str);
//	a = NULL;
//}