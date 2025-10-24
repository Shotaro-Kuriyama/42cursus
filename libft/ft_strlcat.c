/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:16:21 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/24 20:07:58 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
strlcat() は文字列 src を dst の末尾に追加します。
     追加される文字数は最大で dstsize - strlen(dst) - 1 文字です。 その後、NUL終端処理を行います。ただし、
     dstsize が 0 である場合、または元の dst 文字列が dstsize より長い場合を除きます（
     実際には、これは dstsize が不正であるか、dst が適切な文字列ではないことを意味するため、
     発生すべきではありません）。

     src と dst の文字列が重複している場合、動作は未定義です。
*/
#include <stdio.h>

static size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

 size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
 {
    size_t src_len;
    size_t dst_len;
    size_t i;
    size_t space;
    
    src_len = ft_strlen(src);
    dst_len = ft_strlen(dst);

    if (dstsize <= dst_len) //入れ物が小さすぎる
        return (dstsize + src_len);

    space = dstsize - dst_len - 1; //dst配列の全部 - dst配列のうちの文字列の部分 - (ヌル終端保証用)
    i = 0;
    while (i < space && src[i] != '\0')
    {
        dst[dst_len + i] = src[i]; //dst_lenは文字の個数だが、配列は0番目から始まるのでi = 0で文字列の後の配列を指す
        i++;
    }
    // spaceでヌル終端分の配列を確保しているためsrcの文字列 > dstの配列の数　だったとしても強制的に後ろ一個開けて終わらす
    //→ヌル終端が保証される
    dst[dst_len + i] = '\0';
    return (dst_len + src_len);
 }

 int main(void)
{
	char b1[16] = "ABC";
	char b2[8]  = "ABC";
	char b3[4]  = "ABC";
	size_t r;

	/* 余裕あり */
	r = ft_strlcat(b1, "DEF", sizeof(b1));
	printf("b1='%s' r=%zu\n", b1, r);  // b1="ABCDEF", r=6

	/* 途中までしか入らない（切り詰め）*/
	r = ft_strlcat(b2, "DEFGHI", sizeof(b2));
	printf("b2='%s' r=%zu\n", b2, r);  // b2="ABCDEFG" の途中まで, r=3+6=9 (>=8)

	/* まったく入らない（容量 <= 既存長）*/
	r = ft_strlcat(b3, "DEF", sizeof(b3));
	printf("b3='%s' r=%zu\n", b3, r);  // b3="ABC", r=dstsize(4)+3=7 (>=4)

	/* dstsize が 0（何も書けない） */
	char b4[1] = {0}; /* 中身は無視して OK だが dst は NUL である必要あり */
	r = ft_strlcat(b4, "X", 0);
	printf("r=%zu (b4 untouched)\n", r);       // r = 0 + 1 = 1

	return 0;
}
 