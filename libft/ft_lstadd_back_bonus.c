/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:25:24 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:02:43 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	head = *lst;
	while (head->next != NULL)
		head = head->next;
	head->next = new;
}

//#include <stdio.h>

//int	main(void)
//{
//	t_list *head;
//	t_list *n1;
//	t_list *n2;
//	t_list *n3;

//	head = NULL;
//	n1 = ft_lstnew("42Tokyo");
//	n2 = ft_lstnew("Apple");
//	n3 = ft_lstnew("Google");

//	ft_lstadd_front(&head, n1);
//	ft_lstadd_front(&head, n2);
//	ft_lstadd_front(&head, n3);

//	t_list *last;

//	last = ft_lstnew("Skytree");
//	ft_lstadd_back(&head, last);

//	while (head != NULL)
//	{
//		printf("%s\n", (char *)head->content);
//		head = head->next;
//	}
//}