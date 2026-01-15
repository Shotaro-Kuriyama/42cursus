## ディレクトリ構成について


まず起動したときに最初にいる場所は

/home/skuriyam

1. /（ルート）
全部の起点。ここ直下に「役割別フォルダ」が並ぶ。

2. /home
一般ユーザーの作業場所。
Born2beRootで作る あなたのユーザー（例: shotaro） のホームはここ（/home/shotaro）。

3. /root
root専用のホーム。
普段の作業はここでしない（防御の口頭でも「通常は一般ユーザーで作業、必要時のみsudo」が筋）。

4. /etc（いちばん重要）
設定ファイルの本丸。Born2beRootはほぼここを触ると思ってOK。
・SSH: /etc/ssh/sshd_config
・sudo: /etc/sudoers と /etc/sudoers.d/
・パスワードポリシー周り:
・/etc/login.defs
・/etc/pam.d/common-password（＋必要に応じて pwquality など）
・ホスト名: /etc/hostname、/etc/hosts
・UFW: /etc/ufw/（UFWを使う場合）

5. /var（ログと“変わるデータ”）
ログ確認で必ず見る場所。防御でも強い。
・ログ: /var/log/
・認証系（Debianならよく見る）: /var/log/auth.log
・全般: /var/log/syslog
・sudoログを保存する設定をしたなら、その保存先も多くがここ

6. /usr（インストールされたアプリ・コマンド）
aptで入れた多くのコマンドはここ配下にあるイメージ。
・一般コマンド: /usr/bin
・管理系コマンド: /usr/sbin
※最近のDebianは /bin が /usr/bin へのリンクみたいになってることも多い（見た目が違っても中身の役割は同じ）。

7. /bin と /sbin（最低限のコマンド）
起動直後でも必要な基本コマンド群。
（ただし上の通り、現代は /usr に統合されてリンクになりがち）

8. /boot
カーネルやGRUB関連。Born2beRootのパーティション構成で /boot を別に切る話が出るのはここ。

9. /tmp と /run
・/tmp: 一時ファイル（再起動で消える運用が多い）
・/run: 起動中だけ存在する“実行時情報”（PIDなど）

10. /dev /proc /sys
“ファイルに見えるけど実体はカーネル情報”（超重要概念）
・/dev: デバイス（ディスクがここに見える）
・/proc: プロセス・カーネル情報（仮想）
・/sys: デバイス・ドライバ情報（仮想）

