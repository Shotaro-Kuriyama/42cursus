/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:20:12 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/31 19:18:33 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
単方向リストのコード

typedef struct s_node {
    int value;  //箱の中身（数値）
    struct s_node *next; //次の箱への矢印（ポインタ）
} t_node;
*/

#include "push_swap.h"
#include <unistd.h> // write

t_node *new_node(int v)
{
    t_node *n;
	n = malloc(sizeof(t_node));
    if (!n)
        return NULL;
    n->value = v;
    n->next = NULL;
    return n;
}

int push_back(t_node **a, t_node *n)
{
    t_node *cur;

    if (!n)
        return 0;
    if (!*a)
    {
        *a = n;
        return 1;
    }
    cur = *a;
    while (cur->next)
        cur = cur->next;
    cur->next = n;
    return 1;
}

void free_list(t_node *a)
{
	t_node *next;
    while (a)
    {
        next = a->next;
        free(a);
        a = next;
    }
}

bool parse_int_strict_by_atoi(const char *s, int *out)
{
    int     sign = 1;
    int64_t r = 0;
    int     d;
    int     digit_count = 0;

    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;

    if (*s == '+' || *s == '-')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }

    while (*s >= '0' && *s <= '9')
    {
        d = *s - '0';
        digit_count++;

        if (sign == 1)
        {
            if (r > ((int64_t)INT_MAX - d) / 10)
                return false;
        }
        else
        {
            if (r > (((int64_t)INT_MAX + 1) - d) / 10)
                return false;
        }

        r = r * 10 + d;
        s++;
    }

    if (digit_count == 0)
        return false;

    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if (*s != '\0')
        return false;

    *out = (int)(sign * r);  
    return true;
}

void print_list(t_node *a)
{
    while (a)
    {
        printf("%d\n", a->value);
        a = a->next;
    }
}

bool contains(t_node *a, int v)
{
	while (a)
	{
		if (a->value == v)
			return (true);
		a = a->next;
	}
	return (false);
}

int is_ws(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return 1;
	return 0;
}

size_t count_words_ws(const char *s)
{
	size_t count;

	count = 0;
	while(*s)
	{
		if(*s && !is_ws(*s))
		{
			count++;
			while (*s && !is_ws(*s))
				s++;
			
		}
		else
			s++;
	}
	return count;
}

char *dup_range(const char *start, size_t len)
{
	char *p;
	size_t i;

	p = malloc(sizeof(*p) * (len + 1));
	if (!p)
		return NULL;

	i = 0;
	while(i < len)
	{
		p[i] = start[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void free_split(char **tokens)
{
	size_t i;

	if (!tokens)
		return;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	
}

char **split_ws(const char *s)
{
	size_t words;
	char **tokens;
	size_t idx;
	const char *start;
	size_t len;

	
	words = count_words_ws(s);

	tokens = malloc(sizeof (*tokens) * (words + 1));
	if (!tokens)
		return NULL;
	
	idx = 0;
	while (*s)
	{
		while (*s && is_ws(*s))
			s++;
		if (!*s)
			break;
		start = s;
		while (*s && !is_ws(*s))
			s++;
		len = (size_t)(s - start);

		tokens[idx] = dup_range(start, len);
		if (!tokens[idx])
		{
			while (idx > 0)
				free(tokens[--idx]);
			free(tokens);
			return NULL;
		}
		idx++;
	}
	tokens[idx] = NULL; //配列を走査するための終端の印（センチネル）
	return tokens;
}

int error_exit(t_node **a, char **tokens)
{
	write(2, "Error\n", 6);
	free_split(tokens);
	free_list(*a);
	*a = NULL;
	return 1;
}

int main(int argc, char **argv)
{
    t_node *a = NULL;
    t_node *b = NULL;
    int i;
    int v;
	char **tokens;
	int j;
	t_node *n;
    (void)b;

    if (argc < 2)
        return 0;

    i = 1;
	j = 0;
    while (i < argc)
    {
		// argv[i]が"1 2 3"みたいな場合は分割
		tokens = split_ws(argv[i]);
		if (!tokens)
			return (error_exit(&a, NULL));
		// tokens[0]がない→argv[i]が空白のみ→この場合はErrorにしたい
		if (!tokens[0])
			return (error_exit(&a, tokens));

		j = 0;
		while (tokens[j])
		{
			// 文字列をintに変換
			if (!parse_int_strict_by_atoi(tokens[j], &v))
				return error_exit(&a, tokens);
			// 重複がないか確認
			if (contains(a, v))
				return error_exit(&a, tokens);
			// ノードつけるのを失敗したらダメ
			n = new_node(v);
        	if (!n)
				return error_exit(&a, tokens);
			push_back(&a, n);
			j++;
		}
		free_split(tokens);
        i++;
    }

	//スタックaが正しく積めているか確認
    print_list(a);
    free_list(a);
    return 0;
}
