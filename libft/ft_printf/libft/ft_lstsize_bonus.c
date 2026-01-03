/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:48:36 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:58:44 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

//#include <stdio.h>

//int	main(void)
//{
//	t_list	*head;
//	t_list	*n1;
//	t_list	*n2;
//	t_list	*n3;
//	int		i;

//	head = NULL;
//	n1 = ft_lstnew("42Tokyo");
//	n2 = ft_lstnew("Apple");
//	n3 = ft_lstnew("Google");
//	ft_lstadd_front(&head, n1);
//	ft_lstadd_front(&head, n2);
//	ft_lstadd_front(&head, n3);
//	i = ft_lstsize(head);
//	printf("%d\n", i);
//}
