#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h> // write
#include <stdio.h>  // debug用（最終的には消してOK）

typedef struct s_node {
    int value;
    struct s_node *next;
} t_node;

/* ---------- list utils ---------- */

static t_node *new_node(int v)
{
    t_node *n = malloc(sizeof(t_node));
    if (!n) return NULL;
    n->value = v;
    n->next = NULL;
    return n;
}

static int push_back(t_node **a, t_node *n)
{
    t_node *cur;

    if (!n) return 0;
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

static void free_list(t_node *a)
{
    while (a)
    {
        t_node *next = a->next;
        free(a);
        a = next;
    }
}

static bool contains(t_node *a, int v)
{
    while (a)
    {
        if (a->value == v)
            return true;
        a = a->next;
    }
    return false;
}

/* ---------- parse int (strict) ---------- */

static bool parse_int_strict(const char *s, int *out)
{
    int     sign = 1;
    int64_t r = 0;
    int     digit_count = 0;

    // 先頭空白
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;

    // 符号
    if (*s == '+' || *s == '-')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }

    // 数字列
    while (*s >= '0' && *s <= '9')
    {
        int d = *s - '0';
        digit_count++;

        // r*10 + d が範囲内か（符号別）
        if (sign == 1)
        {
            if (r > ((int64_t)INT_MAX - d) / 10)
                return false;
        }
        else
        {
            // INT_MIN まで許す（絶対値は INT_MAX+1）
            if (r > (((int64_t)INT_MAX + 1) - d) / 10)
                return false;
        }

        r = r * 10 + d;
        s++;
    }

    // 1桁も無いのはNG（"+" や "   " など）
    if (digit_count == 0)
        return false;

    // 末尾は空白だけ許可、それ以外が残ってたらNG（"12a"など）
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if (*s != '\0')
        return false;

    *out = (int)(sign * r);
    return true;
}

/* ---------- split by whitespace ---------- */

static int is_ws(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

static size_t count_words_ws(const char *s)
{
    size_t count = 0;

    while (*s)
    {
        while (*s && is_ws(*s))
            s++;
        if (*s)
        {
            count++;
            while (*s && !is_ws(*s))
                s++;
        }
    }
    return count;
}

static char *dup_range(const char *start, size_t len)
{
    char *p = malloc(len + 1);
    if (!p) return NULL;
    for (size_t i = 0; i < len; i++)
        p[i] = start[i];
    p[len] = '\0';
    return p;
}

static void free_split(char **toks)
{
    if (!toks) return;
    for (size_t i = 0; toks[i]; i++)
        free(toks[i]);
    free(toks);
}

static char **split_ws(const char *s)
{
    size_t words = count_words_ws(s);
    char **toks = malloc(sizeof(char *) * (words + 1));
    size_t idx = 0;

    if (!toks) return NULL;

    while (*s)
    {
        const char *start;
        size_t len;

        while (*s && is_ws(*s))
            s++;
        if (!*s) break;

        start = s;
        while (*s && !is_ws(*s))
            s++;
        len = (size_t)(s - start);

        toks[idx] = dup_range(start, len);
        if (!toks[idx])
        {
            free_split(toks);
            return NULL;
        }
        idx++;
    }
    toks[idx] = NULL;
    return toks;
}

/* ---------- error helper ---------- */

static int error_exit(t_node **a, char **toks)
{
    write(2, "Error\n", 6);
    free_split(toks);
    free_list(*a);
    *a = NULL;
    return 1;
}

/* ---------- debug ---------- */

static void print_list(t_node *a)
{
    while (a)
    {
        printf("%d\n", a->value);
        a = a->next;
    }
}

/* ---------- main ---------- */

int main(int argc, char **argv)
{
    t_node *a = NULL;
    t_node *b = NULL;

    (void)b;

    if (argc < 2)
        return 0;

    for (int i = 1; i < argc; i++)
    {
        // argv[i] を空白区切りで分割（"1 2 3" もここで対応）
        char **toks = split_ws(argv[i]);
        if (!toks)
            return error_exit(&a, NULL);

        // toksが0個（argv[i]が空白だけ等）の場合はErrorにしたい
        if (!toks[0])
            return error_exit(&a, toks);

        for (size_t j = 0; toks[j]; j++)
        {
            int v;

            if (!parse_int_strict(toks[j], &v))
                return error_exit(&a, toks);

            if (contains(a, v))
                return error_exit(&a, toks);

            if (!push_back(&a, new_node(v)))
                return error_exit(&a, toks);
        }
        free_split(toks);
    }

    // ここで「Aが正しく積めた」ことを確認
    print_list(a);

    free_list(a);
    return 0;
}
