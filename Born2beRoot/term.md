# そもそもPAMって何だっけ？

超ざっくり：

PAM = パスワード変更やログインのルールを決める仕組み

その中心が
/etc/pam.d/ の設定ファイル


common-* って何？

この4つは「共通ルールの土台」です：

common-auth
ログインなどの認証ルール

common-account
アカウントの条件（有効期限など）

common-password
パスワード変更ルール（あなたが今いじってる最重要）

common-session
ログイン後のセッションルール

# そもそも「パスワード変更」ってOS的に何？

Linuxでは、パスワードの情報は主に

/etc/shadow

に保存されています（暗号化された形）。

でもこのファイルは

管理者しか直接いじれない

重要ファイルです。

だから

一般ユーザーが自分のパスワードを変えるときは
**“安全な正式ルート”**として passwd を使う

rootのパスワードを変えるときは
管理者権限が必要になる

という仕組みです。

passwd が意味していること（理解の核）
✅ 何が起きてる？

passwd を実行すると：

「本人確認」
ふつうは “現在のパスワード” を聞かれる
（本人が勝手に変えられないようにする）

「新パスワードの強度チェック」
ここであなたが設定した
/etc/pam.d/common-password のルールが動く

「/etc/shadow の更新」

sudo passwd root の意味（理解の核）
✅ なんで sudo が必要？

rootのパスワードを変えるのは

システムの最重要アカウントを変更する作業

だから、一般ユーザーの権限ではできません。

そこで

sudo（一時的に管理者権限を借りる）

を付けて実行します。

ここで超大事な勘違いポイント
❗ sudo が聞いてくるのは基本「自分のパスワード」

あなたのスクショにも出てましたよね：

[sudo] password for skuriyam:

これは

「rootのパスワードを聞いてる」んじゃなくて

「あなたが本当にsudoを使える本人か」を確認してる

という意味。


# まず結論：chageは何をする？

chage = ユーザーごとの“パスワードの寿命ルール”を設定/確認するコマンド

パスワードのルールには2種類あります：

強さ（質）
→ 文字数・英数記号など
→ libpam-pwquality や PAM設定

期限・頻度（寿命）
→ 何日で変更が必要？
→ 何日以内に再変更禁止？
→ 期限前に何日前から警告？
→ これが chage

あなたのコマンドの意味（超短く）

sudo chage -l skuriyam

→ skuriyam のパスワード期限ルールを表示（確認）

sudo chage -m 2 skuriyam

→ skuriyam はパスワード変更後、最低2日は再変更できない

Born2beRootでよく使う “3点セット”

（課題要件で数字が指定されてることが多い）

1) 最小変更間隔（すぐ戻すズル防止）

sudo chage -m 2 USER

意味：
変更してから最低2日は、次の変更ができない

2) 最大使用日数（期限）

sudo chage -M 30 USER

意味：
最大30日までしか同じパスワードを使えない

3) 期限前の警告

sudo chage -W 7 USER

意味：
期限の7日前から警告が出る

“確認”はこれ1本でOK

sudo chage -l USER

ここに表示される英語は、ざっくりこう覚えれば十分：

Minimum → -m

Maximum → -M

Warning → -W

Last password change → 最後に変えた日

1分で理解するイメージ

パスワードの寿命ルールは

すぐ変え直せない（-m）

長く使いすぎ禁止（-M）

期限前に注意（-W）

この3つの柱。


login.defs との関係（超初心者向け）
重要ポイントだけ

/etc/login.defs は“初期設定のテンプレ”

新しく作るユーザーのデフォルト値に影響する

つまり：

login.defs = 全体の初期ルール

chage = 個別ユーザーの上書きルール

迷ったら
課題は“ユーザーごとにchageで設定して確認”
が一番安全。


どこに保存されてるの？

chage で設定した内容は裏側で

/etc/shadow

に記録されます。

だから chage は
“/etc/shadow を安全に操作する正規コマンド”
だと思えばOK。

超初心者向けまとめ（暗記用じゃなく理解用）

pwquality/PAM
→ パスワードの強さ（質）

chage
→ パスワードの期限・頻度（寿命）

-m
→ 早すぎる再変更禁止

-M
→ 使い回し期間の上限

-W
→ 期限前アラート

-l
→ 現状確認



# id の出力は Linuxの「権限のしくみ」そのものを短く見せてくれる超重要コマンド。


id testuser
uid=1001(testuser) gid=1001(testuser) groups=1001(testuser),100(users),1002(testgroup)

意味はこう：

testuser というユーザーの

ユーザーID(UID) は 1001

主グループID(GID) は 1001

所属グループ は

1001(testuser)

100(users)

1002(testgroup)



用語を1つずつ（超やさしく）
1) UID（ユーザーID）

ユーザーの“番号つき身分証”

OSは名前より番号で管理する

だから
testuser という名前より、
UID=1001 が本体の識別子。

名前は変えられても、番号で一意に管理できるから安全で確実。

2) GID（グループID）

グループの“番号つき身分証”

これもOSは番号で管理する

3) 主グループ（primary group）

gid=1001(testuser)

これは

testuser の“基本所属チーム”が testuser というグループ

という意味。

Linuxではよく

ユーザーを作ると、同名のグループも自動で作る

設定になってます（Debian系で典型）。

4) 補助グループ（secondary/supplementary groups）

groups= ...,100(users),1002(testgroup)

これは

「基本チーム」以外に参加している“追加チーム”

の一覧。


ここが本質：なぜグループがあるの？
Linuxの権限は基本この3種類

ファイルを ls -l するとこういうやつ：

-rw-r----- 1 owner  group  ...

権限は

owner（所有者）

group（グループ）

others（その他の人）

の3枠で決まります。


**つまり「グループに入れる理由」はこれ**

“個人単位”と“チーム単位”の中間ルールを作るため。

たとえば現実の例え

owner：自分専用の鍵

group：同じチームだけが使える鍵

others：誰でも使える鍵

じゃあこの出力の各グループにはどんな意味がある？

1001(testuser),100(users),1002(testgroup)

A) 1001(testuser)

主グループ

testuser が作ったファイルは基本ここに属する

B) 100(users)

Debianなどでよくある標準的な一般ユーザー向けグループ

ディストリや設定次第で意味合いは少し違うけど

ざっくり言うと

「一般ユーザーとしての共通チーム」

みたいな位置づけ。

C) 1002(testgroup)

あなたが作った（または課題で作る）カスタムグループ

これは

「このグループに入っている人だけOK」
を試すために作ることが多い。

理屈が腹落ちするミニ実験
1) testgroup 専用フォルダを作る

sudo mkdir /srv/testshare
sudo chown root:testgroup /srv/testshare
sudo chmod 770 /srv/testshare

意味

所有者：root

グループ：testgroup

権限：770

つまり

root と testgroupメンバーだけが使える場所


2) testuserが入ってるならアクセスできる

su - testuser
cd /srv/testshare
touch ok.txt


3) 入ってないユーザーは弾かれる

もし別ユーザーが testgroup に入ってなければ

cd /srv/testshare

で Permission denied になる。


よくある操作コマンド（意味付き）
グループに追加

sudo usermod -aG testgroup testuser

usermod：ユーザー設定変更

-G：追加したい補助グループ指定

-a：“追加”モード
※これが超重要
これがないと既存の補助グループが上書きで消えることがある

反映の注意

グループ変更は

一度ログアウト→ログイン

または

newgrp testgroup

で反映されることが多い。

