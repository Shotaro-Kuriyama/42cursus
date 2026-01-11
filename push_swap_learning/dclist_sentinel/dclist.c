/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dclist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:54:27 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/31 18:15:48 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dclist.h"
#include <stdio.h>
#include <stdlib.h>

/*
** 不変条件：
** - 空：sentinel.next == &sentinel かつ sentinel.prev == &sentinel
** - 非空：sentinel.next が先頭、sentinel.prev が末尾
** - NULLは基本的に出てこない（常に循環）
*/

// left <-> node <-> right を作る
static void link_between(t_node *left, t_node *node, t_node *right)
{
    left->next = node;
    node->prev = left;
    node->next = right;
    right->prev = node;
}
/*
一言で言うと：
「a と b がすでに隣り合っているところに、n を間に挟む」
つまり n を (a と b の間) に差し込む関数です。
*/

// nをリングから外す（left <-> node <-> right ）→ノードnを孤立させる
static void  unlink_node(t_node *node) //delete target
{
 	t_node *left;
    t_node *right;

	left = node->prev;
	right = node->next;
	
    left->next = right;
    right->prev = left;
    node->prev = NULL;
    node->next = NULL;
}


//番兵の初期化（空のリングを作る） init = 初期化
void dclist_init(t_list *list)
{

	list->sentinel.next = &list->sentinel;  //listはポインタ、sentinelは実体
    list->sentinel.prev = &list->sentinel;
    list->size = 0;
}

//空判定
bool dclist_empty(const t_list *list)
{
	return (list->sentinel.next == &list->sentinel);
    //空ならリターン1
}

t_node *dclist_node_new(int value)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return NULL;

	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void dclist_node_free(t_node *node)
{
	free(node);
}

// 先頭に挿入：　sent <-> (new) <-> old_first
void dclist_push_front(t_list *list, t_node *node)
{
	if (!list || !node)
        return;
    link_between(&list->sentinel, node, list->sentinel.next);
    list->size++;
}

// 末尾に挿入：　old_last <-> (new) <-> sent
void dclist_push_back(t_list *list, t_node *node)
{
	if (!list || !node)
        return;
    link_between(list->sentinel.prev, node, &list->sentinel);
    list->size++;
}

t_node *dclist_pop_front(t_list *list)
{
	t_node *node;

	if (!list || dclist_empty(list))
		return NULL;
	node = list->sentinel.next;
	unlink_node(node);
	list->size--;
	return node;
}

t_node *dclist_pop_back(t_list *list)
{
    t_node *node;

    if (!list || dclist_empty(list))
        return NULL;
    node = list->sentinel.prev;
    unlink_node(node);
    list->size--;
    return node;
}

void dclist_clear(t_list *list, void (*del)(t_node *))
{
	t_node *node;

    if (!list)
        return;
    while ((node = dclist_pop_front(list)) != NULL)
    {
        if (del)
            del(node); // ←「渡された削除関数」を呼ぶ
        else
            free(node);  // ←削除関数が無いならfreeだけ
    }
}

void dclist_print_forward(const t_list *list)
{
    const t_node *current;

    if (!list)
        return;
    printf("[F] size=%zu : ", list->size);
    current = list->sentinel.next; 
    while (current != &list->sentinel)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}


void dclist_print_backward(const t_list *list)
{
    const t_node *current;

    if (!list)
        return;
    printf("[B] size=%zu : ", list->size);
    current = list->sentinel.prev;
    while (current != &list->sentinel)
    {
        printf("%d ", current->value);
        current = current->prev;
    }
    printf("\n");
}

bool dclist_validate(const t_list *l)
{
	const t_node *current;
	const t_node *next_node;
	const t_node *prev_node;
	size_t i;

	if (!l)
		return false;

	 // next方向：size+1 回たどって sentinel に戻るか
	current = &l->sentinel;
	i = 0;
	while (i < l->size + 1)
	{
		next_node = current->next;  // 番兵（s = cur） <-> cur->next
		if (!next_node)
			return false;
		if (next_node->prev != current)
			return false;
		current = next_node;
		i++;
	}
	if (current != &l->sentinel)
		return false;
	
	// prev方向：size+1 回たどって sentinel に戻るか
	current = &l->sentinel;
	i = 0;
	while (i < l->size + 1)
	{
		prev_node = current->prev;
		if (!prev_node)
			return false;
		if (prev_node->next != current)
			return false;
		current = prev_node;
		i++;
	}
	if (current != &l->sentinel)
		return false;
	
	// emptyのときの形も念押し
	if (l->size == 0)
	{
		if (l->sentinel.next != &l->sentinel)
			return false;
		if (l->sentinel.prev != &l->sentinel)
			return false;
	}
	return true;
}



/*
validateの検証がなぜこのようなコードになるのか？
この関数は「循環リストとして壊れてないか」を検証する関数である。

双方向リストの大事な不変条件（invariant）はこれ：
・A->next == B なら 必ず B->prev == A
・A->prev == B なら 必ず B->next == A

つまり 片方向の矢印だけ正しくてもダメ なんです。

例：壊れてるけど “next だけ” だと気づけないケース
たとえばこういうバグが起きたとします：
・cur->next は正しく nx を指している
・でも nx->prev が 別のノードを指してしまっている（更新漏れ）
このとき nx を next で辿るだけなら普通に進めちゃうので、
「一見動く」けど、prev を使う操作（削除や挿入）が即死します。

例えば remove が危ない

よくある remove はこうします：

a->next = b;
b->prev = a;

もし nx->prev が壊れていると、nx を外すときに
nx->prev->next = nx->next みたいな処理が 関係ない場所を破壊します。

つまりこのチェックは、
「next の鎖」だけじゃなく **next と prev が “相互に整合している”**ことを保証する
ために必須です。
*/









