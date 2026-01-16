# OS / hostname

1. OSの種類、カーネル（Linuxの核）、ホスト名
cat /etc/os-release		 どのOSかを表示する（DebianかRockyかの証拠）
uname -a				　Linuxカーネルの情報（環境の証拠））
hostnamectl				　今のマシン名（hostname）を表示）


2. hostnameの変更
sudo hostnamectl set-hostname newname42
reboot


# user/group

1. ユーザー / グループを確認する
whoami					自分がどのユーザーか
id						自分がどのグループに所属してるか
getent group sudo		グループの中身を見る
getent group user42		グループの中身を見る


2. ユーザー / グループを作る
sudo adduser testuser					新規ユーザー作成

sudo groupadd evaluating				グループを作る	
sudo usermod -aG evaluating testuser	ユーザーを所属させる

getent group evaluating					所属できたか確認	
id testuser								所属できたか確認

# sudo設定

1. sudoが入っているか
sudo -V			sudoが入ってるか
sudo visudo -c	sudoersが壊れてないか（安全確認）


2. sudo設定の場所を見せる

sudo cat /etc/sudoers
sudo cat /etc/sudoers.d/sudo_config 

意味： sudoのルールがどこに書かれてるかを見せる
（追加設定は /etc/sudoers.d/ に入れてることが多い）

3. TTY強制できているか確認

sudo cat /etc/sudoers.d/sudo_config | grep "requiretty"

Defaults requiretty が意味すること（TTY制御）
これは一言でいうと：
TTY（端末）から実行された sudo しか許可しない
requiretty ✅ → TTYが無い sudo を禁止
log_input, log_output ✅ → 入出力ログを取る
iolog_dir="/var/log/sudo" ✅ → 入出力ログの保存先

4. sudoのログが取れてる証拠を見せる

sudo cat /var/log/sudo/sudo_config	これは logfile="..." で指定した 「sudoの実行ログ（イベントログ）」 。


sudo ls -l /var/log/sudo	log_input / log_output の “入出力ログ（録画データ）” が保存されてる証拠 を見せる。
sudo_config → sudoログファイルが存在して書き込まれてる
✅ 00 → I/Oログ保存用ディレクトリが作られてる
✅ seq → I/Oログの管理ファイルがある

sudo grep "COMMAND" /var/log/sudo/sudo_config | wc -l　これは sudoが何回使われたかを数えるためのやり方です。


# パスワードポリシーの設定

1. パスワード有効期限の設定（30日など）

sudo chage -l yourlogin				意味： そのユーザーのパスワード期限を表示する

ここで見たい：
Maximum number of days between password change（最大日数）
Minimum number of days（最短）
warning（日数）

2. 全ユーザーをざっと見る（便利）

sudo chage -l root
sudo chage -l yourlogin


3. システム全体の期限設定が書いてある場所

sudo cat /etc/login.defs | grep -E "PASS_MAX_DAYS|PASS_MIN_DAYS|PASS_WARN_AGE"

4. “強いパスワードルール”が書いてある場所（超重要）

Debianならだいたいここ：
sudo cat /etc/pam.d/common-password

意味： 大文字/小文字/数字、連続文字禁止、長さなどのルールが入ってる場所 (要勉強)


# SSH （ポート4242・root禁止）

1. 	SSHが動いてるか
sudo systemctl status ssh

2. SSH設定を見る（ポートとroot禁止）

sudo grep -E "Port|PermitRootLogin" /etc/ssh/sshd_config

意味：
Port 4242 になってる証拠
PermitRootLogin no になってる証拠

3. 実際に “どのポートが開いてるか” を確認（強い）

sudo ss -tulpn | grep ssh

意味： SSHが本当に4242で待ち受けてるか確認できる


# Firewall（UFW）

1. UFWが有効か

sudo ufw status verbose		(verbose を付けると、表示される情報が増えます。)

意味： firewallがONで、どのルールで許可してるか表示

Status: active		UFWが有効か
Logging: on (low)	ファイアフォールのログを取る
Default: deny (incoming), allow (outgoing), disabled (routed)

deny (incoming)　	外から入ってくる通信は基本すべて拒否
allow (outgoing)	中から外へ出ていく通信は基本すべて許可
disabled (routed)	これは このPCがルーターとして動く場合の通信（中継）をどうするか です。

New profiles: skip	これは「アプリケーションプロファイル（簡易ルール）」の扱いです。


2. 4242を許可する（例）ここは4242になっている前提だが一応

sudo ufw allow 4242/tcp

3. UFWを有効化

sudo ufw enable 


# ディスク（暗号化 + LVM）

1. ディスク構造を一発で見せる
lsblk -f

意味：
crypto_LUKS が出る → 暗号化してる証拠
その下に LVM2_member → 暗号化の中にLVMがある証拠

2. LVMの3点セット（これを言えると強い）
PV（物理ボリューム）
sudo pvs

VG（ボリュームグループ）
sudo vgs

LV（論理ボリューム）
sudo lvs

意味：
PV＝LVMの材料
VG＝プール
LV＝実際に使う論理ディスク（/home とか）

3. どこが何GB使ってるか（マウント状況）

df -hT

-h	サイズをG、M、Kなど単位で表示する
-T は **filesystem Type（ファイルシステムの種類を表示）**です。

df -h だけで良さそうなのに、df -hT を使う理由
・tmpfs
・devtmpfs
これらは ディスクではなくRAM上に作られる一時領域です。

例えば：

tmpfs   484M   0  484M  0% /dev/shm
tmpfs    97M 556K  97M  1% /run

このへんが df -h だけだと
「え？なんか容量いっぱい増えてない？」って混乱しがちですが
-T を付けると tmpfs（メモリ）だから気にしなくていいとすぐ判断できます。

ext4 は一言でいうと、
✅ Linuxで一番よく使われる「ファイルシステム（データの保存ルール）」
です。
そもそも「ファイルシステム」って何？
ディスク（SSD/HDD）って、そのままだと ただの“巨大な空き領域” です。

そこに
・ファイルを置く
・フォルダを作る
・どこに何が入ってるか覚える
・消したり増やしたりする
・ための 管理ルール・仕組み が必要です。

その管理ルールが ファイルシステム。

例（他にも色々あります）：
・ext4（Linuxで定番）
・FAT32（USBでよく見る）
・NTFS（Windows）
・APFS（Mac）

4. 暗号化の状態確認（LUKS）

sudo cryptsetup status sda5_crypt	「暗号化ディスク（LUKS）が今どう動いているか」 を確認するコマンドです。

cryptsetup は Linux の ディスク暗号化（dm-crypt / LUKS） を操作・確認するコマンドです。

# monitoring.sh（wall表示）＋ cron（10分ごと）

1. cronが動いてるか

sudo systemctl status cron		

10分ごと実行の仕組み（cron）が稼働してるか

2. cronに登録されてるか（どこに書いたかで分岐）

(A) rootのcrontabに入れた場合
sudo crontab -l

3. monitoring.shを手動実行して見せる（最強）

bash /path/to/monitoring.sh

/home/skuriyamにある場合
bash monitoring.sh

意味： “本当にこのスクリプトが要件の情報を出せる”証拠

4. スクリプトを編集せず止める（よく聞かれる）

crontabの行を消す（正攻法）
sudo crontab -e

→ */10 * * * * ... を削除




# firewall + ssh
sudo ufw status verbose
sudo systemctl status ssh
sudo grep -E "Port|PermitRootLogin" /etc/ssh/sshd_config
sudo ss -tulpn | grep sshd

# password policy
sudo chage -l yourlogin
sudo grep -E "PASS_MAX_DAYS|PASS_MIN_DAYS|PASS_WARN_AGE" /etc/login.defs
sudo cat /etc/pam.d/common-password

# disk/LVM/crypto
lsblk -f
df -hT
sudo pvs
sudo vgs
sudo lvs

# cron + monitoring
sudo systemctl status cron
sudo crontab -l
bash /path/to/monitoring.sh
wall "monitoring test"


## 超重要：評価で“口で言えると勝ち”な一言テンプレ

最後に、これだけ覚えると強いです。
・lsblk -f →「暗号化(LUKS)→その中にLVMが入ってます」
・pvs/vgs/lvs →「PVが材料、VGがプール、LVが区画です」
・ufw status →「許可してるのは4242だけです」
・ss -tulpn →「実際に4242で待ち受けてます」
・chage -l →「パスワード期限30/最短2/警告7です」
・common-password →「大文字小文字数字、連続文字禁止などはPAMで制御してます」
・sudo crontab -l →「10分ごとにmonitoringを実行してwallで全端末に送ってます」



# A. VM・OSの基本

1. 仮想マシンとは何か／目的は何か（host/guest、仮想ディスク、仮想NICなどの最低限）
仮想マシンとは、仮想化技術を利用して、コンピューター内にもう一つのコンピューターを再現する技術のこと。
仮想化とは、物理的な環境に依存せず、物理マシン（ハードウェア）に含まれるCPU、メモリ、ストレージなどのリソースを論理的に分割する技術です。
今回の仮想マシンは、ハイパーバイザー（例：VirtualBox）がCPU/メモリ/ディスク/ネットワークを仮想的なハードウェアとして提供し、1台の物理PCの中に別のPC環境（ゲストOS）を動かす仕組みです。
目的は、環境を分離して安全に検証できること、構成を再現しやすいこと、失敗しても戻せること（スナップショット）などです。
今回の場合はiMACという物理マシンで、ホストOSはubuntuでその中に仮想環境を作成し、そのゲストOSはdebianということです。

2. DebianかRocky(旧CentOS系)のどちらかを選んだ理由、両者の違い（パッケージ管理・セキュリティ機構など）
基本的にlinuxのOSは2つの流派にわけることができ、それらがdebian系とrad hat系（rockyなど）です。
これらの違いは、Debian系とRHEL系（Rocky）は、パッケージ管理（apt系 / dnf系）や標準のセキュリティ機構（AppArmor / SELinux）、リリース方針が違います。
Debianはコミュニティ主体で安定性重視、Rockyは企業運用を意識したRHEL互換の選択肢です。
今回は学習用途で、情報量が多く扱いやすいDebianを選びました。

3. Debianなら apt と aptitude の違い、AppArmorとは何か（RockyならSELinux/ dnf）
apt
パッケージマネージャーはダウンロードだけでなく、依存関係の処理
このツールを使うには、例えばこのツールも必要だよね？となったときに一緒にダウントードしてくれたり、
あるツールを入れると、他のツールに干渉が起きてしまう可能性があるときに、エラーを起こして教えてくれたりする。

aptitude
aptよりも依存関係の処理が得意（多機能）で「aptだとこれだとだめですよみたいな感じしか送ってくれない」
「aptitudeは選択肢を提示してくれて、例えばバージョンダウンの提案をしてくれたりする」

口頭用
aptはDebianで標準的に使うパッケージ管理のCLI(コマンドラインインターフェース)で、依存関係を解決してインストール/更新/削除ができます。
aptitudeは対話型UIがあり、依存関係の競合が起きたときに代替案（削除/保留/ダウングレードなど）を提示できるのが特徴です。


4. AppArmor
任意アクセス制御だと、権限が強いユーザーが乗っ取られた場合、どうしようもならない。
しかし、強制アクセス制御なら、これだけは譲れない部分を権限に関係なく、「このプロセスだけはアクセスしていいよ」
というよう制限を付与することができる。

AppArmorは強制アクセス制御（MAC）で、特定のプログラムに対して「このファイルしか読めない」「この操作しかできない」という制限をプロファイルでかけます。
そのため、たとえroot権限のプロセスでも、許可されていない動作を防げます。




# UFW・SSH

1. UFWとは？なぜ必要？

口頭用
UFWはUbuntu/Debian系でよく使われるファイアウォール管理ツールで、iptables（またはnftables）のルールを簡単に設定できる仕組みです。
目的は、必要な通信だけ許可して不要なポートを閉じ、外部からの不正アクセスの入口を減らすことです。
Born2BeRootでは SSHの4242/tcpだけ許可して、それ以外は閉じる ように設定しています。
設定は sudo ufw status verbose で確認できます。

1) iptables / nftables って何？

一言でいうと：

✅ Linuxのファイアウォール機能（Netfilter）を操作するための“ルール設定ツール”
です。
もう少し正確に言うと、
・Netfilter（カーネル機能）：実際に通信を止めたり通したりする“本体”
・iptables / nftables（操作ツール）：その本体に「ルール」を入れるための“操作パネル”
という関係です。

2) まず「ファイアウォール」が何をしているか（超シンプル）

Linuxに届く通信は、ざっくり3種類あります：
1. INPUT：外部 → 自分のPC（SSHなど）
2. OUTPUT：自分のPC → 外部（apt updateなど）
3. FORWARD：外部 → 自分を経由して別へ（ルーターみたいな動き）

ファイアウォールはこの通信に対して、
・通す（ACCEPT）
・捨てる（DROP）
・拒否だと返事する（REJECT）
をルールで決めます。

3) iptables とは？

iptables は昔からある「ルールを入れるツール」です。

iptablesの世界観
チェーン（入口の列）に上から順番にルールが並ぶ感じです。
・INPUTチェーン（外から入る通信）
・OUTPUTチェーン（外へ出る通信）
・FORWARDチェーン（中継）

通信が来たら、ルールを上から順番にチェックして
最初に一致したルールが適用されます。
✅ 強いけど、書き方が細かくて長くなりやすい（＝面倒）

4) nftables とは？（iptablesの後継）

nftables は iptables の後継として登場した新しい仕組みです。
nftablesの強み（イメージ）
iptablesは「ルールを1枚1枚ベタベタ貼る」感じだけど、

nftablesは
・ルールの管理がスッキリ
・パフォーマンスも良い
・ルールをまとめやすい（集合・条件が強い）
みたいな “現代版” です。

✅ 今のDebian系だと nftables が標準寄りで使われることが多いです
（※内部的に iptables コマンドが nftables を叩いている場合もあります）

5) じゃあ UFW は何者？

あなたの理解、合ってます。

✅ UFWは「iptables/nftables を簡単に操作するためのラッパー（上位ツール）」
です。

つまり UFW は “ファイアウォールそのもの” ではなく、
・難しいルールを
・人間が覚えやすいコマンドに変換して
・内部で iptables / nftables に反映する
っていう 便利な操作係です。

6) UFWの利点はまさに「簡単に設定できる」こと

あなたの言う通り、UFWの最大の価値はここです。

✅ 利点①：コマンドが直感的（人間向け）
例）
・「4242番を許可したい」
・「外からは基本拒否にしたい」
・「SSHだけ開けたい」
これを UFW だと “日本語に近い命令” でできます。

✅ 利点②：ミスが減る（特に初心者）

iptables/nftablesは自由度が高い分、
・ルールの順番
・例外処理
・既存ルールとの衝突
で事故りやすいです。
UFWはよくある形（deny incoming / allow outgoing）を安全に作れるので、
ミスが減ります。

# SSHとはなにか？なぜ必要か？

SSHは、ネットワーク越しにサーバーへ安全にログインして操作するための仕組みです。通信が暗号化されるので、盗聴や改ざんに強いです。
Born2BeRootでは、外部からの不正アクセスを減らすために デフォルトの22番ではなく4242番を使い、ファイアウォールでも4242/tcpだけを許可しています。
また rootログインを禁止して、まず一般ユーザーでログインし、必要な操作だけsudoで権限昇格する形にしています。
これにより 攻撃されやすいrootを直接狙われるリスクを減らし、操作ログも追えるようになります。

1) 「通信が暗号化されている」ってどういうこと？

✅ 暗号化＝“途中で盗み見られても読めない状態にして送る” こと

たとえばあなたがSSHでコマンドを打つとします：

ls -la

暗号化されてない通信だと、ネットワークの途中で誰かが盗み見たら、

「あ、今 ls -la って打ったな」
「ユーザー名もパスワードも見える」

みたいに 内容がそのまま見えます。

✅ SSHは “鍵” を使って、内容を意味不明な文字列に変える
暗号化されると、通信の中身は例えばこんな感じになります（イメージ）：

9f a2 13 7c 88 1d ...

途中で盗聴されても
・何を打ったか
・パスワード
・表示された内容
全部読めません。

✅ 改ざんにも強い（途中で書き換えられにくい）
暗号化されてると「読むのが難しい」だけじゃなくて、
・途中で書き換えられたら検知できる
・そもそも安全な手順で通信する
みたいな仕組みも一緒に入っています。

2) じゃあ「暗号化されていない通信」ってあるの？

あります。むしろ昔は多かったです。

✅ 暗号化されていない例（昔の代表）

Telnet（SSHの暗号化なし版みたいなやつ）
・HTTP（暗号化なしのWeb）
・FTP（暗号化なしのファイル転送）
・POP3 / SMTP（暗号化なしでメール）
これらは盗聴されると、普通に中身が見えます。

✅ SSH以外にも暗号化された仕組みはある

SSHだけが特別じゃなくて、
・HTTPS（Webの暗号化）
・SFTP（SSH経由のファイル転送）
・VPN（ネット全体を暗号化トンネル化）
なども暗号化です。

3) 「ポート22番に入る」って何？

ここからは “ポート” の理解が肝です。

✅ ポート＝「サーバーの中の“受付窓口番号”」

まず大前提：
あなたが接続しているのは PC（IPアドレス） です。
でもそのPCの中には、
・SSHしたいサービス
・Webサイト（HTTP/HTTPS）
・メール
・DB
みたいに、いろんなサービスが動けます。
そこで必要なのが…
✅ どのサービス宛ての通信なのかを区別する番号
それが ポート番号です。

例：同じIPでもポートで行き先が変わる

あなたが接続する先が同じIPでも、
・IP:22 → SSH（普通
・IP:80 → Web（HTTP）
・IP:443 → Web（HTTPS）
・IP:25 → メール（SMTP）
みたいに 行き先が変わります。

4) 「ポート22番とは何なのか？」
✅ “SSH用の標準ポート” として決められている番号
SSHは昔から ポート22 を使うのが世界標準になってます。
つまり
・「SSHの受付は22番で待ってる」
っていうのが普通のサーバの設定です。



5) じゃあ Born2beRoot で「4242番に変える」って何をしてる？

これはつまり：
✅ SSHの受付を 22番 → 4242番に移動した
という意味です。

サーバ側では
・SSHサーバ（sshd）が 4242番を監視して待つ（listen）
・22番では待たない
という状態にします。

6) 「入る」ってどういう動き？

あなたがSSHする時、内部ではこうなります。
たとえばこう打つ：
ssh -p 4242 user@サーバーIP

すると…
1. あなたのPCが「サーバーのIP」に向けて
2. 「4242番ポート宛て」に通信を送る
3. サーバーがそのポートで待ち受けていれば接続成立
という流れです。

7) “ポートが開いてる/閉じてる” とは？
✅ ポートが開いてる（＝サービスが待ってる）
・サーバが「4242番で待ち受け中」
・外部から来ても通してOK（ファイアウォール許可）
これが揃って初めて繋がる。

✅ ポートが閉じてる（＝繋がらない）

たとえば
・サーバが22番では待ってない（sshdがlistenしてない）
・ファイアウォールがブロックしてる
このどちらかがあると接続できません。

結論
ポート番号とipアドレス（住所）がわかれば接続できる。



# sudoとはなにか？なぜ必要か？

sudoは、一般ユーザーのまま必要な操作だけを一時的に管理者権限で実行できる仕組みです。
常にrootで作業するのは危険なので、通常は一般ユーザーで入り、必要なときだけsudoで権限昇格します。
(実質的に操作する側（人間）が権限を持つものであればパスがわかり、root権限のコマンド(sudo)を実行できる)
また、sudoは 実行履歴がログに残るので、誰が何をしたか追跡できて安全です。
Born2BeRootでは sudoを厳格に設定して、実行ログも保存しています。

# パスワードポリシーを厳しくするメリットとデメリットは？

パスワードポリシーを厳しくすると、短い単純なパスワードや推測されやすいものを避けられるので、辞書攻撃や総当たり攻撃に強くなります。
また有効期限を設けることで、万が一漏洩しても被害期間を短くできます。
一方で厳しすぎると、ユーザーが覚えられず使い回したり、メモしたりして運用上のリスクが増える可能性があるので、強さと運用負荷のバランスが重要です。


# cronとは何ですか？どうやって10分ごとに monitoring.sh を動かしていますか？

cronは、Linuxで決めた時間間隔でコマンドやスクリプトを自動実行する仕組みです。
crontabという設定に「いつ」「何を実行するか」を書くことで、定期実行できます。
Born2BeRootでは、monitoring.sh を 10分ごとに実行して、その結果を wall で全ユーザーに表示するようにしています。
設定は sudo crontab -l で確認できます。

✅ “10分ごと”の書き方（これが核心）

crontabの1行はこういう形です：
分 時 日 月 曜日  実行するコマンド

✅ 10分ごと（最重要）
*/10 * * * * /path/to/monitoring.sh | wall

✅ それぞれの意味（ここを言えると勝ち）
*/10：分 → 10分ごと（0,10,20,30,40,50分）
*（時）：毎時
*（日）：毎日
*（月）：毎月
*（曜日）：毎曜日
→ 結論：いつでもいいから10分おきに実行
