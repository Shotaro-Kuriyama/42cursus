/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:01:21 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 11:18:26 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
STRLCPY(3)                 ライブラリ関数マニュアル       

名前
     strlcpy, strlcat – サイズ制限付き文字列のコピーと連結

ライブラリ
     標準Cライブラリ (libc, -lc)

概要
     #include <string.h>

     size_t
     strlcpy(char * restrict dst, const char * restrict src, size_t dstsize);

     size_t
     strlcat(char * restrict dst, const char * restrict src, size_t dstsize);

説明
     strlcpy() および strlcat() 関数は、snprintf(3) と同じ入力パラメータと出力結果で文字列をコピーおよび連結します。
     これらは、誤用されやすい関数 strncpy(3) および strncat(3) のより安全で一貫性があり、
     エラーの発生しにくい代替手段として設計されています。

 strlcpy() と strlcat() は宛先バッファの全サイズを受け取り、
     余裕があればヌル終端を保証します。 NUL終端用の余地は dstsize に含める必要があることに注意してください。
     また、strlcpy() と strlcat() は真の 『』C『』 文字列のみを操作します。
     これは、strlcpy() では src が NUL 終端され、strlcat() では
      src と dst の両方が NUL 終端されなければならないことを意味します。

     strlcpy() は文字列 src から dstsize - 1 文字までを dst にコピーし、
     dstsize が 0 でない場合に結果を NUL 終端します。

     strlcat() は文字列 src を dst の末尾に追加します。
     追加される文字数は最大で dstsize - strlen(dst) - 1 文字です。 その後、NUL終端処理を行います。ただし、
     dstsize が 0 である場合、または元の dst 文字列が dstsize より長い場合を除きます（
     実際には、これは dstsize が不正であるか、dst が適切な文字列ではないことを意味するため、
     発生すべきではありません）。

     src と dst の文字列が重複している場合、動作は未定義です。

戻り値
     戻り値の型（size_t 対 int）やシグナルハンドラ安全性の議論（snprintf(3) は
     一部のシステムで完全には安全でない）はさておき、以下の2つは同等である：

           n = strlcpy(dst, src, len);
           n = snprintf(dst, len, 「%s」, src);

     snprintf(3)と同様に、strlcpy()およびstrlcat()関数は作成を試みた文字列の
     総長を返す。strlcpy()の場合、これはsrcの長さを意味する。strlcat()の場合、
     これはdstの初期長にsrcの長さを加えた値を意味する。

     戻り値が dstsize 以上であれば、出力文字列は切り詰められています。
この処理は呼び出し元側の責任です。

例
以下のコード断片は単純なケースを示します：

     char *s, *p, buf[BUFSIZ];

           ...

           (void)strlcpy(buf, s, sizeof(buf));
           (void)strlcat(buf, p, sizeof(buf));

     パス名構築時などに切り詰めを検出するには、以下のような処理が考えられる:

           char *dir, *file, pname[MAXPATHLEN];

           ...

           if (strlcpy(pname, dir, sizeof(pname)) >= sizeof(pname))
                   goto toolong;
           if (strlcat(pname, file, sizeof(pname)) >= sizeof(pname))
                   goto toolong;

最初にコピーされた文字数が分かっているため、追加ではなくコピーを使用することで
     処理を少し高速化できます：

           char *dir, *file, pname[MAXPATHLEN];
           size_t n;

           ...

           n = strlcpy(pname, dir, sizeof(pname));
           if (n >= sizeof(pname))
                   goto toolong;
           if (strlcpy(pname + n, file, sizeof(pname) - n) >= sizeof(pname) - n)
                   goto toolong;

     しかし、このような最適化の妥当性には疑問が呈される。なぜなら、
     それらは strlcpy() と strlcat() の本来の目的を完全に損なうからである。
     実際、このマニュアルページの最初のバージョンは誤っていた。

関連項目
     snprintf(3), strncat(3), strncpy(3), wcslcpy(3)

歴史
     strlcpy() および strlcat() 関数は、OpenBSD 2.4 および FreeBSD 3.3 で初めて登場した。

DeepL.com（無料版）で翻訳しました。
*/


#include <stdio.h>

size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;
    size_t src_len;

    src_len = ft_strlen(src);
    if (dstsize == 0)
        return (src_len);

    i = 0;
    while (i < dstsize - 1 && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (src_len);

    /*
    src: "Hello" (長さ5)
    dstsize=4 → コピーは最大3文字まで + '\0'
    dst: "Hel\0"
    返り値: 5   → 5 >= 4 だから「切り詰め発生」が分かる
    */

}

int main(void)
{
	char d1[10]; 
    char d2[10];
	size_t r1;
    size_t r2;

	r1 = ft_strlcpy(d1, "ABCDEF", sizeof(d1));  // 十分に大きい
	printf("d1='%s' r1=%zu\n", d1, r1);        // d1="ABCDEF", r1=6

	r1 = ft_strlcpy(d1, "ABCDE", 4);            // 小さくて切り詰め
	printf("d1='%s' r1=%zu\n", d1, r1);        // d1="ABC", r1=5

	r1 = ft_strlcpy(d1, "", sizeof(d1));        // 空文字
	printf("d1='%s' r1=%zu\n", d1, r1);        // d1="", r1=0

	r1 = ft_strlcpy(d1, "XYZ", 0);              // dstsize=0
	printf("d1(unchanged) r1=%zu\n", r1);      // r1=3, d1 は未定義だが触らない

	/* 余裕があれば本家と一致比較（Linuxはstrlcpyが無いことが多い点に注意） */
	(void)r2; 
    (void)d2;
    
	return 0;
}