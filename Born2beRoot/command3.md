ここからは 「パスワードの強さ（複雑さ）」ルール を入れていきます。
Born2beRoot っぽく、

長さ：10文字以上

大文字・小文字・数字を最低1文字ずつ

同じ文字を3回以上連続で使えない

ユーザー名を含めない

前のパスワードと十分違う

過去4個のパスワードは再利用禁止

くらいを目標にします。

使う仕組み：PAM（pam_pwquality, pam_pwhistory）

パスワードのルールは PAM（Pluggable Authentication Modules） という仕組みで決まっています。

pam_pwquality.so
→ 「長さ・大文字小文字・数字・繰り返し・ユーザー名NG」などをチェック

pam_pwhistory.so
→ 「過去N個のパスワードを再利用させない」

ステップ3-1：pam_pwquality の設定
① 設定ファイルを開く

sudo nano /etc/pam.d/common-password

意味

sudo：1回だけ管理者権限で実行

nano：テキストエディタ

/etc/pam.d/common-password：パスワード変更時のルールを決めるPAM設定

中ほどに、こんな行があるはずです（細かいオプションは違っていてもOK）：

password   requisite    pam_pwquality.so retry=3

この行を、次のように書き換えます：

password   requisite    pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root


オプションの意味

retry=3
→ パスワード入力に失敗しても、3回までやり直しOK

minlen=10
→ 最低10文字

ucredit=-1
→ 大文字（Upper）を最低1文字含める

lcredit=-1
→ 小文字（Lower）を最低1文字含める

dcredit=-1
→ 数字（Digit）を最低1文字含める

maxrepeat=3
→ 同じ文字を 3回以上連続では使えない（aaa までOK、aaaaはNG）

reject_username
→ ユーザー名を含むパスワードは禁止

difok=7
→ 前のパスワードと 最低7文字は違う こと

enforce_for_root
→ rootにも同じルールを適用（rootだけ弱いパスワードを許さない）

編集できたら、

Ctrl + O → 保存 → Enter

Ctrl + X → 終了




ステップ3-2：過去4つのパスワードを再利用禁止 (pam_pwhistory)

同じ /etc/pam.d/common-password の中に
pam_unix.so という行があるはずです：

password   [success=1 default=ignore]   pam_unix.so ...

この 行の上あたり に、次の1行を追加してください：

password   required    pam_pwhistory.so use_authtok remember=4



この行の意味

password …… パスワード変更時のルール

required …… このモジュールに失敗したら絶対NG

pam_pwhistory.so …… パスワード履歴を管理するモジュール

use_authtok …… すでに入力された新パスワード（passwd が受け取ったもの）を使う

remember=4 …… 過去4個分のパスワードは再利用禁止

追加したら、また Ctrl + O → Enter → Ctrl + X で保存＆終了。


ステップ3-3：ルールが効いているかテスト

今の設定がちゃんと働いているか、実験してみます。

① あえて弱いパスワードに変えようとしてみる

sudo passwd skuriyam


意味

passwd …… パスワードを変えるコマンド

sudo passwd skuriyam …… 管理者権限で skuriyam のパスワードを変更

プロンプトに従って、わざと弱いパスワード（例：aaaa1111 みたいなやつ）を入力してみてください。

おそらく「短すぎる」「大文字がない」「数字が足りない」などと怒られて、
変更が拒否されるはずです。

② 強いパスワードなら通る

条件を満たすパスワード（例）

10文字以上

大文字・小文字・数字・記号を含む
例：Abcdef12!? みたいな感じ

を入れると、今度は受け付けられるはずです。

そのあともう一度 sudo passwd skuriyam を実行して、
さっきとほとんど同じパスワードに戻そうとすると、

difok=7 や remember=4 のおかげで拒否されるはずです。

ここまでできれば、

有効期限：30日

2日間隔の変更制限

期限7日前から警告

長さ・大文字・小文字・数字・繰り返し・ユーザー名NG・履歴4個

という、かなりしっかりしたパスワードポリシーが入りました 💪