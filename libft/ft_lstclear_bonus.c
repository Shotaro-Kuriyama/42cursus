/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:21:34 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:52:10 by skuriyam         ###   ########.fr       */
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

// static void	free_wrapper(void *p)
//{
//	free(p); // content が malloc/strdup された前提
//}

// static void	print_list_str(t_list *lst)
//{
//	while (lst)
//	{
//		printf("%s ", (char *)lst->content);
//		lst = lst->next;
//	}
//	printf("\n");
//}

// int	main(void)
//{
//	t_list *head;

//	head = NULL;

//	// 文字列をヒープ確保してノード化（strdup を使う）
//	t_list *n1 = ft_lstnew(ft_strdup("one"));
//	t_list *n2 = ft_lstnew(ft_strdup("two"));
//	t_list *n3 = ft_lstnew(ft_strdup("three"));

//	// 連結
//	ft_lstadd_back(&head, n1);
//	ft_lstadd_back(&head, n2);
//	ft_lstadd_back(&head, n3);

//	print_list_str(head);

//	// ここが本番：全部解放＋head を NULL に
//	ft_lstclear(&head, free_wrapper);

//	// 検証
//	if (head == NULL)
//		printf("head == NULL\n");
//	else
//		printf("head != NULL\n");

//	// 空リストに対してもう一度呼んでも安全であることの確認（何も起きないはず）
//	ft_lstclear(&head, free_wrapper);

//	return (0);
//}