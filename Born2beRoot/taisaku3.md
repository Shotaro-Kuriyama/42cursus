1) ARCH
arch=$(uname -a)

何をしてる？
uname -a は カーネル情報 + OS情報 + CPUアーキテクチャ をまとめて表示します。
口頭での説明（このまま言ってOK）
uname -a でOSのカーネル情報とアーキテクチャを取得しています。

2) CPU PHYSICAL（物理CPU数）
cpuf=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)
何をしてる？
/proc/cpuinfo はCPU情報が入ってる特殊ファイルです。
そこから physical id を抜き出して…
・sort -u：重複を消す（同じCPUを何回も数えない）
・wc -l：行数を数える

→ 物理CPU（ソケット）数を推定しています。

口頭での説明
/proc/cpuinfo の physical id を重複なしで数えて、物理CPU数を出しています。
※VMだと physical id が無い環境もあるので、その時は別手段が必要になることがあります（今は動いてるならOK）。

3) CPU VIRTUAL（vCPU数）
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)

何をしてる？

processor : 0 processor : 1 … が vCPU の数だけ並びます。
それを数えることで vCPUの数＝割り当てられたコア数 を取得しています。

口頭での説明
/proc/cpuinfo の processor 行数を数えて vCPU数を出しています。

4) RAM（使用量・合計・％）
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

何をしてる？
free --mega は メモリ状況をMB単位で出します。
・Mem: 行だけを対象にする（awkの条件）
・$2 = total（合計）
・$3 = used（使用）

最後は used/total*100 で使用率。

awkの読み方（ここが説明できると強い）
・$1 == "Mem:" → 「1列目がMem:の行だけ」
・{print $2} → 「2列目を出す」
・{printf("%.2f"), ... } → 「小数点2桁で表示」

口頭での説明
free --mega の Mem 行から total と used を取り、used/total*100 で割合を出しています。


5) DISK（合計・使用・％）
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf ("%.1fGb"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')

何をしてる？

df -m は ディスク使用量をMB単位で表示します。

ここが超重要👇
・grep "/dev/" → 本物のディスク（デバイス）だけ対象にする（tmpfsなど除外）
・grep -v "/boot" → /bootを除外（Born2BeRootの指定に合わせてる）

その上で awk で合計しています。

awkの意味（ディスク合計の取り方）
・$2 = total(MB)
・$3 = used(MB)
disk_t += $2 で全行合計して最後に
・disk_t/1024 = GBっぽい単位にして表示

口頭での説明
df -m の /dev 配下のディスクだけを対象にして、/bootを除外し、totalとusedを合計して使用率を出しています。

※あなたの表示は totalだけGb、usedはMB なので、そこを突っ込まれたら
“合計は見やすくGbに変換してます”
でOKです。

6) CPU LOAD（CPU使用率）
cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpul)
cpu_fin=$(printf "%.1f" $cpu_op)

何をしてる？

vmstat 1 2 は「1秒間隔で2回」情報を取ります。
・1回目：起動直後でズレることが多い
・2回目：安定した値

tail -1 で 2回目だけ取り出すのがポイント。

vmstat の $15 は **CPU idle（何もしない割合 %）**です。
だから
・CPU使用率 = 100 - idle
という計算になります。

口頭での説明
vmstat から idle% を取って、100から引くことでCPU使用率を出しています。


7) LAST BOOT（最終起動時刻）
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')

何をしてる？

who -b は「最後に起動した時刻」を出します。
awkで日時部分だけ取り出して表示しています。

口頭での説明
who -b で最終起動時刻を取得しています。

8) LVM USE（LVMを使ってるか）
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)

何をしてる？
lsblk はブロックデバイス（ディスク構造）を表示します。

その表示の中に "lvm" が含まれる行が1行でもあれば yes、なければ no。
・grep "lvm" でlvm文字列を探す
・wc -l で行数を数える
・-gt 0（0より大きいなら）

口頭での説明
lsblk の出力に lvm が含まれるかで、LVMを使用しているか判定しています。

✅ 改善するともっと安全（評価で強い）

今の方法でも多くはOKですが、「たまたま文字列が出ただけ」で誤判定する可能性もあるので、より正確にするならこれが強いです：

lvmu=$(if lsblk -o TYPE | grep -qx "lvm"; then echo yes; else echo no; fi)


これは TYPE列が “lvm” のものが存在するか で判定するので確実です。



9) TCP CONNECTIONS（ESTABLISHED）
tcpc=$(ss -ta | grep ESTAB | wc -l)

何をしてる？

ss -ta = TCP接続一覧を表示
ESTAB = 接続が確立している状態（ESTABLISHED）

それを数えてTCP接続数を出しています。

口頭での説明
ss -ta でTCP接続を列挙し、ESTABLISHEDだけ数えています。

10) USER LOG（ログインユーザー数）
ulog=$(users | wc -w)

何をしてる？

users はログイン中のユーザー名を空白区切りで出します。
wc -w は単語数を数えるので ログインユーザー数になります。

口頭での説明
users の出力を単語数カウントして、ログインユーザー数を出しています。

※別解で who | wc -l でもOK。
（users は重複することがあるので、評価では who の方が好まれることもあります）

11) NETWORK（IPとMAC）
ip=$(hostname -I | awk '{print $1}')
mac=$(ip link show | awk '/link\/ether/ {print $2; exit}')

IP
hostname -I でIP一覧（複数出ることもある）
awk '{print $1}' で最初のIPだけ表示

口頭：

hostname -I でIPを取得して最初の1つを表示しています。

MAC
ip link show でNIC情報
link/ether の行にMACがある
awkで $2 を取るとMACになる
exit で最初の1個だけ取って終了（余計な行を拾わない工夫）

口頭：
ip link から link/ether のMACアドレスを取得しています。


12) SUDO（sudo実行回数）
cmnd=$(journalctl _COMM=sudo 2>/dev/null | grep COMMAND | wc -l)

何をしてる？

journalctl _COMM=sudo は **sudoコマンドのログ（journal）**を取得します。
その中の COMMAND 行を数えて「sudoで実行した回数」を出しています。

2>/dev/null はエラーを捨てる（権限や設定でjournal読めない時にうるさいから）

口頭での説明

journalctl から sudo のログを取り、COMMAND行数で sudo 実行回数を数えています。

✅ Born2BeRoot的にもっと強くするなら

課題では /var/log/sudo/ にログ保存する要件があるので、そっちを根拠にするとさらに強いです。

例（あなたの環境に合わせて）：

cmnd=$(grep -R "COMMAND" /var/log/sudo/ | wc -l)




最後の wall（全ユーザーに表示）
wall " Architecture: $arch
...
 Sudo: $cmnd cmd"

何をしてる？

wall は ログイン中の全ユーザーの端末にメッセージを表示するコマンドです。
ここで改行付きで各項目を表示しています。

口頭での説明
最後に wall で集計結果を全ユーザーに表示しています。


✅ このコードを「評価で説明する」最短テンプレ

評価者に聞かれたら、1項目につきこれだけ言えばOKです。

ARCH →「uname -a です」
CPU physical →「/proc/cpuinfo の physical id を重複なしで数えました」
vCPU →「processor の行数です」
RAM →「free --mega の Mem 行から total/used を取り割合にしてます」
DISK →「df -m の /dev の合計で、/bootを除外してます」
CPU load →「vmstat の idle% を100から引いて使用率です」
Last boot →「who -b です」
LVM use →「lsblk にlvmがあるかで判定してます」
TCP →「ss -ta のESTABを数えます」
User log →「users の単語数です」
IP/MAC →「hostname -I と ip linkです」
Sudo →「journalctl のsudoログのCOMMAND数です」
