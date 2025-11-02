/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:36:03 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:51:46 by skuriyam         ###   ########.fr       */
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

//	while (head != NULL)
//	{
//		printf("%s ", (char *)head->content); // void *contentのアドレスからヌル文字まで%sで探索
//		head = head->next;                    // cur のnextは？次のノードの先頭アドレス
//	}

//	//ここから後片付け
//	//今回はcontentはリテラル文字列（mallocじゃない)なのでfreeしない。ノード(node)だけ開放

//	t_list *next;
//	while (head != NULL)
//	{
//		next = head->next; //次のノードを渡しておく
//		free(head);        //自身を開放
//		head = next;       //保存した次のノードを代入
//	}
//}