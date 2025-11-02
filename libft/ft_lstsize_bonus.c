/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:48:36 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:10:14 by skuriyam         ###   ########.fr       */
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

// int	main(void)
//{
//	t_list	*head;
//	t_list	*n1;
//	t_list	*n2;
//	t_list	*n3;
//	int		i;

//	head = NULL;               //まずは空リスト（先頭NULL)
//	n1 = ft_lstnew("42Tokyo"); //新しいノードを作って返す
//	n2 = ft_lstnew("Apple");   //新しいノードを作って返す
//	n3 = ft_lstnew("Google");  //新しいノードを作って返す
//	// headはNULL
//	ft_lstadd_front(&head, n1); //空リストに１つ追加
//	ft_lstadd_front(&head, n2); //さらに先頭に追加
//	ft_lstadd_front(&head, n3); //さらに先頭に追加
//	i = ft_lstsize(head);
//	printf("%d\n", i);
//}
