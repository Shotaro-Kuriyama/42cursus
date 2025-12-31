/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sentinel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:18:03 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/31 23:41:56 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* -------------------------
   sentinel doubly-circular core
   ------------------------- */

//番兵の初期化（空のリングを作る）
void stack_init(t_stack *stack)
{
	stack->sentinel.next = &stack->sentinel;
	stack->sentinel.prev = &stack->sentinel;
	stack->size = 0;
}

/*
* insert_after:
*   pos の直後に node を差し込む
*/

// link_between(left, node, right)の引数一個減らしたバージョン
static void insert_after(t_node *pos, t_node *node)
{
	//... <-> a <-> pos <-> b <-> ...
	node->next = pos->next; // node <-> b
	node->prev = pos; 		// pos <-> node <-> b → ちゃんとnextとprevにbとposをセットしてあげる

	pos->next->prev = node; // pos->next->prev は b->prev
	pos->next = node;
}

/*
* detach:
*   node をリストから抜き取る（前後をつなぎ直す）
*/
static void detach(t_node *node)
{
	node->prev->next = node->next; // L <-> node <-> Rで、node->prev->next → L->next = R
	node->next->prev = node->prev; // L <-> node <-> Rで、node->next->prev → R->prev = L
	//よってL <-> Rとなりnodeが外れた
	
	node->prev = NULL;
	node->next = NULL;
}

t_node *new_node(int value)
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

/* 末尾追加：O(1)（番兵の prev が末尾を指す） */
int push_back_stack(t_stack *stack, t_node *node)
{
	if (!node)
		return 0;
	insert_after(stack->sentinel.prev, node);
	stack->size++;
	return 1;
}

void free_stack(t_stack *stack)
{
	t_node *current;
	t_node *next_node;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	stack_init(stack);
	//stackは結局番兵なので最後に番兵を初期化する。
}

void print_stack(t_stack *stack)
{
	t_node *current;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
}

bool contains_stack(t_stack *stack, int value)
{
	t_node *current;

	current = stack->sentinel.next;
	while (current != &stack->sentinel)
	{
		if (current->value == value)
			return true;
		current = current->next;
	}
	return false;
}

/* -------------------------
   parse （解析、変換）
   ------------------------- */

bool parse_int_strict(const char *p, int *out_value)
{
    int     sign;
    int64_t accumulator;
    int     digit;
    int     num_digits;

    sign = 1;
    accumulator = 0;
    num_digits = 0;

    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;

    if (*p == '+' || *p == '-')
    {
        if (*p == '-')
            sign = -1;
        p++;
    }

    while (*p >= '0' && *p <= '9')
    {
        digit = *p - '0';
        num_digits++;

        if (sign == 1)
        {
            if (accumulator > ((int64_t)INT_MAX - digit) / 10)
                return false;
        }
        else
        {
            if (accumulator > (((int64_t)INT_MAX + 1) - digit) / 10)
                return false;
        }

        accumulator = accumulator * 10 + digit;
        p++;
    }

    if (num_digits == 0)
        return false;

    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;

    if (*p != '\0')
        return false;

    *out_value = (int)(sign * accumulator);
    return true;
}

/* -------------------------
   split helpers
   ------------------------- */

static int is_whitespace(char ch)
{
    return (ch == ' ' || (ch >= 9 && ch <= 13));
}

static size_t count_words_ws(const char *p)
{
    size_t word_count;

    word_count = 0;
    while (*p)
    {
        if (*p && !is_whitespace(*p))
        {
            word_count++;
            while (*p && !is_whitespace(*p))
                p++;
        }
        else
            p++;
    }
    return word_count;
}

static char *dup_range(const char *start, size_t length)
{
    char    *copied;
    size_t  i;

    copied = (char *)malloc(sizeof(*copied) * (length + 1));
    if (!copied)
        return NULL;

    i = 0;
    while (i < length)
    {
        copied[i] = start[i];
        i++;
    }
    copied[i] = '\0';
    return copied;
}

void free_split(char **words)
{
    size_t index;

    if (!words)
        return;

    index = 0;
    while (words[index])
    {
        free(words[index]);
        index++;
    }
    free(words);
}

char **split_ws(const char *p)
{
    size_t      word_count;
    char        **words;
    size_t      index;
    const char  *start;
    size_t      len;

    word_count = count_words_ws(p);

    words = (char **)malloc(sizeof(*words) * (word_count + 1));
    if (!words)
        return NULL;

    index = 0;
    while (*p)
    {
        while (*p && is_whitespace(*p))
            p++;

        if (!*p)
            break;

        start = p;
        while (*p && !is_whitespace(*p))
            p++;
        len = (size_t)(p - start);

        words[index] = dup_range(start, len);
        if (!words[index])
        {
            while (index > 0)
                free(words[--index]);
            free(words);
            return NULL;
        }
        index++;
    }
    words[index] = NULL; // 配列の終端（センチネル）
    return words;
}

/* -------------------------
   error + main
   ------------------------- */

static int error_exit(t_stack *stack_a, char **words)
{
	write(2, "Error\n", 6);
	free_split(words);
	free_stack(stack_a);
	return 1;
}

int main(int argc, char **argv)
{
	t_stack stack_a;
	t_stack stack_b;

	int     arg_index;
    char    **words;
    int     word_index;
    int     value;
    t_node  *node;

	(void)stack_b;

    if (argc < 2)
        return 0;

    stack_init(&stack_a);
    stack_init(&stack_b);

	arg_index = 1;
    while (arg_index < argc)
    {
        words = split_ws(argv[arg_index]);
        if (!words)
            return error_exit(&stack_a, NULL);

        if (!words[0])
            return error_exit(&stack_a, words);

        word_index = 0;
        while (words[word_index])
        {
            if (!parse_int_strict(words[word_index], &value))
                return error_exit(&stack_a, words);

            if (contains_stack(&stack_a, value))
                return error_exit(&stack_a, words);

            node = new_node(value);
            if (!node)
                return error_exit(&stack_a, words);

            if (!push_back_stack(&stack_a, node))
                return error_exit(&stack_a, words);

            word_index++;
        }
        free_split(words);
        arg_index++;
    }

    print_stack(&stack_a);
    free_stack(&stack_a);
    return 0;
}

