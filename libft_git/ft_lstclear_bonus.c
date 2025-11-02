/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:21:34 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:01:28 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*next;

	if (!lst || !del)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		del(cur->content);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}

//#include <stdio.h>

//static void	free_wrapper(void *p)
//{
//	free(p);
//}

//static void	print_list_str(t_list *lst)
//{
//	while (lst)
//	{
//		printf("%s ", (char *)lst->content);
//		lst = lst->next;
//	}
//	printf("\n");
//}

//int	main(void)
//{
//	t_list *head;

//	head = NULL;

//	t_list *n1 = ft_lstnew(ft_strdup("one"));
//	t_list *n2 = ft_lstnew(ft_strdup("two"));
//	t_list *n3 = ft_lstnew(ft_strdup("three"));

//	ft_lstadd_back(&head, n1);
//	ft_lstadd_back(&head, n2);
//	ft_lstadd_back(&head, n3);

//	print_list_str(head);

//	ft_lstclear(&head, free_wrapper);

//	if (head == NULL)
//		printf("head == NULL\n");
//	else
//		printf("head != NULL\n");

//	ft_lstclear(&head, free_wrapper);

//	return (0);
//}