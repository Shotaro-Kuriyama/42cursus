/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:36:03 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 18:02:09 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
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

//	while (head != NULL)
//	{
//		printf("%s ", (char *)head->content);
//		head = head->next;
//	}

//	t_list *next;
//	while (head != NULL)
//	{
//		next = head->next;
//		free(head);
//		head = next;
//	}
//}