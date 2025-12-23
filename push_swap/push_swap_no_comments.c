// push_swap.c
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

    *out = (int)(sign * r);   // ★ここが超重要（out じゃなくて *out）
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

//int main(int argc, char **argv)
//{
//    t_node *a = NULL;
//    t_node *b = NULL;
//    int i;
//    int v;

//    (void)b;

//    if (argc < 2)
//        return 1;

//    i = 1;
//    while (i < argc)
//    {
//        if (!parse_int_strict_by_atoi(argv[i], &v))
//        {
//            write(2, "Error\n", 6);
//            free_list(a);
//            return 1;
//        }

//        if (!push_back(&a, new_node(v)))
//        {
//            write(2, "Error\n", 6);
//            free_list(a);
//            return 1;
//        }
//        i++;
//    }

//    print_list(a);
//    free_list(a);
//    return 0;
//}
