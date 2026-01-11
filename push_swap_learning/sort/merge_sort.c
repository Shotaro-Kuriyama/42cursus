// merge_sort_basic.c
// cc -Wall -Wextra -Werror merge_sort_basic.c -o ms && ./ms

#include <stdio.h>
#include <stdlib.h>

/* 交換は不要（mergeで並べ直す） */

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
 * merge:
 * a[left..mid) と a[mid..right) は「すでにソート済み」
 * それを buf に小さい順に詰めて、最後に a に戻す
 */
static void merge(int *a, int *buf, int left, int mid, int right)
{
    int i = left;   // 左半分の先頭
    int j = mid;    // 右半分の先頭
    int k = left;   // bufに書く位置

    while (i < mid && j < right)
    {
        if (a[i] <= a[j])
            buf[k++] = a[i++];
        else
            buf[k++] = a[j++];
    }
    while (i < mid)
        buf[k++] = a[i++];
    while (j < right)
        buf[k++] = a[j++];

    // bufの結果を a に戻す
    k = left;
    while (k < right)
    {
        a[k] = buf[k];
        k++;
    }
}

/*
 * merge_sort:
 * 区間 a[left..right) をソートする（rightは含まない）
 */
static void merge_sort_range(int *a, int *buf, int left, int right)
{
    int mid;

    // 要素が0個 or 1個なら、すでにソート済み
    if (right - left <= 1)
        return;

    mid = left + (right - left) / 2;

    // 1) 左をソート
    merge_sort_range(a, buf, left, mid);
    // 2) 右をソート
    merge_sort_range(a, buf, mid, right);
    // 3) 左右（ソート済み）を合体
    merge(a, buf, left, mid, right);
}

static int merge_sort(int *a, int n)
{
    int *buf;

    if (n <= 1)
        return 1;

    // merge用の作業配列（同じ長さ）を1回だけ確保して使い回す
    buf = (int *)malloc(sizeof(int) * n);
    if (!buf)
        return 0;

    merge_sort_range(a, buf, 0, n);

    free(buf);
    return 1;
}

int main(void)
{
    int a[] = {43, 2, 44, 21, 1, 4};
    int n = (int)(sizeof(a) / sizeof(a[0]));

    printf("before: ");
    print_array(a, n);

    if (!merge_sort(a, n))
        return 1;

    printf("after : ");
    print_array(a, n);

    printf("check : %s\n", is_sorted(a, n) ? "OK" : "NG");
    return 0;
}

