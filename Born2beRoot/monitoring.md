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

#!/bin/bash

# 1) Architecture + Kernel
arch=$(uname -a)

# 2) Physical CPU (ソケット数)
cpu_physical=$(lscpu | awk '/Socket\(s\)/{print $2}')

# 3) vCPU
vcpu=$(nproc)

# 4) Memory Usage
mem_info=$(free -m | awk '/Mem:/ {printf "%d/%dMB (%.2f%%)", $3, $2, $3/$2*100}')

# 5) Disk Usage (tmpfs等を除外して合計)
disk_info=$(df -BG --total --exclude-type=tmpfs --exclude-type=devtmpfs \
  | awk '/total/ {printf "%s/%s (%s)", $3, $2, $5}')

# 6) CPU load
# topの出力から user + system をざっくり使用率として計算
cpu_load=$(top -bn1 | awk '/Cpu\(s\)/{gsub(",","."); printf "%.1f%%", $2 + $4}')

# 7) Last boot
last_boot=$(who -b | awk '{print $3 " " $4}')

# 8) LVM use
lvm_use=$(lsblk | grep -q "lvm" && echo "yes" || echo "no")

# 9) TCP Connections (ESTABLISHED)
tcp_conn=$(ss -ta state established | tail -n +2 | wc -l)

# 10) User log
user_log=$(who | wc -l)

# 11) Network (IPv4 + MAC)
ip_addr=$(hostname -I | awk '{print $1}')
mac_addr=$(ip link show | awk '/link\/ether/ {print $2; exit}')

# 12) Sudo commands count
sudo_cmd=$(journalctl _COMM=sudo 2>/dev/null | grep -c "COMMAND")

msg="#Architecture: $arch
#CPU physical : $cpu_physical
#vCPU : $vcpu
#Memory Usage: $mem_info
#Disk Usage: $disk_info
#CPU load: $cpu_load
#Last boot: $last_boot
#LVM use: $lvm_use
#Connections TCP : $tcp_conn ESTABLISHED
#User log: $user_log
#Network: IP $ip_addr ($mac_addr)
#Sudo : $sudo_cmd cmd"

wall "$msg"

この形式は、課題例の出力スタイルにも近く、要求項目を満たす構造です。
4) 1行ずつ“意味の骨組み”を理解

シバン
#!/bin/bash

このファイルはbashで実行してねという宣言。

変数に値を入れる

arch=$(uname -a)

uname = OS情報表示

-a = できるだけ全部表示

$(...) = コマンドの結果を文字として取り込む
→ つまり
OS/カーネル情報を arch という箱に入れる


物理CPUとvCPUの違い

物理CPU = 実際のCPUパッケージ（ソケット）数

vCPU = OSが見えているCPUの数（VMでは割り当て数）

cpu_physical=$(lscpu | awk '/Socket\(s\)/{print $2}')
vcpu=$(nproc)

lscpu = CPU詳細

Socket(s) の数字を抜く

nproc = “使えるCPU数”を返す

メモリ

free -m

free = RAM状況

-m = MB単位

awk で
使用中/合計/割合を整形してる。

ディスク

df -BG --total --exclude-type=tmpfs --exclude-type=devtmpfs

df = ディスク使用量

-B G = GB単位

--total = 合計行を作る

--exclude-type=...
RAM上の疑似ファイルシステムを除外して
**“実ディスクの感覚に近い合計”**にする

CPU使用率

top -bn1



    top = プロセス/CPU状況

    -b = バッチモード（文字出力）

    -n1 = 1回だけ

そこから
user と system を足して
“ざっくりCPU使用率”にしています。


最終再起動

who -b

who = ログイン/システム状態

-b = last boot を表示

LVM use

lsblk | grep -q "lvm"

lsblk = ディスク構造表示

grep -q = 見つかったかどうかだけ判定（表示しない）

TCP接続数

ss -ta state established

ss = 通信状況

-t = TCP

-a = 全部

state established = 接続中のものだけ

ログインユーザー数

who | wc -l

who = ログイン中ユーザー

wc -l = 行数
→ ＝人数の目安

IPv4 & MAC

hostname -I
ip link show

hostname -I = IP一覧

awk '{print $1}' で先頭のIPv4を採用

ip link show で link/ether を拾うとMAC

sudoコマンド回数

journalctl _COMM=sudo | grep -c "COMMAND"

journalctl = systemdログ

_COMM=sudo = sudoのログに絞る

grep -c = 件数カウント

課題の「sudoで実行されたコマンド数」を満たす代表的アプローチ。

5) 実行権限を付ける

sudo chmod +x /usr/local/bin/monitoring.sh

chmod = 権限変更

+x = 実行できるようにする

6) 手動でテスト

sudo /usr/local/bin/monitoring.sh

ここでエラーが出ないことが大事。
課題は “No error must be visible.” と明言。

7) cronで「起動時 + 10分ごと」を作る

sudo crontab -e

rootのcronを編集します。

以下を追加：

@reboot /usr/local/bin/monitoring.sh
*/10 * * * * /usr/local/bin/monitoring.sh

これを分解
@reboot

起動時に1回実行

*/10 * * * *

5つの枠は

分 時 日 月 曜日

*/10 = 10分ごと

あとは全部 * で “常に”

cronが設定できたか確認

sudo crontab -l

-l = list（一覧表示）

評価で必ず聞かれるポイント
「スクリプトを改変せずに止めてください」

答えはこれ。

方法A：cronから該当行を消す/コメントアウト

sudo crontab -e

方法B：cronサービスを止める

（環境により）

sudo systemctl stop cron

**“スクリプトに手を入れずに止める”**という条件を満たせます。
よくある詰まりポイント（先回り）
1) wallが出ない

そもそも wall は
ログイン中の端末がある時に意味が出る
VMで1人だけのときは静かに見えることもある。

2) sudo回数が0のまま

それは普通にあり得る

テストとして

sudo ls
sudo apt update

などを数回実行してから
再度スクリプト実行。

3) DiskやCPUの数値が例と少し違う

課題は**“表示形式の完全一致”ではなく**
**“項目が出ていて理屈が説明できるか”**が本質。
