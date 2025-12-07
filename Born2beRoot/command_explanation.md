# sudo

管理者（root）権限でコマンドを実行するための仕組み。

パッケージ管理（OSの部品の追加・更新）は
システム全体に影響するので 一般ユーザーでは基本できません。

例えるなら
sudo = 管理者カードを使って操作する



# apt

Ubuntu/Debian系の標準パッケージ管理コマンド。

ソフトやライブラリを

探す

入れる

更新する

消す
といった操作をまとめて扱う“窓口”。

例えるなら
apt = 公式のアプリストア兼インストーラ



# update

ここが超重要ポイント。

apt update は

✅ ソフトを更新するコマンドではありません
✅ 「カタログ（一覧表）」を更新するコマンドです

具体的には：

/etc/apt/sources.list や
/etc/apt/sources.list.d/ に書かれている**配布元（リポジトリ）**にアクセスして

「今入手可能なパッケージとその最新版情報」の一覧を

あなたのPC内にダウンロードして更新します

例えるなら
update = 店の最新チラシ/在庫表を取りに行く


# sudo apt install libpam-pwquality

install

パッケージをインストールするサブコマンド。

ここで apt は

カタログから目的のパッケージ情報を参照

必要なものを自動で判断

まとめてダウンロード

システムに配置

必要なら設定ファイルや連携も整える

という手順をやってくれます。

④ libpam-pwquality

これがインストールしたい“部品名”。

libpam-pwquality って何？
ざっくり一言

PAM（認証の仕組み）に「強いパスワード判定」を追加するモジュールです。

PAMとは？

Linuxのログインやパスワード変更などの“認証処理”は

アプリ（例：login, sudo, ssh）

↓

PAM

↓

具体的な認証ルールやモジュール

という形で動くことが多いです。

つまり：

PAM = 認証ルールを差し替え可能にした共通基盤

pwqualityとは？

パスワードの品質（強さ）を評価して、弱いなら拒否する仕組み。

例えば Born2beRoot でよく出てくる：

最低文字数

大文字/小文字/数字/記号の要件

同じ文字の連続制限

辞書的に弱いパスワードの拒否

rootに適用するかどうか

こういうルールをPAM経由で実現するための部品がこれです。

この2つのコマンドがどう“連携”してるか
連携の論理フロー

apt update

OSが「今の最新版の部品一覧」を把握する

apt install libpam-pwquality

そのカタログ情報を使って
最適なバージョンを選び
依存関係も含めてインストール

依存関係って何？

libpam-pwquality は単独では動かず、

関連ライブラリ

PAM本体側との連携部品

などが必要な場合があります。

apt はそこを自動で

「この部品を入れるなら、こっちも必要だよね」

と解決してくれる。

これが

apt の強み = 依存関係の自動解決




apt install libpam-pwquality の意味

あなたがやっているのはこれ：

sudo apt install libpam-pwquality

これが必要な理由

あなたが編集している

/etc/pam.d/common-password

の中に

pam_pwquality.so

という **“パスワード強度チェックの部品”**を書いていますよね。

でも…

超重要な理解

設定ファイルに名前を書いただけでは、その部品は存在しません。

その“部品”本体（モジュール）を
OSにインストールして初めて動く。

それが libpam-pwquality です。


# ここまでを暗記じゃなく理解するための超短いまとめ

sudo：OS全体を触るから管理者権限で実行

apt：Ubuntu/Debianのソフト管理の司令塔

update：ソフトを更新するんじゃなく
“最新の部品カタログ”を更新する

install：カタログを見て
必要な部品と関連部品をまとめて入れる

libpam-pwquality：
PAMに“強いパスワード判定ルール”を追加する部品

# sudo systemctl status ssh


# sudoのインストール

su
→rルートユーザーに切り替える。

sudo reboot
→再起動

sudo -V
→sudoのインストールが成功してる場合、バージョンと構成を表示


# ユーザーの作成

sudo adduser skuriyam

# グループの作成
sudo addgroup user42

確認
getnet group user42

# ユーザーをグループに追加する方法

sudo adduser skuriyam user42

sodo adduser skuriyam sodo

グループメンバーシップの確認
getnet group sudo user42

上のコマンドは、グループsudo、user42のメンバーとしてリストされているユーザーを表示する


#　SSHの確認

ssh service ssh status

Active (running)ならok



# find 