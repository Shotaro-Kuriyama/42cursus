/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sentinel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shotarokuriyama <shotarokuriyama@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:18:03 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/04 13:48:13 by shotarokuri      ###   ########.fr       */
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
void insert_after(t_node *pos, t_node *node)
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
//unlink_node(node)
void detach(t_node *node)
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

void push_front_stack(t_stack *stack, t_node *node)
{
    if (!stack || !node)
        return;
    // 先頭に挿入：sentinel と sentinel.next の間
    insert_after(&stack->sentinel, node);
    stack->size++;
}

/* 末尾追加：O(1)（番兵の prev が末尾を指す） */
void push_back_stack(t_stack *stack, t_node *node)
{
	if (!stack || !node)
		return ;
    // 末尾に挿入：末尾(stack->sentinel.prev) と sentinel の間
	insert_after(stack->sentinel.prev, node);
	stack->size++;
}
//　先頭を取り出す
t_node *pop_front_stack(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;
    node = stack->sentinel.next;
    detach(node);
    stack->size--;
    return node;
}
// 末尾を取り出す
t_node *pop_back_stack(t_stack *stack)
{
    t_node *node;

    if (!stack || stack->size == 0)
        return NULL;
    node = stack->sentinel.prev;
    detach(node);
    stack->size--;
    return node;
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

bool stack_validate(const t_stack *stack)
{
    const t_node *sentinel;
    const t_node *current;
    const t_node *next_node;
    const t_node *prev_node;
    size_t  i;

    if (!stack)
        return false;

    sentinel = &stack->sentinel;
    
    /* sentinel 自体のリンクが NULL なのは異常 */
    if (!sentinel->next || !sentinel->prev)
        return false;

    /* 空のときは "自分を指す" 形が必須条件*/
    if (stack->size == 0)
    {
        if (sentinel->next != sentinel)
            return false;
        if (sentinel->prev != sentinel)
            return false;
        return true;
    }

    /* size > 0 なのに self-loop は異常 */
    if (sentinel->next == sentinel || sentinel->prev == sentinel)
        return false;
    
    /*
    * (1) next方向: リンク整合性チェック
    *    「current->next の prev は current である」
    *    を辿りながら確認
    */
    current = sentinel;
    i = 0;
    while (i < stack->size + 1)
    {
        next_node = current->next;
        if (!next_node)
            return false;
        if (next_node->prev != current)
            return false;
        current = next_node;
        i++;
    }
    /* ちょうど size+1 歩で sentinel に戻るべき */
    if (current != sentinel)
        return false;
    
    /*
    * (2) prev方向: リンク整合性チェック
    *    「current->prev の next は current」
    */
    current = sentinel;
    i = 0;
    while (i < stack->size + 1)
    {
        prev_node = current->prev;
        if (!prev_node)
            return false;
        if (prev_node->next != current)
            return false;
        current = prev_node;
        i++;
    }
    if (current != sentinel)
        return false;

    /*
    * (3) 実ノード数を数えて size と一致するかチェック
    *     ※ size が間違っていても (1)(2) が偶然通るケースがあるため
    * ケースA：実際のノード数 N と size が
    * ズレてるけど、size+1 が “1周の長さ” の倍数
    * ケースB：輪は正しいが size が 
    * “大きすぎる” ケースが特に危険
    */
    current = sentinel->next;
    i = 0;
    while (current != sentinel && i <= stack->size)
    {
        current = current->next;
        i++;
    }
    /* sentinel に戻れない or sizeを超えても戻れないのは異常 */
    if (current != sentinel)
        return false;
    /* 実ノード数 i は size と一致するべき */
    if (i != stack->size)
        return false;
    return true;
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

            push_back_stack(&stack_a, node);

            word_index++;
        }
        free_split(words);
        arg_index++;
    }

    //print_stack(&stack_a);
    PS_VALIDATE(&stack_a);

	//sort3_a(&stack_a);
	sort5(&stack_a, &stack_b);
	print_stack(&stack_a);
    free_stack(&stack_a);
    return 0;
}
