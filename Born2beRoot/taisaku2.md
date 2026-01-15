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



A. VM・OSの基本

仮想マシンとは何か／目的は何か（host/guest、仮想ディスク、仮想NICなどの最低限）



DebianかRocky(旧CentOS系)のどちらかを選んだ理由、両者の違い（パッケージ管理・セキュリティ機構など）

Debianなら apt と aptitude の違い、AppArmorとは何か（RockyならSELinux/ dnf）

apt
パッケージマネージャーはダウンロードだけでなく、依存関係の処理
このツールを使うには、例えばこのツールも必要だよね？となったときに一緒にダウントードしてくれたり、
あるツールを入れると、他のツールに干渉が起きてしまう可能性があるときに、エラーを起こして教えてくれたりする。

aptitude
aptよりも依存関係の処理が得意（多機能）で「aptだとこれだとだめですよみたいな感じしか送ってくれない」
「aptitudeは選択肢を提示してくれて、例えばバージョンダウンの提案をしてくれたりする」


AppArmor
任意アクセス制御だと、権限が強いユーザーが乗っ取られた場合、どうしようもならない。
しかし、強制アクセス制御なら、これだけは譲れない部分を権限に関係なく、「このプロセスだけはアクセスしていいよ」
というよう制限を付与することができる。





B. ディスク構成：暗号化 + LVM を説明できる

暗号化されたパーティションをLVMで少なくとも2つ作る（課題要件）

sudo pvs
sudo vgs
sudo lvs

Partition（パーティション）とは？ LVM（PV/VG/LV）の仕組みは？ を口頭で説明

例：lsblk, pvs/vgs/lvs で「今の状態」を見せられる


swao




