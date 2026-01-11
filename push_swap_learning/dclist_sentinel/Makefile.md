1) 使い方（コマンド）

ディレクトリ内で：

make        # ビルド（demo ができる）
./demo      # 実行

make clean  # .o を消す
make fclean # .o と demo を消す
make re     # 全消し→作り直し


2) Makefile超入門：初めて見た人が「一発でわかる」解説
1. ステップ0：Makefileってなに？
・Makefile = “ビルド手順書”（コンパイルのレシピ）
・make というコマンドが Makefile を読んで、必要なコマンドを自動実行します。

つまり、
・Makefile（ファイル）：手順を書く
・make（コマンド）：手順を実行する


ステップ1：Makefileを使うと何が良いの？
✅良いこと1：毎回長いコンパイルコマンドを打たなくていい

本来こう打つところを：

cc -Wall -Wextra -Werror dclist.c main.c -o demo

make だけで済む。

✅良いこと2：「変更したファイルだけ」自動で再コンパイルする

例：
・main.c だけ変更した → main.o だけ作り直す（dclist.oはそのまま）
・だから 速いし、ミスが減る。

✅良いこと3：チーム/課題で手順が統一される

「このプロジェクトのビルド手順は make」で統一できる。

2. ステップ2：MakefileはLinuxと関係ある？Linuxのコマンド？

・make は Linux/Unix文化のビルドツール（GNU make が有名）
・Linuxの“標準コマンド”というより、よく入ってるビルドツールです
・macOSでも普通に使われます

そして重要なポイント：
・Makefileの中身の「コマンド行」は、基本的に シェル（/bin/sh）が実行するコマンド
→ だから rm, cc, echo など Linuxコマンドと直結してます

3. ステップ3：Makefileの基本形（3要素）

Makefileはだいたいこれの繰り返しです：
ターゲット: 依存するもの
	実行するコマンド（Tab）


例：
demo: main.o dclist.o
	cc main.o dclist.o -o demo


意味：
・demo を作るには
・main.o と dclist.o が必要で
・そのために cc ... を実行する

4. ステップ4：「依存」とは何か（ここがキモ）

main.o は main.c から作られるので：
・main.c が更新されたら main.o も作り直すべき
・さらに、dclist.h を変えたら main.c の内容は同じでも、コンパイル結果は変わり得る
→ だから .o は作り直すべき

このために今回こう書いてます：

%.o: %.c dclist.h

5. ステップ5：今回のMakefileを上から読んで理解する
① 変数（見やすくするための“名前”）
PROGRAM_NAME := demo
CC := cc
CFLAGS := -Wall -Wextra -Werror

・「demoって名前で作る」
・「ccを使う」
・「警告系オプションをつける」

② ファイル一覧をまとめる
SRC_FILES := dclist.c main.c
OBJ_FILES := $(SRC_FILES:.c=.o)

$(SRC_FILES:.c=.o) は
・dclist.c main.c
→ dclist.o main.o に変換する書き方です（置換）

③ 最初に動くターゲット
all: demo

make だけ打つと、通常いちばん上のターゲット（ここでは all）が実行されます。
つまり make = make all。

④ 実行ファイルを作る（リンク）
demo: dclist.o main.o
	cc ... -o demo

.o をまとめて実行ファイルにします（リンク）。

⑤ .c → .o を作る（コンパイル）
%.o: %.c dclist.h
	cc ... -c main.c -o main.o


ここで出てくる記号：
・%.o: %.c は “どのファイルにも当てはまるテンプレ”
・$< は「左のルールで最初の依存（= だいたい .c）」
・$@ は「ターゲット名（= 作りたい .o）」

つまり：

$(CC) $(CFLAGS) -c $< -o $@

は、必要に応じて

cc -Wall -Wextra -Werror -c main.c -o main.o


みたいに自動変換されます。

⑥ clean / fclean / re

・clean：途中生成物（.o）を消す
・fclean：.o と実行ファイルも消す
・re：全部消して作り直す

ステップ6：初心者がハマるポイント

Tab必須（コマンド行の先頭）

ターゲット名と同名ファイルがあると挙動が変わることがある
→ それを防ぐのが .PHONY



##　疑問点

1) ar rcs は要らないの？

今回の構成（dclist.c + main.c → 実行ファイル demo）なら不要です。
・ar rcs は **静的ライブラリ（.a）**を作るときのコマンドです。
・例：libft.a を作る、みたいな用途
・今回は .o をまとめて **そのまま実行ファイルを作る（リンクする）**だけなので、
・cc ... dclist.o main.o -o demo
で終わります。

もし「dclist をライブラリ化したい」なら、こういう流れになります：
・ar rcs libdclist.a dclist.o
・cc main.o -Ldclist_dir -ldclist -o demo

でも、学習段階ではまず **“普通に実行ファイルを作る”**でOKです。

2) NAME := demo と NAME = demo は同じ？
見た目は似てるけど、Makefile的には別物です。

:=（シンプル代入 / 即時展開）
・その場で一回だけ展開して固定されます。

=（再帰代入 / 遅延展開）
・使われる時に毎回展開されます。

違いが出る例：

A = hello
B = $(A) world   # (=) なので遅延
C := $(A) world  # (:=) なので即時

A = bye

# このとき
# B は "bye world"
# C は "hello world"


初心者のうちは、:= を使うのが事故りにくくておすすめです。
（= は慣れてくると便利だけど、意図せず値が変わって混乱しやすい）


3) ここを超初歩から説明（%.o: %.c dclist.h と $< $@）

対象の部分：

%.o: %.c dclist.h
	$(CC) $(CFLAGS) -c $< -o $@

ステップ0：まず「コンパイル」って何をしてる？

Cはだいたい2段階です。
1. コンパイル：.c → .o（部品を作る）
2. リンク：複数の .o を合体して実行ファイルを作る

今回だと：
・dclist.c → dclist.o
・main.c → main.o
・dclist.o + main.o → demo

ステップ1：Makefileの基本文法

Makefileはこの形：

ターゲット: 依存ファイル
	コマンド（Tab）

意味は：
・「ターゲットを作るには、依存ファイルが必要」
・「依存ファイルが更新されていたら、下のコマンドを実行して作り直す」

ステップ2：%.o: %.c dclist.h の意味（% は “対応する名前”）
これは **テンプレート（パターンルール）**です。
・%.o … なんでもいいから「〜.o」
・%.c … 同じ名前の「〜.c」

つまりこれを具体化すると：
・main.o: main.c dclist.h
・dclist.o: dclist.c dclist.h

という 2つのルールをまとめて書いてるだけです。

ステップ3：「なぜ dclist.h を依存に入れるの？」
例えば dclist.h の t_node 構造体を変えたら、
main.c のコンパイル結果も変わりますよね？

なので make にこう伝えています：

「dclist.h が変わったら、main.o も dclist.o も作り直してね」

これが依存関係です。

ステップ4：コマンド行の $< と $@ は何？
これは 自動変数です。
・$<：そのルールの 最初の依存ファイル（だいたい .c）
・$@：そのルールの ターゲット名（作りたい .o）

具体例（makeが main.o を作るとき）：
・ターゲット $@ は main.o
・最初の依存 $< は main.c

だから実際に実行されるのは：

cc -Wall -Wextra -Werror -c main.c -o main.o


dclist.o のときは：
cc -Wall -Wextra -Werror -c dclist.c -o dclist.o

ステップ5：-c の意味
-c は「リンクしないで、.o まで作る」オプションです。
・cc -c main.c -o main.o → コンパイルだけ（部品作り）
・cc main.o dclist.o -o demo → こっちはリンク（合体）

4) もう一段だけ大事なこと（実は「これでも完璧ではない」）
今の書き方だと「dclist.h だけ」しか追跡してません。

もし将来、
・utils.h
・dclist_internal.h
みたいなヘッダが増えたら、それも依存に入れるか、もっと賢いやり方（.d自動生成）を使います。

ただ、今は学習用なので この形が一番わかりやすいです。