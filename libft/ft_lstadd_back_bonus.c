/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:25:24 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:51:30 by skuriyam         ###   ########.fr       */
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

// int	main(void)
//{
//	t_list *head;
//	t_list *n1;
//	t_list *n2;
//	t_list *n3;

//	head = NULL;               //まずは空リスト（先頭NULL)
//	n1 = ft_lstnew("42Tokyo"); //新しいノードを作って返す
//	n2 = ft_lstnew("Apple");   //新しいノードを作って返す
//	n3 = ft_lstnew("Google");  //新しいノードを作って返す

//	// headはNULL

//	ft_lstadd_front(&head, n1); //空リストに１つ追加
//	ft_lstadd_front(&head, n2); //さらに先頭に追加
//	ft_lstadd_front(&head, n3); //さらに先頭に追加

//	t_list *last;

//	last = ft_lstnew("Skytree");
//	ft_lstadd_back(&head, last);

//	while (head != NULL)
//	{
//		printf("%s\n", (char *)head->content);
//		head = head->next;
//	}
//}