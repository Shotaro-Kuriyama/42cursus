/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:58:31 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:52:37 by skuriyam         ###   ########.fr       */
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

// void	del_str(void *p)
//{
//	free(p);
//}

//// デバッグ用: リストを表示（content は文字列想定）
// void	print_list(t_list *head)
//{
//	while (head != NULL)
//	{
//		printf("%s -> ", (char *)head->content);
//		head = head->next;
//	}
//	printf("NULL\n");
//}

// int	main(void)
//{
//	// ノード3つ作成（content は strdup でヒープ確保）
//	t_list *a = ft_lstnew(ft_strdup("AAA"));
//	t_list *b = ft_lstnew(ft_strdup("BBB"));
//	t_list *c = ft_lstnew(ft_strdup("CCC"));

//	a->next = b;
//	b->next = c;

//	print_list(a);

//	// 1) 先頭ノード(a)を削除するケース
//	t_list *old_head;

//	old_head = a;

//	a = a->next;                     // 先頭を削除するのでnextに付け替える
//	ft_lstdelone(old_head, del_str); // 元の先頭だけ削除
//	print_list(a);                   // BBB -> CCC -> NULL

//	// 2) 中間ノード(b)を削除するケース（今の先頭は a==b）
//	t_list *prev = a;         // 先頭(BBB) prev = previous(一つ前の−ノード)
//	t_list *target = a->next; // 次(CCC) を消したいなら target = prev->next;
//	// 今回は BBB->CCC の形なので、中間削除の形を模して：
//	// prev->next を飛ばす付け替え（中間削除の一般形）
//	prev->next = target->next; // ここでは target は CCC、next は NULL
//	ft_lstdelone(target, del_str);
//	print_list(a); // BBB -> NULL

//	// 後始末：残りのノード(BBB)を削除
//	ft_lstdelone(a, del_str);
//	a = NULL;
//}