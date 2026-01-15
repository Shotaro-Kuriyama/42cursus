ステップ2-1：パスワードの有効期限の基本ルールを設定

Debian では /etc/login.defs という設定ファイルで、

パスワードの最大有効日数（何日で期限切れにするか）

最低何日空けないと変更できないか

期限切れ前に何日前から警告するか

を決めます。

1) 設定ファイルを開く

sudo nano /etc/login.defs

意味

sudo … この1回だけ管理者権限で実行

nano … シンプルなテキストエディタ

/etc/login.defs … ログイン・パスワード関連のデフォルト設定ファイル

開くといろいろ書いてありますが、その中から次の3行を探してください（ファイルの真ん中あたり）：

PASS_MAX_DAYS   99999
PASS_MIN_DAYS   0
PASS_WARN_AGE   7

これを Born2beRoot 風に、例えばこう直します：

PASS_MAX_DAYS   30    # パスワードの有効期限: 30日
PASS_MIN_DAYS   2     # 変更の間隔: 最低2日あける
PASS_WARN_AGE   7     # 期限切れ7日前から警告

※ # 以降のコメントはあってもなくてもOKですが、書いておくと自分が後で見たときに分かりやすいです。

2) nano の保存・終了

Ctrl + O …… 書き込み（保存）
→ ファイル名が出たらそのまま Enter

Ctrl + X …… エディタを終了



ステップ2-2：今いるユーザーと root にも反映させる

さっきの設定は「これから作るユーザーのデフォルト値」です。
すでに存在している

root

skuriyam

にも適用するために、chage コマンドを使います。


root に適用

sudo chage -M 30 -m 2 -W 7 root

意味

chage …… change age（パスワードの期限を設定）

-M 30 …… Max 30日：有効期限 30日

-m 2 …… Min 2日：変更間隔の最小 2日

-W 7 …… Warn 7日：期限切れ 7日前から警告

root …… 対象ユーザー


skuriyam に適用

sudo chage -M 30 -m 2 -W 7 skuriyam


ステップ2-3：設定が入っているか確認

sudo chage -l root
sudo chage -l skuriyam

意味

-l …… list（そのユーザーのパスワード期限情報を一覧表示）

例として、こんな表示になっていればOKです（数字は多少違っていても大丈夫）：

Last password change                                    : Dec  1, 2025
Password expires                                        : Dec 31, 2025
Password inactive                                       : never
Account expires                                         : never
Minimum number of days between password change          : 2
Maximum number of days between password change          : 30
Number of days of warning before password expires       : 7

ここまでできたら、

「パスワードに有効期限がある」

「短期間に何度も変えられない」

「期限前に警告が出る」

というルールがシステム全体に入りました 💪
