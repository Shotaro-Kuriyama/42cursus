/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:20:12 by skuriyam          #+#    #+#             */
/*   Updated: 2025/12/23 18:18:49 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "push_swap.h"

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

// 末尾に追加する
int push_back (t_node **a, t_node *n)
{
    // 変数aは「先頭ノードを指すポインタ」
    // 変数nは「新しい一つのノード」
    t_node *cur;

    if (!n)
        return 0;

    /*
    もし*aがNULLだったら
    *aは「連結リストの先頭ポインタ(head)」であることより
    「*a == NULLはリストが空」
    ということである。
    */
    if (!*a)
    {
        *a = n;
        return 1;
    }


    cur = *a;
    while (cur->next)
        cur = cur->next;
    //最後まで移動して、最後の連結リストのnextにnを代入
    cur->next = n;

    return 1;
}

/*
正しい値でない場合はErroを表示したいので、
intで返すよりも返り値をbool型にして、intの
intの値はポインタで管理する方が合っている。

厳密に int に変換する関数（成功/失敗を返す）とは
オーバーフロー → 失敗
数字が1文字もない → 失敗
途中に数字以外 → 失敗
末尾は空白のみ許可（"12 " はOKにする人が多い）
*/
static bool parse_int_strict_by_atoi(const char *s, int *out)
{
    int sign;
    int64_t r;
    int d;
    int digit_count;

    digit_count = 0;
    sign = 1;
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if (*s == '+' || *s == '-')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }
    r = 0;
    while (*s >= '0' && *s <= '9')
    {
        d = *s - '0';
        digit_count++;
         if (sign == 1)
        {
            // 安全条件：r * 10 + d <= INT_MAX
            if (r > ((int64_t)INT_MAX - d) / 10)
                return (false);
        }
        else
        {
            // 安全条件：r * 10 + d <= INT_MAX + 1（= 2147483648 まで許可）
            if (r > (((int64_t)INT_MAX + 1) - d) / 10)
                return (false);
        }
        r = r * 10 + d;
        s++;
    }
    if (digit_count == 0)
        return (false);
    
    //末尾の空白だけ許可するためには ("123 ")
    //この時点でsは数字の最後の次の行まで進んでる（空白一個だけ許す）
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if (*s != '\0')
        return (false);

    *out = (int)(sign * r);
    return (true);
}

static void print_list(t_node *a)
{
    while(a)
    {
        printf ("%d\n", a->value);
        a = a->next;
    }
}

static void free_list(t_node *a)
{
    t_node *next;
    while (a)
    {
        next = a->next;
        free(a);
        a = next;
    }
}


int main(int argc, char **argv)
{
    t_node *a; //スタックa
    t_node *b; //スタックb

    int v;

    a = NULL;
    b = NULL;

    if (argc < 2)
    {
        return 1;
    }

    

    int i;
    i = 1; //0番目は./a.outだから飛ばす

    (void)b; //ここではbは使わないのでvoidで使っとく

    while (i < argc)
    {
        if (!parse_int_strict_by_atoi(argv[i], &v)) //ここで文字列の数字をint型に変換
        {
            printf ("Error\n");
            return 1;
        }
            

        //ここから連結リストに入れたい
        if (!push_back(&a, new_node(v)))
        {
            t_node *head;
            head = a;
            while (a)
            {
                a = a->next;
                if (a != NULL)
                    free (a);
            }
            free(head);
            return 1;
        }
             
        i++;
    }

   print_list(a);
}