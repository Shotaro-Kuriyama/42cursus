
## ノートpcでpushして、42の校舎でgit pullし忘れたときの対処法

状況としてはこう
・ノートPCで push 済み（リモートが最新）
・42の校舎PCは pull し忘れて古いまま
・その古い状態のまま校舎PCでさらに作業してローカル変更がある

更に細分化すると

・ノートPCで git push → リモート（GitHub）の履歴が進んだ
・校舎PCは git pull してない → 校舎PCの履歴が古い
・その古い状態のまま校舎PCでファイルを編集 → 校舎PCに未コミット変更がある
ここで git pull をすると、Git は内部的に
1. リモートの新しいコミットを持ってくる（fetch）
2. それを自分の作業中ブランチに合体させる（merge / rebase）
をやります。
問題は 2の「合体」のときに、未コミットの変更が作業ツリー（作業フォルダ）に散らばってると、

合体で書き換えたいファイルを、今あなたがローカルで書き換え中
→ 上書き事故が起きうる
→ Git は事故防止のために止める（“Your local changes would be overwritten…”）

つまり Git 的には
「あなたの手元の作業（未コミット変更）を守りながら、リモート更新を取り込む準備ができてない」
って状態。



## stash とは何か（何をしてる？）

git stash は一言でいうと：

「いま作業中の変更を、一旦作業フォルダから取り除いて、別の安全な場所にしまう」

です。

もう少し正確に言うと、Git には3層あります：

1. HEAD（最後に確定したコミット）
2. index / staging area（git add した“次に確定予定”）
3. working tree（いまエディタで編集してる生の状態）

git stash はこの 2 と 3 の変更をまとめて「しまう」ことで、
作業フォルダを “最後に確定したコミット（HEAD）と同じ状態” に戻します。

だから git pull が安全にできる。

## 手順の意味（1行ずつ、理屈）
1) git status

いまの状態の健康診断です。
・“Changes not staged” → 作業フォルダに変更あり
・“Untracked files” → 新規ファイルがある（Gitがまだ管理してない）
・“ahead/behind” → リモートと比べて履歴が進んでる/遅れてる

ここで状況を把握してから次へ進む。

2) git stash push -u -m "campus work before pulling"

これが核心。
・stash push：退避する
・-u：Untracked（新規ファイル）も退避する
・これを付けないと、新規ファイルは作業フォルダに残り続けて、pull の邪魔になることがある
・-m：ラベルを付けて、後で見返したときに分かりやすくする

これをすると、作業フォルダが（ほぼ）クリーンになる＝pull できる状態になる。

3) git pull

ここで初めてリモート更新を取り込む。

pull の正体はだいたいこれです：
・git fetch（リモートの新しいコミットを持ってくる）
・その後 merge（または設定によって rebase）

stash で作業フォルダを空にしてるので、安全に合体できる。

4) git stash pop

最後に、退避してた作業を戻します。
・stash にしまってた変更を、現在の作業フォルダに “適用” する
・成功すれば stash は自動で消える（pop = apply + drop）

ここであなたの作業（校舎PCでやってた編集）が戻ってくる。

5) 衝突の可能性

衝突は、ざっくり言うと：

・リモート側の更新が 同じ行/近い行 を変えている
・stash の変更も 同じ行/近い行 を変えている

このとき Git は自動で「どっちが正しいか」決められないので、あなたに判断を求めます。

だから stash pop の時に conflict（対立） が出ることがある。
（逆に言うと、別ファイルや別の行なら、たいてい自動で合体できます。）

6) 衝突を解決して前に進む手順

#### 手順1：衝突箇所を見て直す
まず そのファイルを開く：

vim push_swap/order.c
# or code push_swap/order.c

中にこういうのがあるはずです：

<<<<<<< から ======= まで：pull 後の内容（リモート側）

======= から >>>>>>> まで：stash 側の内容（あなたの変更）

※ stash の衝突だと表示が Updated upstream / Stashed changes みたいになってることもあります。

あなたがやることは：
1. どっちを採用するか、または両方を統合するか決める
2. 最終的に正しいCコードにして
3. <<<<<<< ======= >>>>>>> の行を全部消す

#### 手順2：解決宣言（add）

直し終わったら：

git add push_swap/order.c（←例）

これで「order.c の conflict は解決したよ」とGitに伝えられます。

#### 手順3：コミット

全部ステージしたいものが揃ったら：

git commit -m "Apply stashed changes after pulling"

#### 手順4：stash を消す（重要：コミットできた“あと”）

stash が残ってるので、最終的に不要なら：

git stash list
git stash drop stash@{0}

（stash@{0} が今回のやつとは限らないので、必ず list で確認）

今回の場合は 
git stash push -u -m "campus work before pulling"

なので"campus work before pulling"のstashがあればok

### すぐ役に立つ確認コマンド（理解が深まる）

conflict の中身を差分で見る

git diff

README の「ステージ済み差分」を見る

git diff --staged

