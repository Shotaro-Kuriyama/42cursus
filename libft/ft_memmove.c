/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:08:05 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 10:51:49 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
NAME
       memmove - メモリ領域のコピー

SYNOPSIS
       #include <string.h>

       void *memmove(void *dest, const void *src, size_t n);

説明
       memmove() 関数は、メモリ領域 src から n バイトをメモリ領域 dest にコピーします。
       メモリ領域は重複している場合があります。コピー処理は、src のバイトがまず
       src や dest と重複しない一時配列にコピーされ、その後その一時配列から dest に
       バイトがコピーされるかのように行われます。

戻り値
       memmove() 関数は dest へのポインタを返す。

属性
       このセクションで使用される用語の説明については attributes(7) を参照のこと。


今回はC言語のmemmove関数の使い方について説明します。

memmove関数は指定したバイト数のメモリをコピー(移動)する関数です。

■書式
#include <string.h>
void *memmove(void *buf1, const void *buf2, size_t n);

第一引数はコピー先のメモリのポインタ
第二引数はコピー元のメモリのポインタ
第三引数はコピーするサイズ

をそれぞれ指定します。
memcpyもメモリをコピーしますが、memmoveもコピーを行います。
違うのはbuf1とbuf2が重なっているときの動作です。
memcpyの場合はそのときの動作は未定義ですが、memmoveを行うと正しくコピーされます。
つまり移動しているように見えます。
*/



#include <stdio.h>
#include <string.h>

void *ft_memmove(void *dst, const void *src, size_t len)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    d = dst;
    s = src;

	//d == sつまり同じアドレスまたは、コピーするサイズ(len)が0のときdst返す
    if (d == s || len == 0)
        return dst;
    
    if (d < s)
    {
        i = 0;
        while (i < len)
        {
            d[i] = s[i];
            i++;
        }
    }
    else
    {
        i = len;
        while (i > 0)
        {
            d[i - 1] = s[i - 1];
            i--;
        }
    }
    return dst;
}


int main(void)
{
    char buf[] = "ABCDDEFG";
    char buf2[] = "ABCDDEFG";
    //bufの先頭から3バイト進めた位置にbufの先頭から3バイトコピー
    memmove(buf+3,buf,0);
    ft_memmove(buf2+3,buf2,0);
    
    //表示
    printf("%s\n",buf);
    printf("%s\n",buf2);
    
    return 0;
}




