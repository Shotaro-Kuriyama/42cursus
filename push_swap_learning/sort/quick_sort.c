// quick_sort_basic.c
// cc -Wall -Wextra -Werror quick_sort_basic.c -o qs && ./qs

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
 * partition（Lomuto）
 * pivot = a[right] を基準にする
 * 1) i は「pivotより小さいゾーンの最後」を指す
 * 2) j を left..right-1 まで動かし、小さいものを左へ集める
 * 3) 最後に pivot を境界(i+1)へ置く
 *
 * 戻り値：pivotが置かれた位置 p
 */
static int partition(int *a, int left, int right)
{
    int pivot = a[right];
    int i = left - 1;
    int j = left;

    while (j < right)
    {
        if (a[j] < pivot)
        {
            i++;
            swap_int(&a[i], &a[j]);
        }
        j++;
    }
    // pivotを「小さいゾーンの直後」に置く
    swap_int(&a[i + 1], &a[right]);
    return i + 1;
}

static void quick_sort_range(int *a, int left, int right)
{
    int p;

    // 区間が1個以下なら終了
    if (left >= right)
        return;

    p = partition(a, left, right);

    // pivotより左、pivotより右をそれぞれ再帰でソート
    quick_sort_range(a, left, p - 1);
    quick_sort_range(a, p + 1, right);
}

static void quick_sort(int *a, int n)
{
    if (n <= 1)
        return;
    quick_sort_range(a, 0, n - 1);
}

int main(void)
{
    int a[] = {43, 2, 44, 21, 1, 4};
    int n = (int)(sizeof(a) / sizeof(a[0]));

    printf("before: ");
    print_array(a, n);

    quick_sort(a, n);

    printf("after : ");
    print_array(a, n);

    printf("check : %s\n", is_sorted(a, n) ? "OK" : "NG");
    return 0;
}
