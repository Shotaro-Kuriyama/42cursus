


## .gitignore って何をするもの？

.gitignore は一言でいうと：

「Gitに“新しく追加されそうなファイル”を、最初から無視させるルール」

です。

ポイントは “新しく追加されそうな” であって、重要な知識がここ。

超重要：.gitignore は「すでに追跡されてるファイル」には効かない

a.out が すでに tracked なら、.gitignore に書いても Git は無視しません。

だから「ignoreを書いたのに消えない/追跡が止まらない」が起きます。

これが Git の理屈で、

tracked（過去に git add されてコミットされたことがある）ものは「プロジェクトの一部」

ignore は「プロジェクトの一部にしないものを、うっかり add しない」ための仕組み

という役割分担になってます。


### もしa.outが追跡済みの場合は？

a.out を“今後は追跡しない”にするには

やることは2段階です：
1. 追跡をやめる（index から外す）
2. 今後うっかり入らないように ignore する

1) 追跡をやめる（消すけど手元のファイルは残す）
git rm --cached push_swap/a.out

--cached が超大事
→ 作業フォルダ（実ファイル）は残して、Gitの追跡だけ外します

2) .gitignore に追加

プロジェクト直下の .gitignore に例えば：

# build artifacts
a.out
push_swap/a.out
*.o
*.a

# mac
.DS_Store


#### .gitignore のパターンの基礎（必要な知識だけ）

・a.out：どこかにある a.out を無視（場所によって挙動が変に感じたらパス指定も併用）
・push_swap/a.out：その場所の a.out をピンポイントで無視
・*.o：拡張子 .o を全部無視
・dir/：ディレクトリごと無視
・!例外：一度無視したものを「例外として追跡したい」時に使う（否定パターン）

3) コミット
git add .gitignore
git commit -m "Ignore build artifacts; stop tracking a.out"

これで「今後 a.out はリポジトリに入らない」が完成です。

