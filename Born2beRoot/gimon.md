

arch=$(uname -a)

解答
unameでOSのカーネルやマシン情報を表示し、-aオプションで詳細を表示します。



cpuf=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

解答
ここでは物理CPUのプロセッサの数を表示します。ここで、物理プロセッサとは
マザーボードに物理的に刺さっているCPU（ソケット）を指します。
一般的なPCでは1つであることが多いですが、環境によっては複数の場合もあります。

物理プロセッサは英語でPhysical CPUといい、この情報は/proc/cpuinfo ファイルに記録されています。

physical id は物理CPU（ソケット）を識別するためのidを表すことが多く、
/proc/cpuinfo には論理CPUごとの情報が並んでいるため、同じ物理CPUに属する場合は
physical id の行が複数回出てきます。

ゆえに、grepでphysical idを探し、
sort -uで重複を含まないようにして、
最後にwc -lでその行数を数えることで
物理CPU（ソケット）の数を求めています。


cpuv=$(grep "processor" /proc/cpuinfo | wc -l)

解答
ここでは仮想CPUのプロセッサの数を表示します。ここで、仮想プロセッサとは
OSから見える論理CPUのことを言います。

物理CPUは基本的に1つであることが多いですが、その物理CPUには、コアやスレッドという概念があります。
例えば、物理CPU一つに対して、コア：4、スレッド：8だったとすると、このとき
物理プロセッサ数：1、仮想プロセッサ数（論理CPU数）：8となります。

これは、物理的な物体としてのCPUは1つであるが、その物理CPUのなかに、
OS上で認識できる8つの論理的なCPUが存在しているということを示します。

仮想プロセッサは英語でVirtual / Logical CPUというので、cpuvというシェル変数に代入しています。
また、物理CPUと違って仮想プロセッサの個数は複数あるため、
ここではsort -uのような重複排除は行わず、
processor行の数をそのまま数えることで論理CPU数を求めています。



ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

解答
ここではメモリ（RAM）の総容量と使用量、そして使用率を表示します。

freeはメモリの使用状況を表示するコマンドなので、
そこから必要な「総メモリ」と「使用中メモリ」と「使用率」の情報を抜き取っていきます。

このスクリプトでは

総メモリ容量 = total

使用中メモリ = used

メモリ使用率 = used/total * 100

という考え方で完結します。

まず、freeのみだと単位が細かく見づらいので、
--megaオプションを使用してメガバイト表記にします。

次に、awkを使って列に対して操作します。
awkは行を条件で絞って、必要な列だけ抜き出すことができ、

$1 = 1列目

$2 = 2列目

$3 = 3列目

と書きます。

awk '$1 == "Mem:" {print $2}' は
1列目が Mem: の行だけに絞り、2列目（total）を出力するという意味です。
したがって ram_total には**総メモリ容量（MB）**が入ります。

awk '$1 == "Mem:" {print $3}' は
同じく Mem: 行の3列目（used）を出力するので、
ram_use には**使用中メモリ（MB）**が入ります。

awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}' は
used/total * 100 を計算し、
小数2桁で表示するために printf を使っています。
その結果 ram_percent には**メモリ使用率（%）**が入ります。


disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf ("%.1fGb"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')


ここではディスクの総容量と使用量と使用率を表示します。
/bootは除外し、それ以外のディスク領域を合計して計算しています。

dfというコマンドはディスクの使用状況を表示するコマンドなので、
そこから必要な「総容量」と「使用量」と「使用率」の情報を上手いこと抜き取っていきます。

このスクリプトでやりたいことはシンプルで、

ディスク総容量（/boot除外）

ディスク使用量（/boot除外）

ディスク使用率（/boot除外） = 使用量/総容量 * 100

という3点を求めることです。

まず共通処理の意味

3つとも共通して、

df -m | grep "/dev/" | grep -v "/boot"


という形になっています。

df -m

df はディスク使用状況を表示

-m はMB単位で表示

これにより、容量や使用量をMBで扱えるようにしています。

df -m の表では基本的に

$1 = Filesystem

$2 = 総容量（MB）

$3 = 使用量（MB）

$4 = 空き容量（MB）

$5 = 使用率（%）

$6 = マウント先

というイメージです。

grep "/dev/"

ここで、Filesystemが/dev/から始まる行だけを対象にします。
つまり、実際のディスク（パーティション）っぽいものだけを拾う意図です。

grep -v "/boot"

-vは否定なので、
/bootが含まれる行を除外します。

1) disk_total の意味
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf ("%.1fGb"), disk_t/1024}')


ここでは /boot を除いたディスク総容量の合計を表示します。

awkの部分は、

{disk_t += $2}
→ 各行の**総容量（$2）**をdisk_tに足し続ける

END { ... }
→ 全行の足し算が終わった最後に1回だけ実行

printf ("%.1fGb"), disk_t/1024
→ df -mはMBなので、合計はMBになる
→ それをGBっぽく見せるために 1024 で割る
→ さらに 小数1桁で表示する

つまり、

/bootを除いた総容量を合計し、GB表示（小数1桁）に整形して出している

ということです。

2) disk_use の意味
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} END {print disk_u}')


ここでは /boot を除いたディスク使用量の合計を表示します。

awkの部分は、

{disk_u += $3}
→ 各行の**使用量（$3）**をdisk_uに足し続ける

END {print disk_u}
→ 最後に合計使用量を表示

disk_useは数値（MB）の合計が取れればOKなので、
ここではprintfではなくprintでそのまま出しています。

3) disk_percent の意味
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')


ここでは /boot を除いた**ディスク使用率（%）**を表示します。

awkの部分は、

{disk_u += $3}
→ 使用量を合計

{disk_t += $2}
→ 総容量を合計

END {printf("%d"), disk_u/disk_t*100}
→ 合計使用量 / 合計容量 * 100 を計算して
→ **整数表示（%d）**にする

つまり、

/bootを除いた“全体としての使用率”を合計値から計算して出している

ということです。

まとめ（この3行の超短い理解）

df -m でMB単位のディスク表

grep "/dev/" で実ディスクっぽい行だけ

grep -v "/boot" で**/bootを除外**

awkで

$2 を合計 → 総容量

$3 を合計 → 使用量

使用量/総容量*100 → 使用率



cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpul)
cpu_fin=$(printf "%.1f" $cpu_op)


解答（あなたフォーマット寄せ完成版）

ここではCPUの使用率を求めて表示するための処理をしています。
やっていることは大きく分けて

CPUのアイドル率（何もしていない割合）を取得する

100から引いてCPU使用率に変換する

表示の形を整える（小数1桁）

という流れです。

1) cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')

ここではCPUのアイドル率を取得しています。

vmstatはCPU・メモリ・I/Oなどの状態を表示するコマンドです。
vmstat 1 2 の意味は

1 = 1秒ごとに

2 = 2回表示する

ということです。

vmstatは最初の1回目が「起動以降の平均」に近い値で、
2回目が「直近1秒の値」に近いサンプルになるため、
このように 1 2 として2回出し、
より“今に近い値”を取る意図があります。

tail -1 は

出力の最後の1行だけを取り出す

という意味なので、
vmstat 1 2 の2回目のサンプル行を取っています。

最後に

awk '{printf $15}'

で15列目を抜き出しています。

vmstatの出力のCPU欄では一般的に

id（idle）= CPUが何もしていない割合

が含まれており、
このスクリプトではその id に該当する列（15列目）を抜き出して

CPUアイドル率（%）

として cpul に代入しています。

つまりここは

「今のCPUの“空いている割合”を取り出している」

ということです。

2) cpu_op=$(expr 100 - $cpul)

ここではCPU使用率を計算しています。

exprは整数の計算を行うコマンドで、

100 - アイドル率

の計算をしています。

CPU使用率は

使用率 = 100 - アイドル率

という関係になるので、
ここで

CPU使用率（整数%）

を求めて cpu_op に代入しています。

3) cpu_fin=$(printf "%.1f" $cpu_op)

ここでは表示用に値の形式を整えています。

printf "%.1f" は

小数1桁で表示する

という指定です。

そのため cpu_op を

小数1桁の見た目に整えたCPU使用率

として cpu_fin に入れています。

まとめ（この3行の超短い理解）

vmstat 1 2 で今に近いCPU情報を取る

tail -1 で最新の1行を選ぶ

awk '{printf $15}' でアイドル率を抜く

100 - idle で使用率に変換

printf "%.1f" で表示を整える





lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')

解答（あなたフォーマット寄せ完成版）

ここでは**最終起動時刻（最後にOSが起動した日時）**を表示します。

whoは現在ログインしているユーザー情報などを表示するコマンドです。
-bオプションをつけると、システムが最後に起動した時刻を表示します。

その出力はだいたい

system boot YYYY-MM-DD HH:MM

のような形になります。

次に awk を使って必要な列を抜き出しています。

awk '$1 == "system" {print $3 " " $4}'


これは

1列目が system の行を対象にして

3列目と4列目を
"日付 空白 時刻" の形で出力する

という意味です。

つまりこの1行全体は

who -bで最終起動情報を取り、
日付と時刻だけを抜き出して lb に代入している

ということです


lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)



解答（あなたフォーマット寄せ完成版）

ここではLVMを使用しているかどうかを yes/no で表示します。

lsblk は

ディスクやパーティション、論理ボリュームなどの構成を
ツリー形式で表示するコマンドです。

その出力の中に lvm という文字列が含まれていれば、
LVM構成が存在する可能性が高いと判断できます。

そのため

lsblk | grep "lvm" | wc -l


で

lsblk の結果から

lvm を含む行を検索し

その行数を数えています。

次に

if [ ... -gt 0 ]; then echo yes; else echo no; fi


で

行数が 0より大きいなら yes

そうでなければ no

を出力します。

つまりこの1行全体は

lsblk の情報を使って
LVMが使われているかを簡易判定し、
yes/noにして lvmu に代入している

という意味です。


tcpc=$(ss -ta | grep ESTAB | wc -l)


解答（あなたフォーマット寄せ完成版）

ここでは**TCPの接続数（確立済みの接続）**を数えて表示します。

ss は

ソケット（通信状態）を表示するコマンドです。

-t は

TCP の表示

-a は

すべての状態のソケットを表示

という意味です。

つまり

ss -ta


で TCPに関するソケット一覧を表示します。

そこから

grep ESTAB


で

ESTAB（Established）
= 接続が確立して通信中の状態

の行だけを抜き出します。

最後に

wc -l


で行数を数えるので、

現在確立しているTCP接続の数

を tcpc に代入していることになります。



ulog=$(users | wc -w)

解答（あなたフォーマット寄せ完成版）

ここでは現在ログインしているユーザー数を表示します。

users は

ログイン中のユーザー名を
1行に並べて表示するコマンドです。

例：

user1 user2 user1


のように出ることもあります。

次に

wc -w


は

**単語数（words）**を数えます。

つまりこの1行全体は

users の出力に含まれるユーザー名の数を
単語として数え、
ログインユーザー数の目安を ulog に代入している

という意味です。



ip=$(hostname -I | awk '{print $1}')
mac=$(ip link show | awk '/link\/ether/ {print $2; exit}')


解答（あなたフォーマット寄せ完成版）

ここではネットワーク情報としてIPアドレスとMACアドレスを取得して表示するための処理をしています。

やっていることは

IPアドレスを取得する

MACアドレスを取得する

の2つです。

1) ip=$(hostname -I | awk '{print $1}')

ここではIPアドレスを取得しています。

hostname はホスト名に関する情報を表示するコマンドで、
-I オプションをつけると

このマシンに割り当てられているIPアドレスを空白区切りで表示

します。

環境によってはIPが複数表示されることがあるため、
そのままだと値が長くなったり出力が不安定になったりします。

そこで

awk '{print $1}'


を使い、

1列目（最初に出てきたIP）だけを抜き出して

ip というシェル変数に代入しています。

つまりこの1行は

複数IPがある可能性を考慮しつつ、
最初のIPアドレスを1つだけ取得する

という意図です。


2) mac=$(ip link show | awk '/link\/ether/ {print $2; exit}')

ここではMACアドレスを取得しています。

ip link show は

ネットワークインターフェース（NIC）の情報を表示するコマンドです。

その出力の中には

link/ether xx:xx:xx:xx:xx:xx

のような行が出ることがあり、
ここにMACアドレスが含まれています。

そこで

awk '/link\/ether/ {print $2; exit}'


を使います。

これは

link/ether を含む行を見つけたら

その 2列目（MACアドレス）を表示して

exit で そこで処理を終了

という意味です。

exit を入れている理由は

インターフェースが複数ある場合でも
最初に見つかったMACだけを1つ取得して安定させる

ためです。

つまりこの1行は

ip link show から
MACアドレスの行だけを探し、
最初の1つを抜き出して代入している

ということです。


cmnd=$(journalctl _COMM=sudo 2>/dev/null | grep COMMAND | wc -l)


解答（追加解説・あなたフォーマット寄せ）

ここではsudoが実行された回数の目安を表示します。
Born2beRootのmonitoring.shの文脈では

sudoを使ったコマンド実行がどれくらい行われたか

を数値として出すことが目的です。

まず全体の形
cmnd=$( ... )


これは

$(...) の中のコマンドを実行して

その出力結果を

cmnd というシェル変数に代入する

という意味です。

journalctl _COMM=sudo

journalctl は

systemdのログ（ジャーナル）を表示するコマンドです。

ここで

_COMM=sudo


という書き方は

journalctl に対する**検索条件（フィルタ）**です。

つまり

「コマンド名が sudo のログだけを表示してね」

という意味で、
journalctl_COMM=sudo のような別コマンドが存在するわけではありません。

_COMM は

そのログを出したプロセスのコマンド名を表すフィールドの一つであり、
そこが sudo のログだけに絞って表示しています。

2>/dev/null

これは

**標準エラー出力（2）**を

/dev/null に捨てる

という意味です。

/dev/null は

何を書き込んでも消えるゴミ箱のような特殊ファイルです。

したがって

2>/dev/null


は

journalctl実行時に環境によって出る警告やエラー表示を
画面やパイプ処理に混ぜないようにする

という意図です。

cat /dev/null で何も出ないのは正常で、
中身が空であることが仕様です。

| grep COMMAND

| はパイプで、

左の出力を右の入力に渡します。

ここでは

sudo関連ログの中から
COMMAND を含む行だけを抜き出します。

sudoのログには

実行されたコマンドが
COMMAND=... の形で記録されることがあるため、

「実際にsudoでコマンドが実行された記録」を
できるだけ狙って抽出する

という意味になります。

| wc -l

wc -l は

行数を数えるコマンドです。

つまり

COMMAND を含むログ行が何行あるか
＝ sudoによるコマンド実行回数の目安

を計算しています。



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


解答（あなたフォーマット寄せ完成版）

ここでは今まで取得してきた監視情報を、見やすい形でまとめて表示します。
具体的には wall コマンドを使い、

ログイン中の全ユーザーの端末にメッセージを一斉送信

しています。

Born2beRootのmonitoring.shでは
10分ごとにこの情報を自動で通知するのが目的なので、
この出力パートが“完成形の表示”になります。

wall とは何か

wall は

write all の略で、

全ユーザーにメッセージを送るコマンドです。

つまり

wall "メッセージ"


と書くと、

ダブルクォート内の文章が
ログインユーザーの端末に表示される

という仕組みです。

ダブルクォート "..." の意味

ここでダブルクォートを使う理由は2つあります。

1) 変数展開を有効にする

ダブルクォート内では

$arch, $cpuf, $ram_use などの変数が
実際の値に置き換わって表示されます。

もしシングルクォートにすると

wall 'Architecture: $arch'


のように
変数が展開されず文字のまま表示されるので目的に合いません。

2) 改行をそのまま表示できる

この書き方では、ダブルクォートの中に

実際の改行を含めています。

そのため

1行ずつ整った監視表示になる

というメリットがあります。

先頭のインデント（タブ）

あなたの文字列は

"	Architecture: ...


のように
各行の先頭にタブが入っています。

これは

見た目を揃えて読みやすくするため

で、機能的な意味はありません。

${ram_total} のような {} の意味

例えば

$ram_use/${ram_total}MB


の ${} は、

変数名の境界を明確にする

読みやすくする

という目的です。

$ram_totalMB のように誤解される可能性を避けるため、
こう書くのはとても良い習慣です。

各行が何を表示しているか

ここからは1行ずつ意味を確認します。

Architecture: $arch

uname -a で取得した
OS/カーネル/マシン情報の要約

CPU physical: $cpuf

physical id を元に数えた
物理CPU（ソケット）の数

vCPU: $cpuv

processor 行を数えた
論理CPU数（OSから見えるCPU数）

Memory Usage: $ram_use/${ram_total}MB ($ram_percent%)

例の形としては
使用量/総容量 (使用率%)

Disk Usage: $disk_use/${disk_total} ($disk_percent%)

/boot を除いた
使用量/総容量 (使用率%)

CPU load: $cpu_fin%

vmstat のアイドル率から計算した
CPU使用率

Last boot: $lb

who -b から取り出した
最終起動時刻

LVM use: $lvmu

lsblk に lvm があるかで判定した
LVM使用の有無（yes/no）

Connections TCP: $tcpc ESTABLISHED

ss -ta の ESTAB を数えた
確立済みTCP接続数

User log: $ulog

users | wc -w による
ログイン中ユーザー数の目安

Network: IP $ip ($mac)

hostname -I の最初のIP

ip link show から拾ったMAC

をまとめて表示

Sudo: $cmnd cmd

journalctl _COMM=sudo のログから
COMMAND 行を数えた
sudoで実行されたコマンド回数の目安

まとめ（この wall ブロックの役割）

この部分は

これまで作った変数を
“人間が一瞬で読める監視レポート”として整形し、
wallで全ユーザーに一斉表示する

という最終仕上げです。