/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:24:39 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 15:53:25 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

//#include <stdio.h>
// int main(void)
//{
//	char   *s = "Hello";
//	t_list *n = ft_lstnew(s);

//	printf("%s\n", (char *)n->content); // キャストして取り出す
//	// s は文字列リテラルなので free しない
//	free(n); // ノード自体は free する
//	return (0);
//}