/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:54:27 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/30 19:18:38 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dclist.h"


/*
** ルール（不変条件）
** - 空：sent.next == &sent かつ sent.prev == &sent
** - 非空：sent.next が先頭、sent.prev が末尾
** - NULLは出てこない（常に循環）
*/


//番兵の初期化（空のリングを作る） init = 初期化
void list_init(t_list *l)
{
    l->sent.next = &l->sent;  //lはポインタ、sentは実体
    l->sent.prev = &l->sent;
    l->size = 0;
}

//空判定
bool list_empty(const t_list *l)
{
    return (l->sent.next == &l->sent);
    //空ならリターン1
}

t_node *list_new_node(int v)
{
    t_node *n;

    n = (t_node *)malloc(sizeof(t_node));
    if (!n)
        return NULL;
    //ここまででnodeの箱
    n->v = v;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

// a <-> n <-> b を作る
void link_between(t_node *a, t_node *n, t_node *b)
{
    a->next = n;
    n->prev = a;
    n->next = b;
    b->prev = n;
}
/*
一言で言うと：
「a と b がすでに隣り合っているところに、n を間に挟む」
つまり n を (a と b の間) に差し込む関数です。
*/

// nをリングから外す（a <-> n <-> b ）→ノードnを孤立させる
void  unlink_node(t_node *n) //delete target
{
    t_node *a;
    t_node *b;

    a = n->prev;
    b = n->next;
    a->next = b;
    b->prev = a;
    n->prev = NULL;
    n->next = NULL;
}

// 先頭に挿入：　sent <-> (new) <-> old_first
void push_front(t_list *l, t_node *n)
{
    link_between(&l->sent, n, l->sent.next);
    l->size++;
}

// 末尾に挿入：　old_last <-> (new) <-> sent
void push_back(t_list *l, t_node *n)
{
    link_between(l->sent.prev, n, &l->sent); //l->sent.prev = old_last 
	l->size++;
}

t_node *pop_front(t_list *l)
{
	t_node *n;

	if (list_empty(l))
		return NULL;
	n = l->sent.prev;
	unlink_node(n);
	l->size--;
	return n;
}






