/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:58:39 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:59:50 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

//#include <stdio.h>

//int	main(void)
//{
//	t_list	*head;
//	t_list	*n1;
//	t_list	*n2;
//	t_list	*n3;
//	t_list	*last;

//	head = NULL;
//	n1 = ft_lstnew("42Tokyo");
//	n2 = ft_lstnew("Apple");
//	n3 = ft_lstnew("Google");
//	// headはNULL
//	ft_lstadd_front(&head, n1);
//	ft_lstadd_front(&head, n2);
//	ft_lstadd_front(&head, n3);
//	last = ft_lstlast(head);
//	printf("%s\n", (char *)last->content);
//}
