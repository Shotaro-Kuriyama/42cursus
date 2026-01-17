✅ 評価当日：コマンド暗記用 “完全台本”（Debian）

そのままコピペして練習してOKです。

# 0) OS / hostname
cat /etc/os-release
uname -a
hostnamectl

# 1) user / group
whoami
id
getent group sudo
getent group user42

# 2) UFW (Firewall)
sudo ufw status verbose
sudo ufw status numbered

# 3) SSH
sudo systemctl status ssh
sudo grep -E "Port|PermitRootLogin" /etc/ssh/sshd_config
sudo ss -tulpn | grep sshd

# 4) Password policy
sudo chage -l $USER
sudo grep -E "PASS_MAX_DAYS|PASS_MIN_DAYS|PASS_WARN_AGE" /etc/login.defs
sudo cat /etc/pam.d/common-password

passwdでパスワード変更

# 5) Disk / LVM / Crypto
lsblk -f
df -hT
sudo pvs
sudo vgs
sudo lvs

# 6) cron / monitoring
sudo systemctl status cron
sudo crontab -l
bash /path/to/monitoring.sh
wall "test"



hostnameの変更
sudo hostnamectl set-hostname newname42
reboot

✅ “評価者がよく言う追加実演”も暗記しておく（ほぼ出る）
ユーザー作って、グループに入れてって言われるやつ
sudo adduser testuser
sudo groupadd evaluating
sudo usermod -aG evaluating testuser
id testuser
getent group evaluating

「スクリプト編集せずに止めて」
sudo crontab -e
# → */10 の行を削除

# もしくは強引に止めるなら
sudo systemctl stop cron





# 0) OS / hostname


# 1) user / group


# 2) UFW (Firewall)

# 3) SSH

# 4) Password policy

# 5) Disk / LVM / Crypto

# 6) cron / monitoring




