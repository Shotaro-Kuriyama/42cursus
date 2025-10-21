/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:15:21 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 11:15:56 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TOUPPER(3)                          ライブラリ関数マニュアル                          TOUPPER(3)

名前
     toupper, toupper_l – 小文字から大文字への変換

ライブラリ
     標準Cライブラリ (libc, -lc)

概要
     #include <ctype.h>

     int
     toupper(int c);

     #include <ctype.h>
     #include <xlocale.h>

     int
     toupper_l(int c, locale_t loc);

説明
     toupper() 関数は、小文字を対応する大文字に変換します。
     引数は unsigned char として表現可能であるか、EOF の値でなければなりません。

      tupper() 関数は現在のロケールを使用するが、tupper_l() 関数にはロケールを直接渡すことができる。
      詳細は xlocale(3) を参照のこと。

戻り値
     引数が小文字の場合、tupper() 関数は対応する大文字が存在すればそれを返す。存在しない場合は引数を変更せずに返す。

互換性
     大文字セットを持つロケールにおいて、unsigned char 型の範囲外の引数を受け入れるという 4.4BSD 拡張は廃止予定であり、
     将来のリリースではサポートされない可能性がある。代わりに towupper() 関数を使用すべきである。
*/

#include <ctype.h>
#include <stdio.h>

int ft_toupper(int c)
{
    unsigned char uc;

    uc = (unsigned char)c;
    if (uc >= 'a' && uc <= 'z')
       return (uc - ('a' - 'A'));
    return c;
}

int main(void)
{
    unsigned char c = 'b';

    c = (unsigned char)ft_toupper(c);
    printf("%c\n", c);

    char d = 'd';

    printf("%c\n", d);
}