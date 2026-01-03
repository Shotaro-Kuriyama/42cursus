/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:55:03 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/30 17:59:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	if (!f || !del)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			return (ft_lstclear(&new_list, del), NULL);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

//#include <ctype.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//static void	*dup_upper(void *p)
//{
//	char	*s;
//	size_t	n;
//	char	*q;
//	size_t	i;

//	s = (char *)p;
//	n = strlen(s);
//	q = malloc(n + 1);
//	if (!q)
//		return (NULL);
//	i = 0;
//	while (i < n)
//	{
//		q[i] = (char)ft_toupper((unsigned char)s[i]);
//		i++;
//	}
//	q[n] = '\0';
//	return (q);
//}

//static void	del_str(void *p)
//{
//	free(p);
//}

//int	main(void)
//{
//	t_list	*a;
//	t_list	*b;
//	t_list	*c;
//	t_list	*mapped;

//	a = ft_lstnew(strdup("ab"));
//	b = ft_lstnew(strdup("cD"));
//	c = ft_lstnew(strdup("42"));
//	ft_lstadd_back(&a, b);
//	ft_lstadd_back(&a, c);
//	mapped = ft_lstmap(a, dup_upper, del_str);
//	while (mapped != NULL)
//	{
//		printf("%s\n", (char *)mapped->content);
//		mapped = mapped->next;
//	}
//	ft_lstclear(&mapped, del_str);
//	ft_lstclear(&a, del_str);
//	return (0);
//}
