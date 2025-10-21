/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:56:23 by skuriyam          #+#    #+#             */
/*   Updated: 2025/10/20 17:28:33 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
NAME
       memset - メモリを定数バイトで埋める

SYNOPSIS(あらすじ)
       #include <string.h>

       void *memset(void *s, int c, size_t n);

DESCRIPTION(説明)
       memset() 関数は、s が指すメモリ領域の最初の n バイトを定数バイト c で埋めます。

戻り値
       memset() 関数は、メモリ領域 s へのポインタを返す。

属性
       このセクションで使用される用語の説明については、attributes(7) を参照のこと。

ヘッダ 	string.h
書式 	void *memset(void *s, int c, size_t n);
引数 	s … メモリ領域のポインタ
c … メモリ領域に設定する文字
n … 文字cを設定するバイト数
戻り値 	sのポインタ
解説 	メモリ領域sの先頭からnバイトを文字cに設定する関数。メモリ領域を'\0'に設定すれば、
		配列の初期化などに使用できる。
*/

/*
void *sについて

void* 型は単にアドレスを格納する型

一般的なポインタ型（int* 型や char* 型など）は単にアドレスを格納するだけでなく、
「どんなデータであるか」が定義されていました。

それに対して void* 型は単にアドレスを格納する型です。「どんなデータであるか」が定義されていません。

「どんなデータであるか」が定義されていないので、void* 型変数にどんな型の変数を指させても
データの不整合が起きず、どんな変数でも指させることができるようになっています。

こういった特性から、void* 型は汎用ポインタと呼ばれることもあります。
(https://daeudaeu.com/c_void/  参照)

 void *（ボイドポインタ）とは？

**「型不明なメモリ領域を指す“汎用ポインタ”」**です。
例：void *s は「どんな型の配列・構造体の先頭でも指せる」。

できること / できないこと

できる：他のポインタ型（int * や char * など）に 自由にキャストして使う／比較する／NULL と比較する

できない：直に参照はできない（*s や s[i] は不可）。必ずキャストしてから：
*/

#include <stdio.h>
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *p;
	unsigned char d;
	size_t i;
	
	p = (unsigned char*)s;
	d = (unsigned char)c;
	
	i = 0;
	while (i < n)
	{
		p[i] = d;
		i++;
	}

	return s;
}
static void hexdump(const unsigned char *p, size_t n) {

	size_t i;
    
	i = 0;
	while(i < n)
	{
        printf("%02X ", p[i]);
		i++;
    }
    printf("\n");
}

int main(void) {
    unsigned char buf[8];

    ft_memset(buf, 1000, sizeof buf);
    hexdump(buf, sizeof buf);   // 00 00 00 00 00 00 00 00

    ft_memset(buf, '1', sizeof buf);
    hexdump(buf, sizeof buf);   // 31 31 31 31 31 31 31 31 (0x31 = 1)

    ft_memset(buf, 500, sizeof buf);
    hexdump(buf, sizeof buf);   // F4 F4 F4 F4 F4 F4 F4 F4

    ft_memset(buf, 0xAB, 5);
    hexdump(buf, sizeof buf);   // AB AB AB AB AB ?? ?? ??
    return 0;
}

/*
%02X は、printf などで数値を**「16進数・2桁ゼロ埋め・大文字」で表示するためのフォーマット指定子**です。
ひとつひとつ分解して説明します👇

%02X の意味
部分	意味
%	ここからフォーマット指定が始まる印
0	足りない桁を「0」で埋める（ゼロパディング）
2	表示幅2桁（例: 1 → 01）
X	16進数で表示（A〜Fを大文字）

*/


/*
例えば、引数int cにunsigned char以上の値が与えられたとします。
その場合unsigned charにキャストしたとしても、
int cに500という値が与えられていたらunsigned charの値を超えてしまうのでは？



いい質問！結論だけ先に👇

memsetの第2引数 int c は、下位1バイトだけが使われます。

具体的には (unsigned char)c に変換された値が、指定サイズ n バイトぶん 同じ値で埋められる だけです。

例：c = 500 のとき

500 は 16進で 0x01F4。

下位1バイトは 0xF4（10進で 244）。

よってメモリは 0xF4 が n回並ぶ 形で埋まります。

// 例えば
unsigned char buf[4];
memset(buf, 500, sizeof(buf));
// 結果: buf = { 0xF4, 0xF4, 0xF4, 0xF4 }


補足ポイント

これは 標準規格どおり の動作で、memsetは「cの下位8ビットを各バイトに書く」と定義されています（実装上も (unsigned char)c が使われる想定）。

エンディアンは無関係：1バイトを書くだけなので、ビッグ/リトルの違いは出ません。

char が符号付き環境でも、メモリの中身は 0xF4。
その後の解釈（signed charとして読むと -12 など）は表示やキャストの問題で、バイト列自体は 0xF4 です。

よくある混同：
memset(arr, 1, n) は 1で埋める（すべて 0x01）であって、「整数1をnバイトぶん書く」ではありません。
また memset(arr, '1', n) だと 文字 '1'（0x31）で埋まるので、全く別物です。
*/

