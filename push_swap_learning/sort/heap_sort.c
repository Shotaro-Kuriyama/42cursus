// heap_sort_basic.c
// cc -Wall -Wextra -Werror heap_sort_basic.c -o hs && ./hs

#include <stdio.h>

static void swap_int(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

static void print_array(int *a, int n)
{
    int i = 0;
    while (i < n)
    {
        printf("%d%s", a[i], (i + 1 == n) ? "\n" : " ");
        i++;
    }
}

static int is_sorted(int *a, int n)
{
    int i = 1;
    while (i < n)
    {
        if (a[i - 1] > a[i])
            return 0;
        i++;
    }
    return 1;
}

/*
 * sift_down:
 * root から下に向かって、最大ヒープの形（親 >= 子）になるように直す
 *
 * 子の位置:
 * left  = 2*root + 1
 * right = 2*root + 2
 */
static void sift_down(int *a, int n, int root)
{
    while (1)
    {
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        int largest = root;

        if (left < n && a[left] > a[largest])
            largest = left;
        if (right < n && a[right] > a[largest])
            largest = right;

        // 親が最大ならOK
        if (largest == root)
            return;

        // 親が小さいので、最大の子と交換して続ける
        swap_int(&a[root], &a[largest]);
        root = largest;
    }
}

/*
 * heap_sort:
 * 1) 配列を最大ヒープにする（heapify）
 * 2) 先頭（最大）を末尾と交換 → 最大が確定
 * 3) ヒープの範囲を1つ縮めて、また sift_down
 */
static void heap_sort(int *a, int n)
{
    int end;

    if (n <= 1)
        return;

    // 1) heapify：最後の親から逆順に sift_down
    // 最後の親は (n-2)/2
    for (int i = (n - 2) / 2; i >= 0; i--)
        sift_down(a, n, i);

    // 2) 末尾に最大を確定させていく
    end = n - 1;
    while (end > 0)
    {
        swap_int(&a[0], &a[end]);   // 最大を末尾へ
        sift_down(a, end, 0);       // ヒープ範囲は [0..end-1]
        end--;
    }
}

int main(void)
{
    int a[] = {43, 2, 44, 21, 1, 4};
    int n = (int)(sizeof(a) / sizeof(a[0]));

    printf("before: ");
    print_array(a, n);

    heap_sort(a, n);

    printf("after : ");
    print_array(a, n);

    printf("check : %s\n", is_sorted(a, n) ? "OK" : "NG");
    return 0;
}
