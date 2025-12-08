
# 1

**monitoring.mdについて**

問１

cpuf=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

というコマンドについて、この1行は「物理CPU(ソケット)の数を数えてcpufという変数に入れる」という内容
を表しているが、なぜそう言えるのか説明しなさい。
またその際に、環境変数ではなくシェル変数に入れる意味についても言及しなさい。



まず、コマンドについて分解

パイプ（|）とは左の出力を右の入力へ渡すということなので、
このコマンドは３段階で処理される。

1, grep "physical id" /proc/cpuinfo

2, sort -u

3, wc -l

1) grep "physical id" /proc/cpuinfo
grep の役割

grep は指定したパターン（文字列/正規表現）を含む行を探して表示します。

は

/proc/cpuinfo の中から
"physical id" を含む行だけ抜き出す

という意味。

なんで " " で囲むの？

physical id はスペースを含むので、
1つの検索パターンとして扱うために引用符で囲むのが安全です。



2) sort -u

sort は行を並び替えます。

-u は unique（重複削除）。

つまり

sort -u

は

同じ行が何度出てきても1回にまとめる

という意味です。

sort -u はざっくり

sort | uniq

を1コマンドでやっているイメージ。
3) wc -l

wc は文字数/単語数/行数を数えるコマンド。

-l は line（行数）。

wc -l

は

    行数を数える

これで何が数えられるの？

/proc/cpuinfo には CPU 情報がずらっと書かれていて、
論理CPU（スレッド）ごとに同じような情報が繰り返し出てきます。

その中に：

physical id : 0
physical id : 0
physical id : 1
physical id : 1
...


みたいに書かれていることがあり、

physical id は **「物理CPUソケットの番号」**を表すことが多いです（x86系など）。

だから、

grep で physical id の行を抜き出し

sort -u で重複を消し

wc -l で残った行数を数える

→ 物理CPU（ソケット）の数を推定しているわけです。

補足
ソケットの数

CPUの構成で必要なパーツのひとつである「ソケット」は、CPUをサーバー内にどれだけ搭載できるかを示しています。

 

物理CPUにおいてのソケットは、マザーボードにコアを装着するために必要な部品で、板状でピンを差し込み固定する仕様となっています。

 

基本的に、CPUはひとつしか搭載できないものの、高性能なモデルであれば、ふたつ以上のCPUを搭載できる場合があるため、ソケットは重要です。


超直感的なイメージ

/proc/cpuinfo は名簿

physical id は**「所属クラス」**

grep は**“所属クラス”行だけ抜き出す**

sort -u は同じクラス名を1回にまとめる

wc -l はクラス数を数える

→ クラスの数 = 物理CPUの数



# 2

ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')


ざっくり言うとこの3行は、

総RAM（MB）

使用中RAM（MB）

使用率（%）

を取り出して変数に入れるための処理です。

まず共通部分
ram_total=$( ... ) など

これはコマンド置換です。

$(...) の中を実行して

その出力を変数に代入

なので ram_total / ram_use / ram_percent は
シェル変数として値を持ちます（環境変数ではない）。

free --mega とは？

free はメモリ状況を見るコマンド。

--mega は

MB単位で表示

にするオプションです。

実行するとだいたいこんな感じの行が出ます：

              total        used        free      shared  buff/cache   available
Mem:           7972        1234        4567         123        2170        6345
Swap:          2047           0        2047

| パイプ
free --mega | awk ...


は

free の出力を awk に渡して解析する

という意味。

awk の基本（今回使ってる範囲）

awk は行を条件で絞って、必要な列だけ抜き出すのが得意です。

$1 = 1列目

$2 = 2列目

$3 = 3列目

...

1行ずつ解説
① 総RAM
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')


'$1 == "Mem:"'
→ 1列目が Mem: の行だけ対象にする

{print $2}
→ 2列目を出力

つまり

Mem: 行の total 列
→ 総RAM(MB)

② 使用中RAM
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')


同じく

Mem: 行だけ

3列目を取り出す

つまり

Mem: 行の used 列
→ 使用中RAM(MB)

③ 使用率（%）
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')


やりたいことは

使用率 = used / total * 100

で、小数点2桁で表示すること。

ただしこの printf の書き方はほぼ確実にミスです。

正しい形（たぶん意図はこれ）
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f", $3/$2*100)}')


printf("%.2f", 値)
→ 小数点2桁で“改行なし”表示

これで

RAM使用率(%) が入ります。

もう少し親切な改善版

printf は改行が入らないので、
後で扱いやすくするなら改行を入れるのもアリです。

ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f\n", $3/$2*100)}')

3行を1回の free で済ませる書き方（効率＆読みやすさUP）

同じ free を3回呼んでるので、1回にまとめるとスッキリします：

read -r ram_total ram_use ram_percent << EOF
$(free --mega | awk '$1=="Mem:" {printf "%s %s %.2f", $2, $3, $3/$2*100}')
EOF


※これは“理解が進んでからでOK”。
今の段階では元の書き方も十分わかりやすいです。

まとめ

free --mega
→ メモリ情報を MB で表示

awk '$1 == "Mem:" { ... }'
→ Mem: 行だけを処理

$2
→ total

$3
→ used

計算
→ $3/$2*100


**awkの print と printf の違い（超基礎）**
print

指定した値をそのまま表示するための命令。

最後に自動で改行が入る。

値を複数指定するとスペース区切り（正確には OFS）で出る。

echo "Mem: 8000 2000" | awk '{print $2}'

→ 8000（最後に改行あり）

echo "A B C" | awk '{print $1, $3}'


→ A C（自動で間にスペース＋改行）

イメージ：

「とりあえず値を取り出して見せたい」時の最短ルート

printf

C言語のprintfとほぼ同じ。

フォーマット（表示形式）を指定できる。

改行は自動で入らない（必要なら \n を書く）

例：

echo "ratio 25.12345" | awk '{printf("%.2f", $2)}'


→ 25.12（改行なし）

echo "ratio 25.12345" | awk '{printf("%.2f\n", $2)}'


→ 25.12（改行あり）

イメージ：

「小数点○桁にしたい」「%やGbを付けたい」など
“見た目を整えたい” 時に使う

なぜこのRAMの3行で使い分けるの？
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

ram_total / ram_use が print な理由

$2（total）や $3（used）はほぼ整数でOK

そのまま値が欲しいだけ

だから print が自然。

ram_percent が printf な理由

used/total*100 は小数になる

しかも監視表示では
小数点2桁など“見やすい形”に整えることが大事

なので printf が選ばれる。



# 3

1) df -m

df はディスク使用状況を表示。

-m は MB単位で表示。

出力のイメージ：

Filesystem     1M-blocks  Used Available Use% Mounted on
/dev/sda2          30000  12000     18000  40% /
/dev/sda1            500    100       400  20% /boot
...

2) grep "/dev/"

df結果から

実ディスクっぽい行だけを残す

ためのフィルタ。

3) grep -v "/boot"

-v は否定。

/boot を含む行は除外

つまり

/boot パーティションを合計対象から外す

4) awk '{disk_t += $2} END { ... }'
{disk_t += $2}

各行ごとに

2列目（total容量）を足し算していく

disk_t は合計用の変数。

END { ... }

awkの最後の後処理。

全行を読み終えた後に1回だけ実行

printf の意図

「MB合計をGBに直して、1桁小数で “Gb” を付けて表示」

ただしここも printf の書き方が少し崩れているので
意図通りにするならこうが安全：

disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf("%.1fGb", disk_t/1024)}')

この disk_total 全体がやっていること

df -m でMB単位のディスク一覧を取る

/dev/ の行だけに絞る

/boot を除外する

2列目（total）を全部足す

合計MBを ÷1024 してGB換算

%.1f で小数1桁に整えて Gb を付ける

その結果を disk_total に代入