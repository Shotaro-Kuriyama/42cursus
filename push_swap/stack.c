
#include <stdlib.h>

typedef struct s_node {
    int value;
    struct s_node *next;
} t_node;

static t_node *new_node(int v)
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
static void push_back (t_node **a, t_node *n)
{
    t_node *cur;

    /*
    もしaの参照先のメモリのt_node変数の値がNULLだったら
    その*aにnを代入してリターン
    →つまり、連結リスト1個目を作成する場合にここに入るはず？
    */
    if (!*a)
    {
        *a = n;
        return ;
    }

    cur = *a;
    while (cur->next)
        cur = cur->next;
    //最後まで移動して、最後の連結リストのnextにnを代入
    cur->next = n;


}

#include <limits.h>
#include <stdint.h>

int ft_atoi_safe(const char *s)
{
    int sign;
    int64_t r;
    int d;

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
         if (sign == 1)
        {
            // 安全条件：r * 10 + d <= INT_MAX
            if (r > ((int64_t)INT_MAX - d) / 10)
                return (INT_MAX);
        }
        else
        {
            // 安全条件：r * 10 + d <= INT_MAX + 1（= 2147483648 まで許可）
            if (r > (((int64_t)INT_MAX + 1) - d) / 10)
                return (INT_MIN);
        }
        
        r = r * 10 + d;
        s++;
    }
    return (int)(sign * r);
}

int main(int argc, char **argv)
{
    t_node *a; //スタックa
    t_node *b; //スタックb

    a = NULL;
    b = NULL;

    int i;
    i = 1; //0番目は./a.outだから飛ばす

    (void)b; //ここではbは使わないのでvoidで使っとく

    while (i < argc)
    {

    }




    


}