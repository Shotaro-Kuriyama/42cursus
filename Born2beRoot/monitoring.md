STEP Gは**「サーバーを“生き物として監視する習慣”を身につける超重要ステップ」**です。
ここは暗記じゃなくて、

“いまこのサーバーは健康か？”を10分ごとに全員へ通知する仕組み

を作る、と理解すると一気に腑に落ちます。

課題の要求はざっくりこうです：
bashで monitoring.sh を作り、起動時と10分ごとに、wallで全端末へ情報を表示。エラーは見せない。
表示内容は指定の12項目。
さらに評価では「仕組み説明」と「スクリプトを改変せずに止める」ことが求められ、cronが鍵になります。

まず用語を0から
monitoring.sh

monitoring = 監視

.sh = shell script（シェルスクリプト）
つまり
OSに命令を並べて書いた“自動レポート係”。

bash

Linuxで最も標準的なシェル（コマンドを解釈して実行する“司令塔”）。
課題は「bashで作れ」と指定。

wall

Write All のイメージでOK。
ログイン中の全端末にメッセージを一斉表示するコマンド。
→ “全員にアナウンスする館内放送”。

cron

定期実行のスケジューラ。
「10分ごと」や「起動時」に自動でスクリプトを動かすための仕組み。
評価で“スクリプトを改変せずに止める”＝
cronを止める/無効化するのが正解ルート。

STEP Gのゴール（何を作れば合格か）

あなたのスクリプトは常に以下を表示できる必要があります：

OSのアーキテクチャとカーネル

物理CPU数

仮想CPU数（vCPU）

RAM使用量と使用率

ストレージ使用量と使用率

CPU使用率

最終再起動日時

LVMが有効か

TCP接続数

ログイン中ユーザー数

IPv4とMAC

sudoコマンド実行回数

そして
起動時 + 10分ごとに
wallで全端末へ
エラー無しで表示。

ここから“最短だけど理解できる”手順
1) スクリプト置き場を決める

おすすめ：

sudo mkdir -p /usr/local/bin

なぜここ？

/usr/local/bin は
あなたが追加した自作コマンドを置く定番の場所。
OS標準と衝突しにくく、管理もしやすい。

2) monitoring.sh を作る

sudo nano /usr/local/bin/monitoring.sh

nano とは？

ターミナルで使うシンプルなテキストエディタ。

3) まず“完成形サンプル”（その後で1行ずつ解体）

以下は Debianで動く標準コマンド中心の安全構成。
（エラー非表示のため 2>/dev/null を必要に応じて入れています）




**ここから学習向けshファイルの中身**

/proc や基本コマンドから情報を拾って

自分で集計・計算して

最終表示に整える

という流れが見えるから。
これは**“監視って何をどう測って、どう要約するのか”**という本質を学べます。

一方で、私が最初に出した版（lscpu, nproc, df --total など多用）は
“提出事故を減らす”・“短く書く”には強いけど、
仕組みの理解という意味ではブラックボックスが増えます。

だからあなたの目的

「このmonitoring.shに書いてあることがすべて理解して説明できるようにしたい」
には、あなたの修正版が最適です。

学習向けの“本質理解版” monitoring.sh（あなたの修正版ベース）

必要最小の“評価事故回避”だけ入れた形に整えます。



#!/bin/bash

# 1) ARCH
arch=$(uname -a)

# 2) CPU PHYSICAL (unique physical id)
cpuf=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

# 3) CPU VIRTUAL (vCPU)
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)

# 4) RAM
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

# 5) DISK
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf ("%.1fGb"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')

# 6) CPU LOAD
cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpul)
cpu_fin=$(printf "%.1f" $cpu_op)

# 7) LAST BOOT
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')

# 8) LVM USE
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)

# 9) TCP CONNEXIONS
tcpc=$(ss -ta | grep ESTAB | wc -l)

# 10) USER LOG
ulog=$(users | wc -w)

# 11) NETWORK
ip=$(hostname -I | awk '{print $1}')
mac=$(ip link show | awk '/link\/ether/ {print $2; exit}')

# 12) SUDO
cmnd=$(journalctl _COMM=sudo 2>/dev/null | grep COMMAND | wc -l)

wall "	Architecture: $arch
	CPU physical: $cpuf
	vCPU: $cpuv
	Memory Usage: $ram_use/${ram_total}MB ($ram_percent%)
	Disk Usage: $disk_use/${disk_total} ($disk_percent%)
	CPU load: $cpu_fin%
	Last boot: $lb
	LVM use: $lvmu
	Connections TCP: $tcpc ESTABLISHED
	User log: $ulog
	Network: IP $ip ($mac)
	Sudo: $cmnd cmd"



このスクリプトの読み方（“暗記しないための地図”）

monitoring.shは

情報を集める（コマンド）

必要な形に整える（grep/awk/wc/計算）

表示する（wall）

の3段構造です。

ここから“コマンドとオプションを0から全部解体”
シェルの基本記号（最重要）
$(...)

コマンド置換。
中のコマンド結果を“文字列として”取り込む。

例：

arch=$(uname -a)


= uname -a の出力を arch に入れる。


|

パイプ。
左の出力を右の入力へ流す。

例：

grep "physical id" /proc/cpuinfo | sort -u | wc -l

1) ARCH
arch=$(uname -a)

uname

OSやカーネル情報を出す。

-a

all
できるだけ全部出す。

→ これで
OS/カーネル/マシン種別などのまとめ情報が一行で取れる。

2) CPU physical
cpuf=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

ここは“理解の花形”。
/proc/cpuinfo

カーネルが持つCPU情報の生データ。

grep "physical id"

physical id の行だけ抽出。
これは**“どの物理CPU（ソケット）に属するか”の番号**。

sort -u

sort：並べ替え

-u：unique（重複除外）

→ 物理CPU数は
**“physical idの種類数”**なので
重複除外して数えるのが理屈に合う。

wc -l

wc：数える

-l：行数

→ ユニークな physical id の数 = 物理CPU数

3) vCPU
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)


processor は
OSが見ている論理CPU（スレッド単位）の番号行。

VMではこれが割り当てvCPU数に相当。

4) RAM
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

free

メモリの使用状況を表示。

--mega

MB単位で表示。（見やすさ重視）

awk

表（列）から必要な部分を抜き、計算・整形する道具。

'$1 == "Mem:" {print $2}'

$1 = 1列目

$2 = 2列目

行の先頭が Mem: の行だけ対象

Mem: 行は
合計 / 使用 / 空きなどの本体行。

だから

$2 = 合計

$3 = 使用

という読み方。

printf("%.2f")

小数2桁で綺麗に表示。

5) DISK
disk_total
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf ("%.1fGb"), disk_t/1024}')

df

ディスク使用量。

-m

MB単位।

grep "/dev/"

実ディスクっぽい行に限定。

grep -v "/boot"

-v = 除外
boot領域を計算から除く意図。

awk '{disk_t += $2} END {...}'

$2 は通常“容量”列

合計して最後に出す。

disk_t/1024

MB → GB 変換。

disk_use
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} END {print disk_u}')


$3 は通常“使用量”列。

disk_percent
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')


使用合計 ÷ 容量合計 × 100
という“あなたが自分で率を作っている”のが本質。

6) CPU load
cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpul)
cpu_fin=$(printf "%.1f" $cpu_op)

vmstat

CPU/メモリ/IOなどの概要表示。

1 2

1秒間隔で

2回取得

最初の1回はウォームアップ的なので
2回目の値を使うのが定番。

tail -1

最後の1行 = 2回目の結果。

awk '{printf $15}'

vmstat の列のうち
**idle（CPUが暇だった割合）**に該当する列を拾っている想定。

expr 100 - $cpul

expr は整数計算。
100 - idle = 使用率

という理屈。

7) Last boot
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')

who

ログイン情報など。

-b

last boot
最終起動時刻。

8) LVM use
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)

lsblk

ディスク構造の表示。

grep "lvm"

LVMに関連する行があるか確認。

wc -l

行数。

[ ... -gt 0 ]

-gt = greater than
0より大きいか？

→ あれば yes / なければ no。

9) TCP connections
tcpc=$(ss -ta | grep ESTAB | wc -l)

ss

通信状況。

-t

TCP。

-a

全て。

ESTAB

ESTABLISHED（接続確立中）。

10) User log
ulog=$(users | wc -w)

users

ログイン中ユーザー名を並べる。

wc -w

-w = 単語数
= 人数の目安。

11) Network
ip=$(hostname -I | awk '{print $1}')
mac=$(ip link show | awk '/link\/ether/ {print $2; exit}')

hostname -I

IP一覧。

→ 複数出ることがあるので
awk '{print $1}' で“代表1個”に絞る。

ip link show

NIC（ネットワーク機器）一覧。

awk '/link\/ether/ {print $2; exit}'

link/ether 行の

2列目がMAC

exit で最初の1個だけ採用

12) Sudo count
cmnd=$(journalctl _COMM=sudo 2>/dev/null | grep COMMAND | wc -l)

journalctl

systemdのログ閲覧。

_COMM=sudo

sudo由来のログに限定。

2>/dev/null

2> = エラー出力をgrep "/dev/" の意味

grep "/dev/"捨てる
課題の
「エラーを見せるな」対策。

grep COMMAND

sudoログの中で
コマンド実行記録に当たる行だけ拾う。

wc -l

件数。

最後の wall
wall " ... "

wall

ログイン中の全端末へ一斉表示。

monitoring.shの成果物を
“館内放送”として配る役。

じゃあ結局、なぜ書き方が大きく変わるの？

同じゴールでも

“生データから自力で組み立てる派”

あなたの方式

理解が深くなる

“意味がまとまったコマンドを使う派”

私の最初の方式

短く安全に書ける

という違いがあるからです。

あなたの目的が
**“説明できるようになること”**なら
今の修正版が一番筋がいい。

あなたが口頭試問で言えると強い“本質の一言”

monitoring.shは、OSの健康診断を
生データ（/procや基本コマンド）から集めて、集計して、
wallで全員に定期報告する仕組みです。
10分ごとの自動実行はcronが担当します。